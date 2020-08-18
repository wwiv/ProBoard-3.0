class CPBStatusDlg;

class CServerSocket : public CSocket
   {
     // CPBStatusDlg *dlg;
   public:
      CServerSocket(/*CPBStatusDlg *d) : dlg(d*/) {}

      BOOL Create() { return CSocket::Create(23); }

      virtual void OnAccept(int);
   };
   