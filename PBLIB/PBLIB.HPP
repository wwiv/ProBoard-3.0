#ifndef __PBLIB_HPP
#define __PBLIB_HPP

#include <tslib.hpp>

#undef enable
#undef disable

#define DLLCLASS
/*
#ifdef _BUILDING_DLL
#define DLLCLASS __declspec( dllexport )
#else
#define DLLCLASS __declspec( dllimport )
#endif
*/

typedef unsigned char AskType;

class DLLCLASS TpAccessFlags
  {
   DWORD v;
 public:
   TpAccessFlags() { clearall(); }
   void clearall() { v=0L; }
   bool getflag(int flagnr);
   void setflag(int flagnr);
   void clearflag(int flagnr);
   void flagstostr(char *str);

        operator DWORD (              )  {  return(v);  }
   void operator =     (  DWORD flags )  {  v = flags;  }
  };

class DLLCLASS TpCombinedType
  {
   BYTE bits[125];
 public:
   TpCombinedType();
   bool connected(int brdnr);
   void connect(int brdnr);
   void disconnect(int brdnr);
   void toggle(int brdnr);
  };

struct DLLCLASS TpTimeFrame
  {
    BYTE periods[7][6];                 // 7x48 periods of 1/2 hour = one week

    TpTimeFrame();

    void clear();
    void setAll();

    bool enabled()                   const;
    bool enabled(QTime&)              const;
    bool enabled(QDate&,QTime&)        const;
    bool enabled(int dow,QTime&)      const;
    bool enabled(int dow,int period) const;

    void enable(int dow,QTime&);
    void enable(int dow,int period);
    void disable(int dow,QTime&);
    void disable(int dow,int period);
  };

struct DLLCLASS TpAccessRecord
  {
//    AccessRecord();

    WORD         minLevel;              // 0 =           don't care
    WORD         maxLevel;              // 0 =           don't care
    TpAccessFlags  flags;                 // All off =     don't care
    TpAccessFlags  flagsNot;              // All off =     don't care
    BYTE         minAge;                // 0 =           don't care
    BYTE         maxAge;                // 0 =           don't care
    BYTE         sex;                   // 0 =           don't care
    WORD         minTimeLeft;           // 0 =           don't care
    WORD         minTimeOnline;         // 0 =           don't care
    TpTimeFrame    timeFrame;             // All on =      don't care
    BYTE         terminals;             // 0xFF =        don't care
    DWORD        minSpeed;              // 0 =           don't care
    DWORD        maxSpeed;              // 0 =           don't care

    BYTE         nodes[32];             // All 0 or all 0xFF = all nodes

    BYTE         extra[18];             // Extra space
  };


struct DLLCLASS _TpUserIdx
   {
      DWORD nameCrc;
      DWORD aliasCrc;
   };

struct DLLCLASS _TpUser
   {
   private:
      static      QString     sysDir;
      static      QString     lastSearchSpec;
      static      bool       lastSearchAlias;
      static      bool       lastSearchExact;
      static      bool       lastSearchFuzzy;
      static      long       lastSearchRecord;

      bool        Search     ();

   public:
                  _TpUser      ();

      static void SetDir     ( char *dir )
         {
            sysDir = dir;
         }

      static long   NumUsers();
      static QString FindAlias(char *name);

      bool         Read       ( long recno );
      bool         Write      ( bool append );
      bool         Search     ( char *name , bool exact = true , bool fuzzy = false , bool alias = false);
      bool         SearchNext ();

      void         NewUser    ();

      QString     FirstName  ();

      bool         CheckAccess(WORD,TpAccessFlags);
      bool         CheckAccess(WORD,TpAccessFlags,TpAccessFlags);

    //----------------------

    long         record;                // Record number in USERS.BBS

    char         name[36];              // User name
    char         alias[36];             // Alias/Handle
    char         passWord[16];          // Password
    DWORD        passWordCRC;
    WORD         level;                 // Security level
    char         country[26];           // Country
    char         state[26];             // State
    char         city[26];              // City
    char         company[51];           // Company

    char         address1[51];          // Address line 1
    char         address2[51];          // Address line 2
    char         address3[51];          // Address line 3

    char         comment[81];           // Comment
    char         forwardTo[36];         // Forward mail to

    QDate        birthDate;             // Birthday

    char         voicePhone[16];        // Voice phone #
    char         dataPhone [16];        // Data phone #
    char         faxPhone  [16];        // Fax phone #

    BYTE         sex;                   // 0 = Unknown, 1 = Male, 2 = Female
    BYTE         dateFormat;            // Date Format
    BYTE         defaultProtocol;       // Default protocol hotkey
    char         language[9];           // Language
    WORD         screenWidth;           // Screen Width
    WORD         screenLength;          // # of lines

    long         timeUsed;              // time used today

    DWORD        timesCalled;           // # times called
    DWORD        numDownloads;          // # downloads
    DWORD        kbDownloaded;          // K downloaded
    DWORD        numUploads;            // # downloads
    DWORD        kbUploaded;            // K downloaded
    DWORD        msgsPosted;            // # messages posted

    QDate        lastDate;              // Date last called
    QTime        lastTime;              // Time last called
    QDate        lastPwdChange;         // Date of last password change
    QDate        lastNewFilesCheck;     // Date of last check for new files

    TpAccessFlags  aFlags;                // Access flags       (A-Z,1-6)
    DWORD        uFlags;                // Flags (DELETED/ANSI/PAUSE/...)
    WORD         logLevel;              // Log level of user

    TpCombinedType mailCheckBoards;       // Msg areas to check for mail
    TpCombinedType combinedBoards;        // Areas to be used in combined mode

    DWORD        totalTimeUsed;         // Total time used (minutes)

    QDate        expDate;               // Expiration date
    WORD         expLevel;              // Fallback level after expiration
    TpAccessFlags  expFlagsOn;            // Flags to be enabled after expiration
    TpAccessFlags  expFlagsOff;           // Flags to be disabled after expiration

    QDate        firstDate;             // Date of first login
    long         kbToday;               // K downloaded today
    long         credit;                // Netmail credit
    long         pending;               // Netmail credit pending
    WORD         fileArea;              // Last file area accessed
    WORD         msgArea;               // Last msg area accessed

    short        tbTimeBalance;         // Time balance           (Time Bank)
    short        tbKbBalance;           // Kbyte balance          (Time Bank)
    short        tbTimeWithdrawn;       // Time withdrawn today   (Time Bank)
    short        tbKbWithdrawn;         // Kbytes withdrawn today (Time Bank)
    WORD         tbTimeDeposited;
    WORD         tbKbDeposited;
    WORD         tbTimeLoaned;
    WORD         tbKbLoaned;
    QDate        tbLastUsed;            // Date last used         (Time Bank)

    AskType      checkMail;             // Check for mail at logon
    AskType      checkNewFiles;         // Check for new files at logon

    DWORD        highMsgRead;

    WORD         qwkMaxMsgsPerArea;
    WORD         qwkMaxMsgs;
    BYTE         qwkArchiver;
    BYTE         ripFont;

    QDate        tbTimePayback;
    QDate        tbKbPayback;

    WORD         fileGroup;              // Last file area accessed
    WORD         msgGroup;               // Last msg area accessed

    BYTE         extra[390];
  };

struct DLLCLASS _TpConfig
  {
   char        shellMsg[81];         // Message to show when shelling
   char        sysopName[36];        // Name of sysop
   char        txtPath[61];          // Path for textfiles
   char        mnuPath[61];          // Path for menu-files
   char        msgPath[61];          // Path for message base
   char        uploadPath[61];       // Uploadpath
   char        editorName[61];       // Name of external editor
   WORD        newUserLevel;         // Level for new user
   short       newUserLogLevel;       // Loglevel for new user
   TpAccessFlags newUserFlags;  // New user flags
   short       maxPasswordInput;         // Maximum attempts for password entry
   WORD        minPasswordLength;        // Minimum password length
   short       inactivityTime;       // Inactivity time-out limit
   short       maxSysopPages;       // Maximum times sysop can be paged
   short       pageBellLength;       // Length of page-bell (secs)
   short       mailCheck;             // Check for mail at logon?
   short       europeanDate;                // European date format?
   short       numNodes;              // # nodes
   BYTE        allowAnsi;             // Allow ANSI?
   BYTE        allowAvatar;           // Allow AVATAR?
   short       discrete;              // Hide sysop activity?
   short       askVoicePhone;         // Ask for phone number?
   short       allowOneWordNames;          // Allow one-word names
   WORD        crashLevel;            // Level needed for crashmail
   TpAccessFlags crashFlags;            // Flags needed for crashmail
   WORD        attachLevel;           // Level needed for file attach
   TpAccessFlags attachFlags;           // Flags needed for file attach
   short       allowMsgUpload;        // Allow message uploads
   short       allowStacking;         // Allow command stacking
   QTime       pageStart;            // Paging hours start
   QTime       pageEnd;              // Paging hours end
   short       handshaking;           // I/O Handshaking
   short       allowAlias;            // Allow alias for login
   short       logLocal;              // Log local calls
   short       doswap;                // Allow swapping
   char        originLine[61];        // Origin line
   char        nodeListDir[61];       // Nodelist directory
   char        sysopKeys[10][60];     // Sysop hotkeys
   QTime       dlStart;              // Download hours start
   QTime       dlEnd;                // Download hours end
   short       minUploadSpace;           // Space needed for uploads
   char        pvtUploadPath[61];     // Directory for files uploads
   char        quoteString[6];        // String used for quoting
   short       fastMode;              // Use fast mode
   BYTE        killSent;              // Kill netmail after sent
   BYTE        multiLine;             // Use message base sharing?
   BYTE        egaMode;               // Use 43/50 line mode
   BYTE        showUserInfo;          // Show user info while in EGA mode?
   char        pexPath[61];           // Directory for PEX files
   BYTE        allowQuickLogin;       // Allow quick sysop login?
   BYTE        suspendMsgTime;        // Suspend time when writing msgs
   short       securityBoard;         // MsgBoard for security messages
   short       pwdMessages;           // Write security-messages?
   char        bbsName[36];           // Name of the BBS
   char        pwdChar;               // Password character
   short       tbMaxTimeDeposit;
   short       tbMaxKbDeposit;
   short       tbMaxTimeWithdrawal;
   short       tbMaxKbWithdrawal;
   short       usageDays;            // Days to keep usage graphs
   char        systemPassword[16];
   BYTE        useSystemPassword;
   BYTE        askBirthDay;
   short       binlogDays;
   BYTE        binlogLocal;
   short       pageArea;
   BYTE        indexFiles;
   BYTE        checkDupes;
   BYTE        killDupes;
   BYTE        ignoreDupeExt;
   char        ripPath[61];          // Path for RIP scripts
   char        ripIconsPath[61];
   char        location[36];
   char        phone[26];
   char        QWKid[9];
   WORD        IObuffersize;
   TpTimeFrame pagingHours;
   char        defaultLanguage[9];
   BYTE        addUploaderName;
   TpTimeFrame downloadHours;
   BYTE        askDataPhone;
   BYTE        askFaxPhone;
   BYTE        askAddress;
   BYTE        askSex;
   BYTE        askDateFormat;
   BYTE        askState;
   BYTE        askCountry;
   short       fuzzyRate;
   BYTE        hidePassword;
   BYTE        valConfirm;

   char        dateStampSignature[10];
   QDate       dateStamp;
   DWORD       dateStampCrc;

   char        extChat[81];
   char        virScanCommand[61];
   BYTE        virScanType;
   char        virScanSemaphore[13];

   BYTE        listColorTag;
   BYTE        listColorFileName;
   BYTE        listColorSize;
   BYTE        listColorDate;
   BYTE        listColorCounter;
   BYTE        listColorDesc;
   BYTE        listColorSeperator;
   BYTE        listColorMissing;

   BYTE        hideFileCounter;

   BYTE        disableRIP;

   char        extMultiChat[81];

   BYTE        virScanFailedAction;
   WORD        virScanFailedArea;

   BYTE        promptColor;

   BYTE        internalFsed;

   char        extra[2003];
  };


const BYTE VIRSCAN_ACTION_NONE   = 0;
const BYTE VIRSCAN_ACTION_MOVE   = 1;
const BYTE VIRSCAN_ACTION_DELETE = 2;

struct DLLCLASS TpLanguageFile
   {
      char name[41];
      BYTE avail;
      WORD level;
      TpAccessFlags flags;
      char menuPath[61];
      char txtPath[61];
      char questPath[61];
      char copyright[81];
      BYTE attrib;
      BYTE extra[500];
   };

const BYTE LANG_PROMPT  = 0x01;
const BYTE LANG_NOCOLOR = 0x02;

struct DLLCLASS _TpLanguageString
  {
   WORD len;               // Length of string (excl. terminating '\0')
   WORD numHotkeys;        // # Hotkeys defined
   BYTE color;             // Main color
   BYTE highlight;         // Highlight color
   BYTE promptcolor;       // Prompt color
   BYTE flags;             // Prompt/NoColor
   char *s;                // Actual string
   char *hotkeys;          // List of hotkeys

   _TpLanguageString();
   _TpLanguageString( const _TpLanguageString& );
   _TpLanguageString( char *s , char *hotkeys , BYTE color , BYTE highlight , BYTE flags = 0x00, BYTE promptcolor = 0x00);

  ~_TpLanguageString();

   bool read( QFile& );
   bool write( QFile& );
   void operator=( const _TpLanguageString& );
   void clear();
  };



struct DLLCLASS _TpMenuFile
   {
      DWORD attr;   // bit 0 = RIP menu
      char prompt[200];
      BYTE color;
      BYTE highlight;
      char RIPname[9];
      BYTE extra[100];
   };

const DWORD MENU_PASSWORD       = 8;

struct DLLCLASS _TpMenuItem
   {
      DWORD attr;
      char text[160];
      char data[160];
      BYTE color;
      BYTE hotKey;
      WORD function;
      char password[16];

      TpAccessRecord access;

      BYTE extra[50];
   };


struct _TpFilesIdx
  {
   char name[13];
   WORD area;
  };

struct _TpAreaGroup
  {
   char        name[80];
   WORD        level;
   TpAccessFlags flags;
   TpAccessFlags flagsNot;
   BYTE        extra[10];
  };

struct _TpFileArea
  {
   char name[80];        // Name of file area
   char listPath[80];    // Path for file-list
   char filePath[80];    // Path for files
   WORD level;           // Access level
   TpAccessFlags flags;    // Access flags
   BYTE cdrom;           // 1 = CDROM File listing type
   WORD maxFiles;         // Max files per day in this area downloadable
   WORD maxKb;            // Max KBYTEs per day in this area
   BYTE noTops;          // TRUE if not to appear in TOPFILES.A??
   BYTE free;            // TRUE if area is free
   BYTE groups[4];       // Groups belonging to
   BYTE allGroups;       // Belongs to all groups
   BYTE minAge;          // Minimum age
   TpAccessFlags flagsNot; // Access flags
   BYTE dateFormat;
   BYTE extra[2];
  };

#define MSG_BOTH  0
#define MSG_PVT   1
#define MSG_PUB   2
#define MSG_TOALL 3

#define MSG_LOCAL   0
#define MSG_NET     1
#define MSG_ECHO    2
#define MSG_PVTECHO 3

const BYTE MSGBASE_HUDSON = 0;
const BYTE MSGBASE_SQUISH = 1;
const BYTE MSGBASE_SDM    = 2;
const BYTE MSGBASE_JAM    = 3;

struct _TpMsgArea
  {
   WORD areaNum;              // Area number                                       0
   WORD hudsonBase;           // Hudson area number                                2
   char name[81];             // Name of message areas                             4
   BYTE msgType;              // Type of message (Net/Echo/Local)                 85
   BYTE msgKind;              // Kind of message (Private only/Public only/...)   86
   BYTE msgBaseType;          // Type of message base                             87
   char path[81];             // Path to Squish or *.MSG                          88
   BYTE flags;                // Alias allowed/forced/prohibited                 169
   WORD readLevel;            // Minimum level needed to read msgs               170
   TpAccessFlags readFlags;     // flags needed to read msgs                       172
   TpAccessFlags readFlagsNot;  // flags non-grata to read msgs                    176
   WORD writeLevel;           // Minimum level needed to write msgs              180
   TpAccessFlags writeFlags;    // flags needed to write msgs                      182
   TpAccessFlags writeFlagsNot; // flags non-grata to write msgs                   186
   WORD sysopLevel;           // Minimum level needed to change msgs             190
   TpAccessFlags sysopFlags;    // flags needed to change msgs                     192
   TpAccessFlags sysopFlagsNot; // flags non-grata to change msgs                  196

   char origin[62];           // Origin line                                     200
   WORD aka;                  // AKA #                                           262

   WORD rcvKillDays;          //                                                 264
   WORD msgKillDays;          //                                                 266
   WORD maxMsgs;              //                                                 268

   char sysop[36];            //                                                 270
   WORD replyBoard;           //                                                 306

   char tag[61];              // EchoMail Tag Name                               308
   char qwkname[13];          // QWK Area Name                                   369

   BYTE groups[4];            // Groups belonging to                             382
   BYTE allGroups;            // Belongs to all groups                           386
   BYTE minAge;               // Minimum age for this area                       387

   BYTE extra[112] ;          //                                                 388
  };

struct _TpProtocol
{
   char  Name[50];          // Name of protocol
   char  Key;               // Hotkey for Protocol
   char  Flags;             // Protocol behavior
   char  LogFile[60];       // Logfile from protocol
   char  CtlFile[60];       // Control file (redirection file)
   char  DLCommand[126];    // Download command line
   WORD  Efficiency;        // Throughput efficiency
   char  ULCommand[128];    // Upload command line
   char  DLString[80];      // String to place in download control file
   char  ULString[80];      // String to place in upload control file
   char  DLKeyWord[40];     // Download keyWORD to search for in logfile
   char  ULKeyWord[40];     // Upload keyWORD to search for in logfile
   short WordNr;            // File name WORD nr after keyWORD (1-..)
};


const DWORD PVTFILE_KEEP = 0x00000001uL;

struct _TpPrivateFile
   {
      QDate date;
      char fname  [80];
      char to     [36];
      char from   [36];
      char desc   [80];

      DWORD attr;

      BYTE extra  [61];
   };


struct _TpLimit
  {
      WORD     level;
      WORD     timeLimit;
      WORD     dailyDownloadLimit;
      WORD     preDownloadDelay;
      char     id[50];
      WORD     freeKb;              // Free upload in Kb.
      BYTE     factor;            // Percentage upload required
      WORD     maxDownload;      // Max download for this level
      WORD     fallTo;            // Fall to level x when max. reached
      WORD     msgFactor;         // # KBYTEs granted per message written
      WORD     sessionLimit;      // Time limit per session

      BYTE     extra[100];
  };

const DWORD UFLAG_DELETED   = 0x00000001L; //  0 // User deleted
const DWORD UFLAG_ANSI      = 0x00000002L; //  1 // ANSI mode ON
const DWORD UFLAG_PAUSE     = 0x00000004L; //  2 // Pause mode ON
const DWORD UFLAG_CLEAR     = 0x00000008L; //  3 // Screenclear mode ON
const DWORD UFLAG_HOTKEYS   = 0x00000010L; //  4 // Hotkeys?
const DWORD UFLAG_NOIBM     = 0x00000020L; //  5 // User has no IBM-graphics
const DWORD UFLAG_FSED      = 0x00000040L; //  6 // Fullscreen editor used
const DWORD UFLAG_NOKILL    = 0x00000080L; //  7 // Do not kill user
const DWORD UFLAG_IGNORE    = 0x00000100L; //  8 // Ignore DL-hours
const DWORD UFLAG_ATTEN     = 0x00000200L; //  9 // Attention flag
const DWORD UFLAG_NOTOPS    = 0x00000400L; // 10 // Don't appear in tops
const DWORD UFLAG_HIDDEN    = 0x00000800L; // 11 // Hide from lists
const DWORD UFLAG_QUIET     = 0x00001000L; // 12 // Quiet??
const DWORD UFLAG_AVATAR    = 0x00002000L; // 13 // AVT/0 codes
const DWORD UFLAG_AVTPLUS   = 0x00004000L; // 14 // AVT/0+ codes
const DWORD UFLAG_GUEST     = 0x00008000L; // 15 // Guest account
const DWORD UFLAG_PAGEPRI   = 0x00010000L; // 16 // Page priority
const DWORD UFLAG_LOCALONLY = 0x00020000L; // 17 // Local login only
const DWORD UFLAG_MULTILOGIN= 0x00040000L; // 18 // Allow multiple login
const DWORD UFLAG_FREECHAT  = 0x00080000L; // 19 // Freeze timer in chat
const DWORD UFLAG_NORIP     = 0x00100000L; // 20 // Disable RIP

const BYTE  SEX_UNKNOWN     = 0;
const BYTE  SEX_MALE        = 1;
const BYTE  SEX_FEMALE      = 2;


#endif
   
