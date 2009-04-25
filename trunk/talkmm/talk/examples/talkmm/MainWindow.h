/*
 * =====================================================================================
 * 
 *       Filename:  MainWindow.h
 * 
 *    Description:  程序的主窗口
 * 
 *        Version:  1.0
 *        Created:  2007年11月25日 12时56分29秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  wind (xihe), xihels@gmail.com
 *        Company:  cyclone
 * 
 * =====================================================================================
 */


#ifndef _MAINWINDOW_HH
#define _MAINWINDOW_HH


#include <gtkmm.h>
#include <libglademm/xml.h>
#include <glib/gi18n.h>
#include "TrayIcon.h"
#include "MVC.h"

#define main_ui "./main_window.glade"
typedef Glib::Refptr<Gnome::Glade::Xml> GlademmXML;


class MainWindow : public Gtk::Window {
	public:
		MainWindow();
		~MainWindow();
		//void on_conf_window_close(ConfWindow* dlg);
		bool on_key_press_event(GdkEventKey* ev);
		void hide_window();
		void show_window();
		void on_init();
		void on_loginWindow_ok();
		void on_loginWindow_cancel();
		void on_login();
		void signal_on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call);

	protected:
		bool on_delete_event(GdkEventAny* event);
		void on_menu_about();
	private:
		/** 属性窗口退出处理*/
		void on_conf_window_quit();
		/** 双击画面事件*/
		

	private:
		Gtk::Notebook*				main_notebook;
		GlademmXML				main_xml;
		Gtk::Entry*				entry_account;
		Gtk::Entry*				entry_passwd;
		TrayIcon				*tray_icon;
		//ConfWindow*			confwindow;
		int					window_width;
		int					window_height;
		int					window_x;
		int					window_y;
};

#endif // _MAINWINDOW_HH 

