// 1999-03-24 (cc) Paul Houghton <paul4hough@gmail.com>

#include "FileBatch.hpp"
#include "Str.hpp"

namespace clue {

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

  errStr = "FileBatchBase";

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
FileBatchBase::setError( ErrorNum errNum, std::streampos errPos, int osErr )
{
  errorNum  = errNum;
  errorPos  = errPos;
  osErrno   = osErr;

  return( good() );
}

}; // namespace clue
