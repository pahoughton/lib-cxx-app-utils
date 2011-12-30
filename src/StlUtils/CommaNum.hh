#ifndef _CommaNum_hh_
#define _CommaNum_hh_
/**
  File:		CommaNum.hh
  Project:	Stl 
  Desc:

    
  
  Notes:
    
  Author(s):	Paul Houghton <paul4hough@gmail.com>
  Created:	12/10/2004 12:03
  
  Revision History: (See ChangeLog for details)
  
    $Author$
    $Date$
    $Name$
    $Revision$
    $State$

  $Id$

**/
#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <iostream>


class CommaNum
{

public:

  CommaNum( long    num,
	    size_t  width = 0,
	    char    fill = ' ',
	    size_t  decimalPlaces = 0 )
    : value( num ),
      w( width ),
      f( fill ),
      dp( decimalPlaces ) {};

  ostream & toStream( ostream & dest ) const {
    return( CommaNumber( dest, value, w, f, dp ) );
  };
  
protected:

  long	    value;
  size_t    w;
  char	    f;
  size_t    dp;
    
private:

};

inline 
ostream &
operator << ( ostream & dest, const CommaNum & obj ) {
  return( obj.toStream( dest ) );
}


/**
  Detail Documentation
  
    Data Types: - data types defined by this header
  
    	CommaNum	class
  
    Constructors:
  
    	CommaNum( );
  
    Destructors:
  
    Public Interface:
  
  	virtual ostream &
  	write( ostream & dest ) const;
  	    write the data for this class in binary form to the ostream.
  
  	virtual istream &
  	read( istream & src );
  	    read the data in binary form from the istream. It is
  	    assumed it stream is correctly posistioned and the data
  	    was written to the istream with 'write( ostream & )'
  
  	virtual ostream &
  	toStream( ostream & dest ) const;
  	    output class as a string to dest (used by operator <<)
  
  	virtual istream &
  	fromStream( istream & src );
  	    Set this class be reading a string representation from
  	    src. Returns src.
  
    	virtual Bool
    	good( void ) const;
    	    Return true if there are no detected errors associated
    	    with this class, otherwise false.
  
    	virtual const char *
    	error( void ) const;
    	    Return a string description of the state of the class.
  
    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. CommaNum )
  
    	virtual const char *
    	getVersion( bool withPrjVer = true ) const;
    	    Return the version string of this class.
  
  	virtual ostream &
  	dumpInfo( ostream & dest, const char * prefix, bool showVer );
  	    output detail info to dest. Includes instance variable
  	    values, state info & version info.
  
  	static const ClassVersion version
  	    Class and project version information. (see ClassVersion.hh)
  
    Protected Interface:
  
    Private Methods:
  
    Associated Functions:
  
    	ostream &
    	operator <<( ostream & dest, const CommaNum & src );
  
  	istream &
  	operator >> ( istream & src, CommaNum & dest );
  
  Example:
  
  See Also:
  
  Files:
  
  Documented Ver:
  
  Tested Ver:
  
**/

#endif /* ! def _CommaNum_hh_ */

