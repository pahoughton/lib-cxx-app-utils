#ifndef _ClassVersion_hh_
#define _ClassVersion_hh_
//
// File:        ClassVersion.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Provides information about a class's version that is accessible
//  at run time.
//
// Quick Start: - short example of class usage
//
//  class MyClass
//  {
//  public:
//     static const ClassVersion version;
//  };
//
//  in .C (.cpp or whatever)
//
//     const ClassVersion MyClass::version( "MyClass",
//                                          "Version info string",
//					    __FILE__,
//					    __DATE__,
//					    __TIME__,
//					    "RCS_ID_TAG",
//					    "ProjectName",
//					    "2.01.05",
//					    20105L);
//       OR
//
//    CLASS_VERSION( MyClass, "RCS_ID_TAG", "ProjectName", "2.01.05", 20105L );
//
//    See StlUtilsVersion.hh for another example of a helper macro.
//
// Author:      Paul Houghton - (paul_houghton@wcom.com)
// Created:     10/04/95 07:04
//
// Revision History: (See end of file for Revision Log)
//
// %PID%
//

#include "StlUtilsConfig.hh"
#include <iostream>


class STLUTILS_CLASS_T ClassVersion
{

public:

  ClassVersion( const char * className,
		const char * fullVerString,
		const char * fileName,		    // __FILE__
		const char * compileDateString,	    // __DATE__
		const char * compileTimeString,	    // __TIME__
		const char * verIdString,	    // Id:
		const char * prjName = "",
		const char * prjVerNum = "",
		unsigned long prjVer = 0,
		const char * prjVerTag = "" );

  ~ClassVersion( void );

  inline const char *	getVer( bool withPrjVer ) const;
  const char *		getVer( bool withPrjVer,
				const char * baseVerString ) const;
  
  inline const char *   getClassVer( void ) const;
  inline const char *   getPrjVer( void ) const;
  
  inline unsigned long	getPrjVerNum( void ) const;

  inline const char *	getClassName( void ) const;
  inline const char *	getVersion( bool withPrjVer = true ) const;

  inline		operator const char * () const;
  
  friend
  inline ostream & operator << ( ostream & dest, const ClassVersion & obj );

  static const ClassVersion version;
  
protected:

private:

  const char *	verString;
  char *     	classVerString;
  char *	prjVerString;
  
  unsigned long	prjVerNum;

};


#define CLASS_VERSION( className_, verId_, prjName_, prjVer_, prjVerNum_, prjVerTag_ )  \
									      \
const ClassVersion className_::version( #className_,			      \
									      \
"@(#) " prjName_ " - " prjVer_ "\n"					      \
"    " #className_ " - " __FILE__ " - Compiled: " __DATE__ " " __TIME__ "\n"  \
"    CVS Tag: " prjVerTag_ "\n"						      \
"    " verId_,								      \
                                        __FILE__,			      \
					__DATE__,			      \
					__TIME__,			      \
					verId_,				      \
					prjName_,			      \
					prjVer_,			      \
					prjVerNum_,			      \
                                        prjVerTag_ )

#if !defined( STLUTILS_SHORT_FN )
#include <ClassVersion.ii>
#else
#include <ClassVer.ii>
#endif

//
// Detail Documentation
//
//  Types:
//
//  	class	ClassVersion
//
//  Constructors:
//
//  	ClassVersion( const char * className,
//		      const char * fullVerString,
//		      const char * fileName,
//		      const char * compileDateString,
//		      const char * compileTimeString,
//		      const char * verIdString,
//		      const char * prjName = "",
//		      const char * prjVerNum = "",
//		      unsigned long prjVer = 0 );
//	    Construct an instance.
//	    Args:
//		'className'	the name of the class this instance is for.
//		'fullVerString'	the string returned by getVer when
//				withPrjVer == true.
//		'fileName'	source file name (i.e. __FILE__ ).
//		'compileDateString'
//				date compiled (i.e. __DATE__ ).
//		'compileTimeString'
//				time compiled (i.e. __DATE__ ).
//		'verIdString'	version identifier tag that is expanded
//				by source code control software (for
//				rcs, cvs, rpm this is Id:).
//		'prjName'	the name of the project, library or
//				application your class is associated with.
//		'prjVerNum'	the version number for the project
//				something like '2.00.04'.
//		'prjVer'	a long representation of your projects
//				version identifier.
//
//  Destructors:
//
//	~ClassVersion( void );
//
//  Public Interface:
//
//	inline
//	const char *
//	getVer( bool withPrjVer ) const;
//	    Return a string description of the class's version. If
//	    withPrjVer == true, the entire description will be returned.
//	    if withPrjVer == false, just the class's version will be returned.
//
//	const char *
//	getVer( bool withPrjVer, const char * baseVerString ) const;
//	    Same as getVer( bool ) but baseVerString is appended to
//	    the output string. This allows you to provide full version
//	    info for all base classes and contained classes. So, if you
//	    had 'class Sub : public Base { Type var1 }' you could call
//	    'Sub::version.getVer( true, Base::version.getVer( false,
//	    Type::version.getVer( false )))'. See Exmple below for more
//	    info.
//
//	inline
//	const char *
//	getClassVer( void ) const
//	    Return the string description of the class's version string
//	    only. Same as getVer( false ).
//
//	inline
//	const char *
//	getPrjVer( void ) const;
//	    Return the project version string only.
//
//	inline
//	unsigned long
//	getPrjVerNum( void ) const;
//	    Return the project's version number. This is the same value
//	    passed to the constructor as 'prjVer';
//
//  	inline
//	const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. ClassVersion)
//
//	inline
//	const char *
//	getVersion( bool withPrjVer = true ) const;
//	    Return the version information for ClassVersion. Calls
//	    ClassVersion::version.getVer( withPrjVer );
//
//	inline
//	operator const char * () const;
//	    Return the value from getVer( true ).
//
//	static
//	const ClassVersion version;
//	    This is the version info for ClassVersion.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Macros:
//
//	CLASS_VERSION( className, verId, prj, prjVerNum, prjVer )
//	    This is a helper macro for your .C files that will
//	    instantiate a static const ClassVersion className::version
//	    variable for you. Where 'className' is the name of the
//	    class (do NOT quoute), 'verId' is the version id string,
//	    'project' is the project name string, 'prjVerNum' is the project
//	    version number string, and 'prjVer' is a long that identifies
//	    the project's version.
//
//  Associated Functions:
//
//	inline
//  	ostream &
//  	operator << ( ostream & dest, const ClassVersion & obj );
//  	    Put the string returned by getVer( true ) on the ostream.
//
//  Example:
//
//	This is how I use ClassVersion in all my classes.
//
//	class Thing : public Base
//	{
//	public:
//	  ...
//	  virtual const char * getVersion( bool withPrjVer = true ) const;
//
//	  static const ClassVersion version;
//	private:
//	  Stuff   stuffVar;
//	};
//
//	This goes in the .C file.
//
//	CLASS_VERSION( Thing, "Id:", "Project", "1.00.01", 10001L );
//
//	const char *
//	Thing::getVersion( bool withPrjVer ) const
//	{
//	  return( version.getVer( true,
//		    Base::version.getVer( false,
//		      stuffVar.getVersion( false ) ) ) );
//	}
//
// See Also:
//
//  StlUtilsVersion.hh
//
// Files:
//
//  ClassVersion.hh, ClassVersion.ii,
//  StlUtilsConfig.hh, StlUtilsVersion.hh,
//  libStlUtils.a
//
// Documented Ver:  2.5
// Tested Ver:	    2.5
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:29:01  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/03/23 10:44:33  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.1  1997/09/17 15:12:12  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:11  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/04/26 14:41:01  houghton
// Added project tag support.
//
// Revision 3.2  1996/11/19 12:20:26  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:23:28  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/04 13:28:37  houghton
// Added Associated Macros to header comments
// Cleanup header comments.
//
// Revision 2.5  1996/10/28 11:55:23  houghton
// Added: ostream & operator << ( ostream & dest, const ClassVersion & obj )
// Added: operator const char * ()
// Edit and verify header docuementation for man page generation.
//
// Revision 2.4  1996/10/25 12:47:10  houghton
// Added: getClassName.
// Updated documentation.
//
// Revision 2.3  1996/04/27 12:52:40  houghton
// Cleanup.
//
// Revision 2.2  1995/12/04 11:16:59  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:19  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:48  houghton
// New Class Version id method
//
//

#endif // ! def _ClassVersion_hh_ 
