#include <LibTest.hh>
#include <User.hh>

#include <Str.hh>
#include <Compare.hh>

#include <fstream>
#include <strstream>

int
compareGid( gid_t * one, gid_t * two )
{
  return( compare( *one, *two ) );
}

bool
tUser( LibTest & test )
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

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );
    
  }

  {
    // User( bool )

    User t( true );
    
    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() != 0 );
  }

  {
    // User( uid_t )
    
    User t( (uid_t)0 );

    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() == 0 );
  }

  {
    // User( uid_t, bool )

    User t( (uid_t)0, true );
    
    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() != 0 );
  }

  {
    // User( const char * )

    User t( pw.pw_name );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );
  }

  {
    // User( const char *, bool )
    
    User t( pw.pw_name, true );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() != 0 );
  }

  {
    // User( const struct passwd * )

    User t( &pw );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );
  }

  {
    // User( const struct passwd *, bool )
    
    User t( &pw, true );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() != 0 );
  }

  {
    // User( istream & src )

    strstream tStream;

    User uout( uid );

    uout.write( tStream );

    User t( tStream );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );
  }

  {
    // User( istream &, bool )
    strstream tStream;

    User uout( uid );

    tStream << uout;

    User t( tStream, true );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );
  }

  {
    // User( istream &, bool, bool )
    
    strstream tStream;

    User uout( uid );

    tStream << uout;

    User t( tStream, true, true );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() != 0 );
  }

  {
    // effective( void )

    test( User::effective().getUID() == euid );

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

    test( t.getGroups().size() == 0 );

    t.findGroups();

    test( t.getGroups().size() == gCount );

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
	test( found != 0 );
	test( *found == (*them).getGID() );
      }
  }

  {
    // isMember( gid_t )

    User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      test( t.isMember( groups[g] ) );

  }
  
  {
    // isMember( gid_t ) const

    const User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      test( ! t.isMember( groups[g] ) );

  }
    
  {
    // isMember( gid_t ) const

    const User t( uid, true );

    for( size_t g = 0; g < gCount; g++ )
      test( t.isMember( groups[g] ) );

  }

  {
    // isMember( const char * )

    User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      test( t.isMember( getgrgid( groups[g] )->gr_name ) );
  }
  
  {
    // isMember( const char * ) const

    const User t( uid );

    for( size_t g = 0; g < gCount; g++ )
      test( ! t.isMember( getgrgid( groups[g] )->gr_name ) );
  }
  
  {
    // isMember( const char * ) const

    const User t( uid, true );

    for( size_t g = 0; g < gCount; g++ )
      test( t.isMember( getgrgid( groups[g] )->gr_name ) );
  }

  {
    // set( uid_t )

    User t( uid );

    t.set( (uid_t) 0 );

    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() == 0 );
  }

  {
    // set( uid_t, bool )

    User t( uid );

    t.set( (uid_t) 0, true );

    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() != 0 );
  }

  {
    // set( const char * )
    User t( uid );

    t.set( "root" );

    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() == 0 );
  }
  
  {
    // set( const char *, bool )
    User t( uid );

    t.set( "root", true );

    test( t.getUID() == 0 );
    test( compare( t.getName(), "root" ) == 0 );
    test( t.getGroups().size() != 0 );
  }
    
  {
    // set( const struct passwd * )
    
    User t( (uid_t)0 );

    t.set( &pw );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() == 0 );    
  }
    
  {
    // set( const struct passwd * )
    
    User t( (uid_t)0 );

    t.set( &pw, true );

    test( t.getUID() == uid );
    test( compare( t.getName(), pw.pw_name ) == 0 );
    test( compare( t.getPassword(), pw.pw_passwd ) == 0 );
    test( compare( t.getRealName(), pw.pw_gecos ) == 0 );
    test( compare( t.getGecos(), pw.pw_gecos ) == 0 );
    test( compare( t.getHome(), pw.pw_dir ) == 0 );
    test( compare( t.getShell(), pw.pw_shell ) == 0 );
    test( t.getPrimaryGroup().getGID() == pw.pw_gid );
    test( t.getGroups().size() != 0 );    
  }

  {
    // getStreamSize( void ) const
    // write( ostream & ) const
    // read( istream & ) const
    
    const User	    tout( uid );
    User	    tin;

    strstream testStream;

    streampos gpos = testStream.tellg();
    streampos ppos = testStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    test( ppos == 0 );
    test( gpos == 0 );
    
    tout.write( testStream );
    ppos += tout.getStreamSize();
    test( ppos == testStream.tellp() );
      
    tin.read( testStream );
    gpos += tin.getStreamSize();
    test( gpos == testStream.tellg() );
    test( tin == tout );
  }

  {
    // compare( const User & two ) const
    // operator == ( const User & two ) const
    // operator <  ( const User & two ) const
    // operator >  ( const User & two ) const
    
    const User  tr( (uid_t) 0 );
    const User  tu( uid );

    test( tu.compare( tu ) == 0 );
    test( tu == tu );
    test( tu.compare( tr ) != 0 );
    test( tr.compare( tu ) > 0 );
    test( tr > tu );
    test( tu.compare( tr ) < 0 );
    test( tu < tr );
  }

  {
    // operator const char * ( void ) const

    const User t( uid );

    test( strcmp( t, pw.pw_name ) == 0 );
  }

  {
    // operator uid_t ( void ) const

    const User t( uid );

    test( getpwuid( t )->pw_uid == t.getUID() );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // version

    const User t( uid );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream tStream;

    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.version != 0 );
  }

  {
    // ::compare( const User &, const User & );
    
    const User  tr( (uid_t) 0 );
    const User  tu( uid );

    test( compare( tu, tu ) == 0 );
    test( compare( tu, tr ) != 0 );
    test( compare( tr, tu ) > 0 );
    test( compare( tu, tr ) < 0 );
  }
  
  {
    // operator << ( ostream &, const User & )

    const User t;

    strstream tStream;

    tStream << t;
  }

  return( true );
}
