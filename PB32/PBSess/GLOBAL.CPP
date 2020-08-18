#include "proboard.hpp"

TpConfig   cfg;
QFileName SysPath;
QFileName WorkPath;
TpUser     user;

TpTimer    timer;

QLinkedList<TpFilesIdx> TagList;
TpMsgBaseList msgbase;

TpMsgBase *squishMsgBase;
TpMsgBase *hudsonMsgBase;
TpMsgBase *jamMsgBase;

QDate LoginDate;
QTime LoginTime;

int  NumYells      = 0;
bool PasswordOk    = FALSE;
int  PastFirstUse  = 0;
int  TimeLimit     = 0;
int  TimeRemoved   = 0;

int  DownloadLimit = 0;
int  DownloadDelay = 0;
WORD FreeDownload  = 0;
WORD UploadNeeded  = 0;

int NumLimits      = 0;
TpLimit *Limit     = NULL;




int      (*menufunctions[200])(char *);
int      (*pMoreFunction)();


TpMenuStack MenuStack;
_TpLanguageString *lang;

TpLanguageFile   CurrentLanguage;
int              NumLanguageStrings;

long BaudRate;

int  LineCount;
bool StopEnabled;
bool OutputContinuous;
bool OutputStopped;

bool  NewFilesChecked = FALSE;
int   ShellReturnCode;

char *DateFormats[3] = {"MM/DD/YY","YY/MM/DD","DD/MM/YY" };
bool registered = FALSE;

QString (*pControlCodeHandler) (BYTE,BYTE,int width,QString::justification);
bool     (*pLineCountHandler  ) (int);

void (*cbSend)(BYTE);
BYTE (*cbWaitKey)();
BYTE (*cbReadKey)();
BYTE (*cbCurrentAttribute)();

