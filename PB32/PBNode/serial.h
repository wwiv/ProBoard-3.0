#ifndef __SERIAL_H
#define __SERIAL_H

class GFSerial;
class GFComWin32;
class GFComSock;

class CSerial
   {
      GFSerial   *serial;
      GFComWin32 *clWin;
      GFComSock  *clSock;

      enum { Socket, Modem } ComType;

      long baud;

   public:
	   CString IPName();

      enum Protocol { Xmodem, Ymodem, Zmodem };

      CSerial(SOCKET sock);
      CSerial(int comport,long baudrate);
      ~CSerial();

      int RXCount();

      void WaitForEvent();
      void ForceEvent();

      BOOL Carrier();

      int  GetChar();
      int  PutChar(BYTE);

      void ReceiveFile(Protocol);

      long BaudRate();
   };

#endif