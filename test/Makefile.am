CPPFLAGS += -I../include


GEA_STUB = gea_stub.cc

AM_LDFLAGS = -all-static
GEA_LIBS = ../src/libgea2.la ../src/libgea2-posix.la

check_PROGRAMS = periodic blink unixfd broadcast HidSt2 objrepos objrepos2 \
	dependency HidSt HidSt2 

time2array_SOURCES = time2array.cc $(GEA_STUB)

periodic_SOURCES = periodic.cc $(GEA_STUB)
periodic_LDADD  = $(GEA_LIBS)


blink_SOURCES = blink.cc $(GEA_STUB)
blink_LDADD  = $(GEA_LIBS)

dependency_SOURCES = dependency.cc $(GEA_STUB)
dependency_LDADD  = $(GEA_LIBS)

unixfd_SOURCES = unixfd.cc $(GEA_STUB)
unixfd_LDADD  = $(GEA_LIBS)

broadcast_SOURCES = broadcast.cc $(GEA_STUB)
broadcast_LDADD  = $(GEA_LIBS)

HidSt_SOURCES = HidSt.cc $(GEA_STUB)
HidSt_LDADD  = $(GEA_LIBS)

HidStRecv_SOURCES = HidStRecv.cc $(GEA_STUB)
HidStRecv_LDADD  = $(GEA_LIBS)

HidSt2_SOURCES = HidSt2.cc $(GEA_STUB)
HidSt2_LDADD  = $(GEA_LIBS)

objrepos_SOURCES = objrepos.cc $(GEA_STUB)
objrepos_LDADD  = $(GEA_LIBS)

objrepos2_SOURCES = objrepos2.cc $(GEA_STUB)
objrepos2_LDADD  = $(GEA_LIBS)


