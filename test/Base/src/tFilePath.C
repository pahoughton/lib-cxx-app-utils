#include <LibTest.hh>
#include <FilePath.hh>

bool tFilePath01( LibTest & test );
bool tFilePath02( LibTest & test );
bool tFilePath03( LibTest & test );
bool tFilePath04( LibTest & test );

bool
tFilePath( LibTest & test )
{
  test( tFilePath01( test ), true );
  test( tFilePath02( test ), true );
  test( tFilePath03( test ), true );
  test( tFilePath04( test ), true );

  return( true );
}

    
