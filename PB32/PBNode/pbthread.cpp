#include <StdAfx.h>

#include <tslib.hpp>

#include <compplib.hpp>
#include <filexfer.hpp>

#include "gfcomsock.h"
#include "pbthread.h"
#include "rcvthread.h"
#include "pbwnd.h"



CPBThread::CPBThread(CPBWnd *w,CSerial *comlink)
   : inbStackLocal(204) , inbStackRemote(204)
{
   pbwin = w;
   
   serial = comlink;

   evInbound = CreateEvent(NULL,FALSE,FALSE,NULL);

   rcvThread = NULL;

   if(serial != NULL)
   {
      rcvThread  = new CRcvThread(serial,evInbound,inbStackLocal,inbStackRemote);

      rcvThread->Start();
   }

   pbwin->disableCursor();
}

CPBThread::~CPBThread()
{
   if(rcvThread != NULL)
   {
      rcvThread->Terminate();
      rcvThread->WaitForExit();

      delete rcvThread;
   }

   CloseHandle(evInbound);
}


void
CPBThread::Terminate()
{
   CThread::Terminate();

   SetEvent(evInbound);
}


void
CPBThread::SignalQuit()
{                   
   pbwin->GetOwner()->PostMessage(WM_CLOSE);
}


void
CPBThread::keyPressed(UINT key,UINT repeatCount)
{
   if(key >= 8 && key <= 0x7F)
   {                                      
      for(UINT i=0;i<repeatCount;i++)
         inbStackLocal.put(BYTE(key));

      SetEvent(evInbound);
   }
}


void
CPBThread::CheckCarrier()
{
   if(serial)
   {
      if(!serial->Carrier())   
         throw TXNoCarrier();
   }
}

BYTE
CPBThread::ReadKey()
{
   if(inbStackRemote.available())
   {
      remote = true;
      return BYTE(inbStackRemote.get());
   }

   if(inbStackLocal.available())
   {
      remote = false;
      return BYTE(inbStackLocal.get());
   }

   return 0;
}


BYTE
CPBThread::WaitKey()
{
   BYTE c;

   pbwin->PostMessage(WM_USER_UPDATE_CURSOR,0,0);

   while((c=ReadKey()) == 0)
   {
      WaitForInputEvent();

      CheckCarrier();

      if(ShouldTerminate())
         throw TXWindowClosed();
   }

   return c;
}



void
CPBThread::Send(BYTE c)
{
   CheckCarrier();

   if(serial)
      serial->PutChar(c);

   (*pbwin) << c;
}


void
CPBThread::ReceiveFile()
{
   if(rcvThread)
   {
      rcvThread->PauseReceiving();

      serial->ReceiveFile(CSerial::Zmodem);

      rcvThread->ResumeReceiving();
   }
}

BYTE
CPBThread::CurrentAttribute()
{
   return pbwin->attrib();
}



CPBThread *thread;

int  Run(long baud);
void SetCallBack(void (*send)(BYTE),BYTE (*waitkey)(),BYTE (*readkey)(),BYTE (*curattr)());


void _send(BYTE c)
{
   thread->Send(c);
}

BYTE _waitkey()
{
   return thread->WaitKey();
}

BYTE _readkey()
{
   return thread->ReadKey();
}

BYTE _curattr()
{
   return thread->CurrentAttribute();
}

void
CPBThread::Run()
{
   thread = this;

   ::SetCallBack(_send,_waitkey,_readkey,_curattr);

   if(::Run(0))
      SignalQuit();
}