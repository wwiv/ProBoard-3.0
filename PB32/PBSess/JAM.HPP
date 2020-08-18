const DWORD JAM_SIGNATURE = 0x004D414ALU;

struct JamFileHeader
   {
      DWORD    signature;
      DWORD    dateCreated;
      DWORD    modCounter;
      DWORD    activeMsgs;
      DWORD    passWORDCrc;
      DWORD    baseMsgNum;
      BYTE     reserved[1000];
   };

struct JamHeader
   {
      DWORD    signature;
      WORD     revision;
      WORD     reserved;
      DWORD    subFieldLen;
      DWORD    timesRead;
      DWORD    msgidCrc;
      DWORD    replyCrc;
      DWORD    replyTo;
      DWORD    reply1St;
      DWORD    replyNext;
      DWORD    dateWritten;
      DWORD    dateReceived;
      DWORD    dateProcessed;
      DWORD    messageNumber;
      DWORD    attribute;
      DWORD    attribute2;
      DWORD    offset;
      DWORD    txtLen;
      DWORD    passWORDCrc;
      DWORD    cost;
   };

struct JamExtHeader
   {
      int      fromZone;
      int      fromNet;
      int      fromNode;
      int      fromPoint;
      int      toZone;
      int      toNet;
      int      toNode;
      int      toPoint;

      char     from[36];
      char     to[36];
      char     subject[72];
      char     pid[80];
   };

struct JamSubField
   {
      WORD     loId;
      WORD     hiId;
      DWORD    datLen;
   };

struct JamIndex
   {
      DWORD    crc32;
      DWORD    offset;
   };

struct JamLastRead
   {
      DWORD    userCrc;
      DWORD    userId;
      DWORD    lastReadMsg;
      DWORD    highReadMsg;
   };


const WORD JAMID_OADDRESS           =    0;
const WORD JAMID_DADDRESS           =    1;
const WORD JAMID_SENDERNAME         =    2;
const WORD JAMID_RECEIVERNAME       =    3;
const WORD JAMID_MSGID              =    4;
const WORD JAMID_REPLYID            =    5;
const WORD JAMID_SUBJECT            =    6;
const WORD JAMID_PID                =    7;
const WORD JAMID_TRACE              =    8;
const WORD JAMID_ENCLOSEDFILE       =    9;
const WORD JAMID_ENCLOSEDFILEWALIAS =   10;
const WORD JAMID_ENCLOSEDFREQ       =   11;
const WORD JAMID_ENCLOSEDFILEWCARD  =   12;
const WORD JAMID_ENCLOSEDINDIRECTFILE=  13;
const WORD JAMID_EMBINDAT           = 1000;
const WORD JAMID_FTSKLUDGE          = 2000;
const WORD JAMID_SEENBY2D           = 2001;
const WORD JAMID_PATH2D             = 2002;
const WORD JAMID_FLAGS              = 2003;
const WORD JAMID_TZUTCINFO          = 2004;


const DWORD JAM_MSG_LOCAL           = 0x00000001L;
const DWORD JAM_MSG_INTRANSIT       = 0x00000002L;
const DWORD JAM_MSG_PRIVATE         = 0x00000004L;
const DWORD JAM_MSG_READ            = 0x00000008L;
const DWORD JAM_MSG_SENT            = 0x00000010L;
const DWORD JAM_MSG_KILLSENT        = 0x00000020L;
const DWORD JAM_MSG_ARCHIVESENT     = 0x00000040L;
const DWORD JAM_MSG_HOLD            = 0x00000080L;
const DWORD JAM_MSG_CRASH           = 0x00000100L;
const DWORD JAM_MSG_IMMEDIATE       = 0x00000200L;
const DWORD JAM_MSG_DIRECT          = 0x00000400L;
const DWORD JAM_MSG_GATE            = 0x00000800L;
const DWORD JAM_MSG_FILEREQUEST     = 0x00001000L;
const DWORD JAM_MSG_FILEATTACH      = 0x00002000L;
const DWORD JAM_MSG_TRUNCFILE       = 0x00004000L;
const DWORD JAM_MSG_KILLFILE        = 0x00008000L;
const DWORD JAM_MSG_RECEIPTREQ      = 0x00010000L;
const DWORD JAM_MSG_CONFIRMREQ      = 0x00020000L;
const DWORD JAM_MSG_ORPHAN          = 0x00040000L;
const DWORD JAM_MSG_ENCRYPT         = 0x00080000L;
const DWORD JAM_MSG_COMPRESS        = 0x00100000L;
const DWORD JAM_MSG_ESCAPED         = 0x00200000L;
const DWORD JAM_MSG_FPU             = 0x00400000L;
const DWORD JAM_MSG_TYPELOCAL       = 0x00800000L;
const DWORD JAM_MSG_TYPEECHO        = 0x01000000L;
const DWORD JAM_MSG_TYPENET         = 0x02000000L;
const DWORD JAM_MSG_NODISP          = 0x20000000L;
const DWORD JAM_MSG_LOCKED          = 0x40000000L;
const DWORD JAM_MSG_DELETED         = 0x80000000L;
