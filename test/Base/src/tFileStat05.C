#include <LibTest.hh>
#include <FileStat.hh>

bool
tFileStat05( LibTest & test )
{
  {
    // setMode( mode_t )
    
    FileStat t( "data/FileStat.set" );
    FileStat c;
    
    test( t.setMode( 0777 ) );

    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0777 );
    test( (t.getMode() & 0777) == 0777 );

    test( t.setMode( 0644 ) );

    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0644 );
    test( (t.getMode() & 0777) == 0644 );
    
#ifdef HAVE_BIN_UID
    t.stat( "data/FileStat.b.b.yyy.yny.yny" );

    test( ! t.setMode( 0444 ) );
    
    c.stat( "data/FileStat.b.b.yyy.yny.yny" );

    test( (c.getMode() & 0777) == 0755 );
    test( (t.getMode() & 0777) == 0755 );
#endif
  }

  {
    // set( Who, What );
    
    FileStat t( "data/FileStat.set" );
    FileStat c;
    
    test( t.setMode( 0444 ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0444 );
    test( (t.getMode() & 0777) == 0444 );

    test( t.setMode( FileStat::USER, FileStat::EXEC ) );

    c.stat( "data/FileStat.set" );
    
    test( c.canExec( FileStat::USER ) );
    test( t.canExec( FileStat::USER ) );

    test( (c.getMode() & 0777) == 0544 );
    test( (t.getMode() & 0777) == 0544 );
    
    test( t.setMode( FileStat::USER | FileStat::GROUP | FileStat::OTHER,
		     FileStat::WRITE ) );
    
    c.stat( "data/FileStat.set" );
    
    test( c.canWrite( FileStat::USER ) );
    test( c.canWrite( FileStat::GROUP ) );
    test( c.canWrite( FileStat::OTHER ) );

    test( t.canWrite( FileStat::USER ) );
    test( t.canWrite( FileStat::GROUP ) );
    test( t.canWrite( FileStat::OTHER ) );

    test( (c.getMode() & 0777) == 0766 );
    test( (t.getMode() & 0777) == 0766 );
    
  }

  {
    // set( Who, What, bool )

    FileStat t( "data/FileStat.set" );
    FileStat c;
    
    test( t.setMode( 0777 ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0777 );
    test( (t.getMode() & 0777) == 0777 );

    test( t.setMode( FileStat::OTHER, FileStat::EXEC, false ) );

    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0776 );
    test( (t.getMode() & 0777) == 0776 );

    
    test( t.setMode( FileStat::USER | FileStat::GROUP | FileStat::OTHER,
		     FileStat::WRITE, false ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0554 );
    test( (t.getMode() & 0777) == 0554 );
  }

  {
    // setRead( Who )
    // setRead( Who, bool )
    // setWrite( Who )
    // setWrite( Who, bool )
    // setExec( Who )
    // setExec( Who, bool )

    FileStat t( "data/FileStat.set" );
    FileStat c;
    
    test( t.setMode( 0 ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0 );
    test( (t.getMode() & 0777) == 0 );

    test( t.setRead( FileStat::ALL ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0444 );
    test( (t.getMode() & 0777) == 0444 );

    test( t.setRead( FileStat::OTHER, false ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0440 );
    test( (t.getMode() & 0777) == 0440 );

    test( t.setWrite( FileStat::ALL ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0662 );
    test( (t.getMode() & 0777) == 0662 );

    test( t.setWrite( FileStat::OTHER, false ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0660 );
    test( (t.getMode() & 0777) == 0660 );

    test( t.setExec( FileStat::ALL ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0771 );
    test( (t.getMode() & 0777) == 0771 );

    test( t.setExec( FileStat::OTHER, false ) );
    
    c.stat( "data/FileStat.set" );

    test( (c.getMode() & 0777) == 0770 );
    test( (t.getMode() & 0777) == 0770 );

  }

  return( true );
}

      
