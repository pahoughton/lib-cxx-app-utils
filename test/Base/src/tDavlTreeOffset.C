//
// File:        tDvlTreeOffset.C
// Desc:        
//              
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     01/24/95 10:02 
//
// Revision History:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:43  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:14  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:44  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:34  houghton
// Changed to Release 3
//
// Revision 2.2  1996/05/01 11:34:59  houghton
// Use TEST_DATA_DIR define for data path.
//
// Revision 2.1  1995/11/10 12:49:10  houghton
// Change to Version 2
//
// Revision 1.1  1995/02/13  16:12:06  houghton
// Initial libStlUtils test - This has a long way to go.
//
//
static const char * RcsId =
"$Id$";

#include <iostream.h>
#include <DavlTreeOffset.hh>
#include <MultiMemOffsetMapFixed.hh>

#include "DavlTestData.hh"

void walkAction(
  DavlTestData::TestKey &   key,
  time_t    	    	    when,
  DavlTestData::TestData &  data,
  void *    	    	    closure
  )
{
  cout << key << " When: " << when << " " << data << endl;
}

int
tDavlTreeOffset( void )
{

  MultiMemOffsetMapFixed    keyMem( "key.map",
			  DavlTreeOffset<DavlTestData::TestKey,DavlTestData::TestData>::getKeySize() );

  MultiMemOffsetMapFixed    dataMem( "data.map",
				     DavlTreeOffset<DavlTestData::TestKey,DavlTestData::TestData>::getDataSize() );
  

  DavlTreeOffset<DavlTestData::TestKey,DavlTestData::TestData>
    tree( DavlTestData::compareKey,
	  DavlTestData::copyKey,
	  DavlTestData::copyData,
	  &keyMem,
	  &dataMem);

  DavlTestData	    	data( TEST_DATA_DIR "/davl.data" );

  DavlTestData::Action	action;

  while( (action = data.nextTest()) != DavlTestData::DONE )
    {
      switch( action )
	{
	case DavlTestData::ADD:
	  if( tree.add( data.getKey(), data.getWhen(), data.getData() ) != 0 )
	    {
	      data.error();
	      return( 1 );
	    }

	  break;

	case DavlTestData::DEL:
	  if( tree.del( data.getKey(), data.getWhen() ) != RET_SUCCEED )
	    {
	      data.error();
	      return( 1 );
	    }
	  break;

	case DavlTestData::FIND:
	{
	  off_t found = tree.find( data.getKey(), data.getWhen() );

	  if( found )
	    {
	      cout << "Found: " << data.getKey() 
		   << " When: " << data.getWhen()
		   << " " << *(tree.getDataAddr( found ) ) << endl;
	    }
	  else
	    {
	      data.error();
	    }
	}
	break;
	  
	case DavlTestData::WALK_HIST:
	  cout << "--Walk" << endl;
	  tree.walkHist( walkAction );
	  break;

	  
	case DavlTestData::DUMP:
	  cout << "--Dump" << endl;
	  tree.dump( cout );
	  break;

#if 0  
	case DavlTestData::ADD_DUP:
	  if( tree.add( data.getData() ) == 0 )
	    {
	      data.error();
	      return( 1 );
	    }

	  break;

	case DavlTestData::DEL_NOT:
	  if( tree.del( data.getData() ) == RET_SUCCEED )
	    {
	      data.error();
	      return( 1 );
	    }
	  break;

	case DavlTestData::FIND_NOT:
	{
	  off_t found = tree.find( data.getData() );

	  if( found )
	    {
	      data.error();
	      return( 1 );
	    }
	  else
	    {
	      cout << "Not Found: Key: " << data.getData().key << endl;
	    }
	}
	break;


	case DavlTestData::DESTROY:
	  cout << "--Destroy" << endl;
	  tree.destroy();
	  break;
	  
#endif  
	default:
	  cout << "Unknown Action " << action << endl;
	  return( 1 );

	}
      
    }
  return( 0 );
}



//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
