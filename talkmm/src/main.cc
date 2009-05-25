/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main fucition
 *
 *        Version:  1.0
 *        Created:  2009年4月9日 12时13分02秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <gtkmm/main.h>
#include "MainWindow.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

////////////////////////////////////
//added on 2009.5.20 by string
#include <libglademm/xml.h>
////////////////////////////////////


using namespace std;

void getPath()
{
	char buffer[256];
	memset(buffer, 0, 256);
	getcwd(buffer, 256);
	printf( "The current directory is: %s\n",   buffer); 
	printf("File: %s Line: %d\n", __FILE__, __LINE__);
}

int main(int argc, char* argv[])
{
	//setlocale (LC_ALL, "");

	/*
	bindtextdomain (GETTEXT_PACKAGE, GMDEMO_LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, NULL);
	textdomain (GETTEXT_PACKAGE);
	*/


	if (!g_thread_supported())
		g_thread_init(NULL);

	gdk_threads_init();

	////////////////////////////////////
	//added on 2009.5.20 by string
	//test themes
	//gtk_rc_parse("./themes/Afterhours/gtk-2.0/gtkrc");
	//gtk_rc_parse("./themes/Cillop-Midnite/gtk-2.0/gtkrc");
	//gtk_rc_parse("./themes/SoftSquares/metacity-1/metacity-theme-1.xml");
	////////////////////////////////////

	Gtk::Main kit(argc, argv);
	//Talkmm talkmm;
	MainWindow window;

	gdk_threads_enter();
	kit.run();
	gdk_threads_leave();

	return 0;
}

