#if !defined( STLUTILS_SHORT_FN )
#include <Wcf.h>
#include <WcfWt.h>
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>
#include <DateTime.hh>
#include <Bitmask.hh>
#include <FilePath.hh>
#include <User.hh>
#include <UserGroup.hh>
#include <FileStat.hh>
#include <Log.hh>
#include <Param.hh>
#else
#include <Wcf.h>
#include <WcfWt.h>
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RxScan.hh>
#include <DateTime.hh>
#include <Bitmask.hh>
#include <FilePath.hh>
#include <User.hh>
#include <UserGrp.hh>
#include <FileStat.hh>
#include <Log.hh>
#include <Param.hh>
#endif

static int ac = 3;
static char * av[] = { "one","two","three" };

bool
tWithWcf02( LibTest & tester )
{
  {
    Str		tStr;
    RegexScan	tRegexScan( "pattern" );
    DateTime	tDateTime;
    Bitmask	tBitMask(5);
    FilePath	tFilePath( "data" );
    User	tUser;
    UserGroup	tUserGroup;
    FileStat	tFileStat( "data" );
    Log		tLog;
    Param	tParam( ac, av );
    
    TEST( true );
  }
  return( true );
}

    
