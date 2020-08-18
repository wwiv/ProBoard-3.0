#ifndef __RCVTHREAD_H
#define __RCVTHREAD_H

#include "thread.h"
#include "serial.h"

class CRcvThread : public CThread
   {
      virtual void Run();
   protected:

      CSerial *serial;

      QKeyStack& localkeys;
      QKeyStack& remotekeys;

      HANDLE    hEventKeyHit;
   public:
      CRcvThread(CSerial *s,HANDLE,QKeyStack&,QKeyStack&);

      void PauseReceiving();
      void ResumeReceiving();

      virtual void Terminate();
   };

#endif

