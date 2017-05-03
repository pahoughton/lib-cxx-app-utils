//
// File:        tClassVersion.C
// Project:	StlUtils
// Desc:        
//
//  Test for ClassVersion class.
//
// Source Header Version: 2.5
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/25/96 08:21
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include <strstream.h>
#include <cstring>

			
#define CLASS_NAME	"TestClass"
#define FULL_VER_STRING	"Full Version String"
#define FILE_NAME	__FILE__
#define COMPILE_DATE	__DATE__
#define COMPILE_TIME	__TIME__
#define VER_ID_STRING	"Version ID"
#define PRJ_NAME	"Project"
#define PRJ_VER_NUM	"1.00.00"
#define PRJ_VER		10001L
#define PRJ_VER_TAG	"TEST_01"

#define CLASS_VER	CLASS_NAME " - " FILE_NAME " - Compiled: "	      \
			COMPILE_DATE " " COMPILE_TIME "\n"		      \
			"    " VER_ID_STRING  

#define CLASS_NAME_2	    "Class 2"
#define FULL_VER_STRING_2   "Class 2 Full Version String"
#define FILE_NAME_2	    "File 2"
#define COMPILE_DATE_2	    "Date 2"
#define COMPILE_TIME_2	    "Time 2"
#define VER_ID_STRING_2	    "Version ID 2"
#define PRJ_NAME_2	    "Project 2"
#define PRJ_VER_NUM_2	    "2.00.00"
#define PRJ_VER_2	    20001L
#define PRJ_VER_TAG_2	    "TEST_02"
			
#define CLASS_VER_2	CLASS_NAME_2 " - " FILE_NAME_2 " - Compiled: "	      \
			COMPILE_DATE_2 " " COMPILE_TIME_2 "\n"		      \
			"    " VER_ID_STRING_2

// CLASS_VERSION( type name,
//                const char *,
//                const char *,
//                const char *,
//		long
// see below for actual testing

class TestCV
{
public:
  static const ClassVersion version;
};

CLASS_VERSION( TestCV, VER_ID_STRING,
	       PRJ_NAME, PRJ_VER_NUM, PRJ_VER, PRJ_VER_TAG );


bool
tClassVersion( LibTest & tester )
{
  {
    // ClassVersion objects should always be static const
    
    static const ClassVersion	t( CLASS_NAME,
				   FULL_VER_STRING,
				   FILE_NAME,
				   COMPILE_DATE,
				   COMPILE_TIME,
				   VER_ID_STRING,
				   PRJ_NAME,
				   PRJ_VER_NUM,
				   PRJ_VER,
				   PRJ_VER_TAG );
    
    static const ClassVersion	t2( CLASS_NAME_2,
				   FULL_VER_STRING_2,
				   FILE_NAME_2,
				   COMPILE_DATE_2,
				   COMPILE_TIME_2,
				   VER_ID_STRING_2,
				   PRJ_NAME_2,
				   PRJ_VER_NUM_2,
				   PRJ_VER_2,
				   PRJ_VER_TAG_2 );

    
    {
      // const char * getVer( bool ) const

      
      TEST( strcmp( t.getVer( true ), FULL_VER_STRING ) == 0 );
      TEST( strcmp( t.getVer( false ), CLASS_VER ) == 0 );
    }

    {
      // const char * getVer( bool, const char * ) const

      TEST( strcmp( t.getVer( true, t2.getVer( false ) ),
		    FULL_VER_STRING "\n    " CLASS_VER_2 )
	    == 0 );
      
      TEST( strcmp( t.getVer( false, t2.getVer( true ) ),
		    CLASS_VER "\n    " FULL_VER_STRING_2 )
	    == 0 );
      
      // const char * getClassVer( void ) const

      TEST( strcmp( t.getClassVer(), CLASS_VER ) == 0 );

      // const char * getPrjVer( void ) const

      TESTR( t.getPrjVer(), strcmp( t.getPrjVer(),
				    PRJ_NAME " - "
				    PRJ_VER_NUM " - " PRJ_VER_TAG ) == 0 );

      // unsigned long getPrjVerNum( void ) const
      
      TEST( t.getPrjVerNum() == PRJ_VER );

      // const char * getClassName( void ) const

      TEST( strcmp( t.getClassName(), "ClassVersion" ) == 0 );

      // const char * getVersion( void ) const

      TEST( strstr( t.getVersion(), "@(#) libStlUtils - " ) != 0 );
      TEST( strstr( t.getVersion(), "ClassVersion" ) != 0 );
      TEST( strstr( t.getVersion(), "Compiled: " ) != 0 );

      // const char * getVersion( bool ) const
      TEST( strstr( t.getVersion(true), "@(#) libStlUtils - " ) != 0 );
      TEST( strstr( t.getVersion(true), "ClassVersion" ) != 0 );
      TEST( strstr( t.getVersion(true), "Compiled: " ) != 0 );

      TEST( strstr( t.getVersion(false), "@(#) libStlUtils - " ) == 0 );
      TEST( strstr( t.getVersion(false), "ClassVersion" ) != 0 );
      TEST( strstr( t.getVersion(false), "Compiled: " ) != 0 );

      // operator const char * () const
      TEST( strcmp( t, FULL_VER_STRING ) == 0 );

      // ostream & operator << ( ostream & dest, const ClassVersion & obj )

      strstream	buf;
      
      buf << t << ends;
      TEST( strcmp( buf.str(), FULL_VER_STRING ) == 0 );

      buf.rdbuf()->freeze(0);
      
      // static const ClassVersion version
      TEST( strcmp( ClassVersion::version.getVer( true ),
		    t.getVersion( true ) ) == 0 );
      
    }

    {
      // CLASS_VERSION( type name,
      //                const char *,
      //                const char *,
      //                const char *,
      //		long

      TESTR( TestCV::version.getVer( true ),
	     strcmp( TestCV::version.getVer( true ),
		     "@(#) " PRJ_NAME " - " PRJ_VER_NUM "\n"
		     "    TestCV - " __FILE__ " - Compiled: "
		     __DATE__ " " __TIME__ "\n"
		     "    CVS Tag: " PRJ_VER_TAG "\n"
		     "    " VER_ID_STRING ) == 0 );
    }
    
  }
  
  return( true );
}

  
//
// $Log$
// Revision 6.2  2011/12/30 23:57:42  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:06  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:09:38  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/06/09 12:04:18  houghton
// Changed to match latest modifications.
//
// Revision 3.3  1996/11/24 19:14:04  houghton
// Changed for AIX because bool is not a real type.
//
// Revision 3.2  1996/11/19 12:34:17  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:26:25  houghton
// Changed to Release 3
//
// Revision 2.1  1996/11/04 14:46:30  houghton
// Initial Version.
//
//
