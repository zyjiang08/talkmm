bin_PROGRAMS = talkmm
talkmm_CXXFLAGS = $(AM_CXXFLAGS)
talkmm_SOURCES = talkmm.cc main.cc callclient.cc console.cc chatclient.cc fileclient.cc \
		 MainWindow.cc \
		 TrayIcon.cc 
noinst_HEADERS = talkmm.h callclient.h  console.h chatclient.h  fileclient.h \
		 MVC.h \
		 MainWindow.h \
		 TrayIcon.h
talkmm_LDADD =  \
	       $(top_srcdir)/talk/login/libcricketlogin.la \
	       $(top_srcdir)/talk/session/phone/libcricketsessionphone.la \
	       $(top_srcdir)/talk/session/fileshare/libcricketsessionfileshare.la \
	       $(top_srcdir)/talk/session/tunnel/libcricketsessiontunnel.la \
	       $(top_srcdir)/talk/p2p/client/libcricketp2pclient.la \
	       $(top_srcdir)/talk/p2p/base/libcricketp2pbase.la \
	       $(top_srcdir)/talk/xmpp/libcricketxmpp.la \
	       $(top_srcdir)/talk/xmllite/libcricketxmllite.la \
	       $(top_srcdir)/talk/base/libcricketbase.la \
	       $(EXPAT_LIBS) $(ORTP_LIBS) -lpthread -lssl -lcrypto \
		$(ILBC_LIBS) $(SPEEX_LIBS) $(GLIB_LIBS) $(MEDIA_LIBS) $(MEDIASTREAMER_LIBS)
talkmm_LDFLAGS =`pkg-config --libs gtkmm-2.4 libglademm-2.4 gthread-2.0`
AM_CPPFLAGS = -DPOSIX `pkg-config --cflags gtkmm-2.4 libglademm-2.4 gthread-2.0`
#AM_CPPFLAGS = -DPOSIX `pkg-config --cflags glibmm-2.4 gtkmm-2.4 libglademm-2.4`
