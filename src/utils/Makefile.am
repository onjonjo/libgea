CPPFLAGS += -I../../include

bin_PROGRAMS = gea3_start

# lib_LTLIBRARIES = libgea2-utils.la

gea3_start_SOURCES = gea_start.cc
gea3_start_LDADD = ../libgea3.la ../libgea3-posix.la -ldl

#libgea2_utils_la_SOURCES = \
#	SingleShootEvent.cc \
#	MultiShootEvent.cc \
#	MultiShootTimerEvent.cc

#libgea2_utils_la_LDFLAGS= -version-info @MAJOR_VER@:@MINOR_VER@:0
#libgea2_utils_la_LIBADD=../libgea3.la
