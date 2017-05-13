// 2017-05-11 (cc) <paul4hough@gmail.com>

#include <clue/InboundProcessor.hpp>
#include <clue/SigCatcher.hpp>
#include <clue/FilePath.hpp>
#include <valid/verify.hpp>

#define TEST_DATA_DIR "data/InboundProcessor"
using namespace clue;

class FileProc
{
public:

  inline bool	operator () ( const FilePath & fn ) {
    std::cout << "processing: " << fn << std::endl;
  };
};

valid::verify &
v_InboundProcessor( void )
{
  static VVDESC( "clue::InboundProcessor" );
  {

    SigCatcher		signals;
    FileProc		fileProc;
    IbpDefaultPreScan   prescan;

    InboundProcessor< FileProc, IbpDefaultPreScan > t( "*.rdy",
						       TEST_DATA_DIR "/in",
						       TEST_DATA_DIR "/proc",
						       5,
						       &signals,
						       fileProc,
						       prescan );

    VVTRUE( t.good() );

  }

  return( VALID_VALIDATOR );
}
