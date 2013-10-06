AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = bbstrassenfest

noinst_HEADERS = \
	configuration.h \
	manager/strassenfestmanager.h \
	model/strassenfest.h \
	model/strassenfestresult.h

ecppSources = \
	view/strassenfeste.ecpp \
	index.ecpp \
	webmain.ecpp

staticSources = \
	resources/bbstrassenfest.css

bbstrassenfest_SOURCES = \
	controller/strassenfeste.cpp \
	main.cpp \
	configuration.cpp \
	manager/strassenfestmanager.cpp \
	model/strassenfest.cpp \
	model/strassenfestresult.cpp \
	$(ecppSources)

nodist_bbstrassenfest_SOURCES = \
	resources.cpp

bbstrassenfest_LDFLAGS = -lcxxtools -ltntnet -lcxxtools-json

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) resources.cpp

EXTRA_DIST = $(staticSources)

#
# Rules for tntnet applications
#

# resources
resources.cpp: $(staticSources) Makefile.am
	$(ECPPC) -bb -z -n resources -p -o resources.cpp -I$(srcdir) $(staticSources)

SUFFIXES=.ecpp .ico .cpp

.ecpp.cpp:
	$(ECPPC) -I $(top_srcdir)/src -n $(basename $<) -o $@ $<
.ecpp.deps:
	$(ECPPC) -M -n $* -I $(srcdir) -I $(srcdir)/include $< | $(SED) '1s/\(.*\).cpp:/\1.cpp \1.deps:/' > $@
.ico.cpp:
	$(ECPPC) -b -m image/x-icon -o $@ $<

-include $(ecppSources:.ecpp=.deps)
