#ifndef _DateRangeWeekly_hh_
#define _DateRangeWeekly_hh_
//
// File:        DateRangeWeekly.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:25
//
// Revision History:
//
// 
// $Log$
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

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <DateRangeDaily.hh>
#else
#include <ClueCfg.hh>
#include <DateRgDl.hh>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class DateRangeWeekly : public DateRangeDaily
{

public:

  inline DateRangeWeekly( short dayOfWeek, time_t startTime, time_t durSec );
  
  virtual int	    getDayOfWeek( void ) const;
  virtual time_t    getFrequency( void ) const;
  
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
#if !defined( CLUE_SHORT_FN )
#include <DateRangeWeekly.ii>
#else
#include <DateRgWk.ii>
#endif
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

#endif // ! def _DateRangeWeekly_hh_ 
