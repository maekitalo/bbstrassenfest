AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = bbstrassenfest

noinst_HEADERS = \
	configuration.h \
	manager/strassenfestmanager.h \
	model/strassenfest.h \
	model/strassenfestresult.h

ecppSources = \
	view/strassenfeste.ecpp \
	view/suche.ecpp \
	index.ecpp \
	webmain.ecpp

staticSources = \
	resources/bbstrassenfest.css \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/animated-overlay.gif \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_diagonals-thick_18_b81900_40x40.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_diagonals-thick_20_666666_40x40.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_flat_10_000000_40x100.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_glass_100_f6f6f6_1x400.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_glass_100_fdf5ce_1x400.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_glass_65_ffffff_1x400.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_gloss-wave_35_f6a828_500x100.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_highlight-soft_100_eeeeee_1x100.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-bg_highlight-soft_75_ffe45c_1x100.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-icons_222222_256x240.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-icons_228ef1_256x240.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-icons_ef8c08_256x240.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-icons_ffd27a_256x240.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/images/ui-icons_ffffff_256x240.png \
	resources/jquery-ui-1.10.3.custom/css/ui-lightness/jquery-ui-1.10.3.custom.min.css \
	resources/jquery-ui-1.10.3.custom/js/jquery-1.9.1.js \
	resources/jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.min.js

bbstrassenfest_SOURCES = \
	controller/strassenfeste.cpp \
	controller/suche.cpp \
	main.cpp \
	configuration.cpp \
	manager/strassenfestmanager.cpp \
	model/strassenfest.cpp \
	model/strassenfestresult.cpp \
	$(ecppSources)

nodist_bbstrassenfest_SOURCES = \
	resources.cpp

bbstrassenfest_CXXFLAGS = -I$(srcdir)/model -I$(srcdir)/manager
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
