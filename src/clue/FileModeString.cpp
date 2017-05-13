/* 1994-12-23 (cc) Paul Houghton <paul4hough@gmail.com>
 */

#include "Clue.hpp"

/*
#include <sys/types.h>
#include <unistd.h>
*/
#include <sys/stat.h>

namespace clue {

char *
FileModeString( mode_t	mode, char * str, size_t bufsize )
{
  if( bufsize < 11 )
    return 0;

  str[0] = ( S_ISREG( mode )  ? '-' :
	     S_ISLNK( mode )  ? 'l' :
	     S_ISDIR( mode ) 	? 'd' :
	     S_ISCHR( mode ) 	? 'c' :
	     S_ISBLK( mode )	? 'b' :
	     S_ISFIFO( mode ) ? 'p' :
	     S_ISSOCK( mode ) ? 's' : '?' );

  str[1] = ( mode & S_IRUSR ) ? 'r' : '-';
  str[2] = ( mode & S_IWUSR ) ? 'w' : '-';
  str[3] = ( ( mode & S_IXUSR ) ?
	     ( mode & S_ISUID ) ? 's' : 'x' :
	     ( mode & S_ISUID ) ? 'S' : '-' );

  str[4] = ( mode & S_IRGRP ) ? 'r' : '-';
  str[5] = ( mode & S_IWGRP ) ? 'w' : '-';
  str[6] = ( ( mode & S_IXGRP ) ?
	     ( mode & S_ISGID ) ? 's' : 'x' :
	     ( mode & S_ISGID ) ? 'S' : '-' );


  str[7] = ( mode & S_IROTH ) ? 'r' : '-';
  str[8] = ( mode & S_IWOTH ) ? 'w' : '-';
  str[9] = ( mode & S_IXOTH ) ? 'x' : '-';

  str[10] = 0;

  return( str );
}

std::string
FileModeString( mode_t mode )
{
  char str[16];
  return( std::string( FileModeString( mode, str, sizeof( str ) ) ) );
}

}; // namespace clue
