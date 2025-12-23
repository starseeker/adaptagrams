AC_INIT([libcola],[0.1])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(libcola/cola.h)
AC_CONFIG_HEADERS([libcola/config.h])
AM_INIT_AUTOMAKE
# able to choose or disable these two at configure time:
AC_ENABLE_STATIC
AC_ENABLE_SHARED
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
LT_INIT
AC_PROG_INSTALL
#AC_DEFINE(TRACE_LOGGING)
dnl ******************************
dnl   Compilation warnings
dnl ******************************
if test "$GXX" = "yes"; then
  # Use C++11 Extensions
  CXXFLAGS="-std=gnu++11 $CXXFLAGS"
  dnl Alternatively (https://askubuntu.com/a/773293),
  dnl CXXFLAGS="-std=c++11 $CXXFLAGS"
  case "$host_os" in
    darwin*)
      dnl See https://stackoverflow.com/a/14657009
      CXXFLAGS="-stdlib=libc++ $CXXFLAGS"
      ;;
  esac

  # Enable some warnings from g++.
  CXXFLAGS="-Wall -W -Wpointer-arith -Wcast-align -Wsign-compare -Woverloaded-virtual -Wswitch  $CXXFLAGS"

  dnl Test for arch-specific situations.
  case "$host_cpu" in
    mips|mipsel)
      dnl Symbol tables can get too large: this uses alternate tables
      dnl See http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=283476
      CXXFLAGS="$CXXFLAGS -Wa,-xgot"
      CFLAGS="$CFLAGS -Wa,-xgot"
      ;;
  esac
fi

# If we are on a Windows OS using MinGW, extend the linker flags by '-no-undefined'
# to avoid linker warnings
if test "x$host_os" = "xmingw32"; then
  AM_LDFLAGS="$AM_LDFLAGS -no-undefined"
fi
# Distribute the changed linker flags among the Makefiles
AC_SUBST(AM_LDFLAGS)

# Cairo is no longer required - SVG output is now self-contained

AH_BOTTOM([ 
  
])

AC_CONFIG_FILES([Makefile libcola/Makefile libcola/tests/Makefile libvpsc/Makefile libvpsc/tests/Makefile libtopology/Makefile libtopology/tests/Makefile libavoid/Makefile libavoid/tests/Makefile libdialect/Makefile libdialect/tests/Makefile libcola/libcola.pc libavoid/libavoid.pc libvpsc/libvpsc.pc libtopology/libtopology.pc libdialect/libdialect.pc])
AC_OUTPUT
