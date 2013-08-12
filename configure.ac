dnl R interface to Lindo API

AC_INIT([rLindo], 8.0.1)

dnl variable LINDOAPI_HOME must be set
if test -z "$LINDOAPI_HOME" ; then
   AC_MSG_ERROR([Please set environment variable LINDOAPI_HOME to your LINDO API installation path])
fi

dnl test whether variable PKG_CPPFLAGS is set. If not, set it.
if test -z "$PKG_CPPFLAGS" ; then
   PKG_CPPFLAGS="-I${LINDOAPI_HOME}/include"
fi

dnl test whether variable PKG_LIBS is set. If not, set it.
if test -z "$PKG_LIBS" ; then
   if test -d ${LINDOAPI_HOME}/bin/linux64 ; then
      LIBPATH="${LINDOAPI_HOME}/bin/linux64"
      LDFLAGS="-Wl,-rpath-link,${LIBPATH} -Wl,-rpath,${LIBPATH}"
      PKG_LIBS="-L${LIBPATH} -llindo64 -lmosek64 -lconsub3 -lpthread ${LDFLAGS}"
   else
      LIBPATH="${LINDOAPI_HOME}/bin/linux32"
      LDFLAGS="-Wl,-rpath-link,${LIBPATH} -Wl,-rpath,${LIBPATH}"
      PKG_LIBS="-L${LIBPATH} -llindo -lmosek -lconsub3 -lpthread ${LDFLAGS}"
   fi
fi

: ${R_HOME=`R RHOME`}	  

if test -z "${R_HOME}" ; then
   echo "could not determine R_HOME"
   exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CPP=`"${R_HOME}/bin/R" CMD config CPP`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
AC_PROG_CC
AC_PROG_CPP

AC_SUBST(PKG_LIBS)
AC_SUBST(PKG_CPPFLAGS)
AC_OUTPUT(src/Makevars)

exit 0

