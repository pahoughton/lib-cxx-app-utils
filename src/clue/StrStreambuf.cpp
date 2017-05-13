// 1995-05-30 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "StrStreambuf.hpp"
namespace clue {
void
StrStreambuf::readPrep( void )
{
  if( egptr() < pptr() ) {
    setg( gptr(), gptr(), pptr() );
  }
}

std::ostream &
StrStreambuf::dumpInfo(
  std::ostream & dest,
  const char *   prefix
  )
{
  dest << prefix << "length:  " << plen() << '\n'
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
       << prefix << "epptr(): " << (void *) epptr() << '\n'
       << prefix << "eback(): " << (void *) eback() << '\n'
       << prefix << "gptr():  " << (void *) gptr() << '\n'
       << prefix << "egptr(): " << (void *) egptr() << '\n'
       << prefix << "n - b:   " << pptr() - pbase() << '\n'
       << prefix << "string:  '" << (void *)cstr() << "'\n"
       << prefix << "pbase(): " << (void *) pbase() << '\n'
       << prefix << "pptr():  " << (void *) pptr() << '\n'
       << prefix << "length:  " << plen() << '\n'
       << prefix << "size:    " << psize() << '\n'
    ;

  return( dest );
}
}; // namespace clue
