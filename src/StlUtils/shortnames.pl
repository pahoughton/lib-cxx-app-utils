#!/usr/local/bin/perl

%shortNames =
    ("ClueVersion",		    "cluever",
     "DateRange",		    "daterg",
     "DateRangeDaily",		    "datergdl",
     "DateRangeWeekly",		    "datergwk",
     "DateTimeUtils",		    "dttmutil",
     "RegexScan",		    "rxscan",
     "StrStreambuf",		    "strsbuf",
     "StringCapitalize",	    "strcap",
     "StringCaseCompare",	    "strcscmp",
     "StringCaseReverseSearch",	    "stcsrvsr",
     "StringCaseSearch",	    "stcssr",
     "StringLower",		    "strlwr",
     "StringReverseSearch",	    "strrvsr",
     "StringSearch",		    "strsr",
     "StringUpper",		    "strupr",
     "StringUtils",		    "strutil" );

chdir( "../arch/ShortFn/src" );

for( $a = 0; $a < $#ARGV; $a++ )
{
    ($name,$ext) = split( /\./, $ARGV[$a] );
    
    $outExt = $ext;

    if( $outExt eq "C" )
    {
        $outExt = "cpp";
    }

    if( $shortNames{ $name } )
    {
	system( "ln -s ../../../src/$name.$ext $shortNames{$name}.$outExt" );
    }
    else
    {
        $sname = $name;
        $sname =~ y/[A-Z]/[a-z]/;
	system( "ln -s ../../../src/$name.$ext $sname.$outExt" );
    }
}

chdir( "../src" );
    
	       
