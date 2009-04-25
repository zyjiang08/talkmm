bin_PROGRAMS = talkmm
talkmm_CXXFLAGS = $(AM_CXXFLAGS)
talkmm_SOURCES = main.cc talkmm.cc callclient.cc console.cc chatclient.cc fileclient.cc \
		 MainWindow.cpp \
		 TrayIcon.cpp 
noinst_HEADERS = talkmm.h callclient.h  console.h chatclient.h xxpclient.h fileclient.h \
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
	       $(EXPAT_LIBS) $(ORTP_LIBS) -lpthread -lssl -lcrypto  $(ILBC_LIBS) $(SPEEX_LIBS) $(GLIB_LIBS) $(MEDIA_LIBS) $(MEDIASTREAMER_LIBS) \
	     -lgtkmm-2.4 -lgdkmm-2.4 -latkmm-1.6 -lgtk-x11-2.0 -lpangomm-1.4 -lcairomm-1.0 -lglibmm-2.4 -lsigc-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lpango-1.0 -lcairo -lgobject-2.0 -lgmodule-2.0 -ldl -lglib-2.0
#AM_CPPFLAGS  = -DPOSIX
AM_CPPFLAGS = -DPOSIX `pkg-config --cflags gtkmm-2.4`
