//
// File:        main.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     11/09/95 10:13
//
// Revision History:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:04  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:28:00  houghton
// Changed to Release 3
//
// Revision 1.1  1995/11/17 16:59:51  houghton
// Initial Version.
//
//

#include "AppParam.hh"

#include <Wcf.h>
#include <WcfWt.h>

AppParam * App;

Ret_Status
HandlerConnect( WcfContext cid, void * closure );

int
main( int argc , char * argv[] )
{
  App = new AppParam( argc, argv );

  if( App->help() || ! App->good() )
    {
      cout << *App << endl;
      exit( 1 );
    }

  if( WcfInitialize( 0, 0 ) != RET_SUCCEED )
    return( WcfError(  NULL, WcfErrType, WcfErrno, NULL,
		       "Initialization Failed" ) );

  WcfContext cid;
  
  if( WcfInitClient( &cid, App->server(), App->client() ) != RET_SUCCEED )
    return( WcfError( NULL, WcfErrType, WcfErrno, NULL,
		      "Client '%s' init to Server '%s' failed",
		      App->client().cstr(),
		      App->server().cstr() ) );

  if( WcfSetHandlerConnect( cid, HandlerConnect, NULL ) != RET_SUCCEED )
    return( WcfError( NULL, WcfErrType, WcfErrno, NULL,
		      "Can't set Connect handler for '%s'.",
		      App->server().cstr() ) );
  
  if( WcfRun( WcfEifInitWt, NULL ) != RET_SUCCEED )
    return( WcfError( NULL, WcfErrType, WcfErrno, NULL,
		      "Run failed" ) );

  return( 1 );
}
  
