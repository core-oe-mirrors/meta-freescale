# Copyright 2017-2024 NXP

SUMMARY = "OPTEE Client libs"
HOMEPAGE = "http://www.optee.org/"
LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=69663ab153298557a59c67a60a743e5b"

SRC_URI = "file://tee-supplicant.service"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

inherit python3native systemd features_check pkgconfig

DEPENDS = "util-linux-libuuid"

REQUIRED_MACHINE_FEATURES = "optee"

SYSTEMD_SERVICE:${PN} = "tee-supplicant.service"

EXTRA_OEMAKE = " \
	-C ${S} O=${B} \
"

do_install () {
	oe_runmake -C ${S} install

	install -D -p -m0644 ${B}/export/usr/lib/libteec.so.2.0.0 ${D}${libdir}/libteec.so.2.0.0
	ln -sf libteec.so.2.0.0 ${D}${libdir}/libteec.so.2
	ln -sf libteec.so.2.0.0 ${D}${libdir}/libteec.so

	install -D -p -m0644 ${B}/export/usr/lib/libckteec.so.0.1.0 ${D}${libdir}/libckteec.so.0.1.0
	ln -sf libckteec.so.0.1.0 ${D}${libdir}/libckteec.so.0
	ln -sf libckteec.so.0.1.0 ${D}${libdir}/libckteec.so

	install -D -p -m0755 ${B}/export/usr/sbin/tee-supplicant ${D}${bindir}/tee-supplicant

	cp -a ${B}/export/usr/include ${D}${includedir}

	sed -i -e s:/etc:${sysconfdir}:g -e s:/usr/bin:${bindir}:g ${WORKDIR}/tee-supplicant.service
	install -D -p -m0644 ${WORKDIR}/tee-supplicant.service ${D}${systemd_system_unitdir}/tee-supplicant.service
}
