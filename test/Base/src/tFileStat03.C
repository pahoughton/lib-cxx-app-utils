#include <LibTest.hh>
#include <FileStat.hh>

bool
tFileStat03( LibTest & test )
{
  {
    // canRead( void ) const
    // canWrite( void ) const
    // canExec( void ) const
    // canRead( Who ) const
    // canWrite( Who ) const
    // canExec( Who ) const
    
    const FileStat t( "data/FileStat.h.t.yyy.yyy.yyy" );

    test(   t.canRead() );
    test(   t.canWrite() );
    test(   t.canExec() );

    test(   t.canRead( FileStat::USER ) );
    test(   t.canWrite( FileStat::USER ) );
    test(   t.canExec( FileStat::USER ) );

    test(   t.canRead( FileStat::GROUP ) );
    test(   t.canWrite( FileStat::GROUP ) );
    test(   t.canExec( FileStat::GROUP ) );

    test(   t.canRead( FileStat::OTHER ) );
    test(   t.canWrite( FileStat::OTHER ) );
    test(   t.canExec( FileStat::OTHER ) );
    
  }

  {
    const FileStat t( "data/FileStat.h.t.nnn.nnn.nnn" );

    test( ! t.canRead() );
    test( ! t.canWrite() );
    test( ! t.canExec() );

    test( ! t.canRead( FileStat::USER ) );
    test( ! t.canWrite( FileStat::USER ) );
    test( ! t.canExec( FileStat::USER ) );

    test( ! t.canRead( FileStat::GROUP ) );
    test( ! t.canWrite( FileStat::GROUP ) );
    test( ! t.canExec( FileStat::GROUP ) );

    test( ! t.canRead( FileStat::OTHER ) );
    test( ! t.canWrite( FileStat::OTHER ) );
    test( ! t.canExec( FileStat::OTHER ) );
    
  }

  {
    const FileStat t( "data/FileStat.h.t.nnn.yyy.nnn" );

    test( ! t.canRead() );
    test( ! t.canWrite() );
    test( ! t.canExec() );

    test( ! t.canRead( FileStat::USER ) );
    test( ! t.canWrite( FileStat::USER ) );
    test( ! t.canExec( FileStat::USER ) );

    test(   t.canRead( FileStat::GROUP ) );
    test(   t.canWrite( FileStat::GROUP ) );
    test(   t.canExec( FileStat::GROUP ) );

    test( ! t.canRead( FileStat::OTHER ) );
    test( ! t.canWrite( FileStat::OTHER ) );
    test( ! t.canExec( FileStat::OTHER ) );
    
  }
#ifdef HAVE_BIN_UID
  {
    const FileStat t( "data/FileStat.b.b.yyy.yyy.nnn" );

    test( ! t.canRead() );
    test( ! t.canWrite() );
    test( ! t.canExec() );

    test(   t.canRead( FileStat::USER ) );
    test(   t.canWrite( FileStat::USER ) );
    test(   t.canExec( FileStat::USER ) );

    test(   t.canRead( FileStat::GROUP ) );
    test(   t.canWrite( FileStat::GROUP ) );
    test(   t.canExec( FileStat::GROUP ) );

    test( ! t.canRead( FileStat::OTHER ) );
    test( ! t.canWrite( FileStat::OTHER ) );
    test( ! t.canExec( FileStat::OTHER ) );
    
  }

  {
    const FileStat t( "data/FileStat.b.b.yyy.yny.yny" );

    test(   t.canRead() );
    test( ! t.canWrite() );
    test(   t.canExec() );

    test(   t.canRead( FileStat::USER ) );
    test(   t.canWrite( FileStat::USER ) );
    test(   t.canExec( FileStat::USER ) );

    test(   t.canRead( FileStat::GROUP ) );
    test( ! t.canWrite( FileStat::GROUP ) );
    test(   t.canExec( FileStat::GROUP ) );

    test(   t.canRead( FileStat::OTHER ) );
    test( ! t.canWrite( FileStat::OTHER ) );
    test(   t.canExec( FileStat::OTHER ) );
    
  }
#endif
  return( true );
}

