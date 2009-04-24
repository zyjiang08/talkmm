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

#include "MainWindow.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


using namespace std;

int main(int argc, char* argv[])
{
	setlocale (LC_ALL, "");

	/*
	bindtextdomain (GETTEXT_PACKAGE, GMDEMO_LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, NULL);
	textdomain (GETTEXT_PACKAGE);
	*/

	Gtk::Main kit(argc, argv);

	MainWindow wnd; 
	wnd.on_init();
	
	kit.run();

	return 0;
}

