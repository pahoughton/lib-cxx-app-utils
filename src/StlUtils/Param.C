//
// File:        Param.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     01/26/95 14:43 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:53  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "Param.hh"

ostream &
operator<<( ostream & dest, const Param & param )
{
  long oldFlags = dest.setf( ios::left );

  if( param.good() )
    {
      dest << '\n' << param.argv[0] << " help: " << '\n' << '\n';
    }
  else
    {
      dest << '\n' << param.argv[0] << ": param error" << "\n\n";
      dest << "  " << param.error() << "\n\n";
    }

  if( param.ver )
    {
      dest << "Ver: " << param.ver << "\n\n";
    }

  for( Pix a = param.helpList.first();
      a != 0;
      param.helpList.next( a ) )
    {
      dest << "  ";
      
      if( param.helpList(a)->argId )
	{
	  dest << '-' << setw(8) << param.helpList(a)->argId << ' ';
	}

      if( param.helpList(a)->desc )
	{
	  dest << param.helpList(a)->desc << ' ';
	}
      
      if( param.helpList(a)->envVar )
	{
	  dest << '(' << param.helpList(a)->envVar << ") ";
	}
      
      if( param.helpList(a)->value )
	{
	  switch( param.helpList(a)->type )
	    {
	    case Param::ARG_STRING:

	      if( strlen( *((char **)(param.helpList(a)->value)) ) > 20 )
		{
		  dest << "\n            '"
		       << *((char **)(param.helpList(a)->value)) << "'\n";
		}
	      else
		{
		  dest << '\'' << *((char **)(param.helpList(a)->value))
		       << "'\n";
		}
	      break;

	    case Param::ARG_INT:
	      
	      dest << '\'' << *((int *)(param.helpList(a)->value)) << "'\n";
	      break;

	    case Param::ARG_LONG:

	      dest << '\'' << *((long *)(param.helpList(a)->value)) << "'\n";
	      break;

	    case Param::ARG_FLAG:
	    case Param::ARG_BOOL:

	      if( *((Bool*)(param.helpList(a)->value)) != 0 )
		{
		  dest << "'TRUE'" << '\n';
		}
	      else
		{
		  dest << "'FALSE'" << '\n';
		}
	      break;
	      
	    case Param::ARG_DOUBLE:
	      dest << '\'' << *((double *)(param.helpList(a)->value)) << "'\n";
	      break;

	    case Param::ARG_DATETIME:
	    {
	      DateTime 	dt( *((time_t*)(param.helpList(a)->value)) );
	      
	      dest << '\'' << dt << "'\n";
	    }
	    break;

	    case Param::ARG_TELENUM:
	    
	      dest << '\''
		   << TeleNumDataToString( ((TeleNumData*)
					     (param.helpList(a)->value)) )
		   << "'\n";
	      break;
	      
	    default:

	      dest << "Unknown param type" << '\n';
	    }
	}
    }
      
  dest.flush();
  dest.flags( oldFlags );
  
  return( dest );
}



//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
