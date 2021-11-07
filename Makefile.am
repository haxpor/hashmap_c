ACLOCAL_AMFLAGS = -I m4
# for no I/O redirections, so we can printf
# uncomment: the following line to run test without I/O redirections, mostly
# in case of needing to see some printed-out text
AUTOMAKE_OPTIONS = serial-tests

lib_LTLIBRARIES = libhashmap_c.la
libhashmap_c_la_CFLAGS = @MAIN_PROGRAM_CFLAGS@
libhashmap_c_la_LDFLAGS = @MAIN_PROGRAM_LDFLAGS@ -version-info 1:0:0
libhashmap_c_la_SOURCES = src/hashmap_c.c \
						  externals/MurmurHash3/src/MurmurHash3.c

libhashmap_c_ladir=$(includedir)/hashmap_c
libhashmap_c_la_HEADERS = include/hashmap_c/hashmap_c.h

noinst_HEADERS = externals/MurmurHash3/include/MurmurHash3/MurmurHash3.h

check_PROGRAMS = test/tests
TESTS = $(check_PROGRAMS)
test_tests_SOURCES = test/test.c
test_tests_CFLAGS = @TEST_PROGRAM_CFLAGS@
test_tests_LDFLAGS = -lm \
					 -lhashmap_c

EXTRA_DIST = README.md LICENSE autogen.sh
