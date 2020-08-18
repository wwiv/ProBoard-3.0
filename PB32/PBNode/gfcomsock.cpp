#include "StdAfx.h"
#include "afxmt.h"

#include "compplib.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_cppmem.hpp"

#include "gfcomsock.h"

//*
//* GFComSock::GFComSock( int com )
//*
//* ARGUMENTS
//*   int com - The port to open.
//*
//* DESCRIPTION
//*   This constructor will attempt to open a port under the OS/2
//*   operating system.
//*
//* SIDE EFFECTS
//*   Creates a GFComSock object.
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
GFComSock::GFComSock( SOCKET s ) : sock(2048)
{
   Initialize( s );
}


//*
//* GFComSock::GFComSock( GFComSock &prev )
//*
//* ARGUMENTS
//*   GFComSock &prev - The address of a GFComSock object that you wish
//*                    make a copy of.
//*
//* DESCRIPTION
//*   This copy contructor will make a copy of the supplied GFComSock
//*   ojbect.
//*
//* SIDE EFFECTS
//*   Creates another GFComSock object.
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
GFComSock::GFComSock( GFComSock &prev ) : sock(2048)
{
   memcpy(this,&prev,sizeof(prev));
}


//*
//* GFComSock::~GFComSock( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   The destructor checks to see if it is the only instance using
//*   this port, if so, it calls the close function to close the device.
//*
//* SIDE EFFECTS
//*   Destroys a GFComSock object
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
GFComSock::~GFComSock( void )
{
   Close();
}


//*
//* void GFComSock::Initialize( int com )
//*
//* ARGUMENTS
//*   int com - The port to initialize.
//*
//* DESCRIPTION
//*   The Initialize function for GFComSock is much simpler than that
//*   of the MS-DOS version, GFI8250. All the hard work is done by
//*   the OS/2 COMM device driver. open is called to open the port,
//*   the handshaking facility in the device driver is turned off,
//*   and the appropriate rs232 lines are enabled.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*   Janurary 26, 1994 - Had a report that the uninitialized ParmLength and
//*                       DataLength variables were causing an error.  Have
//*                       initialized them to the size of the structures passed
//*                       in.
//*
void GFComSock::Initialize( SOCKET sock )
{
   hSOCKET = sock;
   attached = false;
}


//*
//* int GFComSock::Open( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   This function will attempt to open the port using the
//*   DosOpen API.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_LINK_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::Open( void )
{
  return( GCPP_OK );
}


//*
//* int GFComSock::Close( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   This function will attempt to close the port using the
//*   DosClose API.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_CLOSE_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::Close( void )
{
   Detach();

   return GCPP_OK;
}


//*
//* void GFComSock::GetBufferInfo( GFLinkInfo &sbc, int status_flag )
//*
//* ARGUMENTS
//*   GFLinkInfo &sbc - The address of a GFLinkInfo structure to store
//*                     the info about the buffers.
//*   int status_flag - The type of status to obtain: GCPP_RXINFO, GCPP_TXINFO,
//*                     GCPP_FLOWINFO.
//*
//* DESCRIPTION
//*   The GetBufferInfo() function makes use of the facilities in
//*   the device driver to get the status of the built-in buffers.
//*   Under OS/2 the library functions use the OS/2 interrupt buffers
//*   rather than installing its own. OS/2 1.x has fixed size buffers.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
void GFComSock::GetBufferInfo( GFLinkInfo &sbc, int status_flag )
{
   Attach();

   
  sbc.rxtype = GCPP_BUFTYPE_FIXED;
  sbc.rxcount = sock.RXCount();
  sbc.rxsize  = sock.RXSize();
  sbc.txtype = GCPP_BUFTYPE_FIXED;
  sbc.txsize = 100;
  sbc.txcount = 0;
  sbc.status = 0;
}


//*
//* int GFComSock::NewLinkSize( unsigned insize,
//*                            unsigned room,
//*                            unsigned outsize )
//*
//* ARGUMENTS
//*   unsigned insize - The size of the receive buffer.
//*   unsigned room - The size of the overflow buffer.
//*   unsigned outsize - The size of the transmit buffer
//*
//* DESCRIPTION
//*   Since the OS/2 device driver does not allow for changing the
//*   size of the comm buffers this function does nothing.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_NOT_SUPP
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::NewLinkSize( unsigned insize, unsigned room, unsigned outsize )
{
   Attach();

  return( GCPP_NOT_SUPP );
}


//*
//* int GFComSock::SetHandShake( int inmode, int outmode )
//*
//* ARGUMENTS
//*   int inmode - The incomming handshake line.
//*   int outmode - The outgoing handshake line.
//*
//* DESCRIPTION
//*   The OS/2 COMM device driver can be set to carry out
//*   XON/XOFF or hardware handshaking automatically. The
//*   SetHandShake function uses this facility and also keeps
//*   a record of the current settings which can then be
//*   used by GetHandShake to pass back to the caller in its
//*   reference arguments.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::SetHandShake( int inmode, int outmode )
{
   Attach();

  return( GCPP_OK );
}


//*
//* int GFComSock::GetHandShake( int &inmode, int &outmode)
//*
//* ARGUMENTS
//*   int &inmode - Where to store the incomming handshake method
//*   int &outmode - Where to store the outgoing handshake method
//*
//* DESCRIPTION
//*   This function will return the current handshake method
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
/*
int GFComSock::GetHandShake( int &inmode, int &outmode)
{
  return( GCPP_OK );
}
*/


//*
//* int GFComSock::LineBreak( int state )
//*
//* ARGUMENTS
//*   int state - The state to place the break condition.
//*
//* DESCRIPTION
//*   This function will allow us to set, clear or test the
//*   break condition.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK, TRUE or FALSE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::LineBreak( int state )
{
   Attach();

  return( state );
}


//*
//* int GFComSock::LineControl( int line, int state )
//*
//* ARGUMENTS
//*   int line - The line to test or set.
//*   int state - The state to place the specified line.
//*
//* DESCRIPTION
//*   The OS/2 LineControl functions is somewhat more complicated
//*   than might have been expected. This additional complication
//*   is caused by the need to retain consistency of behavior
//*   with the MS-DOS implementation.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   TRUE or FALSE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::LineControl( int line, int state )
{
   Attach();

   return TRUE;
}


//*
//* int GFComSock::SetDataFormat( long bd, char pr, int dl, int st )
//*
//* ARGUMENTS
//*   long bd - The baud rate to set
//*   char pr - The parity type to set
//*   int dl - The data length to set
//*   int st - The stop bit setting
//*
//* DESCRIPTION
//*   This function will set the various port parameters for the
//*   class.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK, GCPP_BADARGS_ERROR, or GCPP_SYSFAILED_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*   August 8, 1994 - Added a cast for Borland C++ for OS/2 1.5.
//*
int GFComSock::SetDataFormat( long bd, char pr, int dl, int st )
{
   Attach();

  return( GCPP_OK );
}


//*
//* void GFComSock::GetDataFormat( long &bd, char &pr, int &dl, int &st )
//*
//* ARGUMENTS
//*   long &bd - Where to store the baud rate
//*   char &pr - Where to store the parity setting
//*   int &dl - Where to store the data length
//*   int &st - Where to store the stop bit setting
//*
//* DESCRIPTION
//*   This function will poll the system for the port settings and
//*   return the settings to the user.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
/*
void GFComSock::GetDataFormat( long &bd, char &pr, int &dl, int &st )
{
}
*/

//*
//* int GFComSock::PutChar( GCPP_BYTE b )
//*
//* ARGUMENTS
//*   GCPP_BYTE b - The byte to send out the port.
//*
//* DESCRIPTION
//*   This function will send a byte of data out the port using the
//*   DosWrit function.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::PutChar( GCPP_BYTE b )
{
   Attach();

   sock.Send(&b,1);

   return GCPP_OK;
}


//*
//* unsigned GFComSock::PutString( const GCPP_BYTE *string )
//*
//* ARGUMENTS
//*   cont GCPP_BYTE *string - The strign to send out the port.
//*
//* DESCRIPTION
//*   This funciton will attempt to write a string out the port using
//*   the OS/2 API.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   The count of characters written to the port.
//*
//* AUTHOR
//*   Patrick Little
//*
//* MODIFICATIONS
//*
//*
unsigned GFComSock::PutString( const GCPP_BYTE *string )
{
   Attach();

   return sock.Send(string,strlen((char *)string));
}


//*
//* unsigned GFComSock::PutBuffer( const GCPP_BYTE *buf, unsigned n )
//*
//* ARGUMENTS
//*   cont GCPP_BYTE *buf - The buffer to write out the port.
//*   unsigned n - The number of characters in the buffer.
//*
//* DESCRIPTION
//*   This function will apptempt to write a buffer out the port
//*   using the OS/2 API.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   The number of characters placed in the buffer.
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*   Janurary 26, 1994 - We were improperly casting the n parameter to
//*                       unsigned short instead of unsigned long.
//*
unsigned GFComSock::PutBuffer( const GCPP_BYTE *buf, unsigned n )
{
   Attach();

   return sock.Send(buf,n);
}

//*
//* int GFComSock::GetChar( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   Get a character from the receive buffer.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   The character removed from the receive queue.
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::GetChar( void )
{
//  int c;
//  unsigned long fcount;

   Attach();

   BYTE x;

   while(sock.Receive(&x,1) == 0)
   {
   }

   return int(x);
}


//*
//* int GFComSock::GetBuffer( GCPP_BYTE *buffer, unsigned count )
//*
//* ARGUMENTS
//*   GCPP_BYTE *buffer - A pointer to the storage buffer.
//*   unsigned count - The number of characters to retireve.
//*
//* DESCRIPTION
//*   This function will attemp to get a buffer of characters from
//*   the port.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   The number of characters retrieved from the port.
//*
//* AUTHOR
//*   Patrick Little
//*
//* MODIFICATIONS
//*   August 19, 1994 - Modified to support Watcom C++ 10.0.
//*
unsigned GFComSock::GetBuffer( GCPP_BYTE *buffer, unsigned count )
{
   return sock.Receive(buffer,count);
}


//*
//* void GFComSock::Flush( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   Ensures we get current error an line status information.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
void GFComSock::Flush( void )
{
   Attach();
}


//*
//* void GFComSock::UpdateLineStatus( GFlinestat &line )
//*
//* ARGUMENTS
//*   GFlinestat &line - The GFlinestat structure to store the port
//*                      data.
//*
//* DESCRIPTION
//*   Updates the line status information
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*   August 8, 1994 - Added cast operations for the Borland C++ for OS/2.
//*
//*   September 29, 1995 - Chnaged BREAK_DETECTED to GCPP_BREAK_DETECTED.
//*
void GFComSock::UpdateLineStatus( GFlinestat &line )
{
   Attach();
   Flush();

   line.data_terminal_ready = 1;
   line.ready_to_send = 1;
   line.line_break = 0;
   line.data_set_ready = 0;
   line.clear_to_send = 1;
   line.ring_indicator = 0;
   line.carrier_detect = sock.connected();
   line.delta_carrier = !sock.connected();
   line.delta_ring = 0;
   line.delta_cts = 0;
   line.delta_dsr = 0;
   line.got_break = 0;
   line.parity = 0;
   line.framing = 0;
   line.overflow = 0;
   line.overrun = 0;

   if(line.delta_carrier)
   {
      sock.ForceReturnFromWait();      
   }
}


//*
//* int GFComSock::ClearLink( int dir, unsigned numbytes )
//*
//* ARGUMENTS
//*   int dir - The buffer to clear.
//*   unsigned numbytes - The number of bytes to clear out of the
//*                       receive buffer.
//*
//* DESCRIPTION
//*   Flushes the transmit or recieve buffer
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*     December 1, 1995 - if numbytes is 0, the function will flush
//*         primary and secondary buffers.
//*
int GFComSock::ClearLink( int dir, unsigned numbytes )
{
   Attach();
   return( GCPP_OK );                          // Buffer empty
}


//*
//* int GFComSock::SystemIdle( void )
//*
//* ARGUMENTS
//*   NONE
//*
//* DESCRIPTION
//*   This is the system idle routine.  Any routine that needs to wait
//*   will need to call this routine.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*
//* AUTHOR
//*   Patrick Little
//*
//* MODIFICATIONS
//*   November 19, 1993 - Modified the idle routine to call DosSleep to
//*                       free system resources.
//*
/*t GFComSock::SystemIdle( void )
{
  //*
  //* This function can be replaced by the programmer.
  //*
  DosSleep(0);
  return( GCPP_OK );
}
*/

//*
//* int GFComSock::PutImm( GCPP_BYTE b )
//*
//* ARGUMENTS
//*   GCPP_BYTE b - The byte to send out the port.
//*
//* DESCRIPTION
//*   This function will send a byte of data out the immediatly.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   GCPP_OK or GCPP_ERROR
//*
//* AUTHOR
//*   Dave Mansell
//*
//* MODIFICATIONS
//*
//*
int GFComSock::PutImm( GCPP_BYTE b )
{
   Attach();

  GCPP_UNUSED_PARAMETER( b );
  return( GCPP_OK );
}

//*
//* void SetWriteTimeout( unsigned short pause )
//*
//* ARGUMENTS
//*   unsigned short pause - Number units to allow before timeout. Each unit
//*                          is .01 seconds.
//* DESCRIPTION
//*   This function will set the 'usWriteTimeout' member of the device control
//*   block. If the physical device driver does not give any data to the
//*   transmit hardware from the transmit queue within the period of time
//*   specified, then the request is completed.
//*
//* SIDE EFFECTS
//*
//* RETURNS
//*   NONE
//*
//* AUTHOR
//*   Billy Lane
//*
//* MODIFICATIONS
//*
//*
void GFComSock::SetWriteTimeout( unsigned short pause )
{
   Attach();
}

int GFComSock::WaitForInput()
{
   sock.WaitForInput();

   return GCPP_OK;

}
