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
// Revision 2.1  1995/11/10 12:40:26  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:27  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <DateRange.hh>
#else
#include <ClueCfg.hh>
#include <DateRg.hh>
#endif


#if defined( CLUE_DEBUG )
#define inline
#endif

class CLUE_CLASS_T DateRangeDaily : public DateRange
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

#endif // ! def _DateRangeDaily_hh_ 









