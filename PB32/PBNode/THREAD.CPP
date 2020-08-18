#include <StdAfx.h>

#include "thread.h"


void
CThread::Start()
{
   threadID = AfxBeginThread(CThread::Execute,(LPVOID)this);
}


UINT
CThread::Execute(LPVOID obj)
{
   CThread *thread = static_cast<CThread *>(obj);

   thread->status = Running;
   thread->Run();
   thread->status = Ended;

   return 0;
}

void
CThread::WaitForExit()
{
  if (status == Running)
    ::WaitForSingleObject(threadID->m_hThread, INFINITE);
}

void
CThread::Suspend()
{
   if(status == Running)
   {
      threadID->SuspendThread();
      status = Suspended;
   }
}

//
// It's an error to try to resume a thread that isn't suspended.
//
void
CThread::Resume()
{
   if(status = Suspended)
   {
      threadID->ResumeThread();
      status = Running;
   }
}
