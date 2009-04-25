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
        main_xml = Gnome::Glade::Xml::create(main_ui, "main_notebook");
        main_notebook =
                dynamic_cast <
                Gtk::Notebook * > (main_xml->get_widget("main_notebook"));
        main_notebook->set_current_page(0);
        main_notebook->set_show_tabs(false);

	/** first page */
        Gtk::Button * button_cancel =
                dynamic_cast <
                Gtk::Button * > (main_xml->get_widget("login_cancel"));

        button_cancel->signal_clicked().
        connect(sigc::mem_fun(*this, &MainWindow::on_quit));


        entry_account = dynamic_cast<Gtk::Entry*>
                      (main_xml->get_widget("entry_account"));

        entry_passwd = dynamic_cast<Gtk::Entry*>
                      (main_xml->get_widget("entry_passwd"));

	//Gtk::Label* label=Gtk::manage(new Gtk::Label("label demo"));
	//add(*label);

	tray_icon = new TrayIcon(*this);


	add(*main_notebook);
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

}
void MainWindow::on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call)
{
        Glib::ustring name = entry_account->get_text();
        Glib::ustring passwd = entry_passwd->get_text();

        if (name.empty() || passwd.empty())
                return ;
        //main_notebook->set_current_page(LOGIN_LOADING); //设置当前状态为登录中
        main_notebook->set_current_page(1); //设置当前状态为登录中
        if (!(f_handler->*f_call)(name, passwd)) { // 登录失败
		printf("login false\n");
	}
}


void MainWindow::signal_on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call)
{

	Gtk::Button* button_ok = dynamic_cast <Gtk::Button*>(main_xml->get_widget("login_ok"));
	button_ok->signal_clicked().connect(sigc::bind(
				sigc::mem_fun(*this,&MainWindow::on_login),f_handler,f_call));


}

void MainWindow::on_quit()
{
}
