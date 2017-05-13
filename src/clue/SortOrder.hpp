#ifndef _clue_SortOrder_hpp_
#define _clue_SortOrder_hpp_
/* 1995-09-19 (cc) Paul Houghton <paul4hough@gmail.com>

   Provides a template for specifing a sort order.
*/

#include <vector>

namespace clue {

template < class T >
class SortOrder
{

public:

  class LessBase
  {
  public:
    virtual bool    operator () ( const T & one, const T & two ) const = 0;

    virtual LessBase *	dup( void ) const = 0;
  };

  class Less
  {
  public:
    inline Less( void ) : less( 0 ) {};
    inline Less( const LessBase & lessBase ) : less( lessBase.dup() ) {};
    inline Less( const Less & from ) : less( from.less ?
					     from.less->dup() : 0 ) {};
    inline Less &   operator = ( const Less & rhs ) {
      if( less ) delete less;
      less = (rhs.less ? rhs.less->dup() : 0 );
      return( *this );
    };

    inline ~Less( void ) { if( less ) delete less; };

  private:
    friend class SortOrder<T>;

    LessBase * less;
  };

  typedef std::vector< Less >	    Order;

  inline SortOrder( const LessBase & lessBase ) {
    Less l( lessBase );
    order.push_back( l );
  };

  inline bool	    operator () ( const T & one, const T & two ) const {
    for( typename Order::const_iterator them = order.begin();
	 them != order.end();
	 them++ )
      {
	if( (*them).less )
	  {
	    if( (*(*them).less)( one, two ) )
	      return( true );
	    if( (*(*them).less)( two, one ) )
	      return( false );
	}
      }
    return( false );
  };


  inline SortOrder<T>  operator + ( const SortOrder<T> & rhs ) const;

protected:

private:

  Order	    order;
};


template< class T >
inline
SortOrder<T>
SortOrder<T>::operator + ( const SortOrder<T> & rhs ) const
{
  SortOrder<T> l( *this );

  l.order.insert( l.order.end(), rhs.order.begin(), rhs.order.end() );
  return( l );
}

}; // namespace clue

#endif // ! def _clue_SortOrder_hpp_
