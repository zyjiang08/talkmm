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

MsgWindow::MsgWindow(MainWindow* f_parent,const std::string& f_jid):m_parent(f_parent)
					   ,m_jid(f_jid)
{
        msg_xml = Gnome::Glade::Xml::create(msg_ui, "vbox_main");
	Gtk::VBox* vbox_main= dynamic_cast <
                Gtk::VBox * > (msg_xml->get_widget("vbox_main"));
	entry_send = dynamic_cast<Gtk::Entry*>
		(msg_xml->get_widget("entry_send"));
	textview_msg = dynamic_cast<Gtk::TextView*>
		(msg_xml->get_widget("textview_msg"));

	entry_send->signal_activate().connect(sigc::mem_fun(*this,&MsgWindow::send_message));

	add(*vbox_main);
	this->set_size_request(400,200);
	this->show_all();
}
MsgWindow::~MsgWindow()
{

}

void MsgWindow::show_message(const std::string& msg)
{
	textview_msg->set_wrap_mode(Gtk::WRAP_WORD);
        Glib::RefPtr < Gtk::TextBuffer > buffer = textview_msg->get_buffer();
        Gtk::TextBuffer::iterator end = buffer->end();
        Gdk::Rectangle rect;
        textview_msg->get_visible_rect(rect);

        int y = -1;
        int height = -1;
        textview_msg->get_line_yrange(end, y, height);

        buffer->place_cursor(buffer->insert(end, msg));


        if (y < rect.get_y() + rect.get_height() + 16) // 最后一行可见，也就是用户没有向上滚动
                textview_msg->scroll_to_mark(buffer->get_insert(), 0); // 插入文本后也要向下滚动，使最后一行继续可见

}

void MsgWindow::send_message()
{
	std::string text = entry_send->get_text();
	m_parent->on_send_message(m_jid,text);

}
