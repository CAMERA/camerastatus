
AC_INIT([camerastatus], [0.9], [support@crbs.ucsd.edu],
             [camerastatus], [http://www.camera.calit2.net/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.09 -Wall no-define])

# needed to check for curses library with AX_WITH_CURSES call below
# obtained from 
# http://www.gnu.org/software/autoconf-archive/ax_with_curses.html
m4_include([m4/curses.m4])
AC_PROG_CXX
AC_LANG(C++)
AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADERS([time.h])

#check for curses library
AX_WITH_CURSES
if test "x$ax_cv_ncursesw" != xyes && test "x$ax_cv_ncurses" != xyes; then
   AC_MSG_ERROR([requires either NcursesW or Ncurses library])
fi

#need curl 7.15.5 or better
PKG_CHECK_MODULES([CURL],[libcurl >= 7.15.5],
AC_DEFINE([HAVE_CURL],[1],[Define to 1 if libcurl 7.15.5 or better is installed]),
AC_MSG_ERROR([libcurl 7.15.5 or higher must be installed to build]))


PKG_CHECK_MODULES([CPPUNIT],[cppunit],AC_DEFINE(HAVE_CPPUNIT,[1],[Define to 1 if cppunit is installed]),
AC_MSG_WARN([No cppunit installed according to pkg-config. Unit tests will NOT be compiled.  Perhaps the cppunit.pc is installed in an odd location]))

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
