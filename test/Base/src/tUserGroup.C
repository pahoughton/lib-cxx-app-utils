#include <LibTest.hh>
#include <UserGroup.hh>
#include <User.hh>

#include <Compare.hh>

#include <strstream>

bool
tUserGroup( LibTest & test )
{
  gid_t	gid = getgid();
  gid_t egid = getegid();
  gid_t bgid;
    
  struct group grp;
  struct group egrp;
  struct group bgrp;
  
  char name[50];
  char ename[50];
  char bname[50];
  
  struct group * tgrp;

  tgrp = getgrgid( gid );

  strcpy( name, tgrp->gr_name );
  
  memcpy( &grp, tgrp, sizeof( grp ) );
  grp.gr_name = name;
  
  tgrp = getgrgid( egid );

  strcpy( ename, tgrp->gr_name );

  memcpy( &egrp, tgrp, sizeof( egrp ) );
  egrp.gr_name = ename;

  tgrp = getgrnam( "bin" );
  test( tgrp != 0 );

  strcpy( bname, tgrp->gr_name );
  memcpy( &bgrp, tgrp, sizeof( bgrp ) );
  bgrp.gr_name = bname;
  bgid = bgrp.gr_gid;

  size_t bMembCount = 0;

  for( size_t m = 0; tgrp->gr_mem[m]; m++ )
    bMembCount++;
  
  {
    // UserGroup( void )
    // getGID( void ) const
    // getName( void ) const
    // getMembers( void ) const
    
    UserGroup t;

    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( bool )

    UserGroup t( true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( gid_t )

    UserGroup t( bgid );

    test( t.getGID() == bgid );
    test( compare( t.getName(), bgrp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }
  
  {
    // UserGroup( gid_t, bool )

    UserGroup t( gid, true );

    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( const char * )

    UserGroup t( bgrp.gr_name );

    test( t.getGID() == bgid );
    test( compare( t.getName(), bgrp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( const char *, bool )
    
    UserGroup t( grp.gr_name, true );

    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( struct group * )

    UserGroup t( getgrgid( gid ) );

    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( struct group *, bool )

    UserGroup t( getgrgid( gid ), true );

    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( istream & )

    strstream tStream;

    UserGroup gout( gid );

    gout.write( tStream );

    UserGroup t( tStream );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() == 0 );
  }
  
  {
    // UserGroup( istream &, bool )
    strstream tStream;

    UserGroup gout( gid );

    tStream << gout;

    UserGroup t( tStream, true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() == 0 );
  }
  
  {
    // UserGroup( istream &, bool, bool )
    strstream tStream;

    UserGroup gout( gid );

    tStream << gout;

    UserGroup t( tStream, true, true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0);
    test( t.getMembers().size() != 0 );
  }

  {
    // effective( void )

    test( UserGroup::effective().getGID() == egid );
  }

  {
    // findMembers( void )
    // getMembers( void ) const
    // isMember( const User & )

    UserGroup t( gid );

    test( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );
	  
	  test( t.isMember( u ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
    
  }

  {
    // isMember( const User & ) const
    
    const UserGroup t( gid, true );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );
	  
	  test( t.isMember( u ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( uid_t )
    
    UserGroup t( gid );

    test( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );
	  
	  test( t.isMember( u.getUID() ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( uid_t ) const
    
    const UserGroup t( gid, true );


    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );
	  
	  test( t.isMember( u.getUID() ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( const char * )
    
    UserGroup t( gid );

    test( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  test( t.isMember( g.gr_mem[m] ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( const char * ) const
    
    const UserGroup t( gid, true );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );
    
    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	mCount++;
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );
    
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
	  g.gr_mem[m] = strdup( gent->gr_mem[m] );
	}
      g.gr_mem[mCount] = 0;
    }
    
    test( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  test( t.isMember( g.gr_mem[m] ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }
      
  {
    // set( gid_t )

    UserGroup t;

    t.set( bgid );

    test( t.getGID() == bgid );
    test( compare( t.getName(), bgrp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }

  {
    // set( gid_t, bool )

    UserGroup t( bgid );

    t.set( gid, true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() != 0 );
  }

  {
    // set( const char * )

    UserGroup t( bgid );

    t.set( grp.gr_name );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }

  {
    // set( const char *, bool )

    UserGroup t( bgid );

    t.set( grp.gr_name, true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() != 0 );
  }

  {
    // set( const struct group * )

    UserGroup t( bgid );

    t.set( &grp );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() == 0 );
  }

  {
    // set( const struct group *, bool )

    UserGroup t( bgid );

    t.set( &grp, true );
    
    test( t.getGID() == gid );
    test( compare( t.getName(), grp.gr_name ) == 0 );
    test( t.getMembers().size() != 0 );
  }

  {
    // getStreamSize( void ) const
    // write( ostream & ) const
    // read( ostream & )

    const UserGroup tout( gid );
    UserGroup	    tin( bgid );

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
    // compare( const UserGroup & ) const
    // operator == ( const UserGroup & ) const
    // operator <  ( const UserGroup & ) const
    // operator >  ( const UserGroup & ) const
    
    const char * l = 0;
    const char * m = 0;
    
    if( compare( grp.gr_name, bgrp.gr_name ) < 0 )
      {
	l = grp.gr_name;
	m = bgrp.gr_name;
      }
    else
      {
	l = bgrp.gr_name;
	m = grp.gr_name;
      }
	
    const UserGroup t( l );
    const UserGroup tm( m );

    test( t.compare( t ) == 0 );
    test( t == t );
    test( t.compare( tm ) < 0 );
    test( t < tm );
    test( tm.compare( t ) > 0 );
    test( tm > t );
  }

  {
    // operator const char * ( void ) const
    // operator gid_t ( void ) const;

    const UserGroup t( gid );
    
    char gn[ 50 ];

    strcpy( gn, t );

    test( compare( t.getName(), gn ) == 0 );

    test( getgrgid( t )->gr_gid == gid );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // version

    const UserGroup t;

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream tStream;

    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.version != 0 );
  }
  
  {
    // ::compare( const UserGroup &, const UserGroup & );
    const char * l = 0;
    const char * m = 0;
    
    if( compare( grp.gr_name, bgrp.gr_name ) < 0 )
      {
	l = grp.gr_name;
	m = bgrp.gr_name;
      }
    else
      {
	l = bgrp.gr_name;
	m = grp.gr_name;
      }
	
    const UserGroup t( l );
    const UserGroup tm( m );

    test( compare( t, t ) == 0 );
    test( compare( t, tm ) < 0 );
    test( compare( tm, t ) > 0 );
  }

  {
    // operator << ( ostream &, const UserGroup & )

    const UserGroup t( gid );

    strstream tStream;

    tStream << t;
  }

  return( true );
}






