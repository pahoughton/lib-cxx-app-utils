
#ifndef _ClassVersion_hh_
#define _ClassVersion_hh_
//
// File:        ClassVersion.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     10/04/95 07:04
//
// Revision History:
//
// $Log$
// Revision 2.3  1996/04/27 12:52:40  houghton
// Cleanup.
//
// Revision 2.2  1995/12/04 11:16:59  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:19  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  14:48:48  houghton
// New Class Version id method
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <iostream>
#endif


class CLUE_CLASS_T ClassVersion
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
		unsigned long prjVer = 0 );

  ~ClassVersion( void );

  inline const char *	getVer( bool withPrjVer ) const;
  const char *		getVer( bool withPrjVer,
				const char * baseVerString ) const;
  
  inline const char *   getClassVer( void ) const;
  inline const char *   getPrjVer( void ) const;
  
  inline unsigned long	getPrjVerNum( void ) const;

  inline const char *	getVersion( bool withPrjVer = true ) const;

  static const ClassVersion version;
  
protected:

private:

  const char *	verString;
  char *     	classVerString;
  char *	prjVerString;
  
  unsigned long	prjVerNum;

};


#define CLASS_VERSION( className_, verId_, prjName_, prjVer_, prjVerNum_ )    \
									      \
const ClassVersion className_::version( #className_,			      \
									      \
"@(#) " prjName_ " - " prjVer_ "\n"					      \
"    " #className_ " - " __FILE__ " - Compiled: " __DATE__ " " __TIME__ "\n"  \
"    " verId_,								      \
                                        __FILE__,			      \
					__DATE__,			      \
					__TIME__,			      \
					verId_,				      \
					prjName_,			      \
					prjVer_,			      \
					prjVerNum_ )

#if !defined( CLUE_SHORT_FN )
#include <ClassVersion.ii>
#else
#include <ClassVer.ii>
#endif

//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	ClassVersion	class
//
//  Constructors:
//
//  	ClassVersion( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. ClassVersion )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const ClassVersion & obj );

#endif // ! def _ClassVersion_hh_ 

