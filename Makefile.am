
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
	debian/libgea3-dev.dirs \
	debian/libgea3-dev.install \
	debian/libgea3.dirs \
	debian/libgea3.install \
	debian/README debian/rules \
	libgea3.spec libgea3.spec.in

libgea3.spec: version.m4 libgea3.spec.in
	m4 $^ > $@


