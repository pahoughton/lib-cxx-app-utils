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
// Revision 2.4  1996/05/01 11:02:23  houghton
// Bug-Fix: updated to reflect changes in Bitmask constructors.
//
// Revision 2.3  1995/12/31 11:25:31  houghton
// Bug Fix - change the order of includes.
//
// Revision 2.2  1995/12/04 11:20:33  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:47:11  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:49:26  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include "FileStat.hh"
#include <UserGroup.hh>
#include <User.hh>
#include <DateTime.hh>
#include <Bit.hh>
#include <iomanip>
#include <cstring>
#include <cerrno>
#else
#include "FileStat.hh"
#include <UserGrp.hh>
#include <User.hh>
#include <DateTime.hh>
#include <Bit.hh>
#include <iomanip>
#include <cstring>
#include <cerrno>
#endif

#if defined( CLUE_DEBUG )
#include <FileStat.ii>
#endif

CLUE_VERSION(
  FileStat,
  "$Id$");

const int FileStat::badFd = -1;

const FileStat::Who 	FileStat::OTHER( Bit( 0 ) );
const FileStat::Who 	FileStat::GROUP( Bit( 1 ) );
const FileStat::Who 	FileStat::USER( Bit( 2 ) );
const FileStat::Who 	FileStat::ALL( 0x07, false );

const FileStat::What	FileStat::EXEC( Bit( 0 ) );
const FileStat::What	FileStat::WRITE( Bit( 1 ) );
const FileStat::What	FileStat::READ( Bit( 2 ) );


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

const char *
FileStat::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, name.getVersion( false ) ) );
}

ostream &
FileStat::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << FileStat::getClassName() << ":\n"
	 << FileStat::getVersion() << '\n';
  
  
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

    


