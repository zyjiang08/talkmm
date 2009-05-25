bin_PROGRAMS = talkmm
talkmm_CXXFLAGS = $(AM_CXXFLAGS)
talkmm_SOURCES = talkmm.cc \
		 main.cc \
		 callclient.cc \
		 console.cc \
		 chatclient.cc \
		 fileclient.cc \
		 MainWindow.cc \
		 MsgWindow.cc \
		 BuddyView.cc \
		 TreeModelDnd.cc \
		 TreeViewTooltips.cc \
		 TrayIcon.cc \
		 TagList.cc \
		 MsgBox.cc \
		 Unit.cc \
		 pixmaps.cc \
		 ./config/rwxml.cc  ./config/tinystr.cc  ./config/tinyxml.cc  \
		 ./config/tinyxmlerror.cc  ./config/tinyxmlparser.cc
noinst_HEADERS = talkmm.h \
		 callclient.h \
		 console.h \
		 chatclient.h  \
		 fileclient.h \
		 MVC.h \
		 define.h \
		 MainWindow.h \
		 MsgWindow.h  \
		 BuddyView.h \
		 TreeModelDnd.h \
		 TreeViewTooltips.h \
		 TrayIcon.h \
		 SmileTree.h \
		 TagList.h \
		 MsgBox.h \
		 Unit.h \
		 TreeItem.h \
		 pixmaps.h \
		 ./config/rwxml.h  ./config/tinystr.h  ./config/tinyxml.h
talkmm_LDADD =  \
	       talk/login/libcricketlogin.la \
	       talk/session/phone/libcricketsessionphone.la \
	       talk/session/fileshare/libcricketsessionfileshare.la \
	       talk/session/tunnel/libcricketsessiontunnel.la \
	       talk/p2p/client/libcricketp2pclient.la \
	       talk/p2p/base/libcricketp2pbase.la \
	       talk/xmpp/libcricketxmpp.la \
	       talk/xmllite/libcricketxmllite.la \
	       talk/base/libcricketbase.la \
	       $(EXPAT_LIBS) $(ORTP_LIBS) -lpthread -lssl -lcrypto \
		$(ILBC_LIBS) $(SPEEX_LIBS) $(GLIB_LIBS) $(MEDIA_LIBS) $(MEDIASTREAMER_LIBS)
talkmm_LDFLAGS =`pkg-config --libs gtkmm-2.4 libglademm-2.4 gthread-2.0 libsexymm`
AM_CPPFLAGS = -DPOSIX `pkg-config --cflags gtkmm-2.4 libglademm-2.4 gthread-2.0 libsexymm`
