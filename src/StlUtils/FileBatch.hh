#ifndef _FileBatch_hh_
#define _FileBatch_hh_
//
// File:        FileBatch.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides an iterator interface to a file containing fixed length records.
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     11/10/98 10:47
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <FilePath.hh>

#include <iterator>
#include <fstream>
#include <cerrno>

class FileBatchBase
{
public:
  inline const char *	getFileName( void ) const {
    return( name );
  };
  
protected:
  
  typedef STLUTILS_U64_SIZE_T	size_type;
  
  FileBatchBase( const char * fileName, size_type recordSize );
  
  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual const char *	    getClassName( void ) const = 0;

  enum ErrorNum
  {
    E_OK,
    E_OPEN,
    E_SIZE,
    E_READ,
    E_WRITE,
    E_UNDEFINED
  };
  
  bool		setError( ErrorNum errNum, streampos pos, int osErr );
  
  FilePath	name;
  fstream *	batch;
  size_type	recSize;
  
  ErrorNum	errorNum;
  streampos	errorPos;
  int		osErrno;
};

template< class T >
class FileBatch : public FileBatchBase
{

public:

  typedef FileBatch< T >	self;

  typedef T			Rec;
  
  typedef STLUTILS_U64_SIZE_T	size_type;
  typedef ptrdiff_t		difference_type;
  typedef Rec &			reference;
  typedef const Rec &		const_reference;
  
  class const_iterator;

  // * iterator *
  class iterator
    : public std::iterator< bidirectional_iterator_tag,
                            Rec,
                            difference_type,
                            Rec *,
                            Rec & >
  {
  public:

    inline iterator( void )
      : owner( 0 ), pos( 0 ), readPos( 0 )
      {};

    inline iterator( const iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline iterator &	operator ++ ( void ) {
      pos += (streampos) sizeof( Rec );
      return( *this );
    };

    inline iterator &	operator ++ (int) {
      iterator it( *this );
      ++ *this;
      return( it );
    };

    inline iterator &	operator -- ( void ) {
      pos -= (streampos) sizeof( Rec );
      return( *this );
    };

    inline iterator &	operator -- (int) {
      iterator it( *this );
      -- *this;
      return( it );
    };
    
    inline reference	operator *  ( void ) {
      if( readPos != pos )
	{
	  streampos cur( (*owner).file().tellg() );
	  readPos = pos;
	  (*owner).file().seekg( pos, ios::beg );
	  (*owner).read( rec );
	  (*owner).file().seekg( cur, ios::beg );
	}
      return( rec );
    };

    inline iterator &	operator = ( const iterator & rhs ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };
      
    inline bool	    operator == ( const iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

  protected:

    friend class const_iterator;
    friend class FileBatch< T >;

    inline iterator( FileBatch< T > * o, size_type recNum )
      : owner( o ),
	readPos( NPOS )
      {
	streampos cur( (*owner).file().tellg() );

	if( recNum == NPOS )
	  (*owner).file().seekg( 0, ios::end );
	else
	  (*owner).file().seekg( recNum * sizeof( rec ), ios::beg );

	pos = (*owner).file().tellg();

	(*owner).file().seekg( cur, ios::beg );
      };

    FileBatch< T > *	    owner;
    Rec			    rec;
    streampos		    pos;
    streampos		    readPos;
  };


  // * const_iterator *
  class const_iterator
    : public std::iterator< bidirectional_iterator_tag,
                            Rec,
                            difference_type,
                            Rec *,
                            Rec & >
  {
  public:
    inline const_iterator( void )
      : owner( 0 ), pos( 0 ), readPos( 0 )
      {};

    inline const_iterator( const const_iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline const_iterator( const typename self::iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline const_iterator &	operator ++ ( void ) {
      pos += (streampos) sizeof( Rec );
      return( *this );
    };

    inline const_iterator &	operator ++ (int) {
      const_iterator it( *this );
      ++ *this;
      return( it );
    };

    inline const_iterator &	operator -- ( void ) {
      pos -= (streampos) sizeof( Rec );
      return( *this );
    };

    inline const_iterator &	operator -- (int) {
      const_iterator it( *this );
      -- *this;
      return( it );
    };
    
    inline const reference	operator *  ( void ) {
      if( readPos != pos )
	{
	  streampos cur( (*owner).file().tellg() );
	  readPos = pos;
	  (*owner).file().seekg( pos, ios::beg );
	  (*owner).read( rec );
	  (*owner).file().seekg( cur, ios::beg );
	}
      return( rec );
    };

    inline const_iterator &	operator = ( const const_iterator & rhs ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };
      
    inline const_iterator &	operator = (
      const typename self::iterator & rhs
      ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };
      
    inline bool	    operator == ( const const_iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

    inline bool	    operator != ( const const_iterator & rhs ) const {
      return( ! (*this == rhs) );
    };

    inline bool	    operator == ( const typename self::iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

    inline bool	    operator != ( const typename self::iterator & rhs ) const {
      return( !(*this == rhs));
    };
    
  protected:

    friend class iterator;
    friend class FileBatch< T >;

    inline const_iterator( const FileBatch< T > * o, size_type recNum )
      : owner( o ),
	readPos( NPOS )
      {
	streampos cur( (*owner).file().tellg() );

	if( recNum == NPOS )
	  (*owner).file().seekg( 0, ios::end );
	else
	  (*owner).file().seekg( recNum * sizeof( rec ), ios::beg );

	pos = (*owner).file().tellg();

	(*owner).file().seekg( cur, ios::beg );
      };

    const FileBatch< T > *	owner;
    Rec				rec;
    streampos			pos;
    streampos			readPos;
  };
    
  FileBatch( const char *   fileName,
	     ios::open_mode mode = ios::in,
	     unsigned short permMask = 02 );

  FileBatch( const char *   fileName,
	     ios::open_mode mode,
	     bool	    create,
	     unsigned short permMask );

  virtual ~FileBatch( void ) {
    if( batch )	    delete batch;
  };

  const_iterator	    begin( void ) const;
  const_iterator	    end( void ) const;

  iterator		    begin( void );
  iterator		    end( void );

  Rec			    front( void ) const;
  Rec			    back( void ) const;
  
  iterator		    append( void );
  bool			    append( const Rec & src );
  
  FileBatch< T > &	    read( Rec & dest );
  bool			    read( Rec & dest ) const;
  
  FileBatch< T > &	    read( Rec & dest, size_type recNum );
  bool			    read( Rec & dest, size_type recNum ) const;

  FileBatch< T > &	    write( const Rec & src );
  FileBatch< T > &	    write( iterator & it );

  size_type		    size( void ) const;

  Rec			    operator [] ( size_type rec ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< FileBatch >
  dump( const char * preifx = "    ", bool showVer = true ) const;

protected:

  friend class const_iterator;
  friend class iterator;
  
  fstream &	file( void ) const;
  
  size_type	fileSize;

private:

  FileBatch( const FileBatch & from );
  FileBatch & operator =( const FileBatch & from );

};

#include <FileBatch.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	FileBatch	class
//
//  Constructors:
//
//  	FileBatch( );
//
//  Destructors:
//
//  Public Interface:
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
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
// 
// %PL%
// 
// $Log$
// Revision 5.9  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.8  2003/07/19 09:17:12  houghton
// Port to 64 bit.
//
// Revision 5.7  2003/06/07 16:48:23  houghton
// Added typedef Rec.
//
// Revision 5.6  2002/03/25 11:27:00  houghton
// Added typename delcarations.
//
// Revision 5.5  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.4  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.3  2001/01/11 13:47:44  houghton
// Port to Sun CC 5.0.
//
// Revision 5.2  2000/06/27 10:46:05  houghton
// Port Sun C++ 5.0 - change to use 'std' iterator classes.
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.3  1999/06/24 10:25:55  houghton
// Added getFileName().
//
// Revision 4.2  1999/05/01 12:52:10  houghton
// Rework to get around compile problems.
// Added front()
// Added back()
// Added operator []
// Improved error output.
//
// Revision 4.1  1999/03/02 12:46:26  houghton
// Initial Version.
//
//
#endif // ! def _FileBatch_hh_ 

