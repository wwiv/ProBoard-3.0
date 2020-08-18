#ifndef __PROBOARD_HPP
#define __PROBOARD_HPP

const bool TRUE = true;
const bool FALSE = false;

#include "string.h"

#include <tslib.hpp>
#include <pblib.hpp>

#define VERSION "3.00à"

class TpUser     : public _TpUser     {};
class TpFilesIdx : public _TpFilesIdx {};
class TpAreaGroup: public _TpAreaGroup{};
class TpLimit    : public _TpLimit    {};


class TpConfig   : public _TpConfig
   {
      int pastFirstUse;
   public:

      TpConfig() { pastFirstUse = 0; }

      bool Read();
   };


struct TpMenuItem : public _TpMenuItem
   {
      bool CheckAccess() const;
   };


class TpMenuStack
   {
      QString *menus;
      int sp;
   public:
      bool Changed;
      bool Update;

      QString CurMenu;

      TpMenuStack()
      {
         Changed = Update = false;

         menus = new QString[100];

         sp=0;
      }
      ~TpMenuStack()
      {
         delete [] menus;
      }

      void clear()        { sp=0; }
      void push(char *m)  { if(sp<100) menus[sp++] = m; }
      void pop(QString& m) { if(sp>0) m = menus[--sp]; }
   };

struct TpFileArea : _TpFileArea
  {
   static QFile f;
   static int lastAreaNum;
   static TpFileArea *lastArea;
   static int numAreas;

   static void open();
 public:
   int  areaNum;

   bool read(int);

   static void close();
   static int  highAreaNum();
  };


struct TpProtocol : public _TpProtocol
   {
      bool Read(int);
   };

#define PROT_BATCH   1
#define PROT_ENABLED 2
#define PROT_BOTH    4
#define PROT_BIM     8
#define PROT_LOCAL  16

struct NodeListEntry
   {
      BYTE type;

      short zone,
            region,
            net,
            node;

      short cost;

      char name[50];
      char city[50];
   };

struct DownloadFile
   {
      int      area;
      long     size;
      bool     free;
      bool     copy;
      QString name;
   };


class TpTimer
   {
      long   started;
      long   suspend_start;
      long   inactivity_start;

      int suspendedtime;

      int suspended;   //suspended count

      int fixedtime;

   public:
      TpTimer();

      void Start(int minutes);
      void Increase();
      void Decrease();
      void ChangeLeft(int);
      void Suspend();
      void Restart();
      int TimeSuspended() { return suspendedtime; }
      int Left();
      int Online();
      int Used();

      void Check();
      void ClearInactivity();
      void CheckInactivity();
   };


class TXNoCarrier
   {
   };

class TXQuit
   {
   };

class TXWindowClosed
   {
   };

class TXPBGeneral
   {
      char *s;
   public:
      TXPBGeneral() { s = ""; }
      TXPBGeneral(char *p) { s = p; }

      char *Description() { return s; }
   };

class TXFatalError : public TXPBGeneral
	{
   public:
   	TXFatalError(char *s) : TXPBGeneral(s) { }
   };


class TXFileError : public TXFatalError
   {
   public:
      TXFileError(char *fn) : TXFatalError(fn) {}
   };



#include "msgbase.hpp"
#include "prompts.hpp"

const BYTE INPUT_ALL     =   0;
const BYTE INPUT_UPFIRST =   1;
const BYTE INPUT_UPALL   =   2;
const BYTE INPUT_DIGITS  =   3;
const BYTE INPUT_PWD     =  64;
const BYTE INPUT_NOFIELD = 128;

const BYTE SENDFILE_OK          = 0;
const BYTE SENDFILE_INTERRUPTED = 1;
const BYTE SENDFILE_NOTFOUND    = 2;

/*** GLOBAL DATA *************************************************************/

extern TpConfig   cfg;

extern QFileName SysPath;
extern QFileName WorkPath;

extern TpUser     user;
extern QLinkedList<TpFilesIdx> TagList;
extern TpMsgBaseList msgbase;

extern TpMsgBase *squishMsgBase;
extern TpMsgBase *hudsonMsgBase;
extern TpMsgBase *jamMsgBase;

extern TpTimer timer;


extern QDate LoginDate;
extern QTime LoginTime;
extern int  NumYells;
extern bool PasswordOk;
extern int  PastFirstUse;
extern int  TimeLimit;
extern int  TimeRemoved;

extern int  DownloadLimit;
extern int  DownloadDelay;
extern WORD FreeDownload;
extern WORD UploadNeeded;

extern int NumLimits;
extern TpLimit *Limit;

extern int      (*menufunctions[200])(char *);
extern int      (*pMoreFunction)();


extern TpMenuStack MenuStack;
extern _TpLanguageString *lang;

extern TpLanguageFile   CurrentLanguage;
extern int              NumLanguageStrings;

extern long BaudRate;

extern int  LineCount;
extern bool StopEnabled;
extern bool OutputContinuous;
extern bool OutputStopped;

extern int   ShellReturnCode;

extern bool NewFilesChecked;

extern char *DateFormats[3];
extern bool registered;

extern QString (*pControlCodeHandler) (BYTE,BYTE,int width,QString::justification);
extern bool     (*pLineCountHandler  ) (int init = -1);



/*** GOBAL FUNCTIONS *********************************************************/

int   WordWrap(char *s,QString& str,int max);
DWORD RaCrc(char *s);
void  GetNewMessages(TpMarkedMsgList& marked,int area);
void  ReplyMessage(TpMessage& orgmsg);
int   mReadMessages(char *data);
int   mNOP(char *);
void  Initialize();
void  AdjustLimits();

void  InternalMsgEd();
void  WriteMSGINF(char *from , char *to , char *subj , long num , char *area , char *pvt);
void  EditMessage();

void  ParseDate(QDate&,char *,int format);
int   ParseData(char *,QString *);

int   LanguageStringLength(char *);
void  WriteMSGTMP(char *);

void ReadTagList();
void WriteTagList();
long FindTagEntry(QFile&);

bool NewUser(char *username);
bool CheckTrashCan(char *username);

QString ReplaceStringVars(char *);
QString StringVar(char *,int len);

void     MenuProcessor();
void     ExecuteMenuFunction(TpMenuItem *);

QString TranslateMenuText(char *s,BYTE color,BYTE highlight,bool prompt);

/*** Language Functions *************************************************************************/
void     KillLanguage();
bool     ReadLanguage(char *);
char     WaitLanguageHotkeys(char *hk,bool enter = TRUE);

/*** Logging Functions **************************************************************************/
inline void     LOG(char *s,...) { /*MessageBox(NULL,s,"Error",MB_OK);*/ }
inline void     LOG(int level,char *s,...) { /*MessageBox(NULL,s,"Error",MB_OK);*/ }


/*** Miscellaneous functions *********************************************************************/

int      Login();

char     ShowAnsiFile(char *data, char *hotkeys=NULL);

int      ReadNodeListEntry(NodeListEntry&,char *);
void     Delay(int);
void     CreateAreaList(QString param[],int numpara,QBitArray& arealist,bool msgareas = FALSE);
void     RemoveTag(char *name , int area);
bool     IsTagged(char *name , int area);

int      MatchFile(char *search,char *file);
int      MatchString(char *search,char *file);

bool     SelectProtocol(TpProtocol& p , char protocol_key = '\0' , bool seldef =  FALSE);

void     UpdateStatusBar();


/*** Message functions ***************************************************************************/

long     PostMessage(char *from,char *to,char *subj,int area,bool pvt);
long     PostNetmailMessage(char *from,char *to,char *subj,int area,int zone,int net,int node,int point,bool crash,bool attach,bool kill);

/*** I/O Functions *******************************************************************************/


void     Cls();

BYTE     Send(char *s,char *hk = NULL);
void     Send(BYTE c);

BYTE     SendFile(char *fn,char *hotkeys=NULL);

void     WaitKey(BYTE);
BYTE     WaitKeys(BYTE *);
inline char     WaitKeys(char *k)
   {
      return (char)WaitKeys((BYTE *)k);
   }

void     Input(char *buf,int max,BYTE mode=INPUT_ALL);
int      Input(int&,int len=5);
int      Input(long&,int len=7);
void     InputDate(QDate& date);

void     FlushOutput();
void     FlushInput();

void     DisableStop();
void     EnableStop();
int      LineCounter(int count=-1);

void     DrawField(int max);

QString FullColorString(BYTE);
void     FullColor(BYTE);
void     Color(BYTE);
int      Ask(int def=1);

void     ShowIntro();

class IO
   {
   public:
      IO& operator<<(char c)  { Send((BYTE)c); return (*this); }
      IO& operator<<(char *s) { Send(s      ); return (*this); }
   };


static IO io;

enum TTerminal { TTY, Ansi, Avatar };

inline TTerminal Terminal()
   {
      if(user.uFlags & UFLAG_AVATAR) return Avatar;
      if(user.uFlags & UFLAG_ANSI) return Ansi;
      return TTY;
   }

/*** Menu functions **************************************************************************/
int mGotoMenu            (char *data);
int mGosubMenu           (char *data);
int mPrevMenu            (char *data);
int mGotoMenuClear       (char *data);
int mLogoff              (char *data);
int mShowAnsiFile        (char *data);
int mShowAnsiFileAndWait (char *data);
int mRunPex              (char *data);
int mQuestionnaire       (char *data);
int mSelectLanguage      (char *data);
int mWriteMsg            (char *data);
int mChangeDateFormat    (char *data);
int mShell               (char *data);
int mChangeCity          (char *data);
int mChangeVoicePhone    (char *data);
int mChangeDataPhone     (char *data);
int mChangeFaxPhone      (char *data);
int mChangeState         (char *data);
int mChangeCountry       (char *data);
int mChangeAddress       (char *data);
int mChangeHandle        (char *data);
int mChangePassword      (char *data);
int mChangeScreenLines   (char *data);
int mToggleAnsi          (char *data);
int mToggleAvatar        (char *data);
int mToggleCls           (char *data);
int mTogglePause         (char *data);
int mToggleFsEd          (char *data);
int mToggleHotkeys       (char *data);
int mToggleIBM           (char *data);
int mListUsers           (char *data);
int mSelectMessageArea   (char *data);
int mEditTagList         (char *data);
int mReadMessages        (char *data);
int mListFiles           (char *data);
int mSelectFileArea      (char *data);
int mSelectMsgArea       (char *data);
int mSelectFileGroup     (char *data);
int mSelectMsgAreaGroup  (char *data);
int mSelectMsgArea       (char *data);
int mKeywordSearch       (char *data);
int mNewFileSearch       (char *data);
int mFileNameSearch      (char *data);
int mDownload            (char *data);
int mUpload              (char *data);

/*** Callback functions **********************************************************************/

extern void (*cbSend)(BYTE);
extern BYTE (*cbWaitKey)();
extern BYTE (*cbReadKey)();
extern BYTE (*cbCurrentAttribute)();

//void Send(BYTE c) { (*cbSend)(c); }
inline BYTE WaitKey()    { return (*cbWaitKey)(); }
inline BYTE ReadKey()    { return (*cbReadKey)(); }
inline BYTE CurrentAttribute() { return (*cbCurrentAttribute)(); }


#ifndef min
 #define min(a,b) (((a)>(b)) ? (b):(a))
 #define max(a,b) (((a)>(b)) ? (a):(b))
#endif

#endif
