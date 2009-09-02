/*
 * =====================================================================================
 *
 *       Filename:  SettingWindow.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年08月19日 10时55分10秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  junyi, junyi.hit@gmail.com
 *        Company:  Talkmm Team
 *
 * =====================================================================================
 */

#include <glib/gi18n.h>
#include <gtkmm/textbuffer.h>
#include "MainWindow.h"
//#include "MsgWindow.h"
#include "SettingWindow.h"
//#include "MsgBox.h"
#include "pixmaps.h"

using namespace std;

SettingWindow::SettingWindow(MainWindow* f_parent)
{
	this->set_icon(getPix("talkmm.png"));
	
	setting_xml = Gtk::Builder::create_from_file(setting_ui, "vbox_setting");
	Gtk::VBox* vbox_setting= 0;
	setting_xml->get_widget("vbox_setting",vbox_setting);

	add(*vbox_setting);
	this->set_size_request(400 * 2, 300 * 2);
	this->set_title(m_jid);
	this->show_all();
}

SettingWindow::~SettingWindow()
{

}

void SettingWindow::xx(const std::string& flag)
{
	cout << "hello, setting!" << endl;
}
