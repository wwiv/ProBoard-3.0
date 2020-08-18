#include "bufsock.h"

class GCPP_CLASS_TYPE GFComSock : public GFComLink
{
    friend class GFSerial;
    friend class GFDataFormat;
    friend class GFLineStatus;

    friend class CSerial;

    bool attached;
    SOCKET hSOCKET;

    CBufferedSocket sock;

  public:
 	 int WaitForInput();
    void ForceEvent()
    {
       sock.ForceReturnFromWait();
    }

    GFComSock( SOCKET );
    GFComSock( GFComSock &prev );
    ~GFComSock( void );
    void SetWriteTimeout( unsigned short pause = 0 );

  protected:

    void Attach() { if(!attached) sock.Attach(hSOCKET);   attached = true; }
    void Detach() { if(attached) hSOCKET = sock.Detach(); attached = false; }

    void Flush( void );
    int DoError( unsigned short err ) { return err; }
    void Initialize( SOCKET com );
    int Open( void );
    int Close( void );
    int GetError( void );
    void GetBufferInfo( GFLinkInfo &sbc,
              int status_flag = GCPP_RXINFO | GCPP_TXINFO | GCPP_FLOWINFO );
    int NewLinkSize( unsigned insize,
                     unsigned inroom,
                     unsigned outsize = 0 );
    int SetHandShake( int inhand, int outhand );
    int GetHandShake( int &inhand, int &outhand ) { inhand = RTS; outhand = CTS; return GCPP_OK; }
    int LineBreak( int state );
    int LineControl( int line, int state = -1 );
    int SetDataFormat( long bd, char pr, int dl, int st );
    void GetDataFormat( long &bd, char &pr, int &dl, int &st ) { bd = 500000; pr =0; dl=8; st=1; }
    void UpdateLineStatus( GFlinestat &line );
    int PutChar( unsigned char b );
    unsigned PutString( const unsigned char *string );
    unsigned PutBuffer( const unsigned char *buffer, unsigned count );
    int PutImm( unsigned char b );
    unsigned PutChars( const unsigned char* buf, unsigned n );
    int GetChar( void );
    unsigned GetBuffer( unsigned char *buffer, unsigned count );
    int ClearLink( int dir, unsigned numbytes = 0 );
    //void ReportLinkStatus( void (*ViewerOutput)(char *data) );
    virtual int SystemIdle( void ) { return GCPP_OK;}
};
