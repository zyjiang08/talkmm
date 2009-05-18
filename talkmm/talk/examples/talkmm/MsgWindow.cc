/*
 * =====================================================================================
 *
 *       Filename:  MsgWindow.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年04月29日 00时28分33秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */

#include <gtkmm/textbuffer.h>
#include "MainWindow.h"
#include "MsgWindow.h"
#include "MsgBox.h"

MsgWindow::MsgWindow(MainWindow* f_parent,
		     const std::string& f_jid):m_parent(f_parent),
		     m_jid(f_jid)
{
        msg_xml = Gnome::Glade::Xml::create(msg_ui, "vbox_main");
	Gtk::VBox* vbox_main= dynamic_cast < Gtk::VBox * > (msg_xml->get_widget("vbox_main"));

	entry_send = dynamic_cast<Gtk::Entry*> (msg_xml->get_widget("entry_send"));
	entry_send->signal_activate().connect(sigc::mem_fun(*this, &MsgWindow::send_message));

	textview_msg = Gtk::manage(new class MsgBox);
	Gtk::ScrolledWindow* scroll_msg = dynamic_cast<Gtk::ScrolledWindow*>(msg_xml->get_widget("scrolled_msg_show"));
	scroll_msg->add(*textview_msg);
	textview_msg->set_editable(false);

	hbox_cancel = dynamic_cast < Gtk::HBox * > (msg_xml->get_widget("hbox_cancel"));

	button_send_file = dynamic_cast<Gtk::Button*>(msg_xml->get_widget("button_send_file"));
	button_send_file->signal_clicked().connect(sigc::mem_fun(*this, &MsgWindow::on_button_send_file));
	button_cancel_send_file = dynamic_cast<Gtk::Button*>(msg_xml->get_widget("button_cancel_send_file"));
	button_cancel_send_file->signal_clicked().connect(sigc::mem_fun(*this, &MsgWindow::on_button_cancel_send_file));

	button_call = dynamic_cast<Gtk::Button*>(msg_xml->get_widget("button_call"));
	button_call->signal_clicked().connect(sigc::mem_fun(*this, &MsgWindow::on_button_call));
	button_cancel_call = dynamic_cast<Gtk::Button*>(msg_xml->get_widget("button_cancel_call"));
	button_cancel_call->signal_clicked().connect(sigc::mem_fun(*this, &MsgWindow::on_button_cancel_call));

	progress_frame = dynamic_cast<Gtk::Frame*>(msg_xml->get_widget("progress_frame"));
	progressbar_send_file = dynamic_cast<Gtk::ProgressBar*>(msg_xml->get_widget("progressbar_send_file"));
	
	combobox_functions = dynamic_cast<Gtk::ComboBox*>(msg_xml->get_widget("combobox_functions"));

	add(*vbox_main);
	this->set_size_request(350,270);
	this->set_title(m_jid);
	this->show_all();
	progress_frame->hide();
	hbox_cancel->hide();
	combobox_functions->hide();
}
MsgWindow::~MsgWindow()
{

}

bool MsgWindow::on_delete_event(GdkEventAny* event)
{
	m_parent->close_session(m_jid);
	delete this;

}
void MsgWindow::show_message(const std::string& sender,const std::string& msg,bool self)
{
	textview_msg->showTitle(sender,self);
	textview_msg->showMessage(msg);

}
void MsgWindow::show_notify_msg(const std::string& msg)
{
	textview_msg->showSystemMsg(msg);
}


void MsgWindow::send_message()
{
	std::string text = entry_send->get_text();
	m_parent->on_send_message(m_jid,text);
	const std::string& me = m_parent->get_name();
	show_message(me,text,true);
	entry_send->set_text("");

}

void MsgWindow::on_button_send_file()
{
        Gtk::FileChooserDialog dialog(_("Please select a file"), Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
        dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

        std::string filename ;

        //dialog.set_current_folder("~/Desktop");
        int result = dialog.run();

        switch (result) {
        case (Gtk::RESPONSE_OK): {
                        filename = dialog.get_filename(); //注意：这里取回的并不是Glib::ustring, 而是std::string.
			m_parent->on_send_file(m_jid, filename);
                        break;
                }

        case (Gtk::RESPONSE_CANCEL):
                        std::cout << "Cannel choose icon" << std::endl;
                        return ;
        default:
                        std::cout << "Cannel choose icon" << std::endl;
                        return ;
        }

}

void MsgWindow::on_button_cancel_send_file()
{
	//file_transfer_end();
	//hbox_cancel->hide();
	//button_cancel_send_file->hide();
	m_parent->on_cancel_send_file(m_jid);
}

void MsgWindow::on_button_call()
{
	button_call->show();
	button_send_file->show();

	button_cancel_call->show();
	button_cancel_send_file->hide();
	hbox_cancel->show();

	m_parent->send_call_to(m_jid);
}

void MsgWindow::on_button_cancel_call()
{
	hbox_cancel->hide();
	m_parent->hangup_call(m_jid);
}
void MsgWindow::on_call_hangup()
{
	hbox_cancel->hide();
}


void MsgWindow::file_transfer_start()
{
	hbox_cancel->show();
	button_cancel_call->hide();
	progress_frame->show();
}

void MsgWindow::file_transfer_end()
{
	hbox_cancel->hide();
	progress_frame->hide();
}

void MsgWindow::update_file_progress(const std::string& file, float percent, const std::string& describe)
{
	progressbar_send_file->set_fraction(percent);
	progressbar_send_file->set_text(file + describe);
}

