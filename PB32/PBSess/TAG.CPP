#define Use_TagList
#define Use_LinkedList

#include <stdlib.h>
#include <string.h>
#include "proboard.hpp"

int
mEditTagList(char *)
{
   int i;

   if(TagList.count() == 0)
   {
      io << "\n\n\6No files tagged!  " << S_PRESS_ENTER_TO_CONTINUE;

      return 1;
   }

   for(;;)
   {
      io << "\n\f" << S_EDIT_TAGGED_TITLE << "\n\n";

      for(i = 1 , TagList.rewind() ; !TagList.eol() ; TagList++,i++)
      {
         TpFileArea fa;

         fa.read(TagList.get().area);

         io << form("    \3%2d\7 - \6%-12s\7 \2 (%s)\n",i,TagList.get().name,fa.name);
      }

      io << '\n' << S_EDIT_TAGGED_PROMPT;

      char rep = WaitLanguageHotkeys(K_EDIT_TAGGED_PROMPT);

      if(rep == 2) break;

      if(rep == 0)
      {
         while(TagList.count())
         {
            TagList.rewind();
            TagList.remove();
         }

         io <<        K_EDIT_TAGGED_PROMPT[0] << "\n\n" << S_ALL_FILE_TAGS_CLEARED
            << ' ' << S_PRESS_ENTER_TO_CONTINUE;
      }

      if(rep == 1)
      {
         char s[4];

         io <<        K_EDIT_TAGGED_PROMPT[0] << "\n\n" << S_ENTER_FILE_TO_UNTAG;

         Input(s,3,INPUT_DIGITS);

         int n = atoi(s);

         if(n > 0 && n <= TagList.count())
         {
            for(TagList.rewind() , i=1 ; i<n ; i++) TagList++;

            TagList.remove();
         }
      }
   }

   return 0;
}

void
RemoveTag(char *name , int area)
{
   for(TagList.rewind() ; !TagList.eol() ; TagList++)
   {
      if(!stricmp(TagList.get().name,name) && TagList.get().area == area)
      {
         TagList.remove();
         break;
      }
   }
}

bool
IsTagged(char *name , int area)
{
   for(TagList.rewind() ; !TagList.eol() ; TagList++)
   {
      if(!stricmp(TagList.get().name,name) && TagList.get().area == area)
         return TRUE;
   }

   return FALSE;
}
