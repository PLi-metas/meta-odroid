SUMMARY = "Amlogic audio decoders library"
PACKAGE_ARCH = "${MACHINE_ARCH}"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "odroid-libamavutils-${MACHINE} alsa-lib rtmpdump"
RDEPENDS_${PN} = "ffmpeg"

### for DTS encoder: don't check for stripped & text relocations

inherit lib_package pkgconfig

EXTRA_OEMAKE = "\
    'CC=${CC}' \
    'CFLAGS=-O2 -fPIC -pthread -DALSA_OUT -DENABLE_WAIT_FORMAT -I${S}/include -I${S}' \
    'LDFLAGS=-shared -lamavutils -lpthread -lm -lasound -lrt -ldl' \
"

### NOTE: we are installing closed src DTS encoder as well for transcoding
do_install() {
    install -d ${D}${libdir}/pkgconfig
    install -d ${D}${includedir}/amlogic/amadec
    install -d ${D}${nonarch_base_libdir}/firmware
    install -d ${D}${libdir}
    install -m 0755 ${S}/include/* ${D}${includedir}/amlogic/amadec
    install -m 0755 ${S}/libamadec.so ${D}${libdir}
    install -m 0755 ${S}/acodec_lib/*.so  ${D}${libdir}
    install -m 0644 ${WORKDIR}/libamadec.pc ${D}${libdir}/pkgconfig/
}

FILES_${PN} = "${libdir}/* ${nonarch_base_libdir}/firmware"
FILES_${PN}-dev = "${includedir}/*"

do_package_qa() {
}
