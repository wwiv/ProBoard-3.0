#include <pblib.hpp>


#ifndef MSGAPI
  class SQMSG;
#endif

class TpMessage;
class TpMsgBase;
//class TpSquishMsgBase;
class TpHudsonMsgBase;
class TpJamMsgBase;
class TpMsgArea;
class TpMessageIndex;

struct HudsonMsgIdx;
struct HudsonMsgHdr;
struct HudsonMsgToIdx;
struct HudsonMsgInfo;

struct JamFileHeader;
struct JamHeader;
struct JamExtHeader;
struct JamIndex;
struct JamLastRead;

class TpMsgBase
  {
 public:

   virtual ~TpMsgBase() {}

   virtual bool open()   = 0;
   virtual void close()  = 0;

   virtual bool lock()   { return TRUE; }
   virtual bool unlock() { return TRUE; }

   virtual long readMsg(TpMessage& msg , long num)                                = 0;
   virtual unsigned readMsgText(TpMessage& msg, char *text, long offset , unsigned size)  = 0;
   virtual unsigned scanMail(TpMessageIndex *mi,unsigned maxmsgs)                         = 0;
   virtual long appendMsg(TpMessage&)                                             = 0;
   virtual bool updateMsg(TpMessage&)                                             = 0;

   virtual long highMsg(TpMsgArea&)                                               = 0;
   virtual long lowMsg (TpMsgArea&)                                               = 0;
   virtual long numMsgs(TpMsgArea&)                                               = 0;
   virtual long totalMsgs()                                                     = 0;

   virtual bool deleteMsg(TpMessage&)                                             = 0;

   virtual long lastRead(TpMsgArea&)                                     = 0;
   virtual void setLastRead(TpMsgArea&,long num)                         = 0;

   virtual long msgNum(TpMsgArea&,long id)                                        = 0;
   virtual long msgId (TpMsgArea&,long num)                                       = 0;
  };

/*
class TpSquishMsgBase : public TpMsgBase
  {
   SQMSG *lastarea;
   int lastareanum;

   SQMSG *readArea(TpMsgArea&);
 public:
   TpSquishMsgBase() { open(); }
   ~TpSquishMsgBase()  { close(); }

   bool open();
   void close();

   bool lock()   { return TRUE; }
   bool unlock() { return TRUE; }

   long readMsg(TpMessage& msg , long num);
   unsigned readMsgText(TpMessage& msg, char *text, long offset , unsigned size);
   unsigned scanMail(TpMessageIndex *mi,unsigned maxmsgs);
   long appendMsg(TpMessage&);
   bool updateMsg(TpMessage&);

   long highMsg(TpMsgArea&);
   long lowMsg (TpMsgArea&);
   long numMsgs(TpMsgArea&);
   long totalMsgs() { return 0; }

   bool deleteMsg(TpMessage&);

   long lastRead(TpMsgArea&);
   void setLastRead(TpMsgArea&,long num);

   long msgNum(TpMsgArea&,long id);
   long msgId (TpMsgArea&,long num);
  };
*/

class TpHudsonMsgBase : public TpMsgBase
  {
   QFile f_msghdr;
   QFile f_msgtxt;
   QFile f_msgtoidx;
   QFile f_msgidx;
   QFile f_msginfo;

   HudsonMsgIdx *lastMsgIdx;
   int          *highArray;
   int          *lastReadArray;
   long lastIndex;
   long lastReadRecord;
   ///////////////////

   void flushCache();
   void readHighArray();
   void readLastRead(long record);

   void readInfo(HudsonMsgInfo&);
   void writeInfo(HudsonMsgInfo&);

   long findIdx(HudsonMsgIdx &mi,int num,int area,int order);

 public:
   TpHudsonMsgBase();
   ~TpHudsonMsgBase();

   bool open();
   void close();

   bool lock();
   bool unlock();

   long readMsg(TpMessage& msg , long num);
   unsigned readMsgText(TpMessage& msg, char *text, long offset , unsigned size);
   unsigned scanMail(TpMessageIndex *mi,unsigned maxmsgs);
   long appendMsg(TpMessage&);
   bool updateMsg(TpMessage&);

   long highMsg(TpMsgArea&);
   long lowMsg (TpMsgArea&);
   long numMsgs(TpMsgArea&);
   long totalMsgs();

   bool deleteMsg(TpMessage&);

   long lastRead(TpMsgArea&);
   void setLastRead(TpMsgArea&,long num);

   long msgNum(TpMsgArea&,long id);
   long msgId(TpMsgArea& ma, long num);
  };

class TpJamMsgBase : public TpMsgBase
  {
   QFile f_jhr;
   QFile f_jdt;
   QFile f_jdx;
   QFile f_jlr;

   int            lastAreaNum;
   JamFileHeader *jamHeader;

   bool      openArea( TpMsgArea& );

   bool      jamLock();
   bool      jamUnLock();

   bool      readHeader();
   bool      writeHeader();

   long      findIdx( JamIndex &mi,long num,int order );

 public:
   TpJamMsgBase();
   ~TpJamMsgBase();

   bool open();
   void close();

   bool lock()    { return TRUE; }
   bool unlock()  { return TRUE; }

   long readMsg(TpMessage& msg , long num);
   unsigned readMsgText(TpMessage& msg, char *text, long offset , unsigned size);
   unsigned scanMail(TpMessageIndex *mi,unsigned maxmsgs);
   long appendMsg(TpMessage&);
   bool updateMsg(TpMessage&);

   long highMsg(TpMsgArea&);
   long lowMsg (TpMsgArea&);
   long numMsgs(TpMsgArea&);
   long totalMsgs()
      {
         return 0;
      }

   bool deleteMsg(TpMessage&);

   long lastRead(TpMsgArea&);
   void setLastRead(TpMsgArea&,long num);

   long msgNum(TpMsgArea&,long id);
   long msgId (TpMsgArea&,long num);
  };


class TpMsgBaseList
  {
   TpMsgBase *mblist[5];
  public:
    TpMsgBaseList();
   ~TpMsgBaseList();

   void add(TpMsgBase *);

   void close();
   void open();
   bool lock();
   bool unlock();

   unsigned scanMail(TpMessageIndex *,unsigned maxmsgs,_TpUser&);
   long totalMsgs();
  };


class TpMsgArea : public _TpMsgArea
  {
   QFile f;

   void open();

   int numAreas;
 public:

   TpMsgBase *MsgBase();

   bool read(int);
   bool sysopAccess();

   void close();
   static int  highAreaNum();

   long numMsgs()
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->numMsgs(*this);
      }
   long lowMsg()
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->lowMsg (*this);
      }
   long highMsg()
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->highMsg(*this);
      }
   long lastRead()
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->lastRead(*this);
      }
   void setLastRead(long num)
      {
         TpMsgBase *msgBase = MsgBase();

         if(msgBase)
            msgBase->setLastRead(*this,num);
      }
   long msgNum(long id)
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->msgNum(*this,id);
      }
   long msgId (long num)
      {
         TpMsgBase *msgBase = MsgBase();

         return (msgBase==NULL) ? 0L : msgBase->msgId(*this,num);
      }
  };


const DWORD MSGATTR_PRIVATE     = 0x00000001L;
const DWORD MSGATTR_RECEIVED    = 0x00000002L;
const DWORD MSGATTR_DELETED     = 0x00000004L;
const DWORD MSGATTR_NETMAIL     = 0x00000008L;
const DWORD MSGATTR_UNSENT_ECHO = 0x00000010L;
const DWORD MSGATTR_UNSENT_NET  = 0x00000020L;
const DWORD MSGATTR_LOCAL       = 0x00000040L;
const DWORD MSGATTR_KILL        = 0x00000080L;
const DWORD MSGATTR_CRASH       = 0x00000100L;
const DWORD MSGATTR_SENT        = 0x00000200L;
const DWORD MSGATTR_FILE        = 0x00000400L;
const DWORD MSGATTR_FILEREQ     = 0x00000800L;
const DWORD MSGATTR_AUDITREQ    = 0x00001000L;
const DWORD MSGATTR_RECEIPTREQ  = 0x00002000L;
const DWORD MSGATTR_TRANSIT     = 0x00004000L;
const DWORD MSGATTR_HOLD        = 0x00008000L;
const DWORD MSGATTR_IMMEDIATE   = 0x00010000L;
const DWORD MSGATTR_DIRECT      = 0x00020000L;
const DWORD MSGATTR_TRUNCFILE   = 0x00040000L;
const DWORD MSGATTR_DELFILE     = 0x00080000L;
const DWORD MSGATTR_ORPHAN      = 0x00100000L;
const DWORD MSGATTR_ECHOMAIL    = 0x00200000L;
const DWORD MSGATTR_NODISP      = 0x00400000L;
const DWORD MSGATTR_LOCKED      = 0x00800000L;


class TpMessage
  {
  public:
   long  num;
   DWORD id;  // for Squish only, others -> == num

   char  from[36];
   char  to  [36];
   char  subj[66];

   DWORD attr;

   QDate  postDate;
   QTime  postTime;
   QDate  recvDate;
   QTime  recvTime;

   long  next;
   long  prev;

   int   origZone,
         origNet,
         origNode,
         origPoint;

   int   destZone,
         destNet,
         destNode,
         destPoint;

   int   cost;

   /************************************************************/

   static long lastIndex;

   union {
          TpMsgArea *msgArea;
          int area;
         };

   TpMessage(int area = 0);
   TpMessage(TpMessage *, int area = 0);

   ~TpMessage();

   int areaNum() ;

   TpMsgBase *msgBase()
     {
      return msgArea->MsgBase();
     }

   void clear();

   bool setArea  (int num);
   bool read     (long num, int area = 0);
   bool readFirst(int method,int order,long first,char *data,int area = 0);
   bool readNext (int method,int order,char *data);
   bool readPrev (int method,int order,char *data);

   unsigned readText(char *text,long offset,unsigned size)
     {
      return msgBase()->readMsgText(*this, text, offset , size);
     }

   void createMsgTextFile(char *fname , bool append);
   void createMsgTextString(char *string , unsigned maxsize);
   void exportMsg(char *fname);
   void forward();
   void move();

   void setFlag   (DWORD msgflag);
   void clearFlag (DWORD msgflag);
   void toggleFlag(DWORD msgflag);

   bool testFlag (DWORD msgflag) { return (attr & msgflag) ? TRUE:false; }

   void operator=(HudsonMsgHdr&);

   void addReply(TpMessage&);
   void delReply();
   void remove();

   BYTE show();
   void addOrigin();
   int  pointNum(int mode);
   long add();

   long msgNum() { return msgBase()->msgNum(*msgArea,id); }

   bool readAccess();
  };

class TpMessageIndex
  {
  public:
   TpMessageIndex() {}
   TpMessageIndex(int a,long n) { area = a; num = n; }

   int  area;
   long num;
  };

class TpMarkedMsgList
  {
   TpMessageIndex *msgList;
   int n;
  public:
   TpMarkedMsgList();
   TpMarkedMsgList(const TpMarkedMsgList&);
   ~TpMarkedMsgList();

   void operator=(const TpMarkedMsgList&);

   bool add(TpMessageIndex&);
   bool add(TpMessage&);
   void clear() { n = 0; }
   bool remove(TpMessageIndex&);
   void sort();
   int  numMarked() { return n; }
   bool isMarked(TpMessageIndex&);
   TpMessageIndex getMarked(int n)  { return msgList[n]; }
   TpMessageIndex operator[](int n) { return msgList[n]; }
  };


struct TpAKA
  {
      short zone;
      short net;
      short node;
      short point;

      bool read(int n);
  };


const int MAX_MARKED_MSGS = 500;

extern TpMsgBase       *squishMsgBase;
extern TpMsgBase       *hudsonMsgBase;
extern TpMsgBase       *jamMsgBase;
extern TpMsgBaseList    msgbase;
extern TpMarkedMsgList  markedmsglist;

void GetNewMsgs(TpMarkedMsgList& marked,int area);


inline long
TpHudsonMsgBase::msgNum(TpMsgArea&,long id)
{
   return id;
}

inline long
TpHudsonMsgBase::msgId(TpMsgArea&, long num)
{
   return num;
}



#define READMSG_ALL 1
#define READMSG_FWD 1
#define READMSG_REV 2
#define READMSG_SEL 3
#define READMSG_SEARCH 4
#define READMSG_NEW 5
#define READMSG_INDIV 6
#define READMSG_MARKED 7
