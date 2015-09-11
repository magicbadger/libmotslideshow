lib_LIBRARIES = libmotslideshow.a

libmotslideshow_a_SOURCES = slideshow.cpp slideshow.h
libmotslideshow_a_CPPFLAGS = -I${libmot_CFLAGS} -I${libmsc_CFLAGS}
libmotslideshow_a_LIBADD = -lmot 

bin_PROGRAMS = slideshow_encoder 

slideshow_encoder_SOURCES = slideshow_encoder.cpp slideshow_encoder.h
slideshow_encoder_CPPFLAGS = -I${libmot_CFLAGS} -I${libmsc_CFLAGS} -I../src
slideshow_encoder_LDADD = -L${libmot_LIBS} -lmot -L${libmsc_LIBS} -lmsc -L${libcurl_LIBS} -lcurl -L../src -lmotslideshow
