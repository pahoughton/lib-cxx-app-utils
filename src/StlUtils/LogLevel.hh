#ifndef _LogLevel_hh_
#define _LogLevel_hh_
//
// File:        LogLevel.hh
// Desc:        
//              
//
// Notes:   	default copy construtor and assignment operators are ok.
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:27
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:47  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <Clue.hh>

class LogLevel 
{
  
public:
  
  enum Level {
    NONE	= 0,
    ERROR	= Bit(1),
    WARNING	= Bit(2),
    USR_1	= Bit(3),
    USR_2	= Bit(4),
    USR_3	= Bit(5),
    USR_4	= Bit(6),
    INFO    	= Bit(7),
    TEST       	= Bit(8),
    DEBUG	= Bit(9),
    FUNCT	= Bit(10),
    ALL		= 0xffff
  };

  LogLevel( Level out = NONE );
  LogLevel( const char * out );
  
  
  inline Level 	setOutput( Level out );
  Level		setOutput( const char * out );
  
  inline Level 	setCurrent( Level cur );
  Level		setCurrent( const char * cur );

  inline Level	getOutput( void ) const;
  inline Level	getCurrent( void  ) const;
  
  const char *	getName( Level level );
  const char * 	getLevelNames( Level level );
  
  void		setName( Level level, const char * name );

  Bool 		shouldOutput( void ) const;
  
private:

  static const char * LevelNames[];

  Level	    output;
  Level     current;
  
};


//
// Inline methods
//

inline
LogLevel::LogLevel( Level out )
{
  setCurrent( ERROR );
  setOutput( out );
}

inline
LogLevel::LogLevel( const char * out )
{
  setCurrent( ERROR );
  setOutput( out );
}

inline
LogLevel::Level
LogLevel::setOutput( LogLevel::Level out )
{
  Level	old = output;
  output = out;
  return( old );
}

inline
LogLevel::Level
LogLevel::setCurrent( LogLevel::Level cur )
{
  Level	old = current;
  current = cur;
  return( old );
}


inline
LogLevel::Level
LogLevel::getOutput( void ) const
{
  return( output );
}

inline
LogLevel::Level
LogLevel::getCurrent( void  ) const
{
  return( current );
}


inline Bool
LogLevel::shouldOutput( void ) const
{
  return( output & current );
}





#endif // ! def _LogLevel_hh_ 
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
