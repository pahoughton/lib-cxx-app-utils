//
// File:        HandlerConnect.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     11/09/95 10:52
//
// Revision History:
//
// $Log$
// Revision 4.1  1997/09/17 15:15:06  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:28:02  houghton
// Changed to Release 3
//
// Revision 1.1  1995/11/17 17:00:58  houghton
// Initial Version.
//
//

#include "AppParam.hh"

#include <Wcf.h>

Ret_Status
HandlerMesg( WcfContext cid, void * closure, void * mesg, long mesgLen );

Ret_Status
HandlerDisc( WcfContext cid, void * closure );
  
Ret_Status
HandlerConnect( WcfContext cid, void * /* closure */ )
{
  if( WcfSetHandlerDisconnect( cid, HandlerDisc, 0 ) != RET_SUCCEED ||
      WcfSetHandlerMesg( cid, HandlerMesg, 0 ) != RET_SUCCEED )
    {
      WcfError( cid, WcfErrType, WcfErrno, NULL,
		"Can't set handlers\n" );
      WcfConnectionClose( cid );
    }
									   
  char client[128];
  char server[128];

  if( WcfGetServiceName( cid, server, sizeof( server ) ) != RET_SUCCEED  ||
      WcfGetClientName( cid, client, sizeof( client ) ) != RET_SUCCEED )
    {
      WcfError( cid, WcfErrType, WcfErrno, NULL,
		      "Can't get client/server name\n" );
      WcfConnectionClose( cid );
    }

  
    
  ALog( LogLevel::INFO )
    << server << ": " << client << " connected." << endl;

  return( RET_SUCCEED );
    
}
