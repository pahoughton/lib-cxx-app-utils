#!/usr/local/bin/perl

%shortNames =
    ("ClueVersion",		    "cluever",
     "ClassVersion",		    "classver",
     "BinStream",		    "binstrm",
     "NetStream",		    "netstrm",
     "RandomBinStream",		    "rbinstrm",
     "HeapBinStream",		    "hbinstrm",
     "StringUtils",		    "strutil",
     "StripWhite",		    "strpwht",
     "StringCaseCompare",	    "strcscmp",
     "StringLower",		    "strlwr",
     "StringUpper",		    "strupr",
     "StringCapitalize",	    "strcap",
     "StringSearch",		    "strsr",
     "StringReverseSearch",	    "strrvsr",
     "StringCaseSearch",	    "stcssr",
     "StringCaseReverseSearch",	    "stcsrvsr",
     "StrStreambuf",		    "strsbuf",
     "RegexScan",		    "rxscan",
     "DateTimeUtils",		    "dttmutil",
     "DateRange",		    "daterg",
     "DateRangeDaily",		    "datergdl",
     "DateRangeWeekly",		    "datergwk",
     "Directory",		    "director",
     "SortOrder",                   "sortordr" );

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
    
	       
