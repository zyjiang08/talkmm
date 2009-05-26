SUBDIRS= images
talkmm_ui = \
	     main_window.glade \
	     msg_window.glade \
	     talkmm_logo_1.png \
	     talkmm_logo_2.png \
	     user-info.png \
	     talkmm.png


desktopdir       = $(datadir)/applications
desktop_in_files = talkmm.desktop.in
desktop_DATA     = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@


pixmapsdir = $(datadir)/pixmaps
pixmaps_DATA = talkmm.png

talkmmuidir= $(pkgdatadir)
talkmmui_DATA= $(talkmm_ui)

EXTRA_DIST = \
	     $(talkmm_ui) \
	     $(desktop_in_files)
