//
// File:        ArchiveFile.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Compiled sources for ArchiveFile
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/04/99 17:14
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//

#include <FilePath.hh>
#include <FileOp.hh>
#include <Compress.hh>

#include <LibLog.hh>

bool
ArchiveFile(
  const FilePath &  srcFn,
  const FilePath &  archiveDir,
  time_t	    archiveTimeStamp,
  bool		    compressIt
  )
{
  FilePath  destFn;

  FileOp    fileOp;
  
  DateTime	now( archiveTimeStamp ? archiveTimeStamp : time( 0 ), true );
  
  if( Compress::isCompressed( srcFn ) )
    {
      destFn << archiveDir << destFn.dirSep()
	     << srcFn.getName() << '-'
	     << now.getYYYYMMDD() << '.'
	     << now.getHHMMSS() << '.'
	     << srcFn.getExt()
	;
      
      if( ! fileOp.move( srcFn, destFn ) )
	{
	  LLgError << fileOp.error() << endl;
	  return( false );
	}
    }
  else
    {
      destFn << archiveDir << destFn.dirSep()
	     << srcFn.getFileName() << '-'
	     << now.getYYYYMMDD() << '.'
	     << now.getHHMMSS()
	;
      if( compressIt )
	{
	  DateTime	now( time(0), true );
	  
	  destFn << Compress::compExt();
	  
	  Compress	comp;
	  
	  if( ! comp.compress( srcFn, destFn ) )
	    {
	      LLgError << comp.error() << endl;
	      return( false );
	    }
	  
	  if( ! fileOp.remove( srcFn ) )
	    {
	      LLgError << fileOp.error() << endl;
	      return( false );
	    }
	}
      else
	{
	  if( ! fileOp.move( srcFn, destFn ) )
	    {
	      LLgError << fileOp.error() << endl;
	      return( false );
	    }
	}
    }
  
  return( true );
}


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
// Revision 4.1  1999/11/09 11:00:27  houghton
// Initial Version.
//
//
