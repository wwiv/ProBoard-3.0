#include "proboard.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct InputFile
   {
      int    area;
      QString name;

      InputFile();
      InputFile(char *s);
      InputFile(char *s , int area);
   };

const int MAX_DOWNLOADS = 100;

void CreateDirectoryList(int area,char *firstdir,QLinkedList<QString>& dirlist);
bool IsFreeFile(char *fname);
bool SendFiles( TpProtocol& p , QLinkedList<DownloadFile>& files ,QLinkedList<QString>& downloads , QLinkedList<QString>& uploads);
void ReadPersonalFiles( QLinkedList<InputFile>& files );
void DeletePersonalFile( char *name );
void CopyFromCdRom( QLinkedList<DownloadFile> &files , QLinkedList<QString> &copied);
void DeleteFilesCopiedFromCdRom ( QLinkedList<QString> &copied);

void ProcessUploads(TpProtocol& p , char *dir , QLinkedList<QString>& uploads , bool pvt , bool ask_desc ,  bool no_log ,  bool quiet_dl ,  QString extra_log );

bool CheckDSZLOG(TpProtocol& p , QLinkedList<QString>& downloads , QLinkedList<QString>& uploads);
bool CreateDSZCTL(TpProtocol& p , QLinkedList<DownloadFile>& files);

static void
read_from_file(QLinkedList<InputFile>& input_files , char *fn)
{
   QTextFile f(fn);

   if(f.opened())
   {
      while(!f.eof())
      {
         QString s = f.readLine();

         s.delLast('\n');
         s.trim();

         if(!s.len()) continue;

         input_files.add(InputFile(s));
      }
   }
}


int
mDownload(char *data)
{
   bool no_input           = FALSE;
   bool any_file           = FALSE;
   bool private_download   = FALSE;
   bool free_time          = FALSE;
   char protocol_key       = '\0';
   bool quiet_download     = FALSE;
   bool goodbye            = FALSE;
   bool ignore_kBYTEs      = FALSE;
   bool no_log             = FALSE;
   bool ask_description    = TRUE;

   int       npara;
   int       i;
   long      total_BYTEs;
   long      free_BYTEs;
   QString  param[20];
   QBitArray  arealist(10000,1);

   QLinkedList<DownloadFile> files;
   QLinkedList<InputFile>    input_files;
   QLinkedList<QString>     copied_to_cd;

   TpProtocol             prot;

   QFileName             extra_log;

   npara = ParseData(data,param);           // Parse command line

   CreateAreaList(param,npara,arealist);    // Create list of selected file areas

   AdjustLimits();

   for(i=0 ; i<npara ; i++)
   {
      if(param[i][0]=='/')
         switch(toupper(param[i][1]))
         {
            case 'F': if(param[i][2] == '=')
                      {
                        if(param[i][3] == '@')
                           read_from_file(input_files,&param[i][4]);
                        else
                           input_files.add(InputFile(&param[i][3]));
                      }
                      else
                      {
                        input_files.add(InputFile(&param[i][2]));
                      }
                      no_input = TRUE;
            case 'A': any_file = TRUE;
                      break;
            case 'P': private_download = TRUE;
                      no_input         = TRUE;
                      break;
            case 'T': free_time = TRUE;
                      break;
            case 'K': protocol_key = param[i][3];
                      break;
            case 'Q': quiet_download = TRUE;
                      break;
            case 'I': ignore_kBYTEs = TRUE;
                      break;
            case 'N': no_log = TRUE;
                      break;
            case 'L': extra_log = &param[i][3];
                      break;
            case 'D': ask_description = FALSE;
                      break;
         }
   }

   if(user.uFlags & UFLAG_IGNORE)
      ignore_kBYTEs = TRUE;

   if(!quiet_download)
   {
      io << "\n\f" << S_DOWNLOAD_TITLE << "\n\n";

      if(timer.Online() < DownloadDelay && !(user.uFlags & UFLAG_IGNORE) && !private_download)
      {
         if(ShowAnsiFile("DLDELAY") == SENDFILE_NOTFOUND)
         {
            io << S_DOWNLOAD_DELAY(form("%d",DownloadDelay)) << "\n\n";
         }

         io << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      if(!cfg.downloadHours.enabled() && !(user.uFlags & UFLAG_IGNORE) && !private_download)
      {
         io << S_DOWNLOAD_NOT_NOW;
         return 1;
      }
   }

   if(!user.defaultProtocol || !SelectProtocol(prot,user.defaultProtocol))
   {
      if(!SelectProtocol(prot,protocol_key))
         return 1;
   }
   else
   {
      io << S_PROTOCOL_SELECTED(prot.Name);
   }

   if(!any_file && !no_input)
      for(TagList.rewind() ; !TagList.eol() ; TagList++)
      {
         input_files.add( InputFile(TagList.get().name , TagList.get().area) );
      }

   for(input_files.rewind() ; !input_files.eol() ; input_files++)
   {
      if(input_files.get().area)
         arealist.set(input_files.get().area);
   }

   if(!quiet_download && !no_input)
   {
      char s[80];

      io << "\n\n" << S_ENTER_FILES_TO_DOWNLOAD << "\n\n";

      int file_count = 1;

      for( input_files.rewind() ; !input_files.eol() ; input_files++ , file_count++)
      {
         io << S_ENTER_DOWNLOAD_FILENAME(form("%d",file_count));
         io << input_files.get().name << '\n';
      }

      for(;;file_count++)
      {
         io << S_ENTER_DOWNLOAD_FILENAME(form("%d",file_count));

         Input(s,(any_file ? 60:13),INPUT_UPALL);

         if(!s[0]) break;

         char *tmp = strtok(s," ");

         for(i=0 ; tmp != NULL ; tmp = strtok(NULL," "))
         {
            if(strchr(tmp,'\\') && !any_file) continue;

            input_files.add(InputFile(tmp));
         }

         io << "\n";
      }

      if(!input_files.count())
         return 1;

      io << '\n';
   }

   if(!quiet_download)
      io << '\n' << S_SEARCHING_FILE_DATABASE << '\xFF';

   if(private_download)
   {
      ReadPersonalFiles(input_files);

      if(!input_files.count())
      {
         io << S_NO_PERSONAL_FILES_FOUND << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }
   }

   // At this point we have a list of files that have to be downloaded in the
   // linked list called 'input_files'.  If a path name is specified, it
   // should not be looked for in the file areas

   int files_found = 0;

   for( input_files.rewind() ; !input_files.eol() && files_found < MAX_DOWNLOADS; )
   {
      DownloadFile cur_file;

      if(strchr(input_files.get().name , '\\'))   // Explicit path found?
      {
         QDirScan scan(input_files.get().name);

         while(int(scan) && files_found < MAX_DOWNLOADS)
         {
            QFileName fn(input_files.get().name);

            fn.stripName();
            fn.appendBS();

            cur_file.area = 0;
            cur_file.free = FALSE;
            cur_file.copy = FALSE;
            cur_file.size = scan.size();
            cur_file.name = fn + scan.name();

            files.add(cur_file);

            files_found++;

            scan++;
         }

         input_files.remove();
      }
      else
      {
         input_files++;
      }
   }

   if(input_files.count())
   {
      QFile fidx;
      _TpFilesIdx idx;
      TpFileArea fa;

      if(fidx.open(QFileName(SysPath,"FILESIDX.PB") , fmode_read , 8192))
      {
         long idx_size = fidx.len() / sizeof(idx);
         long step = idx_size / 50;
         long count = 0;

         if(step <= 1)
            step = 1;

         fidx.seek(0);

         if(!quiet_download)
         {
            if(Terminal() == TTY)
            {
               io << "\n\n";
            }

            io << "\6³    ³    ³    ³    ³    ³    ³    ³    ³    ³    ³";

            if(Terminal() != TTY)
            {
               io << "\x1b[51D\3";
            }
            else
            {
               io << '\r';
            }
         }

         QString firstchars;
         bool wildcard_found = FALSE;

         for( input_files.rewind() ; !input_files.eol() ; input_files++)
         {
            firstchars << char(toupper(input_files.get().name[0]));
         }

         if(strpbrk(firstchars,"*?")) wildcard_found = TRUE;

         while(files_found < MAX_DOWNLOADS)
         {
            if(fidx.read(&idx,sizeof(idx)) != sizeof(idx))
               break;

            if(!((count++) % step) && !quiet_download) io << "±\xFF";

            if(!wildcard_found && !strchr(firstchars,toupper(idx.name[0]))) continue;

            if(!arealist[idx.area]) continue;

            for( input_files.rewind() ; !input_files.eol() && files_found < MAX_DOWNLOADS ; input_files++)
            {
               if(input_files.get().area && idx.area != input_files.get().area) continue;

               if(!MatchFile(input_files.get().name,idx.name)) continue;

               if(!fa.read(idx.area) || !user.CheckAccess(fa.level,fa.flags,fa.flagsNot)) continue;

               QLinkedList<QString> dirlist;

               CreateDirectoryList(idx.area,fa.filePath,dirlist);

               for( dirlist.rewind() ; !dirlist.eol() && files_found < MAX_DOWNLOADS ; dirlist++)
               {
                  QString wildcard = dirlist.get();

                  wildcard << idx.name;

                  QDirScan scan(wildcard);

                  while(int(scan) && files_found < MAX_DOWNLOADS)
                  {
                     DownloadFile tmpfile;

                     tmpfile.area = idx.area;
                     tmpfile.size = scan.size();
                     tmpfile.free = FALSE;
                     tmpfile.copy = !!fa.cdrom;
                     tmpfile.name = dirlist.get() + scan.name();

                     files.add(tmpfile);
                     files_found++;

                     scan++;
                  }
               }
            }
         }
      }
      else
      {
         LOG("Error opening FILESIDX.PB");
      }
   }

   total_BYTEs = 0;
   free_BYTEs  = 0;

   if(!quiet_download)
   {
      io << '\n';

      if(files.count())
      {
         io << '\n' << S_DOWNLOAD_FILES_FOUND_HEADER << '\n';
      }

      for(files.rewind() ; !files.eol() ; )
      {
         TpFileArea fa;
         QFileName fn;
         QString area_name;

         fn = files.get().name;
         fn.stripPath();

         if(files.get().area)
         {
            fa.read(files.get().area);
            area_name = fa.name;
         }
         else
         {
            if(private_download)
               area_name = "Personal Files";
            else
               area_name = "Global";
         }

         io << S_DOWNLOAD_FILE_FOUND_ENTRY((char *)fn,form("%ld",(files.get().size+512L) / 1024L),(char *)area_name);

         files.get().free = (fa.free || IsFreeFile((char *)fn));

         if((total_BYTEs - free_BYTEs + files.get().size + user.kbToday*1024L) > (1024L*DownloadLimit) && !files.get().free)
         {
            io << S_FILE_EXCEEDS_LIMIT(form("%u",DownloadLimit)) << '\n';

            files.remove();
         }
         else
         {
            if(UploadNeeded > 0 && !files.get().free)
            {
               io << S_UPLOAD_REQUIRED(form("%u",UploadNeeded)) << '\n';

               files.remove();
            }
            else
            {
               io << S_FILE_FOUND_ACTION_PROMPT;

               char action = WaitLanguageHotkeys(K_FILE_FOUND_ACTION_PROMPT);

               int prompt_len = LanguageStringLength(S_FILE_FOUND_ACTION_PROMPT);

               io << QString('\b',prompt_len) << QString(' ',prompt_len) << QString('\b',prompt_len);

               switch(action)
               {
                  case '\r':
                  case 0:
                     {
                        io << S_ACTION_DOWNLOAD << ' ';

                        if(files.get().free)
                        {
                           io << S_FREE_FILE;

                           free_BYTEs += files.get().size;
                        }

                        total_BYTEs += files.get().size;

                        io << '\n';
                        files++;
                     }
                     break;
                  case 1 :
                     {
                        io << S_ACTION_FILE_SKIPPED << '\n';

                        files.remove();
                     }
                     break;
                  case 2 :
                     {
                        io << S_ACTION_FILE_QUIT << '\n';

                        while(!files.eol()) files.remove();
                     }
                     break;
               }
            }
         }
      }

      if(!files.count())
      {
         io << '\n' << S_NO_FILES_FOUND << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      WORD estimated = WORD(total_BYTEs / ((BaudRate ? BaudRate:115200L) * (prot.Efficiency?prot.Efficiency:100)/1000L));

      if(prot.Flags & PROT_LOCAL)
         estimated = 0;

      io << '\n' << S_X_FILES_SELECTED(form("%d",files.count()),form("%d",int(total_BYTEs/1024)),form("%02u:%02u",estimated/60,estimated%60)) << '\n';

      if(!free_time && estimated/60>timer.Left())
      {
         io << '\n' << S_NOT_ENOUGH_TIME_LEFT_FOR_DOWNLOAD << "\n\n" <<  S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      io << '\n' << S_START_DOWNLOAD_PROMPT;

      char k = WaitLanguageHotkeys(K_START_DOWNLOAD_PROMPT);

      if(k==2)
         return 1;

      if(k==1)
      {
         io << S_DOWNLOAD_ACTION_GOODBYE;

         goodbye = TRUE;
      }

      io << "\n\n";

      CopyFromCdRom( files , copied_to_cd);

      io << "\n\n" << S_ACTIVATING_PROTOCOL << '\xFF';
   }

   QLinkedList<QString> downloads,uploads;

   if(free_time) timer.Suspend();

   if(!SendFiles(prot , files , downloads , uploads))
   {
      DeleteFilesCopiedFromCdRom(copied_to_cd);

      return 1;
   }

   DeleteFilesCopiedFromCdRom(copied_to_cd);

   if(free_time)
      timer.Restart();

   total_BYTEs = 0;
   free_BYTEs  = 0;
   files_found = 0;

   for(downloads.rewind() ; !downloads.eol() ; downloads++)
   {
      for(files.rewind() ; !files.eol() ; )
      {
         QFileName fn(files.get().name);

         fn.stripPath();

         if(downloads.get() == fn)
         {
            total_BYTEs += files.get().size;

            if(files.get().free)
               free_BYTEs += files.get().size;

            RemoveTag(fn,files.get().area);

            if(private_download)
               DeletePersonalFile(files.get().name);

            files_found++;

            QFile f;

            if(extra_log.len())
            {
               f.open(extra_log,fmode_copen | fmode_text | fmode_append | fmode_write);

               f.printf("D %d %s %ld %s\n",files.get().area,(char *)files.get().name,files.get().size,files.get().free ? "YES":"NO");
               f.close();
            }

            if(!no_log)
            {
               f.open(QFileName(SysPath,"DOWNLOAD.LOG"),fmode_write | fmode_append |
                                                       fmode_copen | fmode_text);

               f.printf("%05d %s\n",files.get().area,(char *)files.get().name);
               f.close();

               LOG(1,"Download-%c %s",prot.Key,(char *)fn);
            }

            files.remove();
         }
         else
         {
            files++;
         }
      }
   }

   if(!ignore_kBYTEs)
   {
      user.numDownloads += files_found;
      user.kbDownloaded += int((total_BYTEs-free_BYTEs) / 1024L);
      user.kbToday      += int((total_BYTEs-free_BYTEs) / 1024L);
   }

   if(!quiet_download)
   {
      io << "\n\f\n" << S_X_FILES_DOWNLOADED_SUCCESSFULLY(form("%d",files_found),form("%ld",total_BYTEs/1024L)) << "\n\n";

      if(files.count())
         io << S_X_FILES_NOT_DOWNLOADED(form("%d",files.count())) << "\n\n";

      if(goodbye && !files.count() && !uploads.count())
      {
         ::remove(prot.LogFile);
         ::remove(prot.CtlFile);

         io << "\n\n" << S_HANGUP_AFTER_DOWNLOAD_PROMPT << "10";

         for(int i=10;i>0;i--)
         {
            io << form("\b\b%2d\xFF",i);

            char c = toupper(ReadKey());

            if(c==K_HANGUP_AFTER_DOWNLOAD_PROMPT[0]) return 1;
            if(c==K_HANGUP_AFTER_DOWNLOAD_PROMPT[1]) break;

            Delay(1000);
         }

         LOG("Hanging up after download.");

         ShowAnsiFile("DLHANGUP");

         throw TXQuit();
      }

      if(uploads.count())
         ProcessUploads(prot,cfg.uploadPath,uploads,private_download , ask_description , no_log , quiet_download , extra_log );

      io << S_PRESS_ENTER_TO_CONTINUE;
   }

   return 0;
}

void
ReadPersonalFiles( QLinkedList<InputFile>& files )
{
   QFile f(QFileName(SysPath,"PVTFILES.PB"));

   if(!f.opened()) return;

   f.seek(0);

   for(;;)
   {
      _TpPrivateFile pvt;

      if(f.read(&pvt,sizeof(pvt)) != sizeof(pvt))
         break;

      if(strcmpl(pvt.to,user.name) || !pvt.fname[0]) continue;

      QString fname;

      if(!strchr(pvt.fname,'\\'))
         fname = QString(cfg.pvtUploadPath) + pvt.fname;
      else
         fname = pvt.fname;

      QDirScan scan(fname);

      if(int(scan))
         files.add( InputFile(fname) );
   }
}

void
DeletePersonalFile( char *name )
{
   QFile f(QFileName(SysPath,"PVTFILES.PB"),fmode_rw | fmode_excl);

   if(!f.opened())
      return;

   QFileName fn;
   QFileName fn_full( name );

   _TpPrivateFile pvt;

   int num_found = 0;

   for(;;)
   {
      if(f.read(&pvt,sizeof(pvt))!=sizeof(pvt)) break;

      if(!pvt.fname[0])
         continue;

      if(!strchr(pvt.fname,'\\'))
         fn = QString(cfg.pvtUploadPath) + pvt.fname;
      else
         fn = pvt.fname;

      if(fn == fn_full)
         num_found++;
   }

   f.seek(0);

   for(;;)
   {
      if(f.read(&pvt,sizeof(pvt))!=sizeof(pvt)) break;

      if(!pvt.fname[0] || stricmp(pvt.to,user.name))
         continue;

      if(!strchr(pvt.fname,'\\'))
         fn = QString(cfg.pvtUploadPath) + pvt.fname;
      else
         fn = pvt.fname;

      if(fn_full == fn)
      {
         pvt.fname[0]=0;

         f.seek(-long(sizeof(pvt)),seek_cur);
         f.write(&pvt,sizeof(pvt));

         if(pvt.attr & PVTFILE_KEEP)
            continue;

         if(num_found < 2)   // Only kill file if not waiting for oher user
            ::remove(fn_full);
      }
   }
}

InputFile::InputFile()
{
   area = 0;
}

InputFile::InputFile(char *s)
{
   area = 0;

   if(s[0] == '[')
   {
      area = atoi(&s[1]);

      for(int i=0; s[i] ; i++)
      {
         if(s[i] == ']')
         {
            name = &s[i+1];
            return;
         }
      }
   }

   name = s;
}

InputFile::InputFile(char *s,int a)
{
   name = s;
   area = a;
}
