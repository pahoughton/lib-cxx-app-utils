#ifndef _DateRangeWeekly_hh_
#define _DateRangeWeekly_hh_
//
// File:        DateRangeWeekly.hh
// Project:	StlUtils ()
// Desc:        
//              
//  A DateRange who's operations only apply to a specific day of the week.
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:25
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DateRangeDaily.hh>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

class DateRangeWeekly : public DateRangeDaily
{

public:

  inline DateRangeWeekly( short dayOfWeek, time_t startTime, time_t durSec );
  
  virtual DayOfWeek getDayOfWeek( void ) const;
  virtual time_t    getFrequency( void ) const;

  virtual bool	    isIn( const DateTime & dateTwo ) const;
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;
  
  virtual ostream & 	toStream( ostream & dest ) const;
  
  friend inline ostream & operator << ( ostream &		dest,
					const DateRangeWeekly & obj );

  virtual bool		good( void ) const;
  virtual const char *  error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  static const time_t    freq;
};

#if !defined( inline )
#include <DateRangeWeekly.ii>
#else
#undef inline

int
compare( const DateRangeWeekly & one, const DateRangeWeekly & two );

#endif


//
//
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
//  	DateRangeWeekly( short dayOfWeek, time_t startTime, time_t durSec );
//  
//  	virtual int
//  	getDayOfWeek( void ) const;
//
//  	virtual time_t
//  	getFrequency( void ) const;
//
//	virtual bool
//	in( const DateTime & dateTwo ) const;
//	    returns true if dateTwo day of week is the same mine and
//	    its time of day falls within mine.
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
//  	virtual
//  	bool
//  	good( void ) const;
//  	    return true if no detected errors exist. Only setValid will
//  	    detect an invalid date/time value.
//
//  	virtual
//  	const char *
//  	error( void ) const;
//  	    return a string describing the current error state.
//
//  	virtual
//  	const char *
//  	getClassName( void ) const;
//  	    return the name of this class.
//
//  	virtual ostream &
//  	toStream( ostream & dest ) const;
//
//  	virtual ostream &
//  	dumpInfo( ostream & dest ) const;
//
//  Other Accociated Functions:
//

// Revision History:
//
// 
// 
// %PL%
// 
// $Log$
// Revision 5.6  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.5  2003/06/25 08:49:26  houghton
// Change: rename in method it isIn.
//
// Revision 5.4  2003/05/12 15:51:33  houghton
// Added in( const DateTime & dateTwo ) const.
//
// Revision 5.3  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:05:45  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:16  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/08/24 21:54:53  houghton
// Changed getDayOfWeek to return a 'DayOfWeek' (was int).
//
// Revision 3.1  1996/11/14 01:23:35  houghton
// Changed to Release 3
//
// Revision 2.3  1995/11/10 18:46:51  houghton
// Fixed error in comments
//
// Revision 2.2  1995/11/10  14:08:35  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:28  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:29  houghton
// Ports and Version ID changes
//
//
#endif // ! def _DateRangeWeekly_hh_ 
