ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libhashmap_c.la
libhashmap_c_la_CFLAGS = -Wall \
												 -std=c99 \
												 -O2 \
												 -pedantic \
												 -I./include \
												 -I./externals/MurmurHash3/include
libhashmap_c_la_LDFLAGS = -no-undefined -version-info 0:1:0
libhashmap_c_la_SOURCES = src/hashmap_c.c \
													externals/MurmurHash3/src/MurmurHash3.c

libhashmap_c_ladir=$(includedir)/hashmap_c
libhashmap_c_la_HEADERS = include/hashmap_c/hashmap_c.h

noinst_HEADERS = externals/MurmurHash3/include/MurmurHash3/MurmurHash3.h

check_PROGRAMS = test/tests
TESTS = $(check_PROGRAMS)
test_tests_SOURCES = test/test.c
test_tests_CFLAGS = -Wall \
										-std=c99 \
										-O2 \
										-I./include -I./externals/MurmurHash3/include
test_tests_LDFLAGS = -lm \
										 -lhashmap_c

EXTRA_DIST = README.md LICENSE autogen.sh
