ACLOCAL_AMFLAGS = -I config 

SUBDIRS	= doc 

pkgconfig_DATA = src/libmotslideshow.pc

AM_CPPFLAGS = \
    -I$(top_builddir)/include \
    -I$(top_srcdir)/include

#
# Library 
#
lib_LTLIBRARIES = src/libmotslideshow.la

include_HEADERS = \
    include/mot/slideshow.h 

src_libmotslideshow_la_SOURCES = \
    src/slideshow.cpp

src_libmotslideshow_la_CPPFLAGS = 
src_libmotslideshow_la_CXXFLAGS = @LIBMOTSLIDESHOW_EXTRA_CXXFLAGS@
src_libmotslideshow_la_LIBADD =

#
# Tests
#
test_apps = 

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

#
# Utilities (mostly for testing)
#
util_apps = 

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
