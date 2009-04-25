EXTRA_DIST=call.vcproj
bin_PROGRAMS = xxpalk
xxpalk_CXXFLAGS = $(AM_CXXFLAGS)
xxpalk_SOURCES = xxpalk_main.cc callclient.cc console.cc chatclient.cc fileclient.cc
noinst_HEADERS = callclient.h  console.h chatclient.h xxpclient.h fileclient.h
xxpalk_LDADD =  \
	       $(top_srcdir)/talk/login/libcricketlogin.la \
	       $(top_srcdir)/talk/session/phone/libcricketsessionphone.la \
	       $(top_srcdir)/talk/session/fileshare/libcricketsessionfileshare.la \
	       $(top_srcdir)/talk/session/tunnel/libcricketsessiontunnel.la \
	       $(top_srcdir)/talk/p2p/client/libcricketp2pclient.la \
	       $(top_srcdir)/talk/p2p/base/libcricketp2pbase.la \
	       $(top_srcdir)/talk/xmpp/libcricketxmpp.la \
	       $(top_srcdir)/talk/xmllite/libcricketxmllite.la \
	       $(top_srcdir)/talk/base/libcricketbase.la \
	       $(EXPAT_LIBS) $(ORTP_LIBS) -lpthread -lssl -lcrypto  $(ILBC_LIBS) $(SPEEX_LIBS) $(GLIB_LIBS) $(MEDIA_LIBS) $(MEDIASTREAMER_LIBS)
AM_CPPFLAGS  = -DPOSIX