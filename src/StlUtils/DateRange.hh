#ifndef _DateRange_hh_
#define _DateRange_hh_
//
// File:        DateRange.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 08:46
//
// Revision History:
//
// 
// $Log$
// Revision 1.4  1995/11/05 13:28:59  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include <ClueConfig.hh>

#include <DateTime.hh>

#ifdef  CLUE_DEBUG
#define inline
#endif


class DateRange : public DateTime
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

  inline size_t	    getStreamSize( void ) const;
  inline ostream &  write( ostream & dest ) const;
  inline istream &  read( istream & src );
  
  virtual int	    compare( const DateRange & two ) const;
  
  bool		    operator == ( const DateRange & two ) const;
  bool		    operator <  ( const DateRange & two ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;
  
  static const char version[];
  
protected:

  time_t     dur;

private:

};

#ifndef inline
#include <DateRange.ii>
#else
#undef inline

int
compare( const DateRange & one, const DateRange & two );

ostream &
operator << ( ostream & dest, const DateRange & time );

#endif


#endif // ! def _DateRange_hh_ 
