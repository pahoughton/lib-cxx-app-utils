//
// File:        Directory.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Compiled sources for Directory
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/19/95 08:18
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//

#include "Directory.hh"
#include "DateTime.hh"
#include "User.hh"
#include "UserGroup.hh"
#include "Compare.hh"
#include "Bit.hh"
#include <algorithm>
#include <glob.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

#if defined( STLUTILS_DEBUG )
#include "Directory.ii"
#endif

STLUTILS_VERSION(
  Directory,
  "%PID%");


//
// * * * Sort Orders * * *
//

#if defined( Linux )
#define DIRORDER    SortOrder< FileStat >
#else
#define DIRORDER    Directory::DirOrder
#endif

class DirSortName : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    return( one.getName() < two.getName() );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortName( *this ) );
  };
};
    
class DirSortExt : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    return( one.getName().getExt() < two.getName().getExt() );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortExt( *this ) );
  };
};
    
class DirSortSize : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    return( one.getSize() < two.getSize() );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortSize( *this ) );
  };
};
    
class DirSortTime : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    return( one.getModificationTime() < two.getModificationTime() );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortTime( *this ) );
  };
};
    
class DirSortUser : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    User uOne( one.getUID() ); User uTwo( two.getUID() );
    return( uOne < uTwo );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortUser( *this ) );
  };
};
    
class DirSortUserGroup : public DIRORDER::LessBase
{
public:
  bool	operator() ( const FileStat & one, const FileStat & two ) const {
    UserGroup ugOne( one.getUID() ); UserGroup ugTwo( two.getUID() );
    return( ugOne < ugTwo );
  };
  
  DIRORDER::LessBase *   dup( void ) const {
    return( new DirSortUserGroup( *this ) );
  };
};
    
const char *	Directory::DirField::CompTypeString[] =
{
  "==",
  "!=",
  "<",
  ">",
  "<=",
  ">=",
  0
};

const Directory::DirFieldName	Directory::Name;
const Directory::DirFieldSize	Directory::Size;
const Directory::DirFieldTime	Directory::Time;

static DirSortName	DirNameSort;
static DirSortExt	DirExtSort;
static DirSortSize	DirSizeSort;
static DirSortTime	DirTimeSort;
static DirSortUser	DirUserSort;
static DirSortUserGroup	DirGroupSort;

const Directory::DirOrder	Directory::SortName( DirNameSort );
const Directory::DirOrder	Directory::SortExt( DirExtSort );
const Directory::DirOrder	Directory::SortSize( DirSizeSort );
const Directory::DirOrder	Directory::SortTime( DirTimeSort );
const Directory::DirOrder	Directory::SortUser( DirUserSort );
const Directory::DirOrder	Directory::SortUserGroup( DirGroupSort );

const Directory::Option		Directory::Default( Bit( 0 ) );
const Directory::Option		Directory::Recurs( Bit( 1 ) );
const Directory::Option		Directory::All( Bit( 2 ) );


// Directory::DirField methods

Directory::DirField::~DirField( void )
{
}

const char *
Directory::DirField::getClassName( void ) const
{
  return( "Directory::DirField" );
}

ostream &
Directory::DirField::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::DirField::getClassName() << ":\n"
      ;
  
  dest << prefix << "comp:       " << CompTypeString[ comp ] << '\n'
       << prefix << "refCount:   " << refCount << '\n'
    ;
  
  return( dest );
}

// Directory::DirFieldName mehtods

Directory::DirFieldName::~DirFieldName( void )
{
}

bool
Directory::DirFieldName::match( const FileStat & stat ) const
{
  switch( comp )
    {
    case Equal:
      return( value.match( stat.getName() ) );

    case NotEqual:
      return( ! value.match( stat.getName() ) );

    case Less:
      return( stat.getName() < value );

    case More:
      return( stat.getName() > value  );
      
    case LessEqual:
      return( stat.getName() < value ||
	      value.match( stat.getName() ) );

    case MoreEqual:
      return( stat.getName() > value ||
	      value.match( stat.getName() ) );
    }
  
  return( false );
}

Directory::DirField *
Directory::DirFieldName::dup( void ) const
{
  return( new DirFieldName( *this ) );
}

const char *
Directory::DirFieldName::getClassName( void ) const
{
  return( "Directory::DirFieldName" );
}

ostream &
Directory::DirFieldName::dumpInfo( 
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::DirFieldName::getClassName() << ":\n"
      ;

  Str pre;
  pre = prefix;
  pre << DirField::getClassName() << "::";

  DirField::dumpInfo( dest, pre, false );
  
  dest << prefix << "value:       " << value << '\n'
    ;
  
  return( dest );
}

// Directory::DirFieldSize methods

Directory::DirFieldSize::~DirFieldSize( void )
{
}

bool
Directory::DirFieldSize::match( const FileStat & stat ) const
{
  // Special case for directories, always match size
  if( stat.isDir() )
    return( true );
  
  switch( comp )
    {
    case Equal:
      return( stat.getSize() == value );

    case NotEqual:
      return( stat.getSize() != value);

    case Less:
      return( stat.getSize() < value );

    case More:
      return( stat.getSize() > value );

    case LessEqual:
      return( stat.getSize() <= value );

    case MoreEqual:
      return( stat.getSize() >= value );
    }

  return( false );
}

Directory::DirField *
Directory::DirFieldSize::dup( void ) const
{
  return( new DirFieldSize( *this ) );
}

const char *
Directory::DirFieldSize::getClassName( void ) const
{
  return( "Directory::DirFieldSize" );
}

ostream &
Directory::DirFieldSize::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::DirFieldSize::getClassName() << ":\n"
      ;

  Str pre;
  pre = prefix;
  pre << DirField::getClassName() << "::";

  DirField::dumpInfo( dest, pre, false );
  
  dest << prefix << "value:       " << value << '\n'
    ;
  
  return( dest );
}

// Directory::DirFieldTime methods

Directory::DirFieldTime::~DirFieldTime( void )
{
}

bool
Directory::DirFieldTime::match( const FileStat & stat ) const
{
  switch( comp )
    {
    case Equal:
      return( stat.getModificationTime() == value );

    case NotEqual:
      return( stat.getModificationTime() != value);

    case Less:
      return( stat.getModificationTime() < value );

    case More:
      return( stat.getModificationTime() > value );

    case LessEqual:
      return( stat.getModificationTime() <= value );

    case MoreEqual:
      return( stat.getModificationTime() >= value );
    }

  return( false );
}

Directory::DirField *
Directory::DirFieldTime::dup( void ) const
{
  return( new DirFieldTime( *this ) );
}

const char *
Directory::DirFieldTime::getClassName( void ) const
{
  return( "Directory::DirFieldTime" );
}

ostream &
Directory::DirFieldTime::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::DirFieldTime::getClassName() << ":\n"
      ;

  Str pre;
  pre = prefix;
  pre << DirField::getClassName() << "::";

  DirField::dumpInfo( dest, pre, false );
  
  dest << prefix << "value:       " << DateTime( value, true ) << '\n'
    ;
  
  return( dest );
}

// Directory::Where mehtods

Directory::Where::~Where( void )
{
  if( fld && fld->delRef() )
    delete fld;
  if( left && left->delRef() )
    delete left;
  if( right && right->delRef() )
    delete right;
}

const char *
Directory::Where::getClassName( void ) const
{
  return( "Directory::Where" );
}

ostream &
Directory::Where::dumpInfo( 
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::Where::getClassName() << ":\n"
      ;

  dest << prefix << "["
       << refCount << ","
       << leftDepth << ","
       << rightDepth << "]\n";

  Str pre;

  if( fld )
    {
      pre = prefix;
      pre << "fld:";
      fld->dumpInfo( dest, pre, false );
    }
	

  if( left )
    {
      pre = prefix;
      pre << "l:";
      left->dumpInfo( dest, pre, false );
      dest << prefix << (andLR ? "and" : "or" ) << '\n';
    }
  

  if( right )
    {
      pre = prefix;
      pre << "r:";
      right->dumpInfo( dest, pre, false );
    }
  
  return( dest );
}

bool
Directory::Where::match( const FileStat & entry ) const
{
  if( isField() )
    return( getField().match( entry ) );

  if( isAnd() )
    return( getFirst().match( entry ) &&
	    getSecond().match( entry ) );
  else
    return( getFirst().match( entry ) ||
	    getSecond().match( entry ) );
}

Directory::Directory( void )
  : options( Default ),
    where( 0 ),
    order( 0 ),
    osErrno( 0 )
{
}

Directory::Directory( const char * path, const Option & opts )
  : options( opts ),
    where( 0 ),
    order( 0 ),
    osErrno( 0 )
{
  set( path, opts );
}

Directory::Directory(
  const char *	    path,
  const DirOrder &  dirOrder,
  const Option &    opts
  )
  : options( opts ),
    where( 0 ),
    order( 0 ),
    osErrno( 0 )
{
  set( path, dirOrder, opts );
}

Directory::Directory(
  const char *	    path,
  const Where &	    whereClause,
  const Option &    opts
  )
  : options( opts ),
    where( 0 ),
    order( 0 ),
    osErrno( 0 )
{
  set( path, whereClause, opts  );
}

Directory::Directory(
  const char *	    path,
  const Where &	    whereClause,
  const DirOrder &  dirOrder,
  const Option &    opts
  )
  : options( opts ),
    where( 0 ),
    order( 0 ),
    osErrno( 0 )
{
  set( path, whereClause, dirOrder, opts );
}

Directory::Directory( const Directory & from )
  : pattern( from.pattern ),
    options( from.options ),
    where( from.where ),
    order( from.order ),
    list( from.list ),
    osErrno( from.osErrno ),
    errorPath( from.errorPath )
{
}

Directory::~Directory( void )
{
}

bool
Directory::set( const char * path, const Option & opts )
{
  return( set( path, opts, 0, 0 ) );
}

bool
Directory::set(
  const char *	    path,
  const DirOrder &  dirOrder,
  const Option &    opts
  )
{
  return( set( path, opts, 0, & dirOrder ) );
}

bool
Directory::set(
  const char *	    path,
  const Where &	    whereClause,
  const Option &    opts
  )
{
  return( set( path, opts, &whereClause, 0 ) );
}

bool
Directory::set(
  const char *	    path,
  const Where &	    whereClause,
  const DirOrder &  dirOrder,
  const Option &    opts
  )
{
  return( set( path, opts, &whereClause, &dirOrder ) );
}

bool
Directory::sort( const DirOrder & dirOrder )
{
  ::sort( list.begin(), list.end(), dirOrder );
  return( true );
}

ostream &
Directory::toStream( ostream & dest ) const
{
  for( const_iterator them = begin();
       them != end();
       ++ them )
    {
      dest << *them << endl;
    }
  return( dest );
}

bool
Directory::good( void ) const
{
  return( osErrno == 0 );
}

const char *
Directory::error( void ) const
{
  static Str errStr;

  errStr = Directory::getClassName();

  if( good() )
    {
       errStr += ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( osErrno != 0 )
	errStr << ": '" << errorPath << "' - " << strerror( osErrno );
	  
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
Directory::getClassName( void ) const
{
  return( "Directory" );
}

const char *
Directory::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Directory::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Directory::getClassName() << ":\n"
	 << Directory::getVersion() << '\n';

  if( ! Directory::good() )
    dest << prefix << "Error: " << Directory::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "pattern:    '" << pattern << "'\n";

  dest << prefix << "options:    ";
      
  if( options == true )
    {
      if( (options & Default) == true )
	dest << "Default ";
      if( (options & All) == true )
	dest << "All ";
      if( (options & Recurs) == true )
	dest << "Recurs ";
    }
  else
    {
      dest << "None";
    }

  if( ! empty() )
    {
      Str pre;
      pre = prefix;
      pre << "files:      ";
      for( const_iterator them = begin();
	   them != end();
	   ++ them )
	{
	  dest << pre << *them << endl;
	}
    }
  else
    {
      dest << prefix << "files:      (empty)";
    }
  
  return( dest );
}


bool
Directory::set(
  const char *	    path,
  const Option &    opts,
  const Where *	    whereClause,
  const DirOrder *  dirOrder
  )
{
  pattern = path;
  options = opts;
  where = whereClause;
  order = dirOrder;
  
  return( buildDirList() );
}

bool
Directory::buildDirList( void )
{
  
  osErrno = 0;
  errorPath = "";
  
  list.erase( list.begin(), list.end() );
  
  Str::size_type wild = pattern.find_first_of( "*?[" );

  if( wild != Str::npos )
    {
      glob_t	files;

      int  ret = glob( pattern, 0, 0, &files );
      // ( options & All ) ? GLOB_PERIOD : 0,
      // 0,
      // &files );
      
      if( ! ret )
	{
	  FileStat	fStat;
	  bool		status = true;
	  
	  for( int g = 0; g < files.gl_pathc; ++ g )
	    {
	      fStat.stat( files.gl_pathv[g] );

	      if( ! where || where->match( fStat ) )
		{
		  list.push_back( fStat );
	      
		  if( (options & Recurs) == true && fStat.isDir() )
		    {
		      DIR * dir = opendir( fStat.getName() );

		      if( ! dir )
			{
			  status = setError( errno, fStat.getName() );
			  break;
			}
		      else
			{
			  status = readDir( dir,
					    fStat.getName(),
					    where,
					    options );
			  closedir( dir );
			  if( ! status )
			    break;
			}
		    }
		}
	    }
	  
	  globfree( &files );
	  
	  if( ! status )
	    return( status );
	}
      else
	{
	  globfree( &files );
	  if( ret == GLOB_NOMATCH )
	    {
	      if( pattern.getPath().size() )
		{
		  FileStat patDirStat( pattern.getPath() );

		  if( patDirStat.good() )
		    {
		      if( patDirStat.isDir() )
			// no error, just did not find any files.
			return( true );
		      else
			return( setError( ENOTDIR, patDirStat.getName() ) );
		    }
		  else
		    {
		      return( setError( ENOENT, pattern.getPath() ) );
		    }
		}
	      else
		{
		  // no error, just did not find any files.
		  return( true );
		}
	    }
	  else
	    {
	      return( setError( errno, pattern ) );
	    }
	}
    }
  else
    {
      DIR * dir = opendir( pattern );

      if( ! dir )
	{
	  if( errno == ENOTDIR )
	    {
	      FileStat	stat( pattern );
	      
	      if( ! stat.good() )
		{
		  return( setError( stat.getSysError(), pattern ) );
		}

	      list.push_back( stat );
	    }
	  else
	    {
	      return( setError( errno, pattern ) );
	    }  
	}
      else
	{
	  bool status = readDir( dir, pattern, where, options );
	  closedir( dir );
	  if( ! status )
	    return( false );
	}
    }

  if( order )
    sort( *order );
  
  return( true );
}

bool
Directory::setError( int osErr, const char * errPath )
{
  osErrno = osErr;
  errorPath = errPath;
  return( good() );
}

bool
Directory::readDir(
  DIR *		    dir,
  const FilePath &  dirPath,
  const Where *	    whereClause,
  const Option &    opts
  )
{
  for( struct dirent * dEnt = readdir( dir );
       dEnt != 0;
       dEnt = readdir( dir ) )
    {
      if( bool(opts & All) == false  && (dEnt->d_name[0] == '.') )
	continue;
      
      FilePath name( dEnt->d_name );
      
      name.setPrefix( dirPath );
      
      FileStat fs( name );

      if( ! whereClause || whereClause->match( fs ) )
	{
      
	  list.push_back( fs );
      
	  if( fs.good() && fs.isDir() &&
	      strcmp( dEnt->d_name, "." ) && strcmp( dEnt->d_name, ".." ) &&
	      ( opts & Recurs ) == true )
	    {
	      FilePath subDirPath;
	      
	      subDirPath = name;
	      
	      DIR * subDir = opendir( subDirPath );
	      
	      if( ! subDir )
		return( setError( errno, subDirPath ) );
	      else
		{
		  bool status = readDir( subDir, subDirPath, whereClause, opts );
		  closedir( subDir );
		  if( ! status )
		    return( false );
		}
	    }
	}
    }
  return( true );
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:05:45  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.8  2000/03/10 11:33:49  houghton
// Change: cleanup dumpInfo output.
// Change: added '[' to wild card characters.
//
// Revision 4.7  1999/10/28 14:20:09  houghton
// Bug-Fixes
//
// Revision 4.6  1999/10/06 12:47:54  houghton
// Changed: now if a valid single file name is pass that is not
//     a direcotry it will be put in the dir list. (before it would fail
//     because the file was not a directory).
//
// Revision 4.5  1998/10/13 16:19:38  houghton
// Port(Linux): work around compiler problem using SortOrder<> typedef'ed
//     in the class.
//
// Revision 4.4  1998/10/13 15:17:33  houghton
// Bug-Fix: was missing a call to globfree().
//
// Revision 4.3  1998/07/20 11:20:18  houghton
// Port(Hpux10): Changed 'and' to 'andLR'. 'and' is now a keyword.
//
// Revision 4.2  1998/04/02 14:16:01  houghton
// Bug-Fix: was calling globfree multiple multiple times.
//
// Revision 4.1  1997/09/17 15:12:22  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:19  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/07/20 18:50:30  houghton
// Changed so that no matching files found is not an error.
//
// Revision 3.4  1997/07/11 15:55:53  houghton
// Bug-Fix: set() was not emptying list before adding new entries.
// Bug-Fix: convert (opts & All) to a bool.
//
// Revision 3.3  1997/06/09 14:31:16  houghton
// Removed 'include dirent.h' now include StlUtilsDirent.hh is in .hh file.
// Changed AIX41 had to instanciate the sort objects before I could pass
//     them to the DirOrder objects.
//
// Revision 3.2  1997/06/09 12:04:03  houghton
// Completed initial coding.
//
// Revision 3.1  1996/11/14 01:25:18  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:06  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  13:48:11  houghton
// New implementation
//
