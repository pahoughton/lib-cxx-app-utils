// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <fcntl.h>

static valid::verify verify("clue::OpenFlags");
using namespace clue;

bool
v_OpenFlags( void )
{
  // int OpenFlags( std::ios::openmode openMode )

  TEST( OpenFlags( std::ios::in ) == O_RDONLY );
  TEST( OpenFlags( std::ios::out ) == O_WRONLY | O_CREAT );
  TEST( OpenFlags( std::ios::app ) == O_WRONLY | O_CREAT | O_APPEND );
  TEST( OpenFlags( (std::ios::openmode)(std::ios::in | std::ios::out) )
	== O_RDWR | O_CREAT);
  TEST( OpenFlags( (std::ios::openmode)(std::ios::out|std::ios::trunc ) )
	== O_WRONLY | O_TRUNC );

  return( verify.is_valid() );
}
