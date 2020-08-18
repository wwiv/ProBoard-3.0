#include "proboard.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <ctype.h>

static void MoveFailedFile(QFileName full_fn);

static bool FileInIndex(QFileName fn);
       bool CheckDSZLOG(TpProtocol& p , QLinkedList<QString>& downloads , QLinkedList<QString>& uploads);

void ProcessUploads(TpProtocol& p , char *dir , QLinkedList<QString>& uploads , bool pvt , bool ask_desc ,  bool no_log ,  bool quiet_dl ,  QString extra_log );

static char oldpath[70]="";

static char env_buf[80];


int
mUpload(char *data)
{
   bool     private_download = false;
   bool     no_input         = false;
   bool     quiet_download   = false;
   bool     no_log           = false;
   bool     ask_description  = true;
   char     protocol_key     = '\0';
   char     filename[13]     = "";
   QFileName extra_log;
   TpProtocol p;
   int      i,npara;
   QString   param[20];
   char     uploadpath[80];

   AdjustLimits();

   strcpy(uploadpath , cfg.uploadPath);

   npara = ParseData(data,param);           // Parse command line

   for(i=0 ; i<npara ; i++)
   {
      if(param[i][0]=='/')
         switch(toupper(param[i][1]))
         {
            case 'F': strncpy(filename,&param[i][3],12);
                      filename[12] = '\0';
                      no_input         = true;
                      break;
            case 'P': private_download = true;
                      no_input         = true;
                      strcpy(uploadpath , cfg.pvtUploadPath);
                      break;
            case 'K': protocol_key = param[i][3];
                      break;
            case 'Q': quiet_download = true;
                      ask_description = false;
                      break;
            case 'N': no_log = true;
                      break;
            case 'L': extra_log = &param[i][3];
                      break;
            case 'D': ask_description = FALSE;
                      break;
         }
      else
      {
         strcpy(uploadpath , param[i]);
      }
   }

   append_backspace(uploadpath);
   strupr(uploadpath);

   if(!no_log)
      LOG(2,"Upload menu");

   if(!quiet_download)
      io << "\n\f" << S_UPLOAD_TITLE << "\n\n";

   if(ts_DiskFreeSpace(uploadpath) < (1024L*cfg.minUploadSpace))
   {
      io << "\n\n" << S_NOT_ENOUGH_FREE_DISK_SPACE << "\n\n"
         << S_PRESS_ENTER_TO_CONTINUE;

      return 1;
   }

   if(timer.Left()<10 && TimeRemoved>0 && !quiet_download)
   {
      io << S_NO_UPLOAD_DUE_TO_EVENT << "\n\n"
         << S_PRESS_ENTER_TO_CONTINUE;

      return 1;
   }

   if(!SelectProtocol(p,protocol_key)) return 1;

   if(!(p.Flags&PROT_BATCH) && !no_input)
   {
      io << "\n\n" << S_FILE_TO_UPLOAD;

      Input(filename,12,INPUT_UPALL);

      if(!*filename || strchr(filename,':') || strchr(filename,'\\'))
         return 1;

      io << '\n';
   }

   QString command;

   if(p.ULCommand[0] != '@')
      command << "*N*Q";

   for(i=0;i<(int)strlen(p.ULCommand);i++)
      if(p.ULCommand[i] != '#')
      {
         command << p.ULCommand[i];
      }
      else
      {
         command << uploadpath;

         if(!(p.Flags&PROT_BATCH)) command << filename;
      }

   if(!quiet_download)
   {
      io << '\n' << S_UPLOAD_START_PROMPT;

      char k = WaitLanguageHotkeys(K_UPLOAD_START_PROMPT);

      if(k==1) return 1;

      io << "\n\n" << S_READY_TO_UPLOAD_FILES << '\xFF';
   }

   sprintf(env_buf,"DSZLOG=%s%s",(char *)WorkPath,p.LogFile);

   putenv(env_buf);

   timer.Suspend();

   //pushdir(uploadpath);

   if(command[0]=='@')
   {
      mRunPex(ReplaceStringVars(&command[1]));
   }
   else
   {
      mShell(ReplaceStringVars(command));
   }

//   popdir();

   timer.Restart();

   QLinkedList<QString> downloads , uploads;

   CheckDSZLOG(p , downloads , uploads);

   if(!uploads.count())
   {
      if(!quiet_download)
      {
         io << "\n\n" << S_NO_FILES_RECEIVED << "\n\n"
            << S_PRESS_ENTER_TO_CONTINUE;
      }

      return 1;
   }

   ProcessUploads(p,uploadpath,uploads,private_download,ask_description,no_log,quiet_download,extra_log);

   if(!quiet_download)
      io << '\n' << S_PRESS_ENTER_TO_CONTINUE;

   return 0;
}


void
ProcessUploads(TpProtocol& p , char *dir , QLinkedList<QString>& uploads , bool pvt ,
                                                                        bool ask_desc ,
                                                                        bool no_log ,
                                                                        bool quiet_dl ,
                                                                        QString extra_log
                                                                       )
{
   long total_BYTEs = 0;
   int  total_files = 0;
   QString uploadpath(dir);

   bool dupes_found = FALSE;

   if(!quiet_dl)
      io << "\n\n" << S_CHECKING_UPLOADS << "\n\xFF";

   for( uploads.rewind() ; !uploads.eol() ; )
   {
      QFileName fn( uploadpath , uploads.get() );

      fn.upperCase();

      QFileName fullfn(fn);

      QDirScan scan(fullfn);

      if(!int(scan))
      {
         uploads.remove();

         continue;
      }

      fn.stripPath();

      if(!quiet_dl)
         io << '\n' << S_FILE_RECEIVED((char *)fn) << '\xFF';

      QDate date(TODAY);
      QTime time(NOW);

      QFile ul_log;

      if(!no_log)
      {
         ul_log.open(QFileName(SysPath,"UPLOAD.LOG"),fmode_text | fmode_append | fmode_write | fmode_copen);

         ul_log.printf("%s %02d:%02d:%02d Upload of %-13s by %s\n",
                                                   (char *)date.format("DD MMM YYYY"),
                                                   time[0],time[1],time[2],
                                                   (char *)fn,user.name);
         ul_log.close();
      }

      if(extra_log.len())
      {
         ul_log.open(extra_log,fmode_text | fmode_append | fmode_write | fmode_copen);
         ul_log.printf("U 0 %s %ld NO\n",(char *)fullfn,scan.size());
         ul_log.close();
      }

      if(!pvt && cfg.checkDupes && FileInIndex(fn) && !quiet_dl)
      {
         dupes_found = TRUE;

         if(cfg.killDupes)
         {
            unlink(fullfn);

            io << S_DUPLICATE_UPLOAD_REMOVED;
         }
         else
         {
            io << S_DUPLICATE_UPLOAD;
         }

         LOG(1,"Upload-%c %s (DUPE)",p.Key,(char *)fn);

         uploads.remove();
      }
      else
      {
         if(!no_log)
         {
            if(pvt)
               LOG(1,"Upload-%c %s (Personal)",p.Key,(char *)fn);
            else
               LOG(1,"Upload-%c %s",p.Key,(char *)fn);
         }

         total_files++;
         total_BYTEs += scan.size();

         uploads++;
      }
   }

   if(cfg.virScanCommand[0])
   {
      QLinkedList<QFileName> failed_files;

      io << "\n\n" << S_SCANNING_UPLOADS;

      for(uploads.rewind() ; !uploads.eol(); )
      {
         QFileName curfile(uploadpath,uploads.get());

         QDirScan scan(curfile);

         QString cmd     = QString("*Q*N") + cfg.virScanCommand;

         cmd.replace("@<FILE>@",curfile);

         mShell(ReplaceStringVars(cmd));

         if(   (cfg.virScanType && !access(cfg.virScanSemaphore,0))
            || (!cfg.virScanType && ShellReturnCode)
           )
         {
            LOG(1,"File '%s' rejected by upload scanner",(char *)curfile);

            if(cfg.virScanFailedAction == VIRSCAN_ACTION_DELETE)
            {
               unlink(curfile);
            }

            if(cfg.virScanFailedAction == VIRSCAN_ACTION_MOVE)
            {
               MoveFailedFile(curfile);
            }

            uploads.remove();

            failed_files.add(curfile);

            total_files--;
            total_BYTEs -= scan.size();
         }
         else
         {
            uploads++;
         }
      }

      if(failed_files.count())
      {
         io << "\n\n" << S_FOLLOWING_FILES_REJECTED << "\n\n";

         for(failed_files.rewind() ; !failed_files.eol() ; failed_files++)
         {
            QFileName fn = failed_files.get();

            fn.stripPath();

            io << "     " << (char *)fn << '\n';
         }

         io << '\n' << S_PRESS_ENTER_TO_CONTINUE;
      }
   }


   if(total_files)
   {
      if(!pvt)
      {
         user.numUploads += total_files;
         user.kbUploaded += int(total_BYTEs/1024L);

         if(!quiet_dl)
            io << "\n\n" << S_X_FILES_UPLOADED(form("%d",total_files),form("%ld",total_BYTEs/1024L)) << '\n';
      }
   }
   else
   {
      if(!quiet_dl)
         io << "\n\n" << S_NO_FILES_UPLOADED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

      return;
   }

   if(!ask_desc) return;

   if(dupes_found && !quiet_dl) ShowAnsiFile("DUPESFND");

   if(!pvt && uploads.count())
      io << '\n'
         << S_PLEASE_ENTER_UPLOAD_DESCRIPTIONS
         << "\n\n";

   for(uploads.rewind() ; !uploads.eol(); uploads++)
   {
      FlushInput();

      if(pvt)
      {
         TpUser tmpuser;
         char username[36];

         for(;;)
         {
            io << '\n' << S_ENTER_USERNAME_FOR_PERSONAL_FILE((char *)uploads.get());
            Input(username,35,INPUT_UPFIRST);

            if(!strcmpl(username,"Sysop")) strcpy(username,cfg.sysopName);
            if(tmpuser.Search(username)) break;
            io << "\n\n" << S_USER_NOT_LOCATED << '\n';
         }

         QFile f(QFileName(SysPath,"PVTFILES.PB"),fmode_rw | fmode_copen);
         if(!f.opened())
         {
            LOG("Unable to create PVTFILES.PB");
            continue;
         }

         _TpPrivateFile pvt;

         for(int rec=0;;rec++)
         {
            if(f.read(&pvt,sizeof(pvt))!=sizeof(pvt)) break;

            if(!pvt.fname[0]) break;
         }
         strcpy(pvt.fname,uploads.get());
         strcpy(pvt.to,username);
         strcpy(pvt.from,user.name);
         pvt.date.today();
         f.seek(long(rec)*sizeof(pvt));
         f.write(&pvt,sizeof(pvt));
      }
      else
      {
         QFileName fbbs;
         char descr[41];

         io << '\n' << S_ENTER_DESCRIPTION_LINE_1((char *)uploads.get());

         FlushInput();
         Input(descr,40);

         if(descr[0]!='/')
            fbbs(uploadpath,"FILES.BBS");
         else
            fbbs(uploadpath,"FILES.PVT");

         QFile tf(fbbs,fmode_write | fmode_append | fmode_text | fmode_copen);
         tf << form("%-12s %s\n",(char *)uploads.get(),((descr[0]=='/') ? (&descr[1]) : descr));
         while(descr[0])
         {
            io << '\n' << S_ENTER_DESCRIPTION_LINE_X;
            Input(descr,40);
            if(descr[0]) tf << '+' << ((descr[0]=='/') ? (&descr[1]) : descr) << '\n';
         }

         if(cfg.addUploaderName)
            tf << '+' << "[Uploader: " << user.name << ']\n';
      }
   }

   io << '\n';
}


bool
FileInIndex(QFileName fn)
{
   if(cfg.ignoreDupeExt) fn.stripExt();

   QFile idx;

   if(idx.open(QFileName(SysPath,"FILESIDX.PB") , fmode_read , 8192))
   {
      TpFilesIdx fidx;

      for(;;)
      {
         if(idx.read(&fidx,sizeof(fidx)) != sizeof(fidx)) break;

         if(cfg.ignoreDupeExt)
            if(strchr(fidx.name,'.'))
               *strchr(fidx.name,'.') = '\0';

         if(!stricmp(fidx.name,fn)) return TRUE;
      }
   }

   return FALSE;
}

bool
CheckDSZLOG(TpProtocol& p , QLinkedList<QString>& downloads , QLinkedList<QString>& uploads)
{
   QFile dszlog;
   int i;
   char s[200];

   if(dszlog.open(p.LogFile,fmode_read | fmode_text))
   {

      while(dszlog.readLine(s,199))
      {
         bool found_upload   = FALSE;
         bool found_download = FALSE;

         strip_linefeed(s);

         char *ptr=strtok(s," ");

         while(ptr)
         {
            if(!strcmp(ptr,p.DLKeyWord))
            {
               found_download = TRUE;
               break;
            }
            if(!strcmp(ptr,p.ULKeyWord))
            {
               found_upload = TRUE;
               break;
            }

            ptr = strtok(NULL," ");
         }

         if(ptr == NULL) continue;

         for(i=0;i<p.WordNr && ptr!=NULL;i++) ptr = strtok(NULL," ");

         if(ptr==NULL) continue;

         QFileName fn(ptr);
         fn.stripPath();
         fn.upperCase();

         if(found_download)
            downloads.add( fn );

         if(found_upload)
            uploads.add( fn );
      }

      dszlog.close();

      unlink(p.CtlFile);
      unlink(p.LogFile);

      return TRUE;
   }

   unlink(p.CtlFile);
   unlink(p.LogFile);

   return FALSE;
}

bool
CreateDSZCTL(TpProtocol& p , QLinkedList<DownloadFile>& files)
{
   QFile tf;

   if(!tf.open(p.CtlFile,fmode_create | fmode_text))
      return FALSE;

   for(files.rewind() ; !files.eol() ; files++)
   {
      if(p.Flags&PROT_BIM)
      {
         tf << form("U       %-80s%-160s",(char *) files.get().name,"");
      }
      else
      {
         for(int j=0;j<(int)strlen(p.DLString);j++)
            if(p.DLString[j]=='#')
               tf << (char *)files.get().name;
            else
               tf << p.DLString[j];

         tf << '\n';
      }
   }

   files.rewind();

   return TRUE;
}

bool
SendFiles( TpProtocol& p , QLinkedList<DownloadFile>& files , QLinkedList<QString>& downloads , QLinkedList<QString>& uploads )
{
   if(!strchr(p.DLCommand,'#'))
      if(!CreateDSZCTL(p , files)) return FALSE;

   QString command;

   if(p.DLCommand[0] != '@')
      command << "*N*Q";

   files.rewind();

   for(int i=0;i<(int)strlen(p.DLCommand);i++)
      if(p.DLCommand[i] != '#')
         command << p.DLCommand[i];
      else
         command << files.get().name;

   sprintf(env_buf,"DSZLOG=%s%s",(char *)WorkPath,p.LogFile);

   putenv(env_buf);

   if(command[0]=='@')
      mRunPex(ReplaceStringVars(&command[1]));
   else
      mShell(ReplaceStringVars(command));

   return CheckDSZLOG(p , downloads , uploads);
}

void
CreateDirectoryList(int area,char *firstdir,QLinkedList<QString>& dirlist)
{
   QFile f(QFileName(SysPath,form("FA_%d.CTL",area)),fmode_read | fmode_text);

   dirlist.rewind();

   dirlist.add(QString(firstdir));

   for(;;)
   {
      char str[128];

      if(!f.readLine(str,127)) break;

      append_backspace(str);

      dirlist.add(QString(str));
   }
}

bool
IsFreeFile(char *fname)
{
   QFile fp(QFileName(SysPath,"FREEFILE.CTL"),fmode_read | fmode_text);

   if(!fp.opened()) return false;

   for(;;)
   {
      char s[100];

      if(!fp.readLine(s,99)) return false;

      strip_linefeed(s);
      strip_leading(s);
      strip_trailing(s);

      if(MatchFile(s,fname)) return true;
   }
}

static void
MoveFailedFile(QFileName full_fn)
{
   TpFileArea fa;
   QFileName fn = full_fn;

   fn.stripPath();

   if(fa.read(cfg.virScanFailedArea))
   {
      ts_CopyFile(full_fn,fa.filePath,4096);
      unlink(full_fn);

      QFile f(fa.listPath,fmode_rw|fmode_append|fmode_copen);
      f.printf("%-12s <FAILED> Uploaded by %s\n",(char *)fn,user.name);
   }
}
