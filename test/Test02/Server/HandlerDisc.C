//
// File:        HandlerDisc.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     11/09/95 11:04
//
// Revision History:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:06  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:28:02  houghton
// Changed to Release 3
//
// Revision 1.1  1995/11/17 17:00:59  houghton
// Initial Version.
//
//

#include "AppParam.hh"

#include <Wcf.h>

Ret_Status
HandlerDisc( WcfContext cid, void * /* closure */ )
{
  char client[128];
  char server[128];

  if( WcfGetServiceName( cid, server, sizeof( server ) ) != RET_SUCCEED ||
      WcfGetClientName( cid, client, sizeof( client ) ) != RET_SUCCEED )
    {
      WcfError( cid, WcfErrType, WcfErrno, NULL,
		      "Can't get client/server name\n" );
      WcfConnectionClose( cid );
    }

  ALog( LogLevel::INFO )
    << server << ": " << client << " disconnected." << endl;

  return( RET_SUCCEED );
  
}

