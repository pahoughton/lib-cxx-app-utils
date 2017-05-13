// 1995-09-19 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Directory.hpp"
#include "DateTime.hpp"
#include "User.hpp"
#include "UserGroup.hpp"
#include "compare"
#include "bit"

#include <algorithm>
#include <glob.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>


using namespace std::rel_ops;

namespace clue {

//
// * * * Sort Orders * * *
//

#define DIRORDER    SortOrder< FileStat >

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

std::ostream &
Directory::DirField::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{
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

std::ostream &
Directory::DirFieldName::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  Str pre;
  pre = prefix;
  pre << "DirField::";

  DirField::dumpInfo( dest, pre );

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

std::ostream &
Directory::DirFieldSize::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  Str pre;
  pre = prefix;
  pre << "DirField::";

  DirField::dumpInfo( dest, pre );

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

std::ostream &
Directory::DirFieldTime::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  Str pre;
  pre = prefix;
  pre << "DirFieldd::";

  DirField::dumpInfo( dest, pre );

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

std::ostream &
Directory::Where::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  dest << prefix << "["
       << refCount << ","
       << leftDepth << ","
       << rightDepth << "]\n";

  Str pre;

  if( fld )
    {
      pre = prefix;
      pre << "fld:";
      fld->dumpInfo( dest, pre );
    }


  if( left )
    {
      pre = prefix;
      pre << "l:";
      left->dumpInfo( dest, pre );
      dest << prefix << (andLR ? "and" : "or" ) << '\n';
    }


  if( right )
    {
      pre = prefix;
      pre << "r:";
      right->dumpInfo( dest, pre );
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
  std::sort( list.begin(), list.end(), dirOrder );
  return( true );
}

std::ostream &
Directory::toStream( std::ostream & dest ) const
{
  for( const_iterator them = begin();
       them != end();
       ++ them )
    {
      dest << *them << std::endl;
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

  errStr = "Directory";

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


std::ostream &
Directory::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

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
	  dest << pre << *them << std::endl;
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

	  for( unsigned int g = 0; g < files.gl_pathc; ++ g )
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

}; // namespace clue
