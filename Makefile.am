ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = ${top_srcdir}/README.md				\
	     ${top_srcdir}/LICENSE				\
	     ${top_srcdir}/data/budgie-greeter.gresource.xml 	\
	     ${top_srcdir}/data/styling.css

AM_CFLAGS = \
	-fstack-protector -Wall -pedantic \
	-Wstrict-prototypes -Wundef -fno-common \
	-Werror-implicit-function-declaration \
	-Wformat -Wformat-security -Werror=format-security \
	-Wno-conversion -Wunused-variable -Wunreachable-code \
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c99

AM_CPPFLAGS = \
	-I $(top_srcdir)/src

greeter_resources = $(shell glib-compile-resources --sourcedir=$(top_srcdir)/data --generate-dependencies $(top_srcdir)/data/budgie-greeter.gresource.xml)

BUILT_SOURCES = \
	budgie-greeter-resources.h \
	budgie-greeter-resources.c

CLEANFILES = \
	$(BUILT_SOURCES)

# resources
budgie-greeter-resources.h: $(top_srcdir)/data/budgie-greeter.gresource.xml $(greeter_resources)
	glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-header --c-name budgie_greeter $<

budgie-greeter-resources.c: $(top_srcdir)/data/budgie-greeter.gresource.xml $(greeter_resources)
	glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-source --c-name budgie_greeter $<

sbin_PROGRAMS = \
	lightdm-budgie-greeter

lightdm_budgie_greeter_SOURCES = 	\
	src/greeter-window.h	 	\
	src/greeter-window.c	 	\
	src/main.c		 	\
	src/util.h		 	\
	budgie-greeter-resources.h	\
	budgie-greeter-resources.c

lightdm_budgie_greeter_CFLAGS = \
	$(GREETER_CFLAGS)	\
	$(AM_CFLAGS)

lightdm_budgie_greeter_LDADD = \
	$(GREETER_LIBS)
