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
// Revision 2.1  1995/11/10 12:40:24  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  14:44:26  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <DateTime.hh>
#include <BinStream.hh>
#else
#include <ClueCfg.hh>
#include <DateTime.hh>
#include <BinStrm.hh>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class CLUE_CLASS_T DateRange : public DateTime
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

  virtual int	    compare( const DateRange & two ) const;
  
  bool		    operator == ( const DateRange & two ) const;
  bool		    operator <  ( const DateRange & two ) const;
  
  // libClue Common Class Methods
  
  virtual size_t    	getBinSize( void ) const;
  virtual BinStream & 	write( BinStream & dest ) const;
  virtual BinStream & 	read( BinStream & src );
  
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
#if !defined( CLUE_SHORT_FN )
#include <DateRange.ii>
#else
#include <DateRg.ii>
#endif
#else // !def( inline )
#undef inline

int
compare( const DateRange & one, const DateRange & two );

#endif // !def( inline )


#endif // ! def _DateRange_hh_ 
