ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = ${top_srcdir}/README.md \
	     ${top_srcdir}/LICENSE

AM_CFLAGS = \
	-fstack-protector -Wall -pedantic \
	-Wstrict-prototypes -Wundef -fno-common \
	-Werror-implicit-function-declaration \
	-Wformat -Wformat-security -Werror=format-security \
	-Wno-conversion -Wunused-variable -Wunreachable-code \
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c99

AM_CPPFLAGS = \
	-I $(top_srcdir)/src

sbin_PROGRAMS = \
	lightdm-budgie-greeter

lightdm_budgie_greeter_SOURCES = \
	src/greeter-window.h	 \
	src/greeter-window.c	 \
	src/main.c		 \
	src/util.h

lightdm_budgie_greeter_CFLAGS = \
	$(GREETER_CFLAGS)	\
	$(AM_CFLAGS)

lightdm_budgie_greeter_LDADD = \
	$(GREETER_LIBS)
