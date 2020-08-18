#ifndef _PBTHREAD_H
#define _PBTHREAD_H

#include <tslib.hpp>

#include "thread.h"

class GFSerial;
class GFComWin32;
class GFComOS2;
class CRcvThread;
class CPBWnd;
class CSerial;

class CPBThread : public CThread
   {
      virtual void Run();

      CSerial   *serial;
      CRcvThread *rcvThread;
      
      QKeyStack inbStackLocal;
      QKeyStack inbStackRemote;

      HANDLE   evInbound;

   public:

      CPBWnd *pbwin;

      void SignalQuit();

      void CheckCarrier();

      bool remote;

      BYTE CurrentAttribute();

      BYTE ReadKey();
      BYTE WaitKey();

      void Send(BYTE c);

      void ReceiveFile();
      
      void WaitForInputEvent()
      	{
				WaitForSingleObject(evInbound,INFINITE);
      	}

      void keyPressed(UINT key,UINT repeatCount);

      CPBThread(CPBWnd *w,CSerial *);

      virtual ~CPBThread();

      virtual void Terminate();
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
   
#endif
