/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *    Description:  程序的主窗口
 *
 *        Version:  1.0
 *        Created:  2009年4月25日 13时00分30秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua@gmail.com
 *        Company:  cyclone
 *
 k* =====================================================================================
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "talkmm.h"
#include "MainWindow.h"
//#include "ConfWindow.h"
//#include <glib/gi18n.h>
#include <stdio.h>
#include <string.h>
//#include "./config/rwxml.h"
#include "BuddyView.h"
#include "MsgWindow.h"
#include "console.h"
#include "pixmaps.h"

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
void MainWindow::on_button_about()
{
	static Gtk::AboutDialog*  about(0);
	if(about == 0){
		std::vector<Glib::ustring> authors;
		authors.push_back("Talkmm Team:");
		authors.push_back("XiongQin (xiongq@gamil.com)");
		authors.push_back("Lerosua  (lerosua@gmail.com)");
		authors.push_back("Junyi    (junyi.hit@gmail.com)");
		about = new Gtk::AboutDialog;
		//about->set_icon_from_file("talkmm_logo_1.png");
		const static Glib::RefPtr<Gdk::Pixbuf>& logo_icon = getPix("talkmm.png");
		//const static Glib::RefPtr<Gdk::Pixbuf>& logo_icon = Gdk::Pixbuf::create_from_file("talkmm_logo_2.png");
		about->set_icon(logo_icon);

		about->set_logo(logo_icon);
		about->set_program_name("Talkmm");
		about->set_version("0.1");
		about->set_website("http://code.google.com/p/talkmm/");
		about->set_copyright("Copyright (c) 2009 Talkmm Team");
		about->set_comments(_("Talkmm is a full featured gtalk for Linux based on libjingle."));
		about->set_authors(authors);
		about->set_license (_("This program is licenced under GNU General Public Licence (GPL) version 2."));
		about->set_translator_credits("Junyi, Lerosua");
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
	,m_talkmm(NULL)
	,m_session(new Session)
	,m_roster(new RosterMap)
	,m_name("talkmm")
	,combobox_status(NULL)
{
	//this->set_icon_from_file("talkmm_logo_1.png");
	this->set_icon(getPix("talkmm.png"));

        main_xml = Gnome::Glade::Xml::create(main_ui, "main_notebook");
        main_notebook = dynamic_cast < Gtk::Notebook * > (main_xml->get_widget("main_notebook"));
        main_notebook->set_current_page(LOGIN_INIT);
        main_notebook->set_show_tabs(false);

	/** first page */
	check_button_rememberMe = dynamic_cast <Gtk::CheckButton*>(main_xml->get_widget("rememberMe"));
	check_button_rememberMe->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::check_button_rememberme_clicked));
	check_button_keeppasswd = dynamic_cast <Gtk::CheckButton*>(main_xml->get_widget("keeppasswd"));
	check_button_keeppasswd->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::check_button_keeppasswd_clicked));

	button_ok = dynamic_cast <Gtk::Button*>(main_xml->get_widget("login_ok"));
	button_ok->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_login));

        entry_account = dynamic_cast <Gtk::Entry*>(main_xml->get_widget("entry_account"));
        entry_passwd = dynamic_cast <Gtk::Entry*>(main_xml->get_widget("entry_passwd"));
	entry_passwd->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_login_emit));

	if(dealconf.ReadXML() != -2){
		if(dealconf.username_r.size() != 0){
			check_button_rememberMe->set_active();
			entry_account->set_text(dealconf.username_r);
		}

		if(dealconf.password_r.size() != 0){
			check_button_keeppasswd->set_active();
			entry_passwd->set_text(dealconf.password_r);
		}
	}

	tray_icon = new TrayIcon(*this);

	GlademmXML menu_xml = Gnome::Glade::Xml::create(main_ui,"tray_menu");
	tray_pop_menu = dynamic_cast<Gtk::Menu* >(menu_xml->get_widget("tray_menu"));
	Gtk::MenuItem* menu_quit = dynamic_cast<Gtk::MenuItem*>(menu_xml->get_widget("menu_quit"));
	menu_quit->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_quit));
	//Gtk::MenuItem* menu_disconnect=dynamic_cast<Gtk::MenuItem*>(menu_xml->get_widget("menu_disconnect"));
	//menu_disconnect->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_disconnect));
	/**second page*/
        button_cancel = dynamic_cast <Gtk::Button*> (main_xml->get_widget("login_cancel"));
        button_cancel->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_loginWindow_cancel));

	progressbar_login = dynamic_cast <Gtk::ProgressBar*> (main_xml->get_widget("progressbar_login"));

	/**third page*/
	label_user_name = dynamic_cast <Gtk::Label*>(main_xml->get_widget("label_user_name"));

	button_settings = dynamic_cast <Gtk::Button *>(main_xml->get_widget("button_settings"));
	//button_settings->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_set_settings));
	button_about = dynamic_cast <Gtk::Button *>(main_xml->get_widget("button_about"));
	button_about->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_button_about));

	//entry_filter = dynamic_cast<Gtk::Entry*>(main_xml->get_widget("entry_filter"));

        Gtk::HBox* hboxfiler = dynamic_cast<Gtk::HBox*>(main_xml->get_widget("hbox_filter"));

        entry_filter = Gtk::manage(new Sexy::IconEntry());

        hboxfiler->pack_start(*entry_filter);

        entry_filter->add_clear_button();

	Gtk::Image* icon = Gtk::manage(new Gtk::Image(Gtk::Stock::FIND, Gtk::ICON_SIZE_MENU));

        icon->show();

        entry_filter->set_icon(Sexy::ICON_ENTRY_PRIMARY, icon);

	entry_filter->signal_changed().connect(sigc::mem_fun(*this,&MainWindow::on_entry_filter_changed));

	Gtk::Container* list_window = dynamic_cast <Gtk::Container*>(main_xml->get_widget("listWindow"));
	list_view = Gtk::manage(new BuddyView(*this));
	list_window->add(*list_view);


	combobox_status = dynamic_cast<Gtk::ComboBox*>(main_xml->get_widget("combobox_status"));
	combobox_status->set_active(0);
	combobox_status->signal_changed().connect(sigc::mem_fun(*this,&MainWindow::on_combox_status_change));
	add(*main_notebook);


	this->set_size_request(240,576);
	this->show_all();
	this->resize(1,1);
}

MainWindow::~MainWindow()
{
	delete m_session;
	delete m_roster;
	delete m_talkmm;
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

void MainWindow::on_login_error(const std::string& error)
{
        Gtk::MessageDialog dialog(*this, _("Login error"), false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        dialog.set_secondary_text(error);
        dialog.run();
        main_notebook->set_current_page(LOGIN_INIT); //设置当前状态为登录中
}

void MainWindow::on_loginWindow_cancel()
{
	delete m_talkmm;
	m_talkmm = NULL;
        main_notebook->set_current_page(LOGIN_INIT); //设置当前状态为登录中
}

void MainWindow::on_disconnect()
{
	if(m_talkmm != NULL){
		delete m_talkmm;
		m_talkmm = NULL;
	}
        main_notebook->set_current_page(LOGIN_INIT); //设置当前状态为登录中

}

void MainWindow::on_signon()
{
	m_name = m_talkmm->GetUserName();
	label_user_name->set_text(m_name);
	main_notebook->set_current_page(LOGIN_FINISH);
}

void MainWindow::check_button_rememberme_clicked()
{
	//cout << "The rememberme was clicked: state=" << (check_button_rememberMe->get_active() ? "true" : "false") << endl;
	Glib::ustring username_t;
	Glib::ustring password_t;
	string password_t1;

	if(check_button_rememberMe->get_active() == true && check_button_keeppasswd->get_active() == true){
		username_t = entry_account->get_text();
		password_t = entry_passwd->get_text();
		dealconf.WriteXML(username_t, password_t);;
	}
	else if(check_button_rememberMe->get_active() == true && check_button_keeppasswd->get_active() == false){
		username_t = entry_account->get_text();
		password_t1.clear();
		dealconf.WriteXML(username_t, password_t1);;
	}
}

void MainWindow::check_button_keeppasswd_clicked()
{
	//cout << "The keeppasswd was clicked: state=" << (check_button_keeppasswd->get_active() ? "true" : "false") << endl;

	Glib::ustring username_t;
        Glib::ustring password_t;
	string username_t1;

	if(check_button_keeppasswd->get_active() == true && check_button_rememberMe->get_active() == true){
		username_t = entry_account->get_text();
		password_t = entry_passwd->get_text();
		dealconf.WriteXML(username_t, password_t);;
	}
	else if(check_button_keeppasswd->get_active() == true && check_button_rememberMe->get_active() == false){
		password_t = entry_passwd->get_text();
		username_t1.clear();
		dealconf.WriteXML(username_t1, password_t);;
	}
}

void MainWindow::on_login_emit()
{
	button_ok->clicked();
}

void MainWindow::on_login()
{
	const double max = 50;
	//const double max_t = 200;
	double i;

        Glib::ustring name = entry_account->get_text();
        Glib::ustring passwd = entry_passwd->get_text();

        if (name.empty() || passwd.empty())
                return ;

        main_notebook->set_current_page(LOGIN_LOADING); //设置当前状态为登录中

	if(m_talkmm != NULL){
		delete m_talkmm;
	}

	m_talkmm = new Talkmm(this);

	if (!(m_talkmm->OnLogin(name,passwd))){
		printf("login false\n");
	}else{
		for(i = 0; i <= max; ++i)
        	{
			usleep(100000);
			progressbar_login->pulse();

	       		while(Gtk::Main::instance()->events_pending())
	              		Gtk::Main::instance()->iteration();
		}
		
		/*
		for(i = 0; i <= max_t; ++i)
        	{
			progressbar_login->set_fraction(i / max);
	
	        	while(Gtk::Main::instance()->events_pending())
	                 	Gtk::Main::instance()->iteration();
		}
		*/
		check_button_rememberme_clicked();
		check_button_keeppasswd_clicked();
	}

}


void MainWindow::signal_on_login(CLogin::Handler* f_handler,CLogin::View::Func f_call)
{
//	button_ok->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&MainWindow::on_login),f_handler,f_call));
}

void MainWindow::on_quit()
{
	Gtk::Main::quit();
	//m_talkmm->DisConnect();
	exit(0);
	
}

void MainWindow::on_set_settings()
{
	cout << "set_settings" << endl;
}

const RosterItem& MainWindow::get_roster(const std::string& f_jid)
{
    RosterMap::const_iterator iter = m_roster->find(f_jid);
    if (iter != m_roster->end()){
	return (*iter).second;
    }
}

void MainWindow::on_roster_presence(const buzz::Status& status)
{

	RosterItem item;
  	item.jid = status.jid();
  	item.show = status.show();
  	item.status = status.status();
  	item.file_cap = status.fileshare_capability()?1:0;
  	item.phone_cap = status.phone_capability()?1:0;
	item.online = status.available();


  	std::string key = item.jid.Str();
	std::string name = item.jid.node();
  	(*m_roster)[key] = item;
	int show_;
	if(item.online)
		show_= item.show;
	else
		show_=1;

	list_view->refreshBuddyStatus(key,name,item.status,show_,item.phone_cap);
}

void MainWindow::on_receive_message(const std::string& from,const std::string& message)
{

	MsgWindow* msg_window = open_session(from);

	  size_t pos = from.find("@");
	  std::string str = from.substr(0, pos);;
	//std::string utext = str +" : "+message+"\n";
	msg_window->show_message(str,message);

}

MsgWindow* MainWindow::open_session(const std::string& from)
{
	MsgWindow* msg_window = NULL;
	Session::iterator iter = m_session->find(from);

	if(iter != m_session->end()){
		msg_window = iter->second;
	}
	else{
		msg_window =new MsgWindow(this, from);
		(*m_session)[from] = msg_window;
	}

	msg_window->show();

	return msg_window;
}

void MainWindow::close_session(const std::string& from)
{

	Session::iterator iter = m_session->find(from);
	if(iter == m_session->end())
		return;
	m_session->erase(iter);


}
void MainWindow::on_send_message(const std::string& to,const std::string& message)
{
	m_console->SendMessage(to,message);
}

void MainWindow::send_call_to(const std::string& to)
{
	const RosterItem& item = this->get_roster(to);
	if(item.phone_cap)
		m_console->MakeCallTo(to);
	else
		std::cout<<to<<" does not support call  with jingle"<<std::endl;
}

void MainWindow::on_hangup_call(const std::string& from)
{
	MsgWindow* msg_window = open_session(from);
	msg_window->on_call_hangup();
	msg_window->show_notify_msg("remote hangup the call");

}
void MainWindow::hangup_call(const std::string& to)
{
	const RosterItem& item = this->get_roster(to);
	if(item.phone_cap)
		m_console->HangupCall(to);
	else
		std::cout<<to<<"on cancel call"<<std::endl;
}

void MainWindow::on_incoming_call(const std::string& from)
{

        Gtk::MessageDialog dialog(*this, _("Incoming Call"), false,
                                  Gtk::MESSAGE_QUESTION,
                                  Gtk::BUTTONS_OK_CANCEL);

        Glib::ustring msg = from +" Calling you! Are you accept? ";
        dialog.set_secondary_text(msg);
        int result = dialog.run();
        switch (result) {
        case (Gtk::RESPONSE_OK): {
				 	m_console->AnswerCall("true");
					MsgWindow* msg_window = open_session(from);
					msg_window->on_call_start();
					msg_window->raise();
				 	break;
				 }
        case (Gtk::RESPONSE_CANCEL): {
					 m_console->AnswerCall("false");
                        break;
                }
        default: {
					 m_console->AnswerCall("false");
                        break;
                }
	}

}

void MainWindow::on_cancel_send_file(const std::string& to)
{
	m_console->CancelSendFile(to);
#if 0
	const RosterItem& item = this->get_roster(to);
	MsgWindow* msg_window = open_session(to);
	if(item.file_cap){
		//msg_window->file_transfer_end();
		//m_console->CancelSendFile(item.jid);
		m_console->CancelSendFile(to);
	}
	else{
		std::string msg = to +"does not support file translate with jingle";
		std::cout<<msg<<std::endl;
		msg_window->show_notify_msg(msg);
	}
#endif
}

void MainWindow::on_send_file(   const std::string& to,  const std::string& filename)
{
	const RosterItem& item = this->get_roster(to);
	if(item.file_cap){
		MsgWindow* msg_window = open_session(to);
		msg_window->file_transfer_start();
		m_console->SendFile(to, filename);
	}
	else
		std::cout<<to<<" does not support file translate with jingle"<<std::endl;
}


void MainWindow::on_file_receive(const std::string& from,const std::string& file)
{
        Gtk::MessageDialog dialog(*this, _("Receive File"), false,
                                  Gtk::MESSAGE_QUESTION,
                                  Gtk::BUTTONS_OK_CANCEL);

        Glib::ustring msg = from +" want to send a file to you "+"("+file+")";
        dialog.set_secondary_text(msg);
        int result = dialog.run();
	dialog.hide();
        switch (result) {
        case (Gtk::RESPONSE_OK): {

		Gtk::FileChooserDialog dialog_(_("Please select a dir"), Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		dialog_.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dialog_.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

		int result_ = dialog_.run();
			switch (result_) {
				case (Gtk::RESPONSE_OK): {
					std::string folder_ = dialog_.get_current_folder();
					std::cout<<"select folder = "<<folder_<<std::endl;
					m_console->SetRecvFileDir(folder_);
					m_console->AnswerFile("true");
					MsgWindow* msg_window = open_session(from);
					 break;
				 }
				default:
					 m_console->AnswerFile("false");
					 break;
			}

		 break;
	 }
        case (Gtk::RESPONSE_CANCEL): {
					 m_console->AnswerFile("false");
                        break;
                }
        default: {
					 m_console->AnswerFile("false");
                        break;
                }
	}
}


void MainWindow::on_menu_pref_activate()
{
	printf("pref window activate\n");

}

void MainWindow::on_combox_status_change()
{
	int show = combobox_status->get_active_row_number();
	int tshow;
	switch(show){
		case 0:
			tshow=5;
			break;
		case 1:
			tshow=6;
			break;
		case 2:
			tshow=3;
			break;
		case 3:
			tshow=4;
			break;
		case 4:
			tshow=2;
			break;
		case 5:
			tshow=1;
			break;
		default:
			tshow=5;
			break;
	};
	std::string status= "";
	m_console->SendStatus(tshow,status);
	
}

void MainWindow::on_filetranser_statue(const std::string& jid,const std::string& statue)
{
	MsgWindow* msg_window = open_session(jid);

	
	if("started" == statue){
		msg_window->show_notify_msg("file tranfser start");
		msg_window->file_transfer_start();
	}
	else if("failed" == statue){
		msg_window->show_notify_msg("file transfer failed");
		msg_window->file_transfer_end();
	}
	else if("local-canceled" == statue){
		msg_window->show_notify_msg("file transfer canncel by local");
		msg_window->file_transfer_end();
	}
	else if("canceled" == statue){
		msg_window->show_notify_msg("file transfer canncel by remote");
		msg_window->file_transfer_end();
	}
	else if("completed" == statue){
		msg_window->show_notify_msg("file transfer completed");
		msg_window->file_transfer_end();
	}
	
}

void MainWindow::on_calling_statue(const std::string& jid,const std::string& statue)
{
	MsgWindow* msg_window = open_session(jid);
	if("answer"==statue){
		//msg_window->show_notify_msg("please start talk");
		msg_window->on_call_start();

	}
	else if("noanswer" == statue){
		msg_window->show_notify_msg("remote no answer");
		msg_window->on_call_hangup();
	}
	else if("calling" == statue){
		msg_window->show_notify_msg("calling...");
	}
	else if("talking" == statue){

	}

}

void MainWindow::on_file_update_progress(const std::string& jid, const std::string& file,
					 float percent, const std::string& describe)
{
	MsgWindow* msg_window = open_session(jid);

	msg_window->update_file_progress(file, percent, describe);
	cout << "on_file_update_progress........................" << endl;
}

void MainWindow::on_entry_filter_changed()
{
	Glib::ustring filter = entry_filter->get_text();
	list_view->set_filter_text(filter);
}
