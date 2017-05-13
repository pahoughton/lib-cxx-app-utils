#ifndef _clue_Directory_hpp_
#define _clue_Directory_hpp_
/* 1995-09-19 (cc) Paul Houghton <paul4hough@gmail.com>

   Provides a list of files in a directory.
*/

#include <clue/SortOrder.hpp>
#include <clue/FileStat.hpp>
#include <clue/Bitmask.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <dirent.h>

namespace clue {

class Directory
{

public:

  // Directory Fields for Where Clauses
  class DirField
  {
  public:

    enum CompareType
    {
      Equal,
      NotEqual,
      Less,
      More,
      LessEqual,
      MoreEqual
    };

    inline DirField( void );
    virtual ~DirField( void );

    inline void	    addRef( void );
    inline bool	    delRef( void );

    virtual bool	match( const FileStat & stat ) const = 0;
    virtual DirField *	dup( void ) const = 0;

    virtual std::ostream & dumpInfo( std::ostream & dest = std::cerr,
				     const char *   prefix = "    " ) const;

  protected:

    inline DirField( CompareType compType );

    static const char *	    CompTypeString[];

    CompareType  comp;
    size_t	 refCount;

  };

  class DirFieldName : public DirField
  {
  public:

    inline DirFieldName( void );
    inline DirFieldName( const DirFieldName & from );

    virtual ~DirFieldName( void );

    virtual bool match( const FileStat & stat ) const;
    virtual DirField *	dup( void ) const;

    inline DirFieldName	operator == ( const char * rhs ) const;
    inline DirFieldName	operator != ( const char * rhs ) const;
    inline DirFieldName	operator <  ( const char * rhs ) const;
    inline DirFieldName	operator >  ( const char * rhs ) const;
    inline DirFieldName	operator <= ( const char * rhs ) const;
    inline DirFieldName	operator >= ( const char * rhs ) const;

    virtual std::ostream &  dumpInfo( std::ostream &		dest = std::cerr,
				      const char *	prefix = "    " ) const;

  protected:

    inline DirFieldName( CompareType compType, const char * compValue );

    FilePath value;

  private:

  };

  class DirFieldSize : public DirField
  {
  public:

    typedef FileStat::size_type	    size_type;

    inline DirFieldSize( void );
    inline DirFieldSize( const DirFieldSize & from );

    virtual ~DirFieldSize( void );

    virtual bool match( const FileStat & stat ) const;
    virtual DirField *	dup( void ) const;

    inline DirFieldSize	operator == ( size_type rhs ) const;
    inline DirFieldSize	operator != ( size_type rhs ) const;
    inline DirFieldSize	operator <  ( size_type rhs ) const;
    inline DirFieldSize	operator >  ( size_type rhs ) const;
    inline DirFieldSize	operator <= ( size_type rhs ) const;
    inline DirFieldSize	operator >= ( size_type rhs ) const;

    virtual std::ostream &  dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  private:

    inline DirFieldSize( CompareType compType, size_type size );

    size_type value;
  };

  class DirFieldTime : public DirField
  {
  public:

    inline DirFieldTime( void );
    inline DirFieldTime( const DirFieldTime & from );

    virtual ~DirFieldTime( void );

    virtual bool match( const FileStat & stat ) const;
    virtual DirField *	dup( void ) const;

    inline DirFieldTime	operator == ( time_t rhs ) const;
    inline DirFieldTime	operator != ( time_t rhs ) const;
    inline DirFieldTime	operator <  ( time_t rhs ) const;
    inline DirFieldTime	operator >  ( time_t rhs ) const;
    inline DirFieldTime	operator <= ( time_t rhs ) const;
    inline DirFieldTime	operator >= ( time_t rhs ) const;

    virtual std::ostream &  dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  private:

    inline DirFieldTime( CompareType compType, time_t size );

    time_t value;
  };

  class Where
  {
  public:

    inline Where( void );
    inline Where( const DirField & fld );
    inline Where( const Where & where );
    inline Where( const Where & left, bool andLR, const Where & right );

    virtual ~Where( void );

    inline Where	    operator && ( const Where & where ) const;
    inline Where	    operator || ( const Where & where ) const;

    friend inline Where	    operator && ( const DirField & fld,
					  const Where &	    where );
    friend inline Where	    operator || ( const DirField & fld,
					  const Where &	    where );

    inline void		addRef( void );
    inline bool		delRef( void );

    virtual std::ostream &  dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  protected:

    friend class Directory;

    inline bool			isField( void ) const;
    inline bool			isAnd( void ) const;
    inline const DirField &	getField( void ) const;
    inline const Where &	getFirst( void ) const;
    inline const Where &	getSecond( void ) const;

    bool			match( const FileStat & entry ) const;

  private:

    DirField *	fld;

    Where *	left;
    bool	andLR;
    Where *	right;

    size_t    refCount;
    size_t    leftDepth;
    size_t    rightDepth;

  };

  // Types

  typedef std::vector< FileStat >   DirList;
  typedef DirList::iterator	    iterator;
  typedef DirList::const_iterator   const_iterator;
  typedef DirList::size_type	    size_type;

  typedef SortOrder< FileStat >	    DirOrder;
  typedef Bitmask		    Option;

  // Static instance values

  static const DirFieldName	Name;
  static const DirFieldSize	Size;
  static const DirFieldTime	Time;

  static const DirOrder		SortName;
  static const DirOrder		SortExt;
  static const DirOrder		SortSize;
  static const DirOrder		SortTime;
  static const DirOrder		SortUser;
  static const DirOrder		SortUserGroup;

  static const Option		Default;
  static const Option		Recurs;
  static const Option		All;

  // Mehtods

  Directory( void );

  Directory( const char * path, const Option & opts = Default );

  Directory( const char *	path,
	     const DirOrder &	order,
	     const Option &	opts = Default );

  Directory( const char *	path,
	     const Where &	where,
	     const Option &	opts = Default );

  Directory( const char *	path,
	     const Where &	where,
	     const DirOrder &	order,
	     const Option &	opts = Default );

  Directory( const Directory & from );

  virtual ~Directory( void );

  inline iterator		begin( void );
  inline iterator		end( void );
  inline const_iterator		begin( void ) const;
  inline const_iterator		end( void ) const;

  inline size_type		size( void ) const;
  inline bool			empty( void ) const;

  bool		set( const char * path, const Option & opts = Default );
  bool		set( const char *	path,
  		     const DirOrder &   order,
  		     const Option &	opt = Default );
  bool		set( const char *	path,
		     const Where &	where,
		     const Option &	opt = Default );
  bool		set( const char *	path,
		     const Where &	where,
  		     const DirOrder &   order,
		     const Option &	opt = Default );

  inline bool		    reread( void );
  inline bool		    reread( const Where & where );

  bool			    sort( const DirOrder & order );

  virtual std::ostream &    toStream( std::ostream & dest ) const;

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

protected:

  bool	    set( const char *	    path,
		 const Option &	    opts,
		 const Where *	    where,
		 const DirOrder *   order );

  bool	    buildDirList( void );

  bool	    setError( int osErr, const char * errPath );

private:

  bool	readDir( DIR *		    dir,
		 const FilePath &   dirPath,
		 const Where *	    where,
		 const Option &	    opts );

  FilePath	    pattern;
  Option	    options;
  const	Where *	    where;
  const DirOrder *  order;
  DirList	    list;

  int		osErrno;
  FilePath	errorPath;

};


inline
Directory::DirField::DirField( void )
  : comp( Equal ),
    refCount( 1 )
{
}

inline
Directory::DirField::DirField( CompareType compType )
  : comp( compType ),
    refCount( 1 )
{
}

inline
void
Directory::DirField::addRef( void )
{
  refCount++;
}

inline
bool
Directory::DirField::delRef( void )
{
  if( refCount > 0 )
    refCount--;
  return( refCount == 0 );
}

// Directory::DirFieldName inlines

inline
Directory::DirFieldName::DirFieldName( void )
{
}

inline
Directory::DirFieldName::DirFieldName( const DirFieldName & from )
  : Directory::DirField( from ),
    value( from.value )
{
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator == ( const char * rhs ) const
{
  return( DirFieldName( Equal, rhs ) );
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator != ( const char * rhs ) const
{
  return( DirFieldName( NotEqual, rhs ) );
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator < ( const char * rhs ) const
{
  return( DirFieldName( Less, rhs ) );
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator > ( const char * rhs ) const
{
  return( DirFieldName( More, rhs ) );
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator <= ( const char * rhs ) const
{
  return( DirFieldName( LessEqual, rhs ) );
}

inline
Directory::DirFieldName
Directory::DirFieldName::operator >= ( const char * rhs ) const
{
  return( DirFieldName( MoreEqual, rhs ) );
}

inline
Directory::DirFieldName::DirFieldName(
  CompareType	compType,
  const char *	compValue
  )
  : Directory::DirField( compType ),
    value( compValue )
{
}

// Directory::DirFieldSize inlines

inline
Directory::DirFieldSize::DirFieldSize( void )
  : value( 0 )
{
}

inline
Directory::DirFieldSize::DirFieldSize( const DirFieldSize & from )
  : Directory::DirField( from ),
    value( from.value )
{
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator == ( size_type rhs ) const
{
  return( DirFieldSize( Equal, rhs ) );
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator != ( size_type rhs ) const
{
  return( DirFieldSize( NotEqual, rhs ) );
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator < ( size_type rhs ) const
{
  return( DirFieldSize( Less, rhs ) );
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator > ( size_type rhs ) const
{
  return( DirFieldSize( More, rhs ) );
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator <= ( size_type rhs ) const
{
  return( DirFieldSize( LessEqual, rhs ) );
}

inline
Directory::DirFieldSize
Directory::DirFieldSize::operator >= ( size_type rhs ) const
{
  return( DirFieldSize( MoreEqual, rhs ) );
}

inline
Directory::DirFieldSize::DirFieldSize(
  CompareType	compType,
  size_type	compValue
  )
  : Directory::DirField( compType ),
    value( compValue )
{
}

// Directory::DirFieldTime inlines

inline
Directory::DirFieldTime::DirFieldTime( void )
  : value( 0 )
{
}

inline
Directory::DirFieldTime::DirFieldTime( const DirFieldTime & from )
  : Directory::DirField( from ),
    value( from.value )
{
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator == ( time_t rhs ) const
{
  return( DirFieldTime( Equal, rhs ) );
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator != ( time_t rhs ) const
{
  return( DirFieldTime( NotEqual, rhs ) );
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator < ( time_t rhs ) const
{
  return( DirFieldTime( Less, rhs ) );
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator > ( time_t rhs ) const
{
  return( DirFieldTime( More, rhs ) );
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator <= ( time_t rhs ) const
{
  return( DirFieldTime( LessEqual, rhs ) );
}

inline
Directory::DirFieldTime
Directory::DirFieldTime::operator >= ( time_t rhs ) const
{
  return( DirFieldTime( MoreEqual, rhs ) );
}

inline
Directory::DirFieldTime::DirFieldTime(
  CompareType	compType,
  time_t	compValue
  )
  : Directory::DirField( compType ),
    value( compValue )
{
}

// Directory::Where inlines

inline
Directory::Where::Where( void )
  : fld( 0 ),
    left( 0 ),
    andLR( false ),
    right( 0 ),
    refCount( 1 ),
    leftDepth( 0 ),
    rightDepth( 0 )
{
}

inline
Directory::Where::Where( const DirField & dirFld )
  : fld( dirFld.dup() ),
    left( 0 ),
    andLR( false ),
    right( 0 ),
    refCount( 1 ),
    leftDepth( 0 ),
    rightDepth( 0 )
{
}

inline
Directory::Where::Where( const Where & from )
  : fld( from.fld ),
    left( from.left ),
    andLR( from.andLR ),
    right( from.right ),
    refCount( 1 ),
    leftDepth( from.leftDepth ),
    rightDepth( from.rightDepth )
{
  if( fld )
    fld->addRef();

  if( left )
    left->addRef();

  if( right )
    right->addRef();
}

inline
Directory::Where::Where(
  const Where & leftWhere,
  bool		lrAnd,
  const Where & rightWhere
  )
  : fld( 0 ),
    left( new Where( leftWhere ) ),
    andLR( lrAnd ),
    right( new Where( rightWhere ) ),
    refCount( 1 ),
    leftDepth( leftWhere.leftDepth + 1 ),
    rightDepth( rightWhere.rightDepth + 1 )
{
}

inline
Directory::Where
Directory::Where::operator && ( const Where & rhs ) const
{
  Where w( *this, true, rhs );
  return( w );
}

inline
Directory::Where
Directory::Where::operator || ( const Where & rhs ) const
{
  Where w( *this, false, rhs );
  return( w );
}

inline
Directory::Where
operator && ( const Directory::DirField & lhs, const Directory::Where & rhs )
{
  Directory::Where lw( lhs );
  Directory::Where w( lw, true, rhs );
  return( w );
}

inline
Directory::Where
operator || ( const Directory::DirField & lhs, const Directory::Where & rhs )
{
  Directory::Where lw( lhs );
  Directory::Where w( lw, false, rhs );
  return( w );
}

inline
void
Directory::Where::addRef( void )
{
  ++ refCount;
}

inline
bool
Directory::Where::delRef( void )
{
  if( refCount )
    -- refCount;
  return( refCount == 0 );
}

inline
bool
Directory::Where::isField( void ) const
{
  return( fld != 0 );
}

inline
bool
Directory::Where::isAnd( void ) const
{
  return( andLR );
}

inline
const Directory::DirField &
Directory::Where::getField( void ) const
{
  return( *fld );
}

inline
const Directory::Where &
Directory::Where::getFirst( void ) const
{
  if( andLR )
    {
      if( rightDepth > leftDepth )
	return( *right );
      else
	return( *left );
    }
  else
    {
      if( rightDepth < leftDepth )
	return( *right );
      else
	return( *left );
    }
}

inline
const Directory::Where &
Directory::Where::getSecond( void ) const
{
  if( andLR )
    {
      if( rightDepth > leftDepth )
	return( *left );
      else
	return( *right );
    }
  else
    {
      if( rightDepth < leftDepth )
	return( *left );
      else
	return( *right );
    }
}

// Directory inlines

inline
Directory::iterator
Directory::begin( void )
{
  return( list.begin() );
}

inline
Directory::iterator
Directory::end( void )
{
  return( list.end() );
}

inline
Directory::const_iterator
Directory::begin( void ) const
{
  return( list.begin() );
}

inline
Directory::const_iterator
Directory::end( void ) const
{
  return( list.end() );
}

inline
bool
Directory::reread( void )
{
  return( buildDirList() );
}

inline
bool
Directory::reread( const Where & whereClause )
{
  where = &whereClause;
  return( buildDirList() );
}

inline
Directory::size_type
Directory::size( void ) const
{
  return( list.size() );
}

inline
bool
Directory::empty( void ) const
{
  return( size() == 0 );
}


}; // namespace clue


#endif // ! def _clue_Directory_hpp_
