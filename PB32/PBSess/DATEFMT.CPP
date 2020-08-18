#include "proboard.hpp"
#include "stdlib.h"

int
mChangeDateFormat(char *data)
{
   if(data)
   {
      io << "\f\n";

      io << S_CHANGE_DATE_FORMAT_TITLE(DateFormats[user.dateFormat]);

      io << "\n\n";
   }

   io << S_SELECT_DATE_FORMAT_TITLE << "\n\n";

   io << "\3   1. \6" << DateFormats[0] << '\n';
   io << "\3   2. \6" << DateFormats[1] << '\n';
   io << "\3   3. \6" << DateFormats[2] << '\n';

   io << '\n' << S_SELECT_DATE_FORMAT_PROMPT;

   char tmp[2];

   Input(tmp,1);

   if(strlen(tmp)<1 || atoi(tmp) < 1 || atoi(tmp) > 3) return 1;

   user.dateFormat = atoi(tmp) - 1;

   if(data)
      LOG(1,"Date format changed to '%s'",DateFormats[user.dateFormat]);

   return 0;
}

