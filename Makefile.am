

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gea.pc

SUBDIRS = src include 


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
	debian/libgea2.postinst.debhelper \
	debian/libgea2.postrm.debhelper \
	debian/libgea2.substvars \
	debian/README debian/rules \
	libgea.spec libgea.spec.in

libgea.spec: version.m4 libgea.spec.in
	m4 $^ > $@


