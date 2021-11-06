AC_PREREQ([2.69])
AC_INIT([hashmap_c], [0.1], [haxpor@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AM_PROG_AR

AC_ENABLE_SHARED
AC_ENABLE_STATIC

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset pow])

AC_CONFIG_FILES([Makefile])

# enable build for both debug and release output shared library
BUILD_RELEASE="true"
AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug], [configure a debug build])],
	[
	 BUILD_RELEASE="false"
	 AC_MSG_NOTICE("Configured for debug build")
	])
AC_ARG_ENABLE([release], [AS_HELP_STRING([--enable-release], [configure a release build [default=yes]])],
	[
	 BUILD_RELEASE="true"
	 AC_MSG_NOTICE("Configured for release build")
	])

if test x$BUILD_RELEASE = xtrue; then
	MAIN_PROGRAM_CFLAGS="-std=c99 -O2 -pedantic -Wall -Wextra -I./include -I./externals/MurmurHash3/include"
	MAIN_PROGRAM_LDFLAGS="-no-undefined -version-info 0:1:0"
	TEST_PROGRAM_CFLAGS="-std=c99 -O2 -pedantic -Wall -Wextra -I./include -I./externals/MurmurHash3/include"
else
	MAIN_PROGRAM_CFLAGS="-std=c99 -g -O2 -pedantic -Wall -Wextra -I./include -I./externals/MurmurHash3/include"
	MAIN_PROGRAM_LDFLAGS="-no-undefined -version-info 0:1:0"
	TEST_PROGRAM_CFLAGS="-std=c99 -g -O2 -pedantic -Wall -Wextra -I./include -I./externals/MurmurHash3/include"
fi

# expose the variable setting here to automake
AC_SUBST(MAIN_PROGRAM_CFLAGS)
AC_SUBST(MAIN_PROGRAM_LDFLAGS)
AC_SUBST(TEST_PROGRAM_CFLAGS)

AC_OUTPUT
