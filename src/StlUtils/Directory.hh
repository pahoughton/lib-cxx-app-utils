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
// Revision 1.2  1995/11/05 13:22:39  houghton
// New Implementation
//
//

#include <ClueConfig.hh>

#include <FileStat.hh>
#include <SortOrder.hh>

#include <vector>
#include <set>

#include <climits>

#ifdef  CLUE_DEBUG
#define inline
#endif

class Directory
{

public:

  typedef vector< FileStat >	List;
  typedef List::iterator	iterator;
  typedef SortOrder< FileStat >	DirOrder;
  
  static const DirOrder   SortName;
  static const DirOrder   SortExt;
  static const DirOrder   SortSize;
  static const DirOrder   SortTime;
  
  inline Directory( const char * path, bool recurs = false );
  inline Directory( const char * path,
		    const DirOrder & order,
		    bool recurs = false );

  inline Directory( const Directory & from );
  
  virtual ~Directory( void );

  inline iterator	begin( void );
  inline iterator	end( void );

  bool		set( const char * path, bool recurs = false );
  bool		set( const char *	path,
  		     const DirOrder &   order,
  		     bool recurs =	false );
  
  bool		sort( const DirOrder & order );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;

  static const char version[];
  
protected:

private:

  List	list;
  
};

#ifndef inline
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

