// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/User.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <fstream>
#include <sstream>

static valid::verify verify("clue::User");
using namespace clue;


extern "C"
{
  typedef int (*CompFunct)( const void * a, const void * b );
  static int compareGid( const gid_t * one, const gid_t * two );
};

static
int
compareGid( const gid_t * one, const gid_t * two )
{
  return( compare( *one, *two ) );
}

bool
v_User( void )
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
    // FIXME - need to define this in the TestConfig for other platforms.
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
  }

  {
    // User( istream & src )

    std::stringstream tStream;

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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
  }

  {
    // User( istream &, bool )
    std::stringstream tStream;

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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
  }

  {
    // User( istream &, bool, bool )

    std::stringstream tStream;

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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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

  ::qsort( groups, gCount, sizeof( groups[0] ),
	   (CompFunct)compareGid );

  {
    // findGroups( void )
    // getGroups( void ) const

    User t( uid );

    t.findGroups();

    TEST( t.getGroups().size() == gCount
	  || t.getGroups().size() == gCount + 1 );

    for( User::Groups::const_iterator them = t.getGroups().begin();
	 them != t.getGroups().end();
	 them++ )
      {
	const UserGroup & it = *them;
	gid_t key = it.getGID();
	gid_t * found
	  = (gid_t *)::bsearch( &key,
				groups,
				gCount,
				sizeof( groups[0] ),
				(CompFunct)compareGid );

	if( found == 0 )
	  {
	    TEST( key == t.getPrimaryGroup().getGID() );
	  }
	else
	  {
	    TEST( *found == (*them).getGID() );
	  }
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

	TEST( t.isMember( grName ) );
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

	TEST( t.isMember( grName ) );
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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
#if defined( STLUTILS_TEST_MULTI_GROUPS )
    TEST( t.getGroups().size() != 0 );
#endif
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


  {
    // write( ostream & ) const
    // read( istream & )

    const User  tw( uid );
    User	tr;

    std::stringstream tStrm;

    std::streampos gpos = tStrm.tellg();
    std::streampos ppos = tStrm.tellp();

    TEST( ppos == 0 );
    TEST( gpos == 0 );

    tw.write( tStrm );
    ppos += (std::streampos) tw.getBinSize();
    TEST( ppos == tStrm.tellp() );

    tr.read( tStrm );
    gpos += (std::streampos) tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    std::stringstream tStrm;
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

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  {
    // ::compare( const User &, const User & );

    const User  tr( (uid_t) 0 );
    const User  tu( uid );

    TEST( compare( tu, tu ) == 0 );
    TEST( compare( tu, tr ) != 0 );
  }
  return( verify.is_valid() );
}
