#ifndef TSLIB_HPP
#define TSLIB_HPP

#if defined (_DEBUG) 
    #pragma comment(lib,"tslib_d.lib") 
#else 
    #pragma comment(lib,"tslib_r.lib") 
#endif 


#define NULL 0
#define NULLFUNC 0

#ifndef _INC_WINDOWS
   typedef unsigned char  BYTE;
   typedef unsigned short WORD;
   typedef unsigned long  DWORD;
#endif

class QString;


inline bool
TESTBIT(BYTE val,int bit)
{
   return (bool)!!(val & (1<<bit));
}

inline bool
TESTBIT(char val,int bit)
{
   return (bool)!!(val & (1<<bit));
}

inline bool
TESTBIT(WORD val,int bit)
{
   return (bool)!!(val & (1<<bit));
}

inline bool
TESTBIT(int val,int bit)
{
   return (bool)!!(val & (1<<bit));
}

inline bool
TESTBIT(DWORD val,int bit)
{
   return (bool)!!(val & (1L<<bit));
}

inline bool
TESTBIT(long val,int bit)
{
   return (bool)!!(val & (1L<<bit));
}

inline void
SETBIT(WORD& val,int bit)
{
   val |= WORD(1<<bit);
}

inline void
SETBIT(int& val,int bit)
{
   val |= int(1<<bit);
}

inline void
SETBIT(DWORD& val,int bit)
{
   val |= DWORD(1L<<bit);
}

inline void
SETBIT(long& val,int bit)
{
   val |= long(1L<<bit);
}

inline void
CLEARBIT(WORD& val,int bit)
{
   val &= WORD(~(1<<bit));
}

inline void
CLEARBIT(int& val,int bit)
{
   val &= ~(1<<bit);
}

inline void
CLEARBIT(DWORD& val,int bit)
{
   val &= ~(1L<<bit);
}

inline void
CLEARBIT(long& val,int bit)
{
   val &= ~(1L<<bit);
}

/*
#ifndef max
   #define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
   #define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif
*/

#define CLEAR_OBJECT(obj) memset(&(obj),0,sizeof(obj))

/* ----- Miscellaneous functions ------ */

/*** 16 bit CRC functions ***/

WORD crc(const char *);
WORD crc(const void *,unsigned);
WORD upcrc(const char *);

/*** 32 bit CRC functions ***/

DWORD crc32   (const char *);
DWORD upcrc32 (const char *);
DWORD crc32   (const void *,unsigned);

extern "C"
   {
      /*** Constants for File::seek() ***/

      const seek_set           = 0;
      const seek_cur           = 1;
      const seek_end           = 2;
   }

bool	get_ini_var(const char *fname,const char *varname,char *var,int max);
bool	set_ini_var(const char *fname,const char *varname,const char *var);

bool	ts_MakeFullDir(char *dir);                      /* Creates directory even in multiple levels       */
bool	ts_DirExists(char *dir);                        /* Check if directory exists                       */
long	ts_CopyFile(char *from,char *to,int bufsize);   /* Copy file using buffer size                     */
QString	ts_ResolveDir(char *dir);                       /* Resolve directory (strip .. and other elements) */
bool	ts_IsFullPath(char *s);                         /* Check if path consists of drive + directory     */
void	ts_MakeInputPath(QString& s);                    /* Make path suitable for editing                  */
void	ts_MakeInputPath(char *s);                      /* Make path suitable for editing                  */
bool	ts_SyncFileDate(char *fnSource,char *fn);       /* Sync file date of 'fn' with 'fnSource'          */
long	ts_DiskFreeSpace(char *dir);

void	append_backspace(char *);
void	strip_linefeed(char *);
void	strip_trailing(char *);
void	strip_leading(char *);
void	strip_all(char *);

void	c2pas(char *);
void	pas2c(char *);

void	sleep_clock();

#define strcmpl(a,b) stricmp(a,b)
#define msleep(a)    delay(a)

class QString
   {
   public:
      enum justification { left , right , centered };

   private:
      void adjustSize();
      void adjustSize(int l);

		int size;
		int _len;

	protected:
		char *s;

   public:
	  QString();
      QString(const QString&);
      QString(const char *);
      QString(const char,int len=1);
     ~QString();
      void  clear();
      char& operator[](int i)
         {
            return s[i];
         }
      operator char*() const
         {
            return s;
         }

      void operator=(const char*);
      void operator=(const QString&);
      void operator=(char);
      void operator=(int);
      void operator=(long);
      void operator+=(const QString&);
      void operator+=(const char *);
      void operator+=(char);

      int operator==(const char *str) const;
      int operator==(const QString& str) const;
      int operator!=(const char *str) const;
      int operator!=(const QString& str) const;

      QString& operator<<(const QString&);
      QString& operator<<(const char *);
      QString& operator<<(char);
      QString& operator<<(int);
      QString& operator<<(long);

	  void assignFormattedNumber(long n,char thou_sep);
      
      int replace(const char *s,const char *r,bool = false,int max_count = 0);
      int find(const char *s,bool case_sens = false) const;   // returns pos (<0 -> not found)
      int find(char c,bool case_sens = false) const;          // returns pos (<0 -> not found)

      int fuzzySearch(const char *pattern , int degree = 75); // <0 -> not found

      QString sub(int pos,int l) const;        // pos>=0

      void del(int pos,int len=0);              // pos>=0
      void insert(int pos,const char *str);   // pos>=0

      char lastChar() const;
      char firstChar() const { return *s; }

      void delFirst(char = '\0');
      void delLast(char = '\0');

      int len() const { return _len; }
      WORD crc() const;
      WORD upcrc() const;

      void upperCase();
      void lowerCase();
      void mixedCase();

      void ltrim();
      void rtrim();
      void  trim();

      friend QString operator+(const QString&,const QString&);
      friend QString operator+(const QString&,const char * );
      friend QString operator+(const char * ,const QString&);

      void justify(justification , int len = 0);
   };


/*** Date class ***/

#pragma pack(push,1)

#define TODAY (-1L)
#define NOW   0

class QDate
	{
		unsigned short _d : 5;
		unsigned short _m : 4;
		unsigned short _y : 15;
	
		int compare(const QDate&) const;
		void  parse_key(QString&) const;

      static char *weekdays[7];
      static char *s_weekdays[7];
      static char *l_weekdays[7];
      static char *months[12];
      static char *l_months[12];

   public:
      QDate();                   // Initializes date to nothing
      QDate(long);               // Initializes date to julian/today
      QDate(int,int,int);        // Initializes date with specific values
      QDate(const QDate&);

      void operator=( const QDate& );

      void operator()(int day,int month,int year) // Equal to set()
         {
            set(day,month,year);
         }

      int operator[](int i) const;  // 0 = day , 1 = month , 2 = year

      int day() const           // Returns day (1-31)
         {
			return _d;
         }
      int month() const         // Returns month (1-12)
         {
			return _m;
         }
      int year() const          // Returns year (4 digits)
         {
			return _y;
         }

      bool ok() const;           // Returns !=0 if date is valid

      int dayNum() const;       // Returns the number of the day in the year (1-366)
      int weekDay() const;      // Returns the day of week (0=sunday)
      int weekNum() const;      // Returns the week number (1-53)
      int daysInMonth(int = 0) const; // Returns # days in given month
      int daysInYear(int = 0) const;  // Returns # days in given year
      int weeksInYear(int = 0) const; // Returns # weeks in given year

      int age(const QDate& birthdate);

      operator long() const;    // Converts to julian date
      QDate& operator=(long);    // Converts julian date to normal date

      void operator++()
         {
            (*this) = long(*this) + 1;
         }
      void operator++(int)
         {
            operator++();
         }
      void operator--()
         {
            (*this) = long(*this) - 1;
         }
      void operator--(int)
         {
            operator--();
         }
      void operator+=(int n)
         {
            (*this) = long(*this) + n;
         }
      void operator-=(int n)
         {
            (*this) = long(*this) - n;
         }

      void set(int,int,int);    // Set date to a specific date
      void today();             // Set date to today

      int operator<(const QDate&) const;     //  ]
      int operator>(const QDate&) const;     //  ]
      int operator==(const QDate&) const;    //  ] Compare
      int operator!=(const QDate&) const;    //  ]      functions
      int operator<=(const QDate&) const;    //  ]
      int operator>=(const QDate&) const;    //  ]

      int operator-(const QDate&) const;     // Returns difference in number of days

      bool leap()               const;

      QString format(const char *fmt) const;

      void fileDate(WORD);  // Sets date to packed date
   };


/*** Time class ***/

class QTime
   {
      char _h ,
           _m ,
           _s ;

      void QTime::parse_key(QString& key) const;
   public:

      QTime();
      QTime(int)
         {
            now();
         }
      QTime(int h,int m,int s)
         {
            set(h,m,s);
         }

      QTime(const QTime&);

      void operator=(const QTime&);

      void operator()(int h,int m,int s)
         {
            set(h,m,s);
         }

      char& operator[](int i);

      int hour() const
         {
            return _h;
         }
      int minute() const
         {
            return _m;
         }
      int seconds() const
         {
            return _s;
         }

      operator long() const;

      long operator-(const QTime& t) const;

      void operator-=(const QTime&);
      void operator+=(const QTime&);
      void operator=(long);

      void set(int h,int m,int s);     // Set to specific time
      void now();                      // Set to right now

      QString format(const char *) const;

      void fileTime(WORD);

      int operator<(const QTime&)  const;   // ]
      int operator>(const QTime&)  const;   // ]
      int operator==(const QTime&) const;   // ]  Compare
      int operator!=(const QTime&) const;   // ]      functions
      int operator<=(const QTime&) const;   // ]
      int operator>=(const QTime&) const;   // ]
   };

#pragma pack(pop)

class QFileName : public QString
  {
 public:
   QFileName() : QString() {}
   QFileName(const char *p,const char *f=NULL,const char *e=NULL);
   void operator()(const char *p);
   void operator()(const char *p,const char *f);
   void operator()(const char *p,const char *f,const char *e);
   void appendBS();
   void stripPath();
   void stripExt();
   void stripName();
   void changeExt(const char *ext);
   void changePath(const char *path);
   void operator=(const char*);
   void operator=(const QFileName&);
   void operator=(char);
   void operator=(int);
   void operator=(long);
   void fit(int size);
  };

const DIR_NORMAL = 0x00;
const DIR_RDONLY = 0x01;
const DIR_HIDDEN = 0x02;
const DIR_SYSTEM = 0x04;
const DIR_LABEL  = 0x08;
const DIR_DIREC  = 0x10;
const DIR_ARCH   = 0x20;

class QDirScan
  {
   void *data;
   int ok;
   long handle;
 public:

   QDirScan();
   QDirScan(const char *wildcard,int attr);
   QDirScan(const char *wildcard);
  ~QDirScan();

   int first(const char *fname);                    // 0 -> error
   int first(const char *,int);
   int next();                                // 0 -> error
   int operator++()    { return next(); }     // 0 -> error
   int operator++(int) { return next(); }     // 0 -> error

   operator int() const
      {
         return ok;
      }

   char *name() const;
   QDate date()  const;
   QTime time()  const;
   long size()  const;
   int flags()  const;

   operator char*() const  { return name(); }
   operator QDate()  const  { return date(); }
   operator QTime()  const  { return time(); }
  };


// Constants for "File" class

const WORD fmode_read     = 0x000;  // Open for read               ]
const WORD fmode_write    = 0x001;  // Open for write              ] XOR
const WORD fmode_rw       = 0x002;  // Open for read/write         ]

const WORD fmode_create   = 0x004;  // Create new file             ] OR

const WORD fmode_excl     = 0x010;  // Open for exclusive acccess  ]
const WORD fmode_denywr   = 0x020;  // Deny writes by others       ] XOR
const WORD fmode_denyrd   = 0x030;  // Deny reads by other         ]
const WORD fmode_shared   = 0x040;  // Allow read/write by others  ]

const WORD fmode_text     = 0x100;  // Open in text mode           ]
const WORD fmode_copen    = 0x200;  // Create if not exist         ] OR
const WORD fmode_buffered = 0x400;  // Buffered I/O                ]
const WORD fmode_append   = 0x800;  // Open for append             ]

const WORD file_error_ok       = 0;    // No error
const WORD file_error_nofile   = 2;    // No such file
const WORD file_error_nopath   = 3;    // No such directory
const WORD file_error_numfiles = 4;    // No more file handles
const WORD file_error_noaccess = 5;    // Access denied
const WORD file_error_badfh    = 6;    // Bad file handle

class QFile
   {
      int   fh;              // file handle (in OS/2: set to -1 if invalid)

      BYTE *buffer;         // buffer pointer
      BYTE *bufPtr;         // position in buffer
      unsigned bufSize;        // buffer size
      unsigned bytesInBuf;     // # bytes in buffer
      long   bufPos;         // position of buffer in file
      BYTE  bufType;        // Buffer type (R/W)
      WORD  mode;           // file mode
      BYTE  lastAction;     // last physical action (read/write/seek/none)
      bool  atEof;          // at EOF flag
      int    errorCode;      // last error code

      void clearError()
         {
            atEof     = false;
            errorCode = 0;
         }
      void init();
      bool buffered() const
         {
            return (bool)!!(mode & fmode_buffered);
         }
      bool textMode() const
         {
            return (bool)!!(mode & fmode_text);
         }
      bool fillBuffer();

   public:
      QFile(const char *fname,WORD mode = fmode_read,WORD bufsize = 0);
      QFile()
         {
            init();
         }
      ~QFile()
         {
            close();
         }
      bool open(const char *fname,WORD mode = fmode_read,WORD bufsize = 0);
      void close();
      bool eof() const;
      int error() const
         {
            return errorCode;
         }
      void enableBuffer();
      void disableBuffer();
      unsigned read(void *p,unsigned size);
      unsigned write(const void *p,unsigned size);
      long seek(long pos,int mode = seek_set);
      int  readByte();
      bool writeByte(BYTE c);
      bool readLine(char *s,int max);
      QString readLine();

      QFile& operator<<(const char *);
      QFile& operator<<(int);
      QFile& operator<<(WORD);
      QFile& operator<<(long);
      QFile& operator<<(DWORD);
      QFile& operator<<(char);
      QFile& operator<<(const QString& s) { return operator<<((char *)s); }

      QFile& operator>>(char&);
      QFile& operator>>(int&);
      QFile& operator>>(WORD&);
      QFile& operator>>(long&);
      QFile& operator>>(DWORD&);
      QFile& operator>>(QString& s) { s = readLine(); return *this; }

      bool printf(const char *fmt,...);
      long pos();
      long len();
      void cut();
      
	  bool opened() const
         {
            return bool(fh>0);
         }

      bool lock(long pos,long len);
      bool unlock(long pos,long len);
      void flush();

      int   dosHandle() { return fh;    }
   };


class QTextFile : public QFile
   {
   public:
      QTextFile()
         {
         }
      QTextFile(const char *fname , WORD mode = fmode_read , WORD bufsize=512)
      : QFile(fname , mode | fmode_text , bufsize)
         {
         }
      bool open(const char *fname , WORD mode = fmode_read , WORD bufsize=512)
         {
            return QFile::open(fname , mode | fmode_text , bufsize);
         }
   };

class QBitArray
   {
      long start;
      unsigned short *array;
   public:
      QBitArray(long size,long s = 0);
      ~QBitArray();
      bool operator[](long i) const;
      void set(long i);
      void clear(long i);
   };

class QKeyStack
   {
      unsigned char *buffer;
      int head,tail;
      int size;
   public:
      QKeyStack(int s)
         {
            size = s;
            buffer = new unsigned char[size];
            head = tail = 0;
         }
     ~QKeyStack()
         {
            delete [] buffer;
         }

      bool available()
         {
            return head != tail;
         }

      unsigned char get()
         {
            unsigned char c = buffer[head++];

            if(head >= size)
               head = 0;

            return c;
         }

      unsigned char peek()
         {
            return buffer[head];
         }

      void put(unsigned char c)
         {
            buffer[tail++] = c;

            if(tail >= size)
               tail = 0;
         }
   };


bool check_mod97(const char *s);


char *form(const char * ...);

#include <cache.hpp>
#include <recfile.hpp>
#include <llist.hpp>
#include <hash.hpp>

#endif
