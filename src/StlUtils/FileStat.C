//
// File:        FileStat.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/17/95 08:38 
//
// Revision History:
//
// $Log$
// Revision 1.2  1995/11/05 12:55:20  houghton
// Put inlines in their own source file
// Change to be more consistant with the C++ Standard
//
//

#include "FileStat.hh"

#include <User.hh>
#include <UserGroup.hh>
#include <DateTime.hh>

#include <iomanip>

#include <cstring>

#ifdef   CLUE_DEBUG
#define  inline
#include <FileStat.ii>
#endif

const char FileStat::version[] =
LIB_CLUE_VERSION
"$Id$";

const int FileStat::badFd = -1;

const FileStat::Who 	FileStat::OTHER( 0 );
const FileStat::Who 	FileStat::GROUP( 1 );
const FileStat::Who 	FileStat::USER( 2 );
const FileStat::Who 	FileStat::ALL( 0x07, false );

const FileStat::What	FileStat::EXEC( 0 );
const FileStat::What	FileStat::WRITE( 1 );
const FileStat::What	FileStat::READ( 2 );


bool
FileStat::setMode( mode_t mode )
{
  if( ! good() || name.size() == 0 )    
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

  if( who & OTHER )
    {
      if( what & READ )	    change |= S_IROTH;
      if( what & WRITE )    change |= S_IWOTH;
      if( what & EXEC )	    change |= S_IXOTH;
    }
  
  if( who & GROUP )
    {
      if( what & READ )	    change |= S_IRGRP;
      if( what & WRITE )    change |= S_IWGRP;
      if( what & EXEC )	    change |= S_IXGRP;
    }
  
  if( who & USER )
    {
      if( what & READ )	    change |= S_IRUSR;
      if( what & WRITE )    change |= S_IWUSR;
      if( what & EXEC )	    change |= S_IXUSR;
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
  if( ! good() || name.size() == 0 )
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
  if( ! good() || name.size() == 0 )
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
  if( ! good() || name.size() == 0 )
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

  
// good - return TRUE if no detected errors
bool
FileStat::good( void ) const
{
  return( sysError == 0 && (fd >= 0 || name.size() > 0 ));
}

// error - return a string describing the current state
const char *
FileStat::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ": ";

  if( good() )
    {
       errStr << "ok";
    }
  else
    {
      if( sysError )
	errStr << strerror( sysError );
      else
	errStr << "unknown error";
    }

  return( errStr );
}

// getClassName - return the name of this class
const char *
FileStat::getClassName( void ) const
{
  return( "FileStat" );
}

ostream &
FileStat::toStream( ostream & dest ) const
{
  if( ! good() )
    dest << error();
  else
    {
      dest.setf( ios::left );
      
      dest << getModeString() << ' '
	   << setw( 8 ) << getUserName() << ' '
	   << setw( 8 ) << getGroupName() << ' '
	;
      
      dest.unsetf( ios::left );

      DateTime mdt( getModificationTime(), true );
      
      dest << setw( 10 ) << getSize() << ' '
	   << mdt << ' '
	   << getName()
	;
    }

  return( dest );
}

ostream &
FileStat::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    ";
  toStream( dest );
  dest << '\n';
  
  dest << "    Name:       '" << name << "'\n"
       << "    Fd:         " << fd << '\n'
       << "    User:       " << userName << '\n'
       << "    Group:      " << groupName << '\n'
       << "    ModeString: " << modeString << '\n'
       << "    st_dev:     " << st.st_dev << '\n'
       << "    st_ino:     " << st.st_ino << '\n'
       << "    st_mode:    " << st.st_mode << '\n'
       << "    st_nlink:   " << st.st_nlink << '\n'
       << "    st_uid:     " << st.st_uid << '\n'
       << "    st_gid:     " << st.st_gid << '\n'
       << "    st_rdev:    " << st.st_rdev << '\n'
       << "    st_size:    " << st.st_size << '\n'
       << "    st_atime:   " << st.st_atime << '\n'
       << "    st_mtime:   " << st.st_mtime << '\n'
       << "    st_ctime:   " << st.st_ctime << '\n'
       << "    st_blksize: " << st.st_blksize << '\n'
       << "    st_blocks:  " << st.st_blocks << '\n'
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
    name.reset();

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
  modeString.reset();
  
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

    


