#include "StdAfx.h"
#include "compplib.hpp"
#include "gfcomsock.h"

#include "serial.h"

CSerial::CSerial(SOCKET sock)
{
   clWin  = NULL;
   clSock = new GFComSock(sock);

   serial = new GFSerial(clSock);

   ComType = Socket;
}

CSerial::CSerial(int comport,long baudrate)
{
   ComType = Modem;

   clSock = NULL;
   clWin  = new GFComWin32(comport);

   serial = new GFSerial(clWin);

   baud = baudrate;

   serial->GetDataFormat()->BaudRate(baud);
}


CSerial::~CSerial()
{
   if(ComType == Socket)
   {
      delete clSock;
   }
   else
   {
      unsigned long evmask;

      clWin->GetEventMask(evmask);
      clWin->SetEventMask(evmask | ON_RECEIVE_CHARACTER | ON_CD_CHANGED);

      delete clWin;
   }

   delete serial;
}

int
CSerial::RXCount()
{
   return serial->RXCount();
}

int
CSerial::GetChar()
{
   return serial->GetChar();
}

int
CSerial::PutChar(BYTE c)
{
   return serial->PutChar(c);
}

void
CSerial::WaitForEvent()
{
   if(ComType == Socket)
   {
      clSock->WaitForInput();
   }
   else
   {
      unsigned long evmask;

      clWin->GetEventMask(evmask);
      clWin->SetEventMask(evmask | ON_RECEIVE_CHARACTER | ON_CD_CHANGED);
      clWin->WaitForEvent(evmask);
   }
}

void
CSerial::ForceEvent()
{
   if(ComType == Socket)
   {
      clSock->ForceEvent();
   }
   else
   {
      unsigned long evmask;

      clWin->GetEventMask(evmask);
      clWin->SetEventMask(evmask | ON_RECEIVE_CHARACTER | ON_CD_CHANGED);
   }
}

long
CSerial::BaudRate()
{
   return baud;
}


BOOL
CSerial::Carrier()
{
   GFLineStatus *status = serial->GetLineStatus();

   status->Status();

   if(status->Carrier())
      return TRUE;
   else
      return FALSE;
}

void
CSerial::ReceiveFile(Protocol)
{
}

CString 
CSerial::IPName()
{
   UINT port;
   CString stmp;

   if(ComType == Socket)
   {
      clSock->sock.GetPeerName(stmp,port);
   }

   return stmp;
}
