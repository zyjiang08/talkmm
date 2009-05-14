/*
 * =====================================================================================
 * 
 *       Filename:  MsgWindow.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2009年04月29日 00时27分15秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 * 
 * =====================================================================================
 */

#ifndef  MSGWINDOW_FILE_HEADER_INC
#define  MSGWINDOW_FILE_HEADER_INC

#include <gtkmm.h>

#define msg_ui "./msg_window.glade"
//#define msg_ui "./msg_window_t.glade"
//typedef Glib::RefPtr <Gnome::Glade::Xml> GlademmXML;

class MainWindow;
class MsgWindow: public Gtk::Window
{
	public:
		MsgWindow(MainWindow* f_parent,const std::string& f_jid);
		~MsgWindow();
		void show_message(const std::string& msg);
		void send_message();
		void on_button_send_file();
		void on_button_cancel_send_file();
		void on_button_call();
		void on_button_cancel_call();
		void file_tranfer_start();
		void file_tranfer_end();
	protected:
		bool on_delete_event(GdkEventAny* event);
	private:
		MainWindow*				m_parent;
		std::string				m_jid;
		GlademmXML				msg_xml;
		Gtk::Entry*				entry_send;
		Gtk::TextView*				textview_msg;
		Gtk::HBox* 				hbox_cancel;
		Gtk::Button*				button_call;
		Gtk::Button* 				button_send_file;
		Gtk::Button* 				button_cancel_send_file;
		Gtk::Button* 				button_cancel_call;
		//Gtk::VBox*				vbox_file;
		Gtk::Frame*				progress_frame;


};
#endif   /* ----- #ifndef MSGWINDOW_FILE_HEADER_INC  ----- */

