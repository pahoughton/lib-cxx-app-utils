#ifndef _DateRangeDaily_hh_
#define _DateRangeDaily_hh_
//
// File:        DateRangeDaily.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 11:55
//
// Revision History:
//
// 
// $Log$
// Revision 3.3  1997/08/24 21:56:11  houghton
// Changed getDayOfWeek to return a 'DayOfWeek' (was int).
//
// Revision 3.2  1997/07/18 19:11:29  houghton
// Cleanup.
// Added compare( const DateTime & two ) const to eliminate compiler warnings.
//
// Revision 3.1  1996/11/14 01:23:33  houghton
// Changed to Release 3
//
// Revision 2.3  1996/04/27 12:57:00  houghton
// Cleanup.
//
// Revision 2.2  1995/11/10 14:08:34  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:26  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:27  houghton
// Ports and Version ID changes
//
//

#include <ClueConfig.hh>
#include <DateRange.hh>

#if defined( CLUE_DEBUG )
#define inline
#endif

class CLUE_CLASS_T DateRangeDaily : public DateRange
{

public:

  inline DateRangeDaily( time_t startTime, time_t durSec );

  virtual time_t    getSecOfDay( void ) const;
  virtual DayOfWeek getDayOfWeek( void ) const;
  virtual time_t    getStart( void ) const;
  virtual time_t    getFrequency( void ) const;
  
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual time_t    setStart( time_t newStart );

  virtual int	    compare( const DateTime & two ) const;
  virtual int	    compare( const DateRange & two ) const;
  virtual int	    compare( const DateRangeDaily & two ) const;

  bool		    operator == ( const DateRangeDaily & two ) const;
  bool		    operator <  ( const DateRangeDaily & two ) const;
    
  // libClue Common Class Methods
  
  virtual ostream & 	toStream( ostream & dest ) const;
  
  friend inline ostream & operator << ( ostream &		dest,
					const DateRangeDaily &  obj );

  virtual bool	    	good( void ) const;
  virtual const char *  error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  static const time_t	freq;
  
};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <DateRangeDaily.ii>
#else
#include <DateRgDl.ii>
#endif
#else
#undef inline

int
compare( const DateTime & one, const DateTime & two );

#endif

//  Quick Start : - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	DateRangeDaily class
//
//  Constructors:
//
//  Public Interface:
//
//  	DateRangeDaily( time_t startTime, time_t durSec );
//
//  	virtual time_t
//  	getSecOfDay( void ) const;
//
//  	virtual int
//  	getDayOfWeek( void ) const;
//
//  	virtual time_t
//  	getStart( void ) const;
//
//  	virtual time_t
// 	getFrequency( void ) const;
//  
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
//  	virtual time_t
//  	setStart( time_t newStart );
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
//  	virtual int
//  	compare( const DateRangeDaily & two ) const;
//
//  	bool
//  	operator == ( const DateRangeDaily & two ) const;
//
//  	bool
//  	operator <  ( const DateRangeDaily & two ) const;
//    
//  	virtual bool
//  	good( void ) const;
//
//  	virtual const char *
//  	error( void ) const;
//
//  	virtual const char *
//  	getClassName( void ) const;
//
//  	virtual ostream &
//  	toStream( ostream & dest ) const;
//
//  	virtual ostream &
//  	dumpInfo( ostream & dest ) const;
//
//  Protected:
//
//  Private:
//

#endif // ! def _DateRangeDaily_hh_ 

