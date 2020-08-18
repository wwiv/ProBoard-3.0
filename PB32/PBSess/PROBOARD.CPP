#include "proboard.hpp"
#include "direct.h"

static int just_for_a_pointer;


#pragma warning( disable : 4355 )

int __declspec( dllexport )
Run(long baud)
{
   static bool running = FALSE;

   if(running)
         return 1;

   running = TRUE;

   BaudRate = baud;

   Initialize();

   ReadLanguage("ENGLISH");

   try
   {
      ShowIntro();
      Login();
      MenuProcessor();
   }

   catch(TXFatalError& err)
   {
      LOG(form("Fatal Error: %s",err.Description()));
      return 1;
   }

   catch(TXNoCarrier)
   {
      return 1;
   }

   catch(TXQuit)
   {
      return 1;
   }

   catch(TXWindowClosed)
   {
      return 0;
   }

   return 1;
}


void Initialize()
{
   SysPath = "D:\\PB32\\";

   char *p = getcwd(NULL,150);

   QFileName fn(p);

   fn.appendBS();

   fn << form("%08lX\\",(DWORD)&just_for_a_pointer);

   WorkPath = fn;

   fn.delLast('\\');

   mkdir(fn);
   chdir(fn);

   menufunctions[0]  = mNOP;
   menufunctions[1]  = mGotoMenu;
   menufunctions[2]  = mGosubMenu;
   menufunctions[3]  = mPrevMenu;
   menufunctions[4]  = mGotoMenuClear;
   menufunctions[5]  = mShowAnsiFile;
   menufunctions[6]  = mChangeState;
   menufunctions[7]  = mShell;
   menufunctions[8]  = mNOP;
   menufunctions[9]  = mLogoff;
   menufunctions[10] = mNOP;
   menufunctions[11] = mNOP;
   menufunctions[12] = mQuestionnaire;
   menufunctions[13] = mNOP;
   menufunctions[14] = mNOP;
   menufunctions[15] = mShowAnsiFileAndWait;
   menufunctions[16] = mChangeCity;
   menufunctions[17] = mChangePassword;
   menufunctions[18] = mChangeScreenLines;
   menufunctions[19] = mToggleCls;
   menufunctions[20] = mTogglePause;
   menufunctions[21] = mToggleAnsi;
   menufunctions[22] = mNOP;
   menufunctions[23] = mReadMessages;
   menufunctions[24] = mNOP;
   menufunctions[25] = mNOP;
   menufunctions[26] = mNOP;
   menufunctions[27] = mWriteMsg;
   menufunctions[28] = mNOP;
   menufunctions[29] = mNOP;
   menufunctions[30] = mNOP;
   menufunctions[31] = mListFiles;
   menufunctions[32] = mDownload;
   menufunctions[33] = mUpload;
   menufunctions[34] = mNOP;
   menufunctions[35] = mKeywordSearch;
   menufunctions[36] = mFileNameSearch;
   menufunctions[37] = mNewFileSearch;
   menufunctions[38] = mNOP;
   menufunctions[39] = mNOP;
   menufunctions[40] = mNOP;
   menufunctions[41] = mNOP;
   menufunctions[42] = mNOP;
   menufunctions[43] = mNOP;
   menufunctions[44] = mNOP;
   menufunctions[45] = mNOP;
   menufunctions[46] = mNOP;
   menufunctions[47] = mNOP;
   menufunctions[48] = mNOP;
   menufunctions[49] = mSelectMessageArea;
   menufunctions[50] = mNOP;
   menufunctions[51] = mNOP;
   menufunctions[52] = mNOP;
   menufunctions[53] = mNOP;
   menufunctions[54] = mSelectFileArea;
   menufunctions[55] = mNOP;
   menufunctions[56] = mNOP;
   menufunctions[57] = mNOP;
   menufunctions[58] = mNOP;
   menufunctions[59] = mNOP;
   menufunctions[60] = mRunPex;
   menufunctions[61] = mNOP;
   menufunctions[62] = mToggleAvatar;
   menufunctions[63] = mToggleAvatar;
   menufunctions[64] = mNOP;
   menufunctions[65] = mNOP;
   menufunctions[67] = mNOP;
   menufunctions[68] = mEditTagList;
   menufunctions[69] = mSelectLanguage;
   menufunctions[70] = mChangeDateFormat;
   menufunctions[71] = mChangeAddress;
   menufunctions[72] = mChangeFaxPhone;
   menufunctions[73] = mChangeCountry;
   menufunctions[74] = mNOP;
   menufunctions[75] = mNOP;
   menufunctions[76] = mNOP;
   menufunctions[77] = mNOP;
   menufunctions[78] = mNOP;
   menufunctions[79] = mNOP;

   NumYells           = 0;
   PasswordOk         = FALSE;
   LineCount          = 0;
   OutputStopped      = FALSE;
   OutputContinuous   = FALSE;
   lang               = NULL;
   NumLanguageStrings = 0;
   StopEnabled        = TRUE;

   pControlCodeHandler = NULL;
   pLineCountHandler   = NULL;

   cfg.Read();

//   msgbase.add( squishMsgBase = new TpSquishMsgBase(this) );
   msgbase.add( hudsonMsgBase = new TpHudsonMsgBase );
   msgbase.add( jamMsgBase    = new TpJamMsgBase    );
}

int
mNOP(char *)
{
   return 0;
}


struct CallBacks
{
   void (*Send)(BYTE);
   BYTE (*WaitKey)();
   BYTE (*ReadKey)();
   BYTE (*CurrentAttribute)();
};

void __declspec( dllexport )
SetCallBack(void (*send)(BYTE),BYTE (*waitkey)(),BYTE (*readkey)(),BYTE (*curattr)())
{
   cbSend = send;
   cbWaitKey = waitkey;
   cbReadKey = readkey;
   cbCurrentAttribute = curattr;
}

