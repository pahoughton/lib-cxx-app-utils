//
// File:        tLruMap01.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruMap01
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     09/08/98 10:21
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "TestConfig.hh"
#include "LibTest.hh"

#include <LruMap.hh>
#include <FilePath.hh>

#include <vector>

#include <iomanip>

typedef long	LruKey;

class TestObj
{
public:

  typedef long	    Key;
  typedef vector< Key >	    Array;
  
  TestObj( LruKey   k ) : count( 0 ), lru( k ) {
    path.fill('0');
    path << TEST_DATA_DIR << path.dirSep() << "lru."
	 << setw(5) << k
      ;
  };

  LruKey    lru;
  FilePath  path;
  Array	    array;
  long	    count;
  
private:

};

struct LruFunct
{
  LruKey    operator () ( const TestObj::Key & objKey ) {
    return( objKey / 100 );
  };
};

struct LruMax
{
  size_t    operator () ( void ) const { return( 25 ); };
};


bool
tLruMap01( LibTest & tester )
{
  cout << endl;
  
  {

    LruFunct	tLruFunct;
    LruMax	tLruMax;
    
    typedef LruMap< TestObj, TestObj::Key, LruKey, LruFunct, LruMax > TestLru;

    typedef vector< LruKey >  KeyList;
    
    TestLru	t( tLruFunct, tLruMax );

    TestObj::Key  k;

    
    for( long c = 0; c < 1000; ++ c )
      {
	k = rand() % 10000;

	
	cerr << setw( 3 ) << c << ' ' << setw( 5 ) << k ;
	
	++ t.obj( k ).count;
	
	cerr << " " << setw( 4 ) << t.obj( k ).lru
	     << " " << setw( 3 ) << t.obj( k ).count
	     << endl;

	// t.dumpInfo( cerr ) << endl;
      }
    cout << "DONE!" << endl;
  }
  return( true );
}
	
// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1998/10/13 15:22:01  houghton
// Initial Version.
//
//
