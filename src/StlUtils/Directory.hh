#ifndef _Directory_hh_
#define _Directory_hh_
//
// File:        Directory.hh
// Project:	Clue
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/19/95 07:31
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <ClueConfig.hh>
#include <ClueDirent.hh>
#include <SortOrder.hh>
#include <FileStat.hh>
#include <Bitmask.hh>
#include <vector>
#include <set>
#include <climits>

#include <iostream>

#if defined( CLUE_DEBUG )
#define inline
#endif

class Directory
{

public:

  //
  // Directory Fields for Where Clauses
  //
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

    virtual const char *    getClassName( void ) const;
    virtual ostream &	    dumpInfo( ostream &		dest = cerr,
				      const char *	prefix = "    ",
				      bool		showVer = true ) const;

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
    
    virtual const char *    getClassName( void ) const;
    virtual ostream &	    dumpInfo( ostream &		dest = cerr,
				      const char *	prefix = "    ",
				      bool		showVer = true ) const;
    
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

    virtual const char *    getClassName( void ) const;
    virtual ostream &	    dumpInfo( ostream &		dest = cerr,
				      const char *	prefix = "    ",
				      bool		showVer = true ) const;
    
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

    virtual const char *    getClassName( void ) const;
    virtual ostream &	    dumpInfo( ostream &		dest = cerr,
				      const char *	prefix = "    ",
				      bool		showVer = true ) const;
    
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

    virtual const char *    getClassName( void ) const;
    virtual ostream &	    dumpInfo( ostream &		dest = cerr,
				      const char *	prefix = "    ",
				      bool		showVer = true ) const;
    
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
    bool	and;
    Where *	right;

    size_t    refCount;
    size_t    leftDepth;
    size_t    rightDepth;
    
  };

  // Types
  
  typedef vector< FileStat >	    DirList;
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
  
  inline bool			reread( void );
  inline bool			reread( const Where & where );
  
  bool		sort( const DirOrder & order );

#if defined( NOT_READY_FIXME )
  bool		exclude( const char * name );
  bool		excludeDir( const char * path );
  bool		excludeUser( const char * user );
  bool		excludeGroup( const char * group );
  bool		excludeMode( mode_t mode );
  
  bool		resetExclude( void );
#endif
  
  virtual ostream &	    toStream( ostream & dest ) const;

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

  bool	    set( const char *	    path,
		 const Option &	    opts,
		 const Where *	    where,
		 const DirOrder *   order );
		 
  bool	    setError( int osErr, const char * errPath );
  
private:

  bool	readDir( DIR *		    dir,
		 const FilePath &   dirPath,
		 const Where *	    where,
		 const Option &	    opts );

  FilePath	pattern;
  Option	options;
  DirList	list;

  int		osErrno;
  FilePath	errorPath;
  
};


#if !defined( inline )
#include <Directory.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const Directory & src );

istream &
operator >> ( istream & src, const Directory & dest );


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Directory	class
//
//  Constructors:
//
//  	Directory( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Directory )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Directory & src );
//
//	istream &
//	operator >> ( istream & src, Directory & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 3.4  1997/07/11 15:54:13  houghton
// Added Directory( void )
// Added reread().
//
// Revision 3.3  1997/06/09 14:36:33  houghton
// Added include ClueDirent.hh
// Bug-Fix: DirFieldTime copy constructor arg was wrong.
// Bug-Fix: forgot to declere 'Time' (DirField).
//
// Revision 3.2  1997/06/09 12:03:58  houghton
// Completed initial coding.
//
// Revision 3.1  1996/11/14 01:25:19  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:07  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  13:48:11  houghton
// New implementation
//
#endif // ! def _Directory_hh_ 
