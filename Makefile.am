
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gea.pc

SUBDIRS = src include test


# we distribute the stuff for building Debian packages with the source. 
EXTRA_DIST = \
	debian/changelog \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/dirs \
	debian/docs \
	debian/libgea2-dev.dirs \
	debian/libgea2-dev.install \
	debian/libgea2.dirs \
	debian/libgea2.install \
	debian/README debian/rules \
	libgea2.spec libgea2.spec.in

libgea2.spec: version.m4 libgea2.spec.in
	m4 $^ > $@


