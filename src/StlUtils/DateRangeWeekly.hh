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
// Revision 1.3  1995/11/05 13:29:01  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include <ClueConfig.hh>
#include <DateRangeDaily.hh>

#ifdef  CLUE_DEBUG
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
  
  virtual bool		good( void ) const;
  virtual const char *  error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;

  static const char version[];
  
protected:

private:

  static time_t    freq;
};

#ifndef inline
#include <DateRangeDaily.ii>
#else
#undef inline

int
compare( const DateRangeWeekly & one, const DateRangeWeekly & two );

ostream &
operator << ( ostream & dest, const DateTime & time );

#endif

#endif // ! def _DateRangeWeekly_hh_ 
