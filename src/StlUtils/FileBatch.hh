#ifndef _FileBatch_hh_
#define _FileBatch_hh_
//
// File:        FileBatch.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/10/98 10:47
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
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
protected:
  
  typedef STLUTILS_U32_SIZE_T	size_type;
  
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

template< class Rec >
class FileBatch : public FileBatchBase
{

public:

  typedef STLUTILS_U32_SIZE_T	size_type;
  typedef ptrdiff_t		difference_type;
  typedef Rec &			reference;
  typedef const Rec &		const_reference;
  
  class const_iterator;

  // * iterator *
  class iterator
    : public bidirectional_iterator< Rec, difference_type >
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
      pos += sizeof( Rec );
      return( *this );
    };

    inline iterator &	operator ++ (int) {
      iterator it( *this );
      ++ *this;
      return( it );
    };

    inline iterator &	operator -- ( void ) {
      pos -= sizeof( Rec );
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
    friend class FileBatch< Rec >;

    inline iterator( FileBatch< Rec > * o, size_type recNum )
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

    FileBatch< Rec > *	    owner;
    Rec			    rec;
    streampos		    pos;
    streampos		    readPos;
  };


  // * const_iterator *
  class const_iterator
    : public bidirectional_iterator< Rec, difference_type >
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

    inline const_iterator( const iterator & from )
      : owner( from.owner ),
	rec( from.rec ),
	pos( from.pos ),
	readPos( from.readPos )
      {};

    inline const_iterator &	operator ++ ( void ) {
      pos += sizeof( Rec );
      return( *this );
    };

    inline const_iterator &	operator ++ (int) {
      const_iterator it( *this );
      ++ *this;
      return( it );
    };

    inline const_iterator &	operator -- ( void ) {
      pos -= sizeof( Rec );
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
      
    inline const_iterator &	operator = ( const iterator & rhs ) {
      owner	= rhs.owner;
      rec	= rhs.rec;
      pos	= rhs.pos;
      readPos	= rhs.readPos;
      return( *this );
    };
      
    inline bool	    operator == ( const const_iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

    inline bool	    operator == ( const iterator & rhs ) const {
      return( owner == rhs.owner && pos == rhs.pos );
    };

  protected:

    friend class iterator;
    friend class FileBatch< Rec >;

    inline const_iterator( const FileBatch< Rec > * o, size_type recNum )
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

    const FileBatch< Rec > *	owner;
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
  
  FileBatch< Rec > &	    read( Rec & dest );
  bool			    read( Rec & dest ) const;
  
  FileBatch< Rec > &	    read( Rec & dest, size_type recNum );
  bool			    read( Rec & dest, size_type recNum ) const;

  FileBatch< Rec > &	    write( const Rec & src );
  FileBatch< Rec > &	    write( iterator & it );

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
//  	    Return the name of this class (i.e. FileBatch )
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
//  	operator <<( ostream & dest, const FileBatch & src );
//
//	istream &
//	operator >> ( istream & src, FileBatch & dest );
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

