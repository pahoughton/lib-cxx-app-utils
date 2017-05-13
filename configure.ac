dnl configure.ac - 2017-04-19
dnl
dnl (cc) <paul4hough@gmail.com>

AC_PREREQ(2.69)
AC_INIT( [libclue],[1.01.01],[Paul Houghton <paul4hough@gmail.com>])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
LT_INIT

AC_PROG_CXX
AC_LANG([C++])
dnl AC_CONFIG_HEADERS([config.h])
AC_CHECK_HEADERS(valid/verify.hpp,[],[echo ERROR valid.hpp required; exit 1;])
AC_CHECK_HEADERS([iostream])

AC_CONFIG_FILES([Makefile src/clue/Makefile tests/unit/Makefile])
AC_OUTPUT
