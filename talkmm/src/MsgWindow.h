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
#include <deque>
#include <sigc++/connection.h>

#define msg_ui DATA_DIR"/msg_window.glade"

class MsgBox;
//class XWebkit;
class MainWindow;
class MsgWindow: public Gtk::Window
{
	public:
		MsgWindow(MainWindow* f_parent,const std::string& f_jid);
		~MsgWindow();
		//void show_message(const std::string& msg);
		void show_message(const std::string& sender,const std::string& msg,bool self=false);
		void store_message(const std::string& msg);
		void show_notify_msg(const std::string& msg);
		bool on_show_message();
		void send_message();
		void on_button_send_file();
		void on_button_cancel_send_file();
		void on_file_answer();
		void on_incoming_file(const std::string& from);
		void on_button_call();
		//void on_button_call_answer();
		void on_call_answer();
		void on_button_cancel_call();
		void on_call_hangup();
		void on_call_start();
		void file_transfer_start();
		void file_transfer_end();
		void on_incoming_call(const std::string& from);
	//	void update_file_progress(const std::string& file,float percent);
		void update_file_progress(const std::string& file, float percent, const std::string& describe);


	protected:
		bool on_delete_event(GdkEventAny* event);
		bool alarm(const std::string& flag);
	private:
		MainWindow*				m_parent;
		std::string				m_jid;
		GBuilderXML				msg_xml;
		Gtk::Entry*				entry_send;
		typedef std::deque<std::string> MessageDeque;
		MessageDeque				m_message_deque;
		sigc::connection			m_timeout;
		//Gtk::TextView*				textview_msg;
		MsgBox*					textview_msg;
		//XWebkit*				textview_msg;
		Gtk::HBox* 				hbox_functions;
		Gtk::HBox* 				hbox_cancel;
		Gtk::Button*				button_call;
		Gtk::Button*				button_call_answer;
		Gtk::Button* 				button_send_file;
		Gtk::Button*				button_file_answer;
		Gtk::Button* 				button_cancel_send_file;
		Gtk::Button* 				button_cancel_call;
		Gtk::ComboBox*				combobox_functions;
		//Gtk::VBox*				vbox_file;
		Gtk::Frame*				progress_frame;
		Gtk::ProgressBar*			progressbar_send_file;
		bool	file_sending;
		bool	calling;

};
#endif   /* ----- #ifndef MSGWINDOW_FILE_HEADER_INC  ----- */

