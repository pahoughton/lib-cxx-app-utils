#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <SortOrder.hh>
#include <Compare.hh>
#include <algorithm>
#include <vector>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <SortOrdr.hh>
#include <Compare.hh>
#include <algorithm>
#include <vector>
#endif

class Data
{
public:
  int   a;
  int   b;
  int   c;
  Data( int va = 0, int vb = 0, int vc = 0 ) : a(va), b(vb), c(vc) {};
private:
};

class DataCompA : public SortCompareBase<Data>
{
public:
  int   operator () ( const Data & one, const Data & two ) const;
};

int
DataCompA::operator () ( const Data & one, const Data & two ) const
{
  return( compare( one.a, two.a ) );
}

class DataCompB : public SortCompareBase<Data>
{
public:
  int   operator () ( const Data & one, const Data & two ) const;
};

int
DataCompB::operator () ( const Data & one, const Data & two ) const
{
  return( compare( one.b, two.b ) );
}

class DataCompC : public SortCompareBase<Data>
{
public:
  int   operator () ( const Data & one, const Data & two ) const;
};

int
DataCompC::operator () ( const Data & one, const Data & two ) const
{
  return( compare( one.c, two.c ) );
}

DataCompA   CompA;
DataCompB   CompB;
DataCompC   CompC;


bool
tSortOrder( LibTest & tester )
{
  SortOrder< Data >	orderA( CompA );
  SortOrder< Data >	orderB( CompB );
  SortOrder< Data >     orderC( CompC );

  SortOrder< Data >     orderBA( orderB + orderA );
  
  vector< Data >  list;

  list.insert( list.end(), Data( 40, 100, 20 ) );
  list.insert( list.end(), Data( 50, 100, 20 ) );
  list.insert( list.end(), Data( 60, 50,  20 ) );
  list.insert( list.end(), Data( 70, 200, 5  ) );
  list.insert( list.end(), Data( 10, 200, 10 ) );
  list.insert( list.end(), Data( 20, 200, 5  ) );
  list.insert( list.end(), Data( 30, 150, 20 ) );

  {
    sort( list.begin(), list.end(), orderA );

    int prev = 0;
    
    for( vector<Data>::iterator them = list.begin();
	 them != list.end();
	 them++ )
      {
	TEST( prev <= (*them).a );
	prev = (*them).a;
      }
    
  }

  {
    sort( list.begin(), list.end(), orderBA );

    int prevB = 0;
    int prevA = 0;
    
    for( vector<Data>::iterator them = list.begin();
	 them != list.end();
	 them++ )
      {
	TEST( (prevB == (*them).b && prevA <= (*them).a ) ||
	      (prevB < (*them).b ) );
	prevB = (*them).b;
	prevA = (*them).a;
	
      }
  }
  return( true );
}
