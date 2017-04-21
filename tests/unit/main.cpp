// 2017-04-19 (cc) <paul4hough@gmail.com>

extern bool v_bit(void);
extern bool v_compare01(void);
extern bool v_compare02(void);
extern bool v_StringCapitalize(void);
extern bool v_StringCaseCompare(void);
extern bool v_StringFirstNotOf(void);
extern bool v_StringFrom(void);
extern bool v_StringLower(void);
extern bool v_StringSearch(void);
extern bool v_StringTo(void);
extern bool v_StringToInt(void);
extern bool v_StringUpper(void);
extern bool v_StripTrailing(void);
extern bool v_StripWhite(void);

int main( int argc, char * argv[] ) {

  return ! ( v_bit()
	     && v_StringTo()
	     && v_StringCapitalize()
	     && v_StringCaseCompare()
	     && v_StringFirstNotOf()
	     && v_StringFrom()
	     && v_StringLower()
	     && v_StringSearch()
	     && v_StringUpper()
	     && v_StripTrailing()
	     && v_StripWhite()
	     && v_compare01()
	     && v_compare02()
	     );
}
