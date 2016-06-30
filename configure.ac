AC_INIT([lightdm-budgie-greeter], 1, [ikey@solus-project.com], [lightdm-budgie-greeter], [https://github.com/solus-project/lightdm-budgie-greeter])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])
AC_PROG_CC
AC_PROG_CC_STDC
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Unit tests
m4_define([glib_required_version], [2.42.0])
m4_define([gtk_required_version], [3.16.0])
m4_define([gdesktop_required_version], [3.16.0])
m4_define([budgie_required_version], [1])

PKG_CHECK_MODULES([GREETER], [
        glib-2.0 >= glib_required_version
        gtk+-3.0 >= gtk_required_version
        gnome-desktop-3.0
        budgie-theme-1.0 >= budgie_required_version
])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        lightdm-budgie-greeter $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
