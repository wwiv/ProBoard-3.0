#include "proboard.hpp"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static char *valid="ABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890#$";

static void getfname(char *s,char *fn);
static bool displayline(char *line,TpFileArea& fa);

const int MAX_TAGS = 52;

TpFilesIdx local_tags[MAX_TAGS];
int      num_local_tags;

static   int remember_area = 0;
static  long remember_pos  = -1;

static int last_tag = 0;

char tag_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890*#$!@%+=&?|></\\~^";

static bool eol = FALSE;

static int
filelist_more()
{
   int rep;
   int i;

   BYTE oldcolor=CurrentAttribute();

   for(;;)
   {
      if(eol)
         io << S_END_OF_LIST_TAG;
      else
         io << S_MORE_TAG;

      if(eol)
         rep = WaitLanguageHotkeys(K_END_OF_LIST_TAG);
      else
         rep = WaitLanguageHotkeys(K_MORE_TAG);

      io << "\r                                                                   \r";

      if(rep == '\r') rep = 0;

      if(rep == (eol ? 1 : 3))
      {
         QString tagged;

         io << '\r' << S_ENTER_FILE_TAGS;

         for(;;)
         {
            char c = toupper(WaitKey());

            if(c == '\r') break;

            if(c == '\b' && tagged.len())
            {
               io << "\b\b  \b\b";

               tagged.delLast();
            }

            if(tagged.len() >= 26) continue;

            for(i=0; tag_chars[i] ; i++)
            {
               if(c == tag_chars[i]) break;
            }

            if(tag_chars[i] && i < num_local_tags)
            {
               io << c << "\7,\3";
               tagged << c;
            }
         }

         for(i=0;i<tagged.len();i++)
         {
           int j;
            for(j=0; tag_chars[j] ; j++)
            {
               if(tagged[i] == tag_chars[j]) break;
            }

            if(!tag_chars[j]) continue;

            if(j+1 > num_local_tags) continue;

            if(!IsTagged(local_tags[j].name, local_tags[j].area))
               TagList.add(local_tags[j]);
         }

         io << '\r' << S_X_FILES_TAGGED(form("%d",TagList.count()));

         WaitKey('\r');

         io << "\7\r" << QString(' ',LanguageStringLength(S_X_FILES_TAGGED(form("%d",TagList.count())))) << '\r';
      }

      if(rep == (eol ? 2:4))
      {
         mEditTagList(NULL);

         io << "\f\7";

         rep = 0;
      }

      if(eol)
      {
         if(rep == 0) break;
      }
      else
      {
         if(rep >= 0 && rep <= 2) break;
      }

   }

   FullColor(oldcolor);

   return rep;
}

void
clear_tags()
{
   last_tag       = 0;
   num_local_tags = 0;
}

static bool
is_whitespace(char c)
{
   return (c==' ' || c=='\t');
}

static char
first_nonblank( char *line )
{
   char f =*line;

   if(is_whitespace(*line))
   {
     int i;
      for(i=0 ; line[i] != '\0' && is_whitespace(line[i]) ; i++) {}

      f = line[i];
   }

   return f;
}

static int
display_areaname(int areanum, char *areaname , int prevsize)
{
   io << form("\7%3d - %*s\r\xFF",areanum,-prevsize,areaname);

   return strlen(areaname);
}

int
mListFiles(char *data)
{
   TpFileArea fa;
   int areanum;

   io << "\f\n" << S_FILELIST_PRESS_S_TO_STOP << "\n\n\xFF";

   LineCounter(2);
   EnableStop();

   if(toupper(data[0])=='X')
      areanum = user.fileArea;
   else
      areanum = atoi(data);

   if(!fa.read(areanum)) return 1;

   LOG(2,"Files listed (%s)",fa.name);

   QFile tf;
   if(!tf.open(fa.listPath,fmode_read | fmode_text))
   {
      LOG("Can't open file list %s",fa.listPath);
      return 1;
   }

   eol = FALSE;
   pMoreFunction = filelist_more;
   clear_tags();

   char *line = new char[500];

   bool interrupted = FALSE;

   remember_area = fa.areaNum;
   remember_pos  = 0;

   while(tf.readLine(line,499))
   {
      strip_linefeed(line);

      if(!displayline(line,fa))
      {
         interrupted = TRUE;
         break;
      }

      remember_pos = tf.pos();
   }

   pMoreFunction = NULLFUNC;

   delete [] line;

   if(!interrupted)
   {
      if(num_local_tags)
      {
         eol = TRUE;
         filelist_more();
      }

      //io << '\n' << S_END_OF_FILE_LISTING << ' ' << S_PRESS_ENTER_TO_CONTINUE;
   }

   return 0;
}

int
mKeywordSearch(char *data)
{
   TpFileArea fa;
   char item[41];

   io << "\f\n" << S_KEYWORD_SEARCH_TITLE_AND_PROMPT;

   Input(item,40,INPUT_UPALL);

   if(!*item) return 1;

   QString buffer[10];

   int pointer = 0,
       found   = 0,
       group   = 0;

   QString param[40];
   QBitArray arealist(10000,1);

   int npara=ParseData(data,param);

   LOG(2,"KeyWORD search (%s)",item);

   io << "\n\f\n" << S_SEARCHING_FOR_KEYWORD(item) << "\n\n";

   CreateAreaList(param,npara,arealist);

   for(int i = 0;i<npara;i++)
   {
      if(param[i] == QString("/FG"))
         group           = user.msgGroup;

      if(!strnicmp(param[i],"/FG=",4))
         group           = atoi(&param[i][4]);
   }

   LineCounter(2);
   EnableStop();
   QFile tf;

   char *line = new char[500];

   eol = FALSE;
   pMoreFunction = filelist_more;
   clear_tags();

   bool interrupted = FALSE;
   int prev_arealen = 1;

   for(int z=1 ; z<=TpFileArea::highAreaNum() && !interrupted; z++)
   {
      bool linefeed = TRUE;

      if(!arealist[z] || !fa.read(z) || !user.CheckAccess(fa.level,fa.flags,fa.flagsNot)) continue;

      if(group && !fa.allGroups)
      {
        int g;
         for(g=0;g<4;g++)
         {
            if(fa.groups[g] == group)
               break;
         }

         if(g==4)
            continue;
      }

      prev_arealen = display_areaname(z,fa.name,prev_arealen);

      if(OutputStopped) break;

      tf.close();
      if(!tf.open(fa.listPath,fmode_read | fmode_text))
      {
         LOG("Can't open file list %s",fa.listPath);
         continue;
      }

      while(tf.readLine(line,499) && !interrupted)
      {
         strip_linefeed(line);
         if(strchr(valid,toupper(*line)) && *line)
         {
            found=0;
            pointer=0;
            buffer[0]=line;
            if(QString(line).find(item) >= 0)
            {
               found = TRUE;

               if(linefeed)
               {
                  io << '\n';

                  if(LineCounter())
                  {
                     interrupted = TRUE;
                     break;
                  }
               }

               linefeed = FALSE;

               if(!displayline(line,fa))
               {
                  interrupted = TRUE;
                  break;
               }
            }
         }
         else
         {
            char fnb = first_nonblank(line);

            if(fnb && strchr("+!;|",fnb))
            {
               if(pointer<9)
                  pointer++;
               else
                  pointer=1;

               buffer[pointer]=line;

               if(found)
               {
                  if(linefeed)
                  {
                     io << '\n';

                     if(LineCounter())
                     {
                        interrupted = TRUE;
                        break;
                     }
                  }

                  linefeed = FALSE;

                  if(!displayline(line,fa))
                  {
                     interrupted = TRUE;
                     break;
                  }
               }
               else
               {
                  if(QString(line).find(item) >= 0)
                  {
                     for(int i=0;i<=pointer && !interrupted;i++)
                     {
                        if(linefeed)
                        {
                           io << '\n';

                           if(LineCounter())
                           {
                              interrupted = TRUE;
                              break;
                           }
                        }

                        linefeed = FALSE;

                        if(!displayline(buffer[i],fa))
                        {
                           interrupted = TRUE;
                           break;
                        }
                     }

                     found = TRUE;
                  }
               }
            }
         }
      }
   }

   delete [] line;

   pMoreFunction = NULLFUNC;

   if(num_local_tags && !interrupted)
   {
      eol = TRUE;
      filelist_more();
   }

   return 0;
}

#define MAX_NEWFILES 200

int
mNewFileSearch(char *data)
{
   int group = 0;
   TpFileArea fa;
   QDate cmpdate;
   QString param[40];
   QBitArray arealist(10000,1);

   struct newfile
   {
      char name[13];
   } *newf;

   int npara=ParseData(data,param);

   for(int i = 0;i<npara;i++)
   {
      if(param[i] == QString("/FG"))
         group           = user.msgGroup;

      if(!strnicmp(param[i],"/FG=",4))
         group           = atoi(&param[i][4]);
   }

   LOG(2,"New files listed");

   io << "\f\n" << S_NEW_FILES_SEARCH_TITLE_AND_PROMPT(DateFormats[user.dateFormat]);

   InputDate(cmpdate);

   if(!cmpdate.ok())
   {
      cmpdate = user.lastNewFilesCheck;
      NewFilesChecked = TRUE;
   }

   io << "\n\f\n"
      << S_SEARCHING_FOR_NEW_FILES(form("%d %s %4d",(char *)cmpdate.format(DateFormats[user.dateFormat])))
      << "\n\n\xFF";

   CreateAreaList(param,npara,arealist);

   newf = new newfile[MAX_NEWFILES];

   LineCounter(2);
   EnableStop();

   eol = FALSE;
   pMoreFunction = filelist_more;
   clear_tags();

   char *line = new char[500];

   bool interrupted = FALSE;
   int prev_arealen = 1;

   for(int z=1 ; z<=TpFileArea::highAreaNum() && !interrupted; z++)
   {
      bool linefeed = TRUE;

      if(!arealist[z] || !fa.read(z) || !user.CheckAccess(fa.level,fa.flags,fa.flagsNot)) continue;

      if(group && !fa.allGroups)
      {
        int g;
         for(g=0;g<4;g++)
         {
            if(fa.groups[g] == group)
               break;
         }

         if(g==4)
            continue;
      }

      prev_arealen = display_areaname(z,fa.name,prev_arealen);

      if(OutputStopped)
      {
         interrupted = TRUE;
         break;
      }

      QDirScan find(QFileName(fa.filePath,"*.*"));
      int num_new;
      for(num_new=0;int(find) && num_new<MAX_NEWFILES;find++)
      {
         if(find.date() >= cmpdate)
            strcpy(newf[num_new++].name,find.name());
      }

      if(!num_new) continue;

      QFile tf;

      if(!tf.open(fa.listPath,fmode_read | fmode_text))
      {
         LOG("Can't open file list %s",fa.listPath);

         continue;
      }

      for(bool found = FALSE ; tf.readLine(line,499) ; )
      {
         strip_linefeed(line);

         if(strchr(valid,toupper(*line)) && *line)
         {
            char file[13];

            found = FALSE;

            getfname(line,file);
            strupr(file);

            int i;
            for(i=0;i<num_new;i++)
               if(!strcmp(newf[i].name,file))
                  break;

            if(i<num_new)
            {
               found = TRUE;

               if(linefeed)
               {
                  io << '\n';

                  if(LineCounter())
                  {
                     interrupted = TRUE;
                     break;
                  }
               }
               linefeed = FALSE;
               if(!displayline(line,fa))
               {
                  interrupted = TRUE;
                  break;
               }
            }
         }
         else
         {
            char fnb = first_nonblank(line);

            if(fnb && found && strchr("+|!;",fnb))
            {
               if(linefeed)
               {
                  io << '\n';

                  if(LineCounter())
                  {
                     interrupted = TRUE;
                     break;
                  }
               }
               linefeed = FALSE;

               if(!displayline(line,fa))
               {
                  interrupted = TRUE;
                  break;
               }
            }
         }
      }
   }

   delete [] line;
   delete [] newf;

   pMoreFunction = NULLFUNC;

   if(!interrupted)
   {
      if(num_local_tags)
      {
         eol = TRUE;
         filelist_more();
      }

      //io << '\n' << S_END_OF_FILE_SEARCH << ' ' << S_PRESS_ENTER_TO_CONTINUE;
   }

   return 0;
}


int
mFileNameSearch(char *data)
{
   int group = 0;
   char search[13];

   io << "\f\n" << S_FILENAME_SEARCH_TITLE_AND_PROMPT;

   Input(search,12,INPUT_UPALL);

   if(!*search) return 1;

   TpFileArea fa;
   QString param[40];
   QBitArray arealist(10000,1);

   int npara = ParseData(data,param);

   for(int i = 0;i<npara;i++)
   {
      if(param[i] == QString("/FG"))
         group           = user.msgGroup;

      if(!strnicmp(param[i],"/FG=",4))
         group           = atoi(&param[i][4]);
   }

   LOG(2,"Filename search (%s)",search);

   io << "\n\f\n" << S_SEARCHING_FOR_FILENAME(search) << "\n\n\xFF";

   CreateAreaList(param,npara,arealist);

   LineCounter(2);
   EnableStop();

   char *line = new char[500];

   bool interrupted = FALSE;
   int prev_arealen = 1;

   eol = FALSE;
   pMoreFunction = filelist_more;
   clear_tags();

   for(int z=1 ; z<=TpFileArea::highAreaNum() && !interrupted ; z++)
   {
      bool linefeed = TRUE;

      if(!arealist[z] || !fa.read(z) || !user.CheckAccess(fa.level,fa.flags,fa.flagsNot)) continue;

      if(group && !fa.allGroups)
      {
        int g;
         for(g=0;g<4;g++)
         {
            if(fa.groups[g] == group)
               break;
         }

         if(g==4)
            continue;
      }

      prev_arealen = display_areaname(z,fa.name,prev_arealen);
      //io << form("\7%3d - %s\n\xFF",z,fa.name);

      QFile tf;

      if(!tf.open(fa.listPath,fmode_read | fmode_text))
      {
         LOG("Can't open file list %s",fa.listPath);
         continue;
      }

      if(OutputStopped)
      {
         interrupted = TRUE;
         break;
      }

      for(bool found = FALSE ; tf.readLine(line,499) ; )
      {
         strip_linefeed(line);
         if(strchr(valid,toupper(*line))  && *line)
         {
            found=0;
            char file[13];
            getfname(line,file);

            if(!MatchFile(search,file)) continue;

            found = TRUE;

            if(linefeed)
            {
               io << '\n';

               if(LineCounter())
               {
                  interrupted = TRUE;
                  break;
               }
            }
            linefeed = FALSE;

            if(!displayline(line,fa))
            {
               interrupted = TRUE;
               break;
            }
         }
         else
         {
            char fnb = first_nonblank(line);

            if(fnb && found && strchr("+|!;",fnb))
            {
               if(linefeed)
               {
                  io << '\n';

                  if(LineCounter())
                  {
                     interrupted = TRUE;
                     break;
                  }
               }

               linefeed = FALSE;

               if(!displayline(line,fa))
               {
                  interrupted = TRUE;
                  break;
               }
            }
         }
      }
   }

   delete [] line;

   pMoreFunction = NULLFUNC;

   if(!interrupted)
   {
      if(num_local_tags)
      {
         eol = TRUE;
         filelist_more();
      }

      //io << '\n' << S_END_OF_FILE_SEARCH << ' ' << S_PRESS_ENTER_TO_CONTINUE;
   }

   return 0;
}

static void
getfname(char *s,char *fn)
{
   for(int i=0 ; i<12 && *s!=' ' && *s ; i++) *fn++ = *s++;
   *fn = '\0';
}

void
split_line( char *s , QString& fname , QDate& date , long& size , int& counter , QString& desc , TpFileArea& fa)
{
   char *prev_s;
   QString token;

   size = -1;
   date.set(0,0,0);

   fname = "";
   while(!is_whitespace(*s) && *s) fname << (*s++);

   prev_s = s;

   while(*s)
   {
      token.clear();

      prev_s = s;

      while(is_whitespace(*s) && *s) s++;                   // Skip whitespace
      while(!is_whitespace(*s) && *s) token << (*s++);

      bool date_del_found = FALSE;
      bool non_num_found  = FALSE;

      for(int j=0;token[j];j++)
      {
         char c = token[j];

         if(strchr("/-.",c))
            date_del_found = TRUE;
         else
            if(!isdigit(c))
               non_num_found = TRUE;
      }

      if(non_num_found)
         break;

      if(date_del_found)
         ParseDate(date,token,fa.dateFormat);
      else
         size = atol(token);

      if(!*s)
         prev_s = s;
   }

   s = prev_s;

   while(is_whitespace(*s) && *s) s++;                   // Skip whitespace

   desc = s;

   if(size<0 || !date.ok())
   {
      QDirScan f(QFileName(fa.filePath,fname));

      if(!int(f))
      {
         size = 0;
         date(0,0,0);
      }
      else
      {
         if(!date.ok())
            date = f.date();

         if(size < 0)
            size = f.size();
      }
   }

   counter = 0;

   bool in_counter = FALSE;
   QString counter_string;

   for(int i=0 ; desc[i] ; i++)
   {
      if(desc[i] == ']')
      {
         i++;
         while(is_whitespace(desc[i]) && desc[i]) i++;

         if(!desc[i]) i--;

         desc.del(0,i);

         counter = atoi(counter_string);
         break;
      }

      if(in_counter)
      {
         if(isdigit(desc[i]))
            counter_string << desc[i];
         else
            break;
      }

      if(desc[i] == '[')
         in_counter = TRUE;
   }
}

static void
RemoveDangerousChars(QString& s)
{
   if(strpbrk(s,"\x09\x18\x19"))
   {
      int i;

      while((i = s.find("\x09")) >= 0)
         s.del(i,1);
      while((i = s.find("\x18")) >= 0)
         s.del(i,1);
      while((i = s.find("\x19")) >= 0)
         s.del(i,1);
   }
}

static bool
displayline(char *line,TpFileArea& fa)
{
   QString str,wrap;
   QString wrapcolor;
   int left_margin;

   if( (strchr(valid,toupper(*line)) || (*line=='!' && strchr(valid,toupper(line[1]))))
      && *line)
   {
      QDate date;
      long size;
      int counter;
      QString fname;
      QString desc;

      split_line(line , fname , date , size , counter , desc , fa);

      RemoveDangerousChars(desc);

      str = FullColorString( cfg.listColorTag );

      local_tags[last_tag].area = fa.areaNum;
      strcpy(local_tags[last_tag].name, fname);
      strupr(local_tags[last_tag].name);

      if(size)
      {
         str << tag_chars[last_tag] << ' ';

         if(last_tag >= num_local_tags) num_local_tags = last_tag+1;

         last_tag = (++last_tag) % min(MAX_TAGS,(/*rip_mode ? rip_screenlines:*/user.screenLength));
      }
      else
      {
         str << "  ";
      }

      str << FullColorString( cfg.listColorFileName );
      str << form("%-12s " , (char *)fname);

      if(size)
      {
         str << FullColorString( cfg.listColorDate );
         str << date.format(DateFormats[user.dateFormat]);

         //form("%02d/%02d/%02d",date[(cfg.europe ? 0 : 1)],date[(cfg.europe ? 1 : 0)],date[2]);

         str << FullColorString( cfg.listColorSize );

         if((size+512L)/1024L > 1000L)
            str << form("%2ld.%1ldM " , (size+512L)/1024L/1024L,((size+512L)%(1024L*1024L))/1024L*10L/1024L);
         else
            if(size >= 1000L)
               str << form("%4ldk " , (size+512L)/1024L);
            else
               str << form("%4ldb " , size);
      }
      else
      {
         str << FullColorString(cfg.listColorMissing);
         str << "  <MISSING>   ";
      }

      if(!cfg.hideFileCounter)
      {
         str << FullColorString( cfg.listColorCounter );
         str << form("[%02d]" , counter);
         if(counter < 100)
            str << ' ';
      }

      wrapcolor = FullColorString( cfg.listColorDesc );
      str << wrapcolor;

      io << str;

      if(OutputStopped) return FALSE;

      left_margin = 34-5*cfg.hideFileCounter;

      str = desc;
   }
   else
   {
      char fnb = first_nonblank(line);

      if(fnb && strchr("+|",fnb))
      {
         line = strchr(line,fnb);
      }

      switch(*line)
      {
         case '|':
         case '+':
            {
               line++;
               while(is_whitespace(*line) && *line != '\0') line++;
               left_margin = 34-5*cfg.hideFileCounter;
               wrapcolor = FullColorString(cfg.listColorDesc);
               FullColor(cfg.listColorDesc);
               io << QString(' ',left_margin);
            }
            break;
         case '!':
            {
               left_margin = 0;
               FullColor(cfg.listColorDesc);
               wrapcolor = FullColorString(cfg.listColorDesc);
               line++;
            }
            break;
         case ';':
            {
               left_margin = 0;
               FullColor(cfg.listColorDesc);
               wrapcolor = FullColorString(cfg.listColorDesc);
               line++;
            }
            break;
         default :
            {
               left_margin = 0;
               FullColor(cfg.listColorSeperator);
               wrapcolor = FullColorString(cfg.listColorSeperator);
            }
            break;
       }

       str = line;

       RemoveDangerousChars(str);
   }

   if(OutputStopped) return FALSE;

   for(;;)
   {
      int l = WordWrap(str,wrap,79 - left_margin);

      str << '\n';
      io << str;
      if(LineCounter() || OutputStopped) return FALSE;

      if(!l) break;

      io << wrapcolor << QString(' ',left_margin);

      if(OutputStopped) return FALSE;

      str = wrap;
   }

   FlushOutput();

   return TRUE;
}


int
MatchFile(char *search,char *file)
{
   QString sbody,sext,fbody,fext;

   while(*search!='.' && *search)
      sbody << *search++;

   if(!*search++) return 0;

   while(*search)
      sext << *search++;

   while(*file!='.' && *file)
      fbody << *file++;

   if(!*file++) return 0;

   while(*file)
      fext << *file++;

   if(MatchString(sbody,fbody) && MatchString(sext,fext))
      return 1;

   return 0;
}

int
MatchString(char *s,char *d)
{
   for(;*s && *d;s++,d++)
   {
      switch(*s)
      {
         case '?': continue;
         case '*': return 1;
         default : if(toupper(*s)!=toupper(*d)) return 0;
      }
   }
   if(toupper(*s) != toupper(*d) && *s!='*')
      return 0;
   else
      return 1;
}

