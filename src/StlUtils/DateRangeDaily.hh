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
// Revision 1.3  1995/11/05 13:29:00  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include <ClueConfig.hh>
#include <DateRange.hh>

#ifdef  CLUE_DEBUG
#define inline
#endif

class DateRangeDaily : public DateRange
{

public:

  inline DateRangeDaily( time_t startTime, time_t durSec );

  virtual time_t    getSecOfDay( void ) const;
  virtual int       getDayOfWeek( void ) const;
  virtual time_t    getStart( void ) const;
  virtual time_t    getFrequency( void ) const;
  
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual time_t    setStart( time_t newStart );
  
  inline size_t	    getStreamSize( void ) const;
  inline ostream &  write( ostream & dest ) const;
  inline istream &  read( istream & src );
  
  virtual int	    compare( const DateRange & two ) const;
  virtual int	    compare( const DateRangeDaily & two ) const;

  bool		    operator == ( const DateRangeDaily & two ) const;
  bool		    operator <  ( const DateRangeDaily & two ) const;
    
  virtual bool	    	good( void ) const;
  virtual const char *  error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;
  
  static const char version[];
  
protected:

private:

  static time_t	    freq;
  time_t	    start;
  
};

#ifndef inline
#include <DateRangeDaily.ii>
#else
#undef inline

int
compare( const DateTime & one, const DateTime & two );

ostream &
operator << ( ostream & dest, const DateTime & time );

#endif

#endif // ! def _DateRangeDaily_hh_ 









