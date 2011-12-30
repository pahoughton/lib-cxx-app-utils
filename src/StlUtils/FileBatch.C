//
// File:        FileBatch.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for FileBatch
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     03/24/99 06:54
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "FileBatch.hh"
#include <Str.hh>

#if defined( STLUTILS_DEBUG )
#include "FileBatch.ii"
#endif


FileBatchBase::FileBatchBase( const char * fileName, size_type recordSize )
  : name( fileName ),
    batch( 0 ),
    recSize( recordSize ),
    errorNum( E_OK )
{
}

bool
FileBatchBase::good( void ) const
{
  return( errorNum == E_OK && batch && (*batch).good() );
}

const char *
FileBatchBase::error( void ) const
{
  static Str errStr;

  errStr = getClassName();

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      errStr << ": '" << name << "' ";
      
      if( ! batch )
	{
	  errStr << "no batch.";
	}
      else
	{
	  switch( errorNum )
	    {
	    case E_OPEN:
	      errStr << "open failed - "
		     << strerror( osErrno ) << '.';
	      break;
	      
	    case E_SIZE:
	      errStr << "invalid size '"
		     << errorPos << "' expect multiple of '"
		     << recSize << "'.";
	      break;

	    case E_WRITE:
	      errStr << "writing at '" << errorPos
		     << "' - " << strerror( osErrno ) << '.';
	      break;

	    case E_READ:
	      errStr << "reading at '" << errorPos
		     << "' - " << strerror( osErrno ) << '.';
	      break;

	    default:
	      if( ! (*batch).good() )
		{
		  errStr << ": '" << name << "' - "
			 << strerror( osErrno );
		}
	      else
		{
		  errStr << "unknown error.";
		}
	    }
	}
    }
  return( errStr.c_str() );
}       

bool
FileBatchBase::setError( ErrorNum errNum, streampos errPos, int osErr )
{
  errorNum  = errNum;
  errorPos  = errPos;
  osErrno   = osErr;
  
  return( good() );
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:12  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:41  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.1  1999/05/01 12:51:01  houghton
// Initial Version.
//
//
