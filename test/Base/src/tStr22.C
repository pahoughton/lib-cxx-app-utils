#include <LibTest.hh>
#include <Str.hh>

#include <fstream>

#define T1 "first part"
#define T2 "second part"
#define T3 "third part"
#define T4 "forth part"
#define T5 "fifth part"

bool
tStr22( LibTest & test )
{
  {
    // good( void ) const
    // error( void ) const
    // getClassName( void  ) const
    // version
    
    const Str t( "simple test string" );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );
    test( t.version != 0 );
  }

  {
    // toStream( ostream & ) const
    
    ofstream out( "data/Str.operator.output" );

    const Str t("This is an output test from Str\n" );
    t.toStream( out );
    out.close();
    test.file( "data/Str.operator.output" );
  }

  {
    // dumpInfo( ostream & ) const
    
    ofstream out( "data/Str.operator.output" );

    const Str t("This is an output test from Str\n" );
    t.dumpInfo( out );    
    out.close();
  }
  
  {
    // operator << ( ostream &, const Str & )
    
    ofstream out( "data/Str.operator.output" );

    Str t("This is an output test from Str\n" );
    out << t;
    out.close();
    test.file( "data/Str.operator.output" );
  }

  {
    // operator >> ( istream &, Str & )
    
    ifstream in( "data/Str.operator.input" );

    Str t;

    in >> t;
    test( t == "input" );
    in >> t;
    test( t == "string" );
  }

  {
    // getline( istream & )
    
    ifstream in( "data/Str.getline.input" );

    Str t;

    test( t.getline( in ).good() );
    test( t == "first input line" );
    test( t.getline( in ).good() );
    test( t == "last input line" );
    test( ! t.getline( in ).good() );
    test( t == "last input line" );
  }

  {
    // getDelim( istream &, const char * )

    Str	t;

    ifstream in( "data/Str.getDelim.input" );
    
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "this" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "is" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "a" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "delimited" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t.empty() );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "line" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "next" );
    test( t.getDelim( in, " \t\n" ).good() );
    test( t == "line" );
    test( ! t.getDelim( in, " \t\n" ).good() );
  }
      
  {
    // getDelim( istream &, const char *, bool )

    Str t;
    
    ifstream in( "data/Str.getDelim.input" );

    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "this " );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "is\t" );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "a " );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "delimited\t" );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == " " );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "line\n" );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "next " );
    test( t.getDelim( in, " \t\n", false ).good() );
    test( t == "line\n" );
    test( ! t.getDelim( in, " \t\n", false ).good() );
  }

  {
    // getDelim( istream &, char )
    Str t;
    
    ifstream in( "data/Str.getDelim.char.input" );

    test( t.getDelim( in, " " ).good() );
    test( t == "test" );
    test( t.getDelim( in, " " ).good() );
    test( t == "char" );
    test( ! t.getDelim( in, " " ).good() );
    test( t == "delim\n" );
    test( ! t.getDelim( in, " " ).good() );
  }
  
  {
    // getDelim( istream &, char, bool )
    Str t;
    
    ifstream in( "data/Str.getDelim.char.input" );

    test( t.getDelim( in, " ", false ).good() );
    test( t == "test " );
    test( t.getDelim( in, " ", false ).good() );
    test( t == "char " );
    test( ! t.getDelim( in, " ", false ).good() );
    test( t == "delim\n" );
    test( ! t.getDelim( in, " ", false ).good() );
  }

  {
    // getStreamSize( void ) const

    Str t;

    const char * T = "the string to test";

    t = T;
    test( t.getStreamSize() == strlen( T ) + sizeof( size_t ) );
  }

  {
    // write( ostream & )

    ofstream out( "data/Str.bin.data" );

    Str t;

    t = T1;
    test( t.write( out ).good() );
    t = T2;
    test( t.write( out ).good() );
    t = T3;
    test( t.write( out ).good() );
    t = T4;
    test( t.write( out ).good() );
    t = T5;
    test( t.write( out ).good() );
  }

  {
    // read( istream & )

    ifstream in( "data/Str.bin.data" );

    Str t;

    test( t.read( in ).good() );
    test( t == T1 );
    test( t.read( in ).good() );
    test( t == T2 );
    test( t.read( in ).good() );
    test( t == T3 );
    test( t.read( in ).good() );
    test( t == T4 );
    test( t.read( in ).good() );
    test( t == T5 );
  }

  return( true );
}

   
      
      

      
    
