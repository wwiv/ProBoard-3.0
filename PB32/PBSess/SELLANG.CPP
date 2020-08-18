#include "proboard.hpp"


const int MAX_LANGUAGES = 20;

int
mSelectLanguage(char *data)
{
   if(data != NULL)
      io << "\n\f\n";

   io << S_SELECT_LANGUAGE_TITLE << "\n\n";

   QFileName *languages = new QFileName[20];

   QDirScan scan(QFileName(SysPath,"*.PBL"));

   for(int i = 0; int(scan.operator int()) ; scan++ , i<MAX_LANGUAGES)
   {
      if(QString(scan.name()) == QString("_DEFAULT.PBL"))
         continue;

      QFile f(QFileName(SysPath,scan.name()));

      if(f.opened())
      {
         TpLanguageFile lf;

         if(f.read(&lf , sizeof(TpLanguageFile)) != sizeof(TpLanguageFile))
            continue;

         if(!user.CheckAccess(lf.level,lf.flags))
            continue;

         if(!lf.avail)
            continue;

         io << form("\7 %3d. \6%s\n",i+1,lf.name);

         languages[i] = scan.name();
         languages[i++].stripExt();
      }
   }

   io << '\n' << S_SELECT_LANGUAGE;

   int num=0;

   Input(num,2);

   if(num == 0)
   {
      delete [] languages;
      return 1;
   }

   if(num >= 1 && num <= i)
   {
      if(data)
         io << "\n\n" << S_READING_LANGUAGE_FILE;

      if(!ReadLanguage( languages[num-1] ))
         if(!ReadLanguage( cfg.defaultLanguage ))
            throw TXFatalError("Error reading default language file");

      strcpy(user.language,languages[num-1]);

//      readconfig();
   }
   else
   {
      if(num)
         io << "\n\n" << S_INVALID_ENTRY;
   }

   if(num && data)
      io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

   delete [] languages;

   return 0;
}



















