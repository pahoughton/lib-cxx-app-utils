#ifndef _Directory_hh_
#define _Directory_hh_
//
// File:        Directory.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     09/19/95 07:31
//
// Revision History:
//
// $Log$
// Revision 1.3  1995/11/05 13:48:11  houghton
// New implementation
//
//

#ifdef CLUE_SHORT_FN
#include <ClueCfg.hh>
#include <SortOrdr.hh>
#include <FileStat.hh>
#include <BinMask.hh>
#include <vector>
#include <set>
#include <climits>
#include <dirent.h>
#else
#include <ClueConfig.hh>
#include <SortOrder.hh>
#include <FileStat.hh>
#include <BinMask.hh>
#include <vector>
#include <set>
#include <climits>
#include <dirent.h>
#endif


#if defined( CLUE_DEBUG )
#define inline
#endif


  
class Directory
{

public:

  typedef vector< FileStat >	List;
  typedef List::iterator	iterator;
  typedef SortOrder< FileStat >	DirOrder;
  typedef BitMask		Options;

  class DirField
  {
  public:

    inline DirField( void ):
    virtual ~DirField( void );
    
    enum CompareType
    {
      Equal,
      NotEqual,
      Less,
      More,
      LessEqual,
      MoreEqual
    };

    inline void	    addRef( void );
    inline bool	    delRef( void );
    
    virtual bool	match( const FileStat & stat ) const == 0;
    virtual DirField *	newCopy( void ) const = 0;
    virtual ostream &	dumpInfo( ostream & dest = cerr );
    
  protected:
    
    CompareType  comp;
    size_t	 refCount;
    
  };

  class DirFieldFileName : public DirField
  {
  public:

    inline DirFieldFileName( const DirFieldName & from );
    virtual DirFieldFileName( void ) {};
    
    virtual bool match( const FileStat & stat ) const;
    virtual DirField *	newCopy( void ) const;
    
    inline DirFieldFileName	operator == ( const char * rhs ) const;
    inline DirFieldFileName	operator != ( const char * rhs ) const;
    inline DirFieldFileName	operator <  ( const char * rhs ) const;
    inline DirFieldFileName	operator >  ( const char * rhs ) const;
    inline DirFieldFileName	operator <= ( const char * rhs ) const;
    inline DirFieldFileName	operator >= ( const char * rhs ) const;
    
    virtual ostream &	dumpInfo( ostream & dest = cerr );
    
  private:
    
    Str value;
  };

  class DirFieldSize : public DirField
  {
  public:

    inline DirFieldSize( const DirFieldSize & from );
    virtual DirFieldSize( void ) {};
    
    virtual bool match( const FileStat & stat ) const;
    virtual DirField *	newCopy( void ) const;
    
    inline DirFieldSize	operator == ( time_t rhs ) const;
    inline DirFieldSize	operator != ( time_t rhs ) const;
    inline DirFieldSize	operator <  ( time_t rhs ) const;
    inline DirFieldSize	operator >  ( time_t rhs ) const;
    inline DirFieldSize	operator <= ( time_t rhs ) const;
    inline DirFieldSize	operator >= ( time_t rhs ) const;

    virtual ostream &	dumpInfo( ostream & dest = cerr );
    
  private:

    size_t value;
  };
  
  class Where
  {
  public:

    inline Where( const DirField & fld );
    inline Where( const Where & where );
    inline Where( const Where & left, bool andLR, const Where & right );

    inline Where( void );

    inline Where	    operator && ( const Where & where ) const;
    inline Where	    operator || ( const Where & where ) const;

    friend inline Where	    operator && ( const DirField & fld,
					  const Where &	    where );
    friend inline Where	    operator || ( const DirField & fld,
					  const Where &	    where );

    inline void		addRef( void );
    inline bool		delRef( void );

    ostream &		dumpInfo( ostream &	dest = err,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;

    const char *	getVersion( void ) const;
    static const char version[];

  protected:

    friend class Directory;
    
    inline bool			isField( void ) const;
    inline bool			isAnd( void ) const;
    inline const DataFld &	getField( void ) const;
    inline const DataWhere &	getFirst( void ) const;
    inline const DataWhere &	getSecond( void ) const;
  
  private:
  
    DirField *	fld;

    here *	left;
    bool	and;
    Where *	right;

    size_t    refCount;
    size_t    leftDepth;
    size_t    rightDepth;
    
  };

  
  static const DirOrder	    SortName;
  static const DirOrder	    SortExt;
  static const DirOrder	    SortSize;
  static const DirOrder	    SortTime;
  static const DirOrder	    SortUser;
  static const DirOrder	    SortUserGroup;

  static const Options	    Default;
  static const Options	    Recurs;
  static const Options	    All;

  
  
  inline Directory( const char * path, const Options & opt = Default );
  inline Directory( const char *	path,
		    const DirOrder &	order,
		    const Options &	opt = Default );

  inline Directory( const Where & where, const Options & opt = Default );
  inline Directory( const Where &	where,
		    const DirOrder &	order,
		    const Options &	opt = Default );
  
  inline Directory( const Directory & from );
  
  virtual ~Directory( void );

  inline iterator	begin( void );
  inline iterator	end( void );
  inline size_t		size( void ) const;

  bool		set( const char * path, const Options & opt = Default );
  bool		set( const char *	path,
  		     const DirOrder &   order,
  		     const Options &	opt = Default );

  bool		set( const Where &	where,
		     const Options &	opt = Default );
  
  bool		set( const Where &	where,
  		     const DirOrder &   order,
		     const Options &	opt = Default );
  
  bool		sort( const DirOrder & order );

  bool		exclude( const char * name );
  bool		excludeDir( const char * path );
  bool		excludeUser( const char * user );
  bool		excludeGroup( const char * group );
  bool		excludeMode( mode_t mode );
  
  bool		resetExclude( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream &	toStream( ostream & dest = cout ) const;
  virtual ostream &	dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
				  bool		showVer = true ) const;

  virtual const char *	getVersion( void ) const;
    
  static const char version[];
  
protected:

private:

  bool	readDir( DIR *		    dir,
		 const FilePath &   dirPath,
		 const FilePath &   matchPath,
		 Options	    options );
  
  List	list;
  
};

#if !defined( inline )
#include <Directory.ii>
#else
#undef inline
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
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Directory )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Directory & obj );

#endif // ! def _Directory_hh_ 

