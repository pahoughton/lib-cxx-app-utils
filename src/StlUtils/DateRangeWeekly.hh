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
// Revision 1.4  1995/11/05 14:44:29  houghton
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

#endif // ! def _DateRangeWeekly_hh_ 
