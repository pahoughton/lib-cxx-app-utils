#ifndef _clue_CommaNum_hpp_
#define _clue_CommaNum_hpp_
// 2004-04-02 (cc) Paul Houghton - (paul4hough@gmail.com)

#include <clue/Clue.hpp>
#include <clue/DumpInfo.hpp>
#include <iostream>

namespace clue {

class CommaNum
{

public:

  CommaNum( long    num,
	    size_t  width = 0,
	    char    fill = ' ',
	    size_t  decimalPlaces = 0 )
    : value( num ),
      w( width ),
      f( fill ),
      dp( decimalPlaces ) {};

  std::ostream & toStream( std::ostream & dest ) const {
    return( CommaNumber( dest, value, w, f, dp ) );
  };

protected:

  long	    value;
  size_t    w;
  char	    f;
  size_t    dp;

private:

};

inline
std::ostream &
operator << ( std::ostream & dest, const CommaNum & obj ) {
  return( obj.toStream( dest ) );
}

}

#endif /* ! def _clue_CommaNum_hpp_ */
