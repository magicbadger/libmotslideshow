bin_PROGRAMS = encode_image 

encode_image_SOURCES = encode_image.cpp
encode_image_CPPFLAGS = -I${libmot_CFLAGS} -I${libmsc_CFLAGS}
encode_image_LDADD = -L../src -L${libmot_LIBS} -lmot -L${libmsc_LIBS} -lmsc -L${libcurl_LIBS} -lcurl
