/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *    Description:  程序的主窗口
 *
 *        Version:  1.0
 *        Created:  2007年11月25日 13时00分30秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wind (xihe), xihels@gmail.com
 *        Company:  cyclone
 *
 k* =====================================================================================
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "MainWindow.h"
#include "LoginWindow.h"
//#include "ConfWindow.h"
#include <glib/gi18n.h>
#include <stdio.h>
#include <string.h>

using namespace std;


void MainWindow::show_window()
{
	this->show();
	this->move(window_x, window_y);
}

void MainWindow::hide_window()
{
	this->get_position(window_x, window_y);
	this->hide();
}

bool MainWindow::on_delete_event(GdkEventAny* event)
{
	this->get_position(window_x, window_y);
	return Gtk::Window::on_delete_event(event);
}

/*
void MainWindow::on_menu_view_preferences()
{
	if(NULL==confwindow)
	{
		confwindow = new ConfWindow(this);
		confwindow->signal_quit().connect(sigc::mem_fun(*this, &MainWindow::on_conf_window_quit));
	}
	else
		confwindow->raise();
}

*/
void MainWindow::on_menu_about()
{
	static Gtk::AboutDialog*  about(0);
	if(about == 0){
		std::vector<Glib::ustring> authors;
		authors.push_back("lerosua ");
		about = new Gtk::AboutDialog ;
		//about->set_logo(ui_logo);
		about->set_program_name("GMDemo");
		about->set_version("0.10");
		about->set_website("http://lerosua.org");
		about->set_copyright("Copyright (c) 2009 lerosua");
		about->set_comments(_("GMDemo is gtkmm program demo"));
		about->set_authors(authors);
		about->set_license (_("This program is licenced under GNU General Public Licence (GPL) version 2."));
		about->set_translator_credits("lerosua");


	}
	about->run();
	delete about;
	about=0;

}

void MainWindow::on_conf_window_quit()
{
}

/*
void MainWindow::on_conf_window_close(ConfWindow* dlg)
{
	g_assert(dlg == confwindow);
	delete confwindow;
	confwindow=NULL;
}
*/

MainWindow::MainWindow():
	window_width(1)
	,window_height(1)
	//,confwindow(NULL)
	,tray_icon(NULL)
{
	//notebook=Gtk::manage(new Gtk::Notebook());
	Gtk::Label* label=Gtk::manage(new Gtk::Label("label demo"));
	add(*label);

	tray_icon = new TrayIcon(*this);

	this->set_size_request(100,400);
	this->show_all();
	this->resize(1,1);

}

MainWindow::~MainWindow()
{
}

bool MainWindow::on_key_press_event(GdkEventKey* ev)
{
	if(ev->type !=GDK_KEY_PRESS)
		return Gtk::Window::on_key_press_event(ev);
	
	switch(ev->keyval){
		case GDK_Escape:
			break;
		case GDK_F11:
			break;
		default:
			return Gtk::Window::on_key_press_event(ev);

	}
	return true;
}

void MainWindow::on_loginWindow_cancel()
{


}

void MainWindow::on_loginWindow_ok()
{

}

void MainWindow::on_init()
{

	this->hide();
	LoginWindow* dlg = new LoginWindow(*this);

}
void MainWindow::on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call)
{
	this->show();
}


void MainWindow::signal_on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call)
{

	button_ok->signal_clicked().connect(sigc::bind(
				sigc::mem_fun(*this,&MainWindow::on_login),f_handler,f_call));


}
