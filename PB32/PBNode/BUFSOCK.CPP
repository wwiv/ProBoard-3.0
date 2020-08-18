#include "StdAfx.h"
#include "afxmt.h"


#include "bufsock.h"

void
CBufferedSocket::OnReceive(int errcode)
{
   if(errcode)
         return;

   CSingleLock lock(&semaphore,TRUE);

   DWORD left;

   IOCtl(FIONREAD,&left);  // Get # bytes in input buffer

   while(left)
   {
      int actual = CSocket::Receive(tmpbuf,left);

	  if(actual == 0 || actual == SOCKET_ERROR)
		  break;

	  for(int i=0;i<actual;i++)  // Copy to circular queue
	  {
		  *pin++ = *tmpbuf++;

		  if(pin > pend)
			  pin = pbase;
	  }

	  IOCtl(FIONREAD,&left);  // Get # bytes in input buffer
   }


   SetEvent(hEv);
}

void
CBufferedSocket::OnClose(int /*errcode*/)
{
   closed = TRUE;
   SetEvent(hEv);
}


int
CBufferedSocket::Receive(void *destptr,int n,int /*flags*/)
{
   CSingleLock lock(&semaphore,TRUE);

   int max = int(pin-pout);

   if(max<0)
	   max += size;

   if(n > max)
	   n = max;

   BYTE *p = (BYTE *)destptr;

   for(int i=0; i<n && pin!=pout;i++)
   {
	   *p++ = *pout++;

	   if(pout>pend)
		   pout = pbase;

	   i++;
   }

   return n;
}

int
CBufferedSocket::RXCount()
{
   CSingleLock lock(&semaphore,TRUE);

   int n = int(pin-pout);

   if(n<0)
	   n += size;

   return n;
}

