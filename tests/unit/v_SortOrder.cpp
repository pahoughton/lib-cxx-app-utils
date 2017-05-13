// 1995-11-05 (cc) <paul4hough@gmail.com>

#include <clue/SortOrder.hpp>
#include <clue/compare>

#include <algorithm>
#include <vector>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::AbsLong");
using namespace clue;

class Data
{
public:
  int   a;
  int   b;
  int   c;
  Data( int va = 0, int vb = 0, int vc = 0 ) : a(va), b(vb), c(vc) {};
private:
};

typedef SortOrder< Data >    DataSort;

template < class T >
T *
duplicate( const T & from )
{
  return( new T( from ) );
}

class DataCompA : public DataSort::LessBase
{
public:
  bool	operator () ( const Data & one, const Data & two ) const {
    return( one.a < two.a );
  };

  DataSort::LessBase *	dup( void ) const {
    return( duplicate( *this ) );
  };
};

class DataCompB : public DataSort::LessBase
{
public:
  bool	operator () ( const Data & one, const Data & two ) const {
    return( one.b < two.b );
  };

  DataSort::LessBase *	dup( void ) const {
    return( duplicate( *this ) );
  };

};

class DataCompC : public DataSort::LessBase
{
public:
  bool	operator () ( const Data & one, const Data & two ) const {
    return( one.c < two.c );
  };

  DataSort::LessBase *	dup( void ) const {
    return( duplicate( *this ) );
  };

};

DataCompA   CompA;
DataCompB   CompB;
DataCompC   CompC;


bool
v_SortOrder( void )
{
  SortOrder< Data >	orderA( CompA );
  SortOrder< Data >	orderB( CompB );
  SortOrder< Data >     orderC( CompC );

  SortOrder< Data >     orderBA( orderB + orderA );

  std::vector< Data >  list;

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

    for( std::vector<Data>::iterator them = list.begin();
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

    for( std::vector<Data>::iterator them = list.begin();
	 them != list.end();
	 them++ )
      {
	TEST( (prevB == (*them).b && prevA <= (*them).a ) ||
	      (prevB < (*them).b ) );
	prevB = (*them).b;
	prevA = (*them).a;

      }
  }
  return( verify.is_valid() );
}
