CPPFLAGS += "-I../include"

lib_LTLIBRARIES =  libgea3.la libgea3-posix.la

libgea3_la_SOURCES = \
	EventHandler.cc \
	gea.cc \
	Blocker.cc \
	Handle.cc \
	UdpHandle.cc \
	DependHandle.cc \
	ObjRepository.cc

#libgea_la_CXXFLAGS = -fvisibility=hidden

libgea3_posix_la_SOURCES = \
	Time.cc \
	UnixFdHandle.cc \
	ShadowBlocker.cc \
	ShadowHandle.cc \
	ShadowEventHandler.cc \
	ShadowUdpHandle.cc \
	ShadowDependHandle.cc \
	NodeColor.cc \
	guess_iface.cc \
	compat.cc \
	AnimLink.cc

libgea3_posix_la_CPPFLAGS = -DGEA_POSIX

libgea3_posix_la_LDFLAGS = @NETWORK_LIBS@ -version-info @MAJOR_VER@:@MINOR_VER@:0
libgea3_posix_la_LIBADD = libgea3.la

libgea3_la_LDFLAGS = -version-info @MAJOR_VER@:@MINOR_VER@:0

SUBDIRS = . utils
