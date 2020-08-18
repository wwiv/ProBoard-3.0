#ifndef __THREAD_H
#define __THREAD_H


class CThread
   {
      bool TerminationRequested;
      enum { Suspended, Running, Ended, Created } status;


      CWinThread *threadID;

   public:

      CThread() : TerminationRequested(false) , status(Created) {}

      
      virtual void Run() = 0;

      virtual void Start();
      virtual void Suspend();
      virtual void Resume();

      virtual void WaitForExit();
      virtual void TerminateAndWait() { Terminate(); WaitForExit(); }
      virtual void Terminate() { TerminationRequested = true; }

      virtual bool ShouldTerminate() { return TerminationRequested; }

   private:
      static UINT Execute(LPVOID obj);

   };

#endif
