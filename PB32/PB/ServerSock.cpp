#include "StdAfx.h"

#include "PB.h"
#include "StatDlg.h"

void
CServerSocket::OnAccept(int)
{
   char buf[100];

   CSocket sock;

   Accept(sock);

   SOCKET s = sock.Detach();

   static PROCESS_INFORMATION pinfo;
   STARTUPINFO info;

   memset(&info,0,sizeof(info));

   info.cb = sizeof(info);

   sprintf(buf,"PBNODE.EXE /T=%08lX",(DWORD)s);

   CreateProcess(NULL,buf,NULL,NULL,TRUE,0,NULL,NULL,&info,&pinfo);
}