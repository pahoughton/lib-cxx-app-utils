//
// File:        HandlerMesg.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/09/95 11:08
//
// Revision History:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:51  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:04  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:27:59  houghton
// Changed to Release 3
//
// Revision 1.1  1995/11/17 16:59:50  houghton
// Initial Version.
//
//

#include "AppParam.hh"

#include <HeapNetStream.hh>
#include <DateTime.hh>

#include <Wcf.h>

Ret_Status
HandlerMesg( WcfContext cid, void * /* closure */, void * mesg, long mesgLen )
{
  
  char client[128];
  char server[128];

  if( WcfGetServiceName( cid, server, sizeof( server ) ) != RET_SUCCEED ||
      WcfGetClientName( cid, client, sizeof( client ) ) != RET_SUCCEED )
    {
      WcfError( cid, WcfErrType, WcfErrno, NULL,
		      "Can't get client/server name" );
      WcfConnectionClose( cid );
    }

  ALog( LogLevel::INFO )
    << "Message Received: " << server
    << " from: " << client << " size: " << mesgLen << endl;

  HeapNetStream	msg;

  msg.write( mesg, mesgLen );
  
  DateTime  serverTime;
  
  if( msg.getSize() != serverTime.getBinSize() )
    {
      ALog( LogLevel::ERROR )
	<< server << " sent a wrong sized message to " << client
	<< " expected: " << serverTime.getBinSize()
	<< " was: " << msg.getSize()
	<< endl;
      return( RET_SUCCEED );
    }

  msg.read( serverTime );

  ALog( LogLevel::INFO )
    << "Server time: " << serverTime << endl;

  WcfConnectionClose( cid );
    
  return( RET_SUCCEED );
}
