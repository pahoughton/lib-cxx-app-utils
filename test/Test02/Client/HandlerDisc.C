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
// Revision 1.1  1995/11/17 16:59:49  houghton
// Initial Version.
//
//

#include "AppParam.hh"

#include <Wcf.h>

#include <cstdlib>

Ret_Status
HandlerDisc( WcfContext cid, void * closure )
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
    << client << ": " << server << " disconnected." << endl;

  exit( 0 );
  
  return( RET_SUCCEED );
  
}

