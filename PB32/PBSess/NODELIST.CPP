#include "proboard.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NODE_ZONE 1
#define NODE_REGION 2
#define NODE_HOST 3
#define NODE_HUB 4
#define NODE_PVT 5
#define NODE_DOWN 6
#define NODE_HOLD 7
#define NODE_NODE 7

#define LISTNODE_SINGLE   1
#define LISTNODE_MULTIPLE 2

struct NodeListIndex
   {
      BYTE type;
      long offset;
      union
      {
         short zone,
               net;
      };

      short cost;

      long fill;
   };

static int   ListNode(NodeListIndex& idx,char *fname,char mode);

static void
getnode(char *temp,NodeListEntry& n)
{
   char *options[]={"ZONE","REGION","HOST","HUB","PVT","DOWN","HOLD"};
   char slices[6][100];

   for(int i=0;i<6;i++)
   {
      int y=0;
      while (*temp != ',')
         if (*temp != '_')
         {
            slices[i][y++] = *temp++;
         }
         else
         {
            slices[i][y++] = ' ';
            temp++;
         }

      temp++;

      slices[i][y] = '\0';
    }

   for(i=0;i<7;i++) if(!strcmpl(slices[0],options[i])) break;

   n.type=i+1;

   strcpy(n.name,slices[2]);
   strcpy(n.city,slices[3]);

   switch(i+1)
   {
      case NODE_ZONE   : n.zone = atoi(slices[1]);

      case NODE_REGION : n.region = atoi(slices[1]);

      case NODE_HOST   : n.net  = atoi(slices[1]);
                         n.node = 0;
                         break;

      default          : n.node = atoi(slices[1]);
                         break;
   }
}



static int
ListNode(NodeListIndex& idx,char *fname,char mode)
{
   char *types[]={ "","ZONE","REGION","NET","HUB","PVT","DOWN","HOLD","" };

   QFile fp(QFileName(cfg.nodeListDir,fname),fmode_read | fmode_text);

   if(!fp.opened()) return -1;

   fp.seek(idx.offset);
   NodeListEntry n;
   n.net=idx.net;

   for(;;)
   {
      int num;
      char s[300];

      if(!fp.readLine(s,299)) break;

      if(s[0]==';') continue;

      getnode(s,n);

      if(mode==LISTNODE_MULTIPLE && n.net!=idx.net) break;

      switch(n.type)
      {
         case NODE_ZONE  : num = n.zone;   break;
         case NODE_REGION: num = n.region; break;
         case NODE_HOST  : num = n.net;    break;
         default         : num = n.node;   break;
      }

      EnableStop();
      OutputStopped = 0;

      io << form("\2 %-6s \3%5d \7%-28.28s \6%-28.28s \3%4d\n",types[n.type],num,n.name,n.city,idx.cost);

      DisableStop();

      if(OutputStopped || LineCounter()) return -1;

      if(mode == LISTNODE_SINGLE) break;
   }

   return 0;
}

int
ReadNodeListEntry(NodeListEntry& entry,char *s)
{
   char nodenr[14];
   char *tmp=nodenr;
   int point=0;

   strcpy(nodenr,s);

   if((s=strchr(tmp,'.'))!=NULL)
   {
      point = atoi(s+1);

      *s=0;
   }

   if((s=strchr(tmp,':'))!=NULL)
   {
      *s++ = 0;
      entry.zone = atoi(tmp);
      tmp  = s;
   }
   else
   {
      if(tmp[0]=='?')
         entry.zone = -1;
   }

   if((s=strchr(tmp,'/'))!=NULL)
   {
      *s++=0;

      if(tmp[0]!='?')
         entry.net = atoi(tmp);
      else
         entry.net = -1;

      tmp = s;
   }
   else
   {
      if(tmp[0]=='?')
         entry.net = -1;
   }

   if(tmp[0]!='?')
      entry.node = atoi(tmp);
   else
      entry.node = -1;

   NodeListIndex idx;

   char nl_name[13];

   QFile f(QFileName(SysPath,"NODE_IDX.PRO"),fmode_read,512);

   if(!f.opened()) return -1;

   BYTE xor[13]={ 234,123,76,245,87,12,43,56,23,12,98,55,34 };

   int curzone=0;

   if(entry.zone==-1)
   {
      io << S_ZONELIST_HEADER << '\n';
   }
   else
   {
      if(entry.net==-1)
      {
         io << S_NETLIST_HEADER(form("%d",entry.zone)) << '\n';
      }
      else
      {
         if(entry.node==-1)
         {
            char *s = form("%d:%d",entry.zone,entry.net);

            io << S_NODELIST_HEADER(s) << '\n';
         }
      }
   }

   LineCounter(2);

   for(;;)
   {
      if(f.read(&idx,sizeof(idx))!=sizeof(idx)) break;

      char *ptr=(char *)&idx;

      for(int i=0;i<13;i++)
         ptr[i] ^= xor[i];

      if(idx.type>10)
      {
         strcpy(nl_name,ptr);
         continue;
      }

      if(idx.type==NODE_ZONE)
      {
         curzone=idx.zone;

         if(entry.zone==-1)
         {
            if(ListNode(idx,nl_name,LISTNODE_SINGLE)<0)
               break;

            continue;
         }

         idx.net = curzone;

         if(curzone!=entry.zone)
            continue;
      }

      if(curzone==entry.zone && entry.net==-1)
      {
         if(ListNode(idx,nl_name,LISTNODE_SINGLE)<0)
            break;

         continue;
      }

      if(idx.net==entry.net && entry.zone==curzone)
      {
         if(entry.node==-1)
         {
            if(ListNode(idx,nl_name,LISTNODE_MULTIPLE)<0)
               return -1;

            break;
         }

         NodeListEntry tmp;

         tmp.zone = curzone;
         tmp.net  = idx.net;
         tmp.cost = idx.cost;

         QFile fp(QFileName(cfg.nodeListDir,nl_name),fmode_read | fmode_text);

         if(!fp.opened()) return -1;

         fp.seek(idx.offset);

         for(;;)
         {
            char s[300];

            if(fp.readLine(s,299)==NULL) break;

            if(s[0]==';') continue;

            getnode(s,tmp);

            if(tmp.type<NODE_HUB && tmp.net!=entry.net) break;

            if(tmp.node==entry.node)
            {
               entry = tmp;

               return point;
            }
         }

         fp.close();

         break;
      }
   }

   if(entry.zone!=-1 && entry.net!=-1 && entry.node!=-1)
      io << S_NODE_NUMBER_NOT_FOUND;

   return -1;
}

