bin_PROGRAMS = pcp 
pcp_CXXFLAGS = $(AM_CXXFLAGS)
pcp_SOURCES = pcp_main.cc
pcp_LDADD = $(top_srcdir)/talk/login/libcricketlogin.la \
	     $(top_srcdir)/talk/session/phone/libcricketsessionphone.la \
             $(top_srcdir)/talk/session/fileshare/libcricketsessionfileshare.la \
             $(top_srcdir)/talk/session/tunnel/libcricketsessiontunnel.la \
             $(top_srcdir)/talk/p2p/client/libcricketp2pclient.la \
             $(top_srcdir)/talk/p2p/base/libcricketp2pbase.la \
             $(top_srcdir)/talk/xmpp/libcricketxmpp.la \
             $(top_srcdir)/talk/xmllite/libcricketxmllite.la \
             $(top_srcdir)/talk/base/libcricketbase.la \
             $(EXPAT_LIBS) -lpthread -lssl -lcrypto \
	     -lgtkmm-2.4 -lgdkmm-2.4 -latkmm-1.6 -lgtk-x11-2.0 -lpangomm-1.4 -lcairomm-1.0 -lglibmm-2.4 -lsigc-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lpango-1.0 -lcairo -lgobject-2.0 -lgmodule-2.0 -ldl -lglib-2.0

AM_CPPFLAGS = -DPOSIX `pkg-config --cflags gtkmm-2.4`
#EXTRA_DIST = pcp.vcproj
