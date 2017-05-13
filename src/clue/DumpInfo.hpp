#ifndef _clue_DumpInfo_hpp_
#define _clue_DumpInfo_hpp_
/* 1996-12-08 (cc) Paul Houghton <paul4hough@gmail.com>

   Most of my classes have a method called dumpInfo that is
   used to dump the entire contents of the instance to an
   std::ostream. This is mostly used for debuging.

   The DumpInfo<T> template class makes it easier to use the
   dumpInfo methdod. To use it, your class must have a the
   a 'ostream & dumpInfo( std::ostream &, const char * , bool )' method
   that dumps an instance to the stream in a readable form.
   The DumpInf<T> object can only be instaciated by the
   class specified as 'T' and only has a toStream method.

   A class that uses this should return an instance that can
   then be inserted (i.e. <<) into an std::ostream. Please see the
   example.

   Example:

    #include <clue/DumpInfo.hpp>
    class MyClass {
    public:
      std::ostream & dumpInfo( std::ostream & dest,
			       const char *   prefix = "    " ) const;

      inline
      DumpInfo<MyClass> dump( const char *  prefix = "    " ) const {
	return( DumpInfo<MyClass>( *this, prefix ) );
      }

      // So Now you can do the follwing

      MyClass obj;

      std::cerr << obj.dump() << endl;

      // Without dump info you would have to

      dumpInfo( std::cerr ) << endl;

*/

#include <iostream>

template< class T >
class DumpInfo
{

public:
  inline DumpInfo( const T & dumpObj, const char * pre )
    : obj( dumpObj ), prefix( pre ) {};

  inline std::ostream &	    toStream( std::ostream & dest ) const {
    return( obj.dumpInfo( dest, prefix ) ); };

protected:

  const T &	obj;
  const char *	prefix;

};

template< class T >
inline
std::ostream &
operator << ( std::ostream & dest, const DumpInfo<T> & src )
{
  return( src.toStream( dest ) );
}

#endif // ! def _clue/DumpInfo_hpp_
