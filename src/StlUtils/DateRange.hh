#ifndef _DateRange_hh_
#define _DateRange_hh_
//
// File:        DateRange.hh
// Desc:    	Used in comparing two DateRanges. A DateRange has a start 
//  	    	(date/time) plus a duration(end date/time)
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 08:46
//

#include <StlUtilsConfig.hh>
#include <DateTime.hh>


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class STLUTILS_CLASS_T DateRange : public DateTime
{
public:

  inline DateRange( time_t startTime, time_t durSec );
  inline DateRange( const DateTime & startTime, time_t durSec );
  inline DateRange( const DateTime & startTime, const DateTime & stopTime );

  virtual time_t    getDur( void ) const;
  virtual time_t    setDur( time_t newDur );
  virtual time_t    getSecOfDay( void ) const;
  
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual int	    compare( const DateTime & two ) const;
  virtual int	    compare( const DateRange & two ) const;
  
  inline bool	    operator == ( const DateRange & two ) const;
  inline bool	    operator == ( const DateTime & two ) const;
  inline bool	    operator <  ( const DateRange & two ) const;
  inline bool	    operator <  ( const DateTime & two ) const;
  
#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool		operator != ( const DateRange & rhs ) const;
  inline bool		operator >  ( const DateRange & rhs ) const;
  inline bool		operator <= ( const DateRange & rhs ) const;
  inline bool		operator >= ( const DateRange & rhs ) const;
#endif
  // libStlUtils Common Class Methods
  
  virtual size_t    	getBinSize( void ) const;
  
  virtual ostream & 	write( ostream & dest ) const;
  virtual istream & 	read( istream & src );
  
  virtual ostream & 	toStream( ostream & dest = cout ) const;
  
  friend inline ostream & operator << ( ostream &	    dest,
					const DateRange &   obj );
  
  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char * 	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

  time_t     dur;

private:

};

#if !defined( inline )
#include <DateRange.ii>
#else // !def( inline )
#undef inline

int
compare( const DateRange & one, const DateRange & two );

#endif // !def( inline )


//  Quick Start:
//
//  DataTypes:
//
//  Constructors:
//
//  Destructors:
//
//
//  Public Interface:
//
//  	DateRange( time_t startTime, time_t durSec );
//  	    Set the value of startTime and duration(durSec).
//
//  	DateRange( const DateTime & startTime, time_t durSec );
//
//  	DateRange( const DateTime & startTime, const DateTime & stopTime );
//
//  	virtual	time_t
//  	getDur( void ) const;
//
//  	virtual time_t
//  	setDur( time_t newDur );
//
//  	virtual time_t
//  	getSecOfDay( void ) const;
//  
//  	virtual time_t
//  	secIn( const DateRange & dateTwo ) const;
//  	    returns the number of seconds that DateRange (two) is within
//  	    DateRange (one). 
//
//  	virtual time_t
//  	startsIn( const DateRange & dateTwo ) const;
//  	    return the number of seconds from the start of DateRange (two)
//  	    that is within DateRange (one). If the start of DateRange (two)
//          is before the start of DateRange (one) a zero(0) is returned.
//
//  	size_t
//  	getStreamSize( void ) const;
//
//  	ostream &
//  	write( ostream & dest ) const;
//
//  	istream &
//  	read( istream & src );
//
//  	virtual int
//  	compare( const DateRange & two ) const;
//
//  	bool
//  	operator == ( const DateRange & two ) const;
//
//  	bool
//  	operator <  ( const DateRange & two ) const;
// 
//  	virtual bool
//  	good( void ) const;
//  	    return true if no detected errors exist. Only setValid will
//  	    detect an invalid date/time value.
//
//  	virtual const char *
//  	error( void ) const;
//  	    return a string describing the current error state.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    return the name of this class.
//
//  	virtual ostream &
//  	toStream( ostream & dest ) const;
//  	    send a formated string of the current date/time to 'dest'
//  	    The format is '02/03/95 15:13:03'.
//
//  	virtual ostream &
//  	dumpInfo( ostream & dest ) const;
//
//
//  Other Accociated Functions:
//

// Revision History:
//
// 
// $Log$
// Revision 5.2  2000/05/25 17:05:45  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/03/23 10:44:40  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.1  1997/09/17 15:12:14  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:12  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 19:10:47  houghton
// Cleanup.
// Added compare( const DateTime & two ) const to eliminate compiler warnings.
//
// Revision 3.2  1996/11/20 12:11:40  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:23:32  houghton
// Changed to Release 3
//
// Revision 2.3  1996/04/27 12:56:04  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/11/10 14:08:34  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:24  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  14:44:26  houghton
// Ports and Version ID changes
//
//
#endif // ! def _DateRange_hh_ 
