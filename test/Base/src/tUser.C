#include "TestConfig.hh"
#include "LibTest.hh"
#include "User.hh"
#include "Compare.hh"
#include <fstream>
#include <strstream.h>


int
compareGid( gid_t * one, gid_t * two )
{
  return( compare( *one, *two ) );
}

bool
tUser( LibTest & tester )
{
  uid_t	    uid = getuid();
  uid_t	    euid = geteuid();

  struct passwd * tpw;
  struct passwd  pw;
  struct passwd  epw;

  char name[50];
  char password[50];
  char gecos[50];
  char dir[50];
  char shell[50];
  
  char e_name[50];
  char e_password[50];
  char e_gecos[50];
  char e_dir[50];
  char e_shell[50];

  tpw = getpwuid( uid );
  strcpy( name, tpw->pw_name );
  strcpy( password, tpw->pw_passwd );
  strcpy( gecos, tpw->pw_gecos );
  strcpy( dir, tpw->pw_dir );
  strcpy( shell, tpw->pw_shell );
  
  memcpy( &pw, tpw, sizeof( struct passwd ) );
  pw.pw_name = name;
  pw.pw_passwd = password;
  pw.pw_gecos = gecos;
  pw.pw_dir = dir;
  pw.pw_shell = shell;
 
  tpw = getpwuid( euid );

  strcpy( e_name, tpw->pw_name );
  strcpy( e_password, tpw->pw_passwd );
  strcpy( e_gecos, tpw->pw_gecos );
  strcpy( e_dir, tpw->pw_dir );
  strcpy( e_shell, tpw->pw_shell );
  
  memcpy( &epw, tpw, sizeof( struct passwd ) );
  epw.pw_name = e_name;
  epw.pw_passwd = e_password;
  epw.pw_gecos = e_gecos;
  epw.pw_dir = e_dir;
  epw.pw_shell = e_shell;
  
  {
    // User( void )
    // getUID( void ) const
    // getName( void ) const
    // getPassword( void ) const
    // getRealName( void ) const
    // getGecos( void ) const
    // getHome( void ) const
    // getShell( void ) const
    // getPrimaryGroup( void ) const
    // getGroups( void ) const
    
    User t;

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
    
  }

  {
    // User( bool )

    User t( true );
    
    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( uid_t )
    
    User t( (uid_t)0 );

    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( uid_t, bool )

    User t( (uid_t)0, true );
    
    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( const char * )

    User t( pw.pw_name );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( const char *, bool )
    
    User t( pw.pw_name, true );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( const struct passwd * )

    User t( &pw );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( const struct passwd *, bool )
    
    User t( &pw, true );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( istream & src )

    strstream tStream;

    User uout( uid );

    uout.write( tStream );

    User t( tStream );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( istream &, bool )
    strstream tStream;

    User uout( uid );

    tStream << uout;

    User t( tStream, true );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // User( istream &, bool, bool )
    
    strstream tStream;

    User uout( uid );

    tStream << uout;

    User t( tStream, true, true );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // effective( void )

    TEST( User::effective().getUID() == euid );

  }

  // get the groups and put them in a sorted array for the
  // next few test

  setgrent();
  gid_t	groups[250];
  size_t gCount = 0;

  for( struct group * gr = getgrent(); gr; gr = getgrent() )
    {
      for( size_t memb = 0; gr->gr_mem[ memb ]; memb++ )
	{
	  if( ! compare( pw.pw_name, gr->gr_mem[ memb ] ) )
	    {
	      groups[ gCount ] = gr->gr_gid;
	      gCount++;
	    }
	}
    }

  qsort( groups, gCount, sizeof( groups[0] ),
	 (int(*)(const void*,const void*))compareGid );
  
  {
    // findGroups( void )
    // getGroups( void ) const
    
    User t( uid );

    t.findGroups();

    TEST( t.getGroups().size() == gCount );

    for( User::Groups::iterator them = t.getGroups().begin();
	 them != t.getGroups().end();
	 them++ )
      {
	const UserGroup & it = *them;
	gid_t key = it.getGID();
	gid_t * found = (gid_t *)bsearch( &key,
					  groups,
					  gCount,
					  sizeof( groups[0] ),
					  (int(*)(const void*,const void*))compareGid );
	TEST( found != 0 );
	TEST( *found == (*them).getGID() );
      }
  }

  {
    // isMember( gid_t )

    User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      TEST( t.isMember( groups[g] ) );

  }
  
  {
    // isMember( gid_t ) const

    const User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      TEST( ! t.isMember( groups[g] ) );

  }
    
  {
    // isMember( gid_t ) const

    const User t( uid, true );

    for( size_t g = 0; g < gCount; g++ )
      TEST( t.isMember( groups[g] ) );

  }

  {
    // isMember( const char * )

    User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      {
	Str grName( getgrgid( groups[g] )->gr_name ); ;
	
	TESTR( grName, t.isMember( grName ) );
      }
  }
  
  {
    // isMember( const char * ) const

    const User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      TEST( ! t.isMember( getgrgid( groups[g] )->gr_name ) );
  }
  
  {
    // isMember( const char * ) const

    const User t( uid, true );

    for( size_t g = 0; g < gCount; g++ )
      {
	Str grName( getgrgid( groups[g] )->gr_name ); ;
	
	TESTR( grName, t.isMember( grName ) );
      }
  }

  {
    // set( uid_t )

    User t( uid );

    t.set( (uid_t) 0 );

    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // set( uid_t, bool )

    User t( uid );

    t.set( (uid_t) 0, true );

    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }

  {
    // set( const char * )
    User t( uid );

    t.set( "root" );

    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }
  
  {
    // set( const char *, bool )
    User t( uid );

    t.set( "root", true );

    TEST( t.getUID() == 0 );
    TEST( compare( t.getName(), "root" ) == 0 );
    TEST( t.getGroups().size() != 0 );
  }
    
  {
    // set( const struct passwd * )
    
    User t( (uid_t)0 );

    t.set( &pw );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );    
  }
    
  {
    // set( const struct passwd * )
    
    User t( (uid_t)0 );

    t.set( &pw, true );

    TEST( t.getUID() == uid );
    TEST( compare( t.getName(), pw.pw_name ) == 0 );
    TEST( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    TEST( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    TEST( compare( t.getHome(), pw.pw_dir ) == 0 );
    TEST( compare( t.getShell(), pw.pw_shell ) == 0 );
    TEST( t.getPrimaryGroup().getGID() == pw.pw_gid );
    TEST( t.getGroups().size() != 0 );    
  }

  {
    // compare( const User & two ) const
    // operator == ( const User & two ) const
    // operator <  ( const User & two ) const
    // operator >  ( const User & two ) const
    
    const User  tr( (uid_t) 0 );
    const User  tu( uid );

    TEST( tu.compare( tu ) == 0 );
    TEST( tu == tu );
    TEST( tu.compare( tr ) != 0 );
    TEST( tr.compare( tu ) > 0 );
    TEST( tr > tu );
    TEST( tu.compare( tr ) < 0 );
    TEST( tu < tr );
  }

  {
    // operator const char * ( void ) const

    const User t( uid );

    TEST( strcmp( t, pw.pw_name ) == 0 );
  }

  {
    // operator uid_t ( void ) const

    const User t( uid );

    TEST( getpwuid( t )->pw_uid == t.getUID() );
  }

#if defined( CLUE_BINSTREAM )
  {
    // getBinSize( void ) const
    // write( BinStream & dest ) const
    // read( BinStream & src )
    // BinStream::write( const BinObject & obj )
    // BinStream::read( BinObject & obj )

    HeapBinStream tStrm;

    const User  tw( uid );
    User	tr;

    TEST( tw.getBinSize() );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tStrm.good() );
    TEST( (size_t)tStrm.tellp() == tw.getBinSize() );
    TEST( tStrm.tellg() == tStrm.tellp() );
    TEST( tr.getBinSize() == tw.getBinSize() );
    TEST( tw == tr );

    tr = 0;
    TEST( tw != tr );
    
    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
  }
#endif
  
  {
    // write( ostream & ) const
    // read( istream & )

    const User  tw( uid );
    User	tr;

    strstream tStrm;

    streampos gpos = tStrm.tellg();
    streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tw.write( tStrm );
    ppos += tw.getBinSize();
    TEST( ppos == tStrm.tellp() );
      
    tr.read( tStrm );
    gpos += tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    strstream tStrm;
    const User t( uid );

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const User t( uid );

    TESTR( t.error(), t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const User t( uid );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
  {
    // ::compare( const User &, const User & );
    
    const User  tr( (uid_t) 0 );
    const User  tu( uid );

    TEST( compare( tu, tu ) == 0 );
    TEST( compare( tu, tr ) != 0 );
    TEST( compare( tr, tu ) > 0 );
    TEST( compare( tu, tr ) < 0 );
  }
  
  return( true );
}
