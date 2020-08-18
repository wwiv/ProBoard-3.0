#include "afxmt.h"

class CBufferedSocket : public CSocket
   {
      int size;
      bool closed;

	  BYTE *pbase;

	  BYTE *pend;
	  BYTE *pin;
	  BYTE *pout;

	  BYTE *tmpbuf;

      HANDLE hEv;
      CSemaphore semaphore;

    public:
      CBufferedSocket(unsigned bufsize) 
         { 
            hEv = CreateEvent(NULL,FALSE,FALSE,NULL);

			size = bufsize;

			tmpbuf = new BYTE[size];
			pbase = new BYTE[size];
			pend  = pbase+size-1;

			pin = pout = pbase;

            closed = FALSE;
         }
      ~CBufferedSocket()
         {
            delete [] pbase;
			delete [] tmpbuf;

            CloseHandle(hEv);
         }


      virtual void WaitForInput() 
         { 
            WaitForSingleObject(hEv,INFINITE); 
         }

      virtual void ForceReturnFromWait()
         {
            SetEvent(hEv);
         }

      virtual void OnReceive(int errcode);
      virtual void OnClose(int errcode);
      virtual int Receive(void *,int,int = 0);

      BOOL connected() { return !closed; }

      int RXCount();
      int TXCount() { return 0; }

      int RXSize() { return size-1; }
      int TXSize() { return 10;   }
   };