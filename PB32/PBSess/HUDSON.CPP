#include "proboard.hpp"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef min
	#define min(a,b) (((a)<(b))?(a):(b))
#endif

struct HudsonMsgInfo
   {
      short low,high,total;
      short active[200];
   };

struct HudsonMsgIdx
   {
      short num;
      BYTE area;
   };

struct HudsonMsgToIdx
   {
      char to[36];
   };

struct HudsonMsgHdr
   {
      short msgNum,
            prevMsg,
            nextMsg,
            tRead;
      WORD  startRec;
      short numRecs,
            destNet,
            destNode,
            orgNet,
            orgNode;
      char  destZone,
            orgZone;
      short cost;
      BYTE  msgAttr,
            netAttr,
            area;
      char  postTime [6];
      char  postDate [9];
      char  to       [36];
      char  from     [36];
      char  subj     [67];
      QDate  recvDate;
      QTime  recvTime;

      void  operator=(TpMessage&);
   };

 const BYTE QMSGATTR_DELETED       = 0x01;
 const BYTE QMSGATTR_UNMOVED_NET   = 0x02;
 const BYTE QMSGATTR_NET           = 0x04;
 const BYTE QMSGATTR_PVT           = 0x08;
 const BYTE QMSGATTR_RECEIVED      = 0x10;
 const BYTE QMSGATTR_UNMOVED_ECHO  = 0x20;
 const BYTE QMSGATTR_LOCAL         = 0x40;

 const BYTE QNETATTR_KILL          = 0x01;
 const BYTE QNETATTR_SENT          = 0x02;
 const BYTE QNETATTR_ATTACH        = 0x04;
 const BYTE QNETATTR_CRASH         = 0x08;
 const BYTE QNETATTR_REQ           = 0x10;
 const BYTE QNETATTR_AUD           = 0x20;
 const BYTE QNETATTR_RET           = 0x40;

 const int  CACHE_NEXT             = 1;
 const int  CACHE_PREV             = 2;
 const int  CACHE_START            = 3;


TpHudsonMsgBase::TpHudsonMsgBase()
{
   lastMsgIdx = new HudsonMsgIdx;
   lastReadArray = NULL;
   highArray    = NULL;

   open();
}

TpHudsonMsgBase::~TpHudsonMsgBase()
{
   close();

   delete lastMsgIdx;

   if(highArray)    delete [] highArray;
   if(lastReadArray) delete [] lastReadArray;
}


#pragma warning( disable : 4244 4018 )

void
HudsonMsgHdr::operator=(TpMessage &msg)
{
   msg.to[35] = msg.from[35]
              = msg.subj[65] = '\0';      // Safety measure

   msgNum   = short(msg.id);
   prevMsg  = short(msg.prev);
   nextMsg  = short(msg.next);
   tRead    = 0;
   destNet  = (short)msg.destNet;
   destZone = (short)msg.destZone;
   destNode = (short)msg.destNode;
   orgNet   = (short)msg.origNet;
   orgZone  = (short)msg.origZone;
   orgNode  = (short)msg.origNode;
   cost     = (short)msg.cost;
   area     = (short)msg.areaNum();

   msgAttr = 0;
   netAttr = 0;

   if(     msg.attr & MSGATTR_ECHOMAIL
      && !(msg.attr & MSGATTR_SENT)
      &&   msg.attr & MSGATTR_LOCAL)    msgAttr |= QMSGATTR_UNMOVED_ECHO;

   if(     msg.attr & MSGATTR_NETMAIL
      && !(msg.attr & MSGATTR_SENT)
      &&   msg.attr & MSGATTR_LOCAL  )  msgAttr |= QMSGATTR_UNMOVED_NET;

   if(msg.attr & MSGATTR_DELETED     )  msgAttr |= QMSGATTR_DELETED     ;
   // if(msg.attr & MSGATTR_UNSENT_NET  )  msgAttr |= QMSGATTR_UNMOVED_NET ;
   if(msg.attr & MSGATTR_NETMAIL     )  msgAttr |= QMSGATTR_NET         ;
   if(msg.attr & MSGATTR_PRIVATE     )  msgAttr |= QMSGATTR_PVT         ;
   if(msg.attr & MSGATTR_RECEIVED    )  msgAttr |= QMSGATTR_RECEIVED    ;
   // if(msg.attr & MSGATTR_UNSENT_ECHO )  msgAttr |= QMSGATTR_UNMOVED_ECHO;
   if(msg.attr & MSGATTR_LOCAL       )  msgAttr |= QMSGATTR_LOCAL       ;

   if(msg.attr & MSGATTR_KILL        )  netAttr |= QNETATTR_KILL  ;
   if(msg.attr & MSGATTR_CRASH       )  netAttr |= QNETATTR_CRASH ;
   if(msg.attr & MSGATTR_SENT        )  netAttr |= QNETATTR_SENT  ;
   if(msg.attr & MSGATTR_FILE        )  netAttr |= QNETATTR_ATTACH;
   if(msg.attr & MSGATTR_FILEREQ     )  netAttr |= QNETATTR_REQ   ;
   if(msg.attr & MSGATTR_AUDITREQ    )  netAttr |= QNETATTR_AUD   ;
   if(msg.attr & MSGATTR_RECEIPTREQ  )  netAttr |= QNETATTR_RET   ;

   sprintf(postTime,"%02d:%02d",msg.postTime[0],msg.postTime[1]);
   c2pas(postTime);

   sprintf(postDate,"%02d-%02d-%02d",msg.postDate[1],msg.postDate[0],msg.postDate[2]);
   c2pas(postDate);

   strcpy(to,msg.to);
   c2pas(to);

   strcpy(from,msg.from);
   c2pas(from);

   strcpy(subj,msg.subj);
   c2pas(subj);

   recvDate = msg.recvDate;
   recvTime = msg.recvTime;
}

void
TpMessage::operator=(HudsonMsgHdr& mh)
{
   num      = mh.msgNum;
   id       = mh.msgNum;
   prev     = mh.prevMsg;
   next     = mh.nextMsg;
   destNet  = mh.destNet;
   destZone = mh.destZone;
   destNode = mh.destNode;
   origNet  = mh.orgNet;
   origZone = mh.orgZone;
   origNode = mh.orgNode;
   cost     = mh.cost;

   attr = 0;

   if(mh.msgAttr & QMSGATTR_DELETED     ) attr |= MSGATTR_DELETED     ;
   if(mh.msgAttr & QMSGATTR_UNMOVED_NET ) attr |= MSGATTR_NETMAIL     ;
   if(mh.msgAttr & QMSGATTR_NET         ) attr |= MSGATTR_NETMAIL     ;
   if(mh.msgAttr & QMSGATTR_PVT         ) attr |= MSGATTR_PRIVATE     ;
   if(mh.msgAttr & QMSGATTR_RECEIVED    ) attr |= MSGATTR_RECEIVED    ;
   if(mh.msgAttr & QMSGATTR_UNMOVED_ECHO) attr |= MSGATTR_ECHOMAIL    ;
   if(mh.msgAttr & QMSGATTR_LOCAL       ) attr |= MSGATTR_LOCAL       ;

   if(mh.netAttr & QNETATTR_KILL        ) attr |= MSGATTR_KILL        ;
   if(mh.netAttr & QNETATTR_SENT        ) attr |= MSGATTR_SENT        ;
   if(mh.netAttr & QNETATTR_ATTACH      ) attr |= MSGATTR_FILE        ;
   if(mh.netAttr & QNETATTR_CRASH       ) attr |= MSGATTR_CRASH       ;
   if(mh.netAttr & QNETATTR_REQ         ) attr |= MSGATTR_FILEREQ     ;
   if(mh.netAttr & QNETATTR_AUD         ) attr |= MSGATTR_AUDITREQ    ;
   if(mh.netAttr & QNETATTR_RET         ) attr |= MSGATTR_RECEIPTREQ  ;

   if(attr & MSGATTR_LOCAL)
   {
      if(!(mh.msgAttr & QMSGATTR_UNMOVED_ECHO) && !(mh.msgAttr & QMSGATTR_UNMOVED_NET))
         attr |= MSGATTR_SENT;
   }

   setArea(mh.area);

   mh.postTime[0] = (char)min( (BYTE)mh.postTime[0] ,5 );
   pas2c(mh.postTime);

   postTime[0] = (char)atoi(strtok(mh.postTime,":"));
   postTime[1] = (char)atoi(strtok(NULL,":"));
   postTime[2] = 0;

   mh.postDate[0] = (char)min( (BYTE)mh.postDate[0] , 8 );
   pas2c(mh.postDate);

   int _d[3];

   _d[1] = (char)atoi(strtok(mh.postDate,"-"));
   _d[0] = (char)atoi(strtok(NULL,"-"));
   _d[2] = (char)atoi(strtok(NULL,"-"));

	postDate.set(_d[0],_d[1],_d[2]);

   mh.to[0] = (char)min((BYTE)mh.to[0],35);
   pas2c(mh.to);
   strcpy(to,mh.to);

   mh.from[0] = (char)min((BYTE)mh.from[0],35);
   pas2c(mh.from);
   strcpy(from,mh.from);

   mh.subj[0] = (char)min((BYTE)mh.subj[0],65);
   pas2c(mh.subj);
   strcpy(subj,mh.subj);

   recvDate = mh.recvDate;
   recvTime = mh.recvTime;
}

bool
TpHudsonMsgBase::open()
{
   QFileName fn_msghdr  (cfg.msgPath,"MSGHDR.BBS"  ),
              fn_msgtxt  (cfg.msgPath,"MSGTXT.BBS"  ),
              fn_msgtoidx(cfg.msgPath,"MSGTOIDX.BBS"),
              fn_msgidx  (cfg.msgPath,"MSGIDX.BBS"  ),
              fn_msginfo (cfg.msgPath,"MSGINFO.BBS" );


   if(   !f_msghdr  .open(fn_msghdr  ,fmode_rw | fmode_copen)
      || !f_msgtxt  .open(fn_msgtxt  ,fmode_rw | fmode_copen)
      || !f_msgtoidx.open(fn_msgtoidx,fmode_rw | fmode_copen , 2048)
      || !f_msgidx  .open(fn_msgidx  ,fmode_rw | fmode_copen , 1024)
      || !f_msginfo .open(fn_msginfo ,fmode_rw | fmode_copen))
   {
      if(f_msghdr  .error()) throw TXFatalError(fn_msghdr  );
      if(f_msgtxt  .error()) throw TXFatalError(fn_msgtxt  );
      if(f_msgtoidx.error()) throw TXFatalError(fn_msgtoidx);
      if(f_msgidx  .error()) throw TXFatalError(fn_msgidx  );
      if(f_msginfo .error()) throw TXFatalError(fn_msginfo );

      throw TXFatalError("Error creating Hudson message base");
   }

   flushCache();

   return TRUE;
}

void
TpHudsonMsgBase::close()
{
   flushCache();

   f_msghdr  .close();
   f_msgtxt  .close();
   f_msgtoidx.close();
   f_msgidx  .close();
   f_msginfo .close();
}

long
TpHudsonMsgBase::highMsg(TpMsgArea& ma)
{
   readHighArray();

   return long(highArray[ma.areaNum-1]);
}

long
TpHudsonMsgBase::lowMsg(TpMsgArea&)
{
   HudsonMsgInfo mi;

   readInfo(mi);

   return long(mi.low);
}

long
TpHudsonMsgBase::numMsgs(TpMsgArea& ma)
{
   HudsonMsgInfo mi;

   readInfo(mi);

   return long(mi.active[ma.areaNum - 1]);
}

long
TpHudsonMsgBase::totalMsgs()
{
   HudsonMsgInfo mi;

   readInfo(mi);

   return long(mi.total);
}

void
TpHudsonMsgBase::readInfo(HudsonMsgInfo &mi)
{
   CLEAR_OBJECT(mi);

   f_msginfo.seek(0);
   f_msginfo.flush();
   f_msginfo.read(&mi,sizeof(mi));
}

void
TpHudsonMsgBase::writeInfo(HudsonMsgInfo &mi)
{
   f_msginfo.seek(0);
   f_msginfo.write(&mi,sizeof(mi));
   f_msginfo.flush();
}

long
TpHudsonMsgBase::readMsg(TpMessage &msg,long num)
{
   HudsonMsgIdx mi;
   int order = 1;

   f_msgidx.seek(0);

   if(num < 0)
   {
      order = -1;
      num = -num;
   }

   long index = findIdx(mi , int(num) , msg.areaNum() , order);

   if(index < 0) return -1;

   HudsonMsgHdr hdr;

   f_msghdr.seek(index * sizeof(hdr));

   if(f_msghdr.read(&hdr,sizeof(hdr)) != sizeof(hdr)) return -1;

   msg = hdr;     // Conversion applied!

   return msg.id;
}

void
TpHudsonMsgBase::flushCache()
{
   lastReadRecord   = -1;
   lastIndex        = -1;
   lastMsgIdx->num  = -1;
   lastMsgIdx->area = 0;

   if(highArray     != NULL) delete [] highArray;
   if(lastReadArray != NULL) delete [] lastReadArray;

   highArray     = NULL;
   lastReadArray = NULL;
}

void
TpHudsonMsgBase::readHighArray()
{
   if(highArray) return;

   highArray = new int[200];

   HudsonMsgIdx mi;

   memset(highArray,0,sizeof(*highArray)*200);

   f_msgidx.seek(0);

   for(;;)
   {
      if(f_msgidx.read(&mi,sizeof(mi)) != sizeof(mi)) break;

      if(mi.num > 0 && mi.area > 0 && mi.area < 200 && mi.num > highArray[mi.area-1])
         highArray[mi.area-1] = mi.num;
   }
}

long
TpHudsonMsgBase::findIdx(HudsonMsgIdx &mi,int num,int area,int order)
{
   long idx = -1;

   if(order < 0) idx = f_msgidx.len() / 3;

   if(lastMsgIdx->num == num && lastMsgIdx->area == area)
   {
      mi = *lastMsgIdx;

      return lastIndex;
   }

   if(order == 0) flushCache();

   if(lastMsgIdx->num > 0)
   {
      if(num > lastMsgIdx->num && order > 0)
         idx = lastIndex;

      if(num < lastMsgIdx->num && order < 0)
         idx = lastIndex;
   }

   if(order < 0)
   {
      f_msgidx.disableBuffer();

      for(idx-- ; idx >= 0 ; idx--)
      {
         f_msgidx.seek(idx * sizeof(HudsonMsgIdx));
         f_msgidx.read(lastMsgIdx,sizeof(*lastMsgIdx));

         if(lastMsgIdx->num < 1) continue;

         if(lastMsgIdx->num <= num && lastMsgIdx->area == area)
         {
            lastIndex = idx;

            mi = *lastMsgIdx;

            f_msgidx.enableBuffer();
            return idx;
         }
      }

      f_msgidx.enableBuffer();
   }
   else // >=0
   {
      for(idx++ ; ; idx++)
      {
         f_msgidx.seek(idx * sizeof(HudsonMsgIdx));
         if(f_msgidx.read(lastMsgIdx,sizeof(*lastMsgIdx)) != sizeof(*lastMsgIdx)) break;

         if(lastMsgIdx->area == area)
         {
            if(lastMsgIdx->num == num
               || (lastMsgIdx->num >= num && order>0))
            {
               lastIndex = idx;

               mi = *lastMsgIdx;

               return idx;
            }
         }
      }
   }

   flushCache();

   return -1;
}

unsigned
TpHudsonMsgBase::readMsgText(TpMessage& msg , char *ptr , long offset , unsigned size)
{
   HudsonMsgIdx mi;
   HudsonMsgHdr hdr;

   long index = findIdx(mi,int(msg.id),msg.areaNum(),0);

   if(index < 0) return 0;

   f_msghdr.seek(index * sizeof(HudsonMsgHdr));

   if(f_msghdr.read(&hdr,sizeof(hdr)) != sizeof(hdr)) return 0;

   long rec = hdr.startRec + offset/255;

   BYTE buf[256];

   unsigned bytescopied = 0;

   int  buf_index = int(offset % 255);

   for( ; rec < (hdr.startRec + hdr.numRecs) && bytescopied<size; rec++)
   {
      f_msgtxt.seek(rec * 256);
      f_msgtxt.read(buf,256);

      int l = int(buf[0]);

      pas2c((char *)buf);

      l -= buf_index;

      if(l < 1) break;

      if(l > size-bytescopied) l = size-bytescopied;

      memcpy(ptr + bytescopied, &buf[buf_index] , l);

      bytescopied += l;

      buf_index = 0;
   }

   return bytescopied;
}

unsigned
TpHudsonMsgBase::scanMail(TpMessageIndex *mi,unsigned maxmsgs)
{
   f_msgtoidx.seek(0);
   int i;
   int num_found;
   long index;
   TpMsgArea ma;

   for(index = 0 , i=0 ; i < maxmsgs ;index++)
   {
      HudsonMsgToIdx h_mti;
      HudsonMsgIdx   h_mi;

      if(f_msgtoidx.read(&h_mti,sizeof(h_mti)) != sizeof(h_mti)) break;

      pas2c(h_mti.to);

      if(stricmp(user.name,h_mti.to) && stricmp(user.alias,h_mti.to)) continue;

      f_msgidx.seek(index * 3);
      if(f_msgidx.read(&h_mi,sizeof(h_mi)) == sizeof(h_mi))
      {
         mi[i].num  = h_mi.num;
         mi[i].area = h_mi.area;

         if(!ma.read(mi[i].area)) continue;

         if(!stricmp(user.alias,h_mti.to) && !ma.flags && strcmp(user.name,user.alias)) continue;

         if(   mi[i].num > 1
            && user.mailCheckBoards.connected(mi[i].area)
            && ma.msgBaseType == MSGBASE_HUDSON
            && (user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot) || ma.sysopAccess())
            ) i++;
      }
   }

   num_found = i;

   bool *to_all_areas = new bool[200];

   for(i=0;i<200;i++) to_all_areas[i] = false;

   for(i=1;i<=200 && i<=TpMsgArea::highAreaNum();i++)
   {
      if(   !ma.read(i)
         || !user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot)
         || ma.msgBaseType != MSGBASE_HUDSON
         || ma.msgType != MSG_TOALL) continue;

      to_all_areas[i-1] = true;
   }

   f_msgidx.seek(0);

   while(num_found < 200)
   {
      HudsonMsgIdx tmp_mi;

      if(f_msgidx.read(&tmp_mi,sizeof(tmp_mi)) != sizeof(tmp_mi)) break;

      if(tmp_mi.num < 1) continue;

      if(tmp_mi.area < 1 || tmp_mi.area > 200 || !to_all_areas[tmp_mi.area-1]) continue;

      if(!ma.read(tmp_mi.area)) continue;

      if(tmp_mi.num > ma.lastRead())
      {
         mi[num_found].num  = tmp_mi.num;
         mi[num_found].area = tmp_mi.area;

         num_found++;
      }
   }

   delete [] to_all_areas;

   return num_found;
}

long
TpHudsonMsgBase::appendMsg(TpMessage& msg)
{
   QFile ft;
   HudsonMsgIdx midx;
   HudsonMsgToIdx mtidx;
   HudsonMsgInfo minfo;
   long startrec,numrecs;
   long index;

   if(msg.areaNum() < 1 || msg.areaNum() > 200) return -1;

   readInfo(minfo);

   if(!lock()) return -1;

   msg.id  = ++minfo.high;
   msg.num = msg.id;

   minfo.total++;
   minfo.active[msg.areaNum() - 1]++;

   midx.num  = short(msg.id);
   midx.area = (short)msg.areaNum();

   index = WORD(f_msghdr.len() / sizeof(HudsonMsgHdr));

   if(!ft.open("MSGTMP"))
   {
      unlock();
      return -1;
   }

   startrec = f_msgtxt.len() / 256L;

   f_msgtxt.seek(256L * startrec);

   for(numrecs=0 ;; numrecs++)
   {
      char x[256];
      int l = 0;
      if(!numrecs)
      {
         strcpy(x,"\1PID: ProBoard\r\n");
         l = strlen(x);
      }

      l += ft.read(&x[l],255-l);
      x[l] = 0;

      if(l<1) break;

      c2pas(x);

      f_msgtxt.write(x,256);
   }

   ft.close();

   msg.postDate.today();
   msg.postTime.now();

   HudsonMsgHdr hdr;

   hdr = msg;  // Conversion applied

   hdr.startRec = WORD(startrec);
   hdr.numRecs  = short(numrecs);

   f_msghdr.seek (index * sizeof(HudsonMsgHdr));
   f_msghdr.write(&hdr,sizeof(hdr));

   strcpy(mtidx.to,msg.to);
   c2pas(mtidx.to);

   f_msgtoidx.seek (index * sizeof(HudsonMsgToIdx));
   f_msgtoidx.write(&mtidx,sizeof(mtidx));

   f_msgidx.seek (index * sizeof(HudsonMsgIdx));
   f_msgidx.write(&midx,sizeof(midx));

   writeInfo(minfo);

   unlock();

   flushCache();

   return msg.id;
}

bool
TpHudsonMsgBase::updateMsg(TpMessage& msg)
{
   HudsonMsgIdx midx;
   HudsonMsgToIdx mtidx;
   long index;

   if(msg.areaNum() < 1 || msg.areaNum() > 200) return FALSE;

   index = findIdx(midx,int(msg.id),msg.areaNum(),0);

   if(index < 0) return FALSE;

   HudsonMsgHdr hdr;

   f_msghdr.seek(index * sizeof(hdr));

   if(f_msghdr.read(&hdr,sizeof(hdr)) != sizeof(hdr)) return FALSE;

   if(!lock()) return FALSE;

   hdr = msg;

   f_msghdr.seek (index * sizeof(hdr));
   f_msghdr.write(&hdr,sizeof(hdr));

   strcpy(mtidx.to,msg.to);

   if(msg.attr & MSGATTR_RECEIVED) strcpy(mtidx.to,"* Received *");
   if(msg.attr & MSGATTR_DELETED)  strcpy(mtidx.to,"* Deleted *");

   c2pas(mtidx.to);

   f_msgtoidx.seek (index * sizeof(HudsonMsgToIdx));
   f_msgtoidx.write(&mtidx,sizeof(mtidx));

   unlock();

   flushCache();

   return true;
}


bool
TpHudsonMsgBase::deleteMsg(TpMessage& msg)
{
   HudsonMsgIdx midx;
   HudsonMsgToIdx mtidx;
   HudsonMsgInfo minfo;
   long index;

   if(msg.areaNum() < 1 || msg.areaNum() > 200) return FALSE;

   index = findIdx(midx,int(msg.id),msg.areaNum(),0);

   if(index < 0) return FALSE;

   HudsonMsgHdr hdr;

   f_msghdr.seek(index * sizeof(hdr));

   if(f_msghdr.read(&hdr,sizeof(hdr)) != sizeof(hdr)) return FALSE;

   if(!lock()) return FALSE;

   msg.attr |= MSGATTR_DELETED;

   hdr = msg;

   f_msghdr.seek (index * sizeof(hdr));
   f_msghdr.write(&hdr,sizeof(hdr));

   strcpy(mtidx.to,"* Deleted *");

   c2pas(mtidx.to);

   f_msgtoidx.seek (index * sizeof(HudsonMsgToIdx));
   f_msgtoidx.write(&mtidx,sizeof(mtidx));

   midx.num = -1;

   f_msgidx.seek (index * 3);
   f_msgidx.write(&midx,3);

   readInfo(minfo);

   minfo.total--;
   minfo.active[msg.areaNum() - 1]--;

   writeInfo(minfo);

   unlock();

   flushCache();

   return true;
}


bool
TpHudsonMsgBase::lock()
{
   f_msghdr.flush();
   f_msgtxt.flush();
   f_msginfo.flush();
   f_msgtoidx.flush();
   f_msgidx.flush();

   if(!f_msginfo.lock(407,1))
   {
      int err = f_msginfo.error();

      throw TXFatalError(form("FILE LOCK ERROR (%d)" , err));
   }

   return true;
}

bool
TpHudsonMsgBase::unlock()
{
   f_msghdr.flush();
   f_msgtxt.flush();
   f_msginfo.flush();
   f_msgtoidx.flush();
   f_msgidx.flush();

   if(!f_msginfo.unlock(407,1))
   {
      int err = f_msginfo.error();

      throw TXFatalError(form("FILE UNLOCK ERROR (%d)" , err ));
   }

   return true;
}

long
TpHudsonMsgBase::lastRead(TpMsgArea& ma)
{
   readLastRead(user.record);

   if(ma.areaNum < 1 || ma.areaNum > 200) return 0;

   return long(lastReadArray[ma.areaNum-1]);
}

void
TpHudsonMsgBase::setLastRead(TpMsgArea& ma,long num)
{
   QFile f;

   readLastRead(user.record);

   if(!f.open(QFileName(cfg.msgPath,"LASTREAD.BBS"),fmode_rw | fmode_copen)) return;

   if(f.len() < (user.record+1)*400)
   {
      WORD n = 0;
      long r = f.len() / 400 * 400;

      f.seek(r);

      for(;r<(user.record+1)*400;r+=2)
         f.write(&n,2);
   }

   if(ma.areaNum < 1 || ma.areaNum > 200) return;

   long pos = user.record * 400 + (ma.areaNum-1) * 2;

   f.seek(pos);

   f.write(&num,2);

   lastReadArray[ma.areaNum-1] = int(num);
}

void
TpHudsonMsgBase::readLastRead(long recno)
{
   static time_t ticks = time(NULL);

   if(time(NULL) - ticks > 10)
   {
      ticks = time(NULL);

      flushCache();
   }

   if(lastReadArray && recno == lastReadRecord) return;

   if(lastReadArray == NULL)
   {
      lastReadArray  = new int[200];

      memset(lastReadArray,0,400);
   }

   lastReadRecord = recno;

   QFile f;

   if(!f.open(QFileName(cfg.msgPath,"LASTREAD.BBS"))) return;

   f.seek(recno * 400);

   if(f.read(lastReadArray,400) != 400)
   {
      lastReadRecord = -1;

      memset(lastReadArray,0,400);
   }
}
