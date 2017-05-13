// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include "FileStat.hpp"

#include "UserGroup.hpp"
#include "User.hpp"
#include "DateTime.hpp"
#include "bit"

#include <iomanip>
#include <sstream>
#include <cstring>

#include <utime.h>

namespace clue {

const int FileStat::badFd = -1;

const FileStat::Who 	FileStat::OTHER( Bit( 0 ) );
const FileStat::Who 	FileStat::GROUP( Bit( 1 ) );
const FileStat::Who 	FileStat::USER( Bit( 2 ) );
const FileStat::Who 	FileStat::ALL( 0x07, false );

const FileStat::What	FileStat::EXEC( Bit( 0 ) );
const FileStat::What	FileStat::WRITE( Bit( 1 ) );
const FileStat::What	FileStat::READ( Bit( 2 ) );

bool
FileStat::setTimes(
  time_t    accessTime,
  time_t    modificationTime
  )
{
  struct utimbuf tv;

  tv.actime = accessTime;
  tv.modtime = modificationTime;

  if( utime( name, &tv ) )
    {
      sysError = errno;
      return( false );
    }
  else
    {
      st.st_atime = accessTime;
      st.st_mtime = modificationTime;
      return( true );
    }
}

bool
FileStat::setMode( mode_t mode )
{
  if( ! good() || name.length() == 0 )
    return( false );

  if( chmod( name, mode ) )
    {
      sysError = errno;
      return( false );
    }

  st.st_mode = mode;
  setModeString();

  return( true );
}


bool
FileStat::setMode( Who who, What what, bool on )
{
  mode_t mode = getMode();
  mode_t change = 0;

  if( (who & OTHER) == true )
    {
      if( (what & READ) == true )   change |= S_IROTH;
      if( (what & WRITE) == true )  change |= S_IWOTH;
      if( (what & EXEC) == true )   change |= S_IXOTH;
    }

  if( (who & GROUP) == true )
    {
      if( (what & READ) == true )   change |= S_IRGRP;
      if( (what & WRITE) == true )  change |= S_IWGRP;
      if( (what & EXEC) == true )   change |= S_IXGRP;
    }

  if( (who & USER) == true )
    {
      if( (what & READ) == true )   change |= S_IRUSR;
      if( (what & WRITE) == true )  change |= S_IWUSR;
      if( (what & EXEC) == true )   change |= S_IXUSR;
    }

  if( on )
    mode |= change;
  else
    mode &= ~change;

  return( setMode( mode ) );
}

bool
FileStat::setUser( uid_t uid )
{
  if( ! good() || name.length() == 0 )
    return( false );

  if( chown( name, uid, getGID() ) )
    {
      sysError = errno;
      return( false );
    }

  st.st_uid = uid;
  setUserString();

  return( true );
}

bool
FileStat::setGroup( gid_t gid )
{
  if( ! good() || name.length() == 0 )
    return( false );

  if( chown( name, getUID(), gid ) )
    {
      sysError = errno;
      return( false );
    }

  st.st_gid = gid;
  setGroupString();

  return( true );
}

bool
FileStat::setOwner( uid_t uid, gid_t gid )
{
  if( ! good() || name.length() == 0 )
    return( false );

  if( chown( name, uid, gid ) )
    {
      sysError = errno;
      return( false );
    }

  st.st_uid = uid;
  st.st_gid = gid;

  setUserString();
  setGroupString();

  return( true );
}

std::ostream &
FileStat::toStream( std::ostream & dest ) const
{
  if( ! good() )
    dest << error();
  else
    {
      dest.setf( std::ios::left );

      dest << getModeString() << ' '
	   << std::setw( 8 ) << getUserName() << ' '
	   << std::setw( 8 ) << getGroupName() << ' '
	;

      dest.unsetf( std::ios::left );

      DateTime mdt( getModificationTime(), true );

      dest << std::setw( 10 ) << getSize() << ' '
	   << mdt << ' '
	   << getName()
	;
    }

  return( dest );
}

bool
FileStat::clear( void )
{
  sysError = 0;
  return( good() );
}

// good - return TRUE if no detected errors
bool
FileStat::good( void ) const
{
  return( sysError == 0 && (fd >= 0 || name.length() > 0 ));
}

// error - return a string describing the current state
const char *
FileStat::error( void ) const
{
  static Str errStr;

  errStr = "FileStat";

  if( good() )
    {
       errStr << ": ok";
    }
  else
    {
      if( sysError )
	errStr << ": '" << name << "' - ("
	       << sysError << ") " << strerror( sysError );
      else
	errStr << ": " << name << " - unknown error";
    }

  return( errStr.c_str() );
}

std::ostream &
FileStat::dumpInfo(
  std::ostream & dest,
  const char *   prefix
  ) const
{

  if( ! FileStat::good() )
    dest << prefix << "Error: " << FileStat::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix;
  toStream( dest );
  dest << '\n';

  dest << prefix << "name:       '" << name << "'\n"
       << prefix << "fd:         " << fd << '\n'
       << prefix << "user:       " << userName << '\n'
       << prefix << "group:      " << groupName << '\n'
       << prefix << "modeString: " << modeString << '\n'
       << prefix << "st_dev:     " << st.st_dev << '\n'
       << prefix << "st_ino:     " << st.st_ino << '\n'
       << prefix << "st_mode:    " << st.st_mode << '\n'
       << prefix << "st_nlink:   " << st.st_nlink << '\n'
       << prefix << "st_uid:     " << st.st_uid << '\n'
       << prefix << "st_gid:     " << st.st_gid << '\n'
       << prefix << "st_rdev:    " << st.st_rdev << '\n'
       << prefix << "st_size:    " << st.st_size << '\n'
       << prefix << "st_atime:   " << st.st_atime << '\n'
       << prefix << "st_mtime:   " << st.st_mtime << '\n'
       << prefix << "st_ctime:   " << st.st_ctime << '\n'
       << prefix << "st_blksize: " << st.st_blksize << '\n'
       << prefix << "st_blocks:  " << st.st_blocks << '\n'
    ;

  dest << '\n';

  return( dest );
}


bool
FileStat::canDo( mode_t uMode, mode_t gMode, mode_t oMode ) const
{
  User	me;

  if( me.getUID() == getUID() || me.effective().getUID() == getUID() )
    return( ( getMode() & uMode ) ? true : false );

  UserGroup grp( getGID(), true );

  if( grp.isMember( me ) )
    return( ( getMode() & gMode ) ? true : false );

  return( ( getMode() & oMode ) ? true : false );
}

void
FileStat::setStrings( bool keepName )
{
  if( ! keepName )
    name = "";

  setUserString();
  setGroupString();
  setModeString();
}

void
FileStat::setStrings( const char * fileName )
{
  name = fileName;

  setUserString();
  setGroupString();
  setModeString();
}

void
FileStat::setUserString( void )
{
  User	u( getUID() );

  userName = u.getName();
}

void
FileStat::setGroupString( void )
{
  UserGroup g( getGID() );

  groupName = g.getName();
}

void
FileStat::setModeString( void )
{
  modeString = "";

  modeString
    << ( isReg()   ? '-' :
	 isDir()   ? 'd' :
	 isBlock() ? 'b' :
	 isChar()  ? 'c' :
	 isFifo()  ? 'p' : '?' )
    << ( canRead( USER )   ? 'r' : '-' )
    << ( canWrite( USER )  ? 'w' : '-' )
    << ( canExec( USER )   ? isSetUID() ? 's' : 'x' : isSetUID() ? 'S' : '-' )
    << ( canRead( GROUP )  ? 'r' : '-' )
    << ( canWrite( GROUP ) ? 'w' : '-' )
    << ( canExec( GROUP )  ? isSetGID() ? 's' : 'x' : isSetGID() ? 'S' : '-' )
    << ( canRead( OTHER )  ? 'r' : '-' )
    << ( canWrite( OTHER ) ? 'w' : '-' )
    << ( canExec( OTHER )  ? 'x' : '-' )
    ;
}

}; // namespace clue
