#include <StdAfx.h>

#include <tslib.hpp>
#include <compplib.hpp>

#include "gfcomsock.h"

#include "rcvthread.h"

CRcvThread::CRcvThread(CSerial *s,HANDLE h,QKeyStack& lk,QKeyStack& rk)
   : serial(s), localkeys(lk), remotekeys(rk), hEventKeyHit(h)
{             
}

void
CRcvThread::Run()
{
   while(!ShouldTerminate())
   {
      if(!serial->RXCount())
			serial->WaitForEvent();

      if(serial->RXCount())
      {

	      while(serial->RXCount())
         {
            int c = serial->GetChar();

            if(c > 0 && c < 255)
               remotekeys.put(BYTE(c));
         }
      }
      
      SetEvent(hEventKeyHit);
   }
}

void
CRcvThread::PauseReceiving()
{
   serial->ForceEvent();

   Suspend();
}

void
CRcvThread::ResumeReceiving()
{
   serial->ForceEvent();

   Resume();
}

void
CRcvThread::Terminate()
{
   CThread::Terminate(); // Signal thread to quit

   serial->ForceEvent();
}
