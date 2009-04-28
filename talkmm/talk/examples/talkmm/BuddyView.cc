/*
* =====================================================================================
*
*       Filename:  BuddyView.cpp
*
*    Description:  显示好友列表的控件
*
*        Version:  1.0
*        Created:  2007年06月28日 19时26分39秒 CST
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  wind (xihe), xihels@gmail.com
*        Company:  cyclone
*
*  纪念5.12汶川地震中消逝的那些生命
* =====================================================================================
*/

#include <glib/gi18n.h>
#include <fstream>
#include <unistd.h>
#include "BuddyView.h"

BuddyView::BuddyView(MainWindow & f_parent):
m_parent(f_parent)
{
	set_headers_visible(false);
	set_border_width(5);
	set_name("icalk_blist_treeview");


	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_MOTION_MASK |
		   Gdk::
		   BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::
		   ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK);

	m_treestore = TreeModelDnd::create(buddyColumns);
	set_model(m_treestore);


	append_column("ICON", buddyColumns.icon);
	//set_show_expanders(false); //gtkmm 2.12

	Gtk::TreeView::Column * col =
	    Gtk::manage(new Gtk::TreeView::Column("iCalk"));
	col->pack_start(m_rendtext);

	col->add_attribute(m_rendtext.property_markup(),
			   buddyColumns.nickname);
	col->set_resizable(true);
	col->set_expand();


	this->append_column(*col);
	this->append_column("Voip", buddyColumns.audioicon);

	/*
	   this->signal_enter_notify_event().connect(sigc::mem_fun(
	   *this,&BuddyView::on_enter_event));
	 */
	show_all_children();
}

BuddyView::~BuddyView()
{
	//delete m_tooltips;

}

Gtk::TreeModel::iterator BuddyView::getListIter(Gtk::
						TreeModel::Children
						children,
						const Glib::ustring & id)
{
	/*查找好友列表项 */
	return find_if(children.begin(),
		       children.end(),
		       bind2nd(CompareBuddy(buddyColumns), id));
}

bool BuddyView::remove(const Glib::ustring & id) {
	return false;
}

void BuddyView::add(const std::string & jid_str) {

        Gtk::TreeModel::iterator listiter = m_treestore->append();
	(*listiter)[buddyColumns.id] = jid_str;
	(*listiter)[buddyColumns.nickname] = jid_str;
	this->expand_all();
}

void BuddyView::refreshBuddyStatus(const Glib::ustring & jid_ctr)
{
}

bool BuddyView::on_button_press_event(GdkEventButton * ev)
{
	bool result = Gtk::TreeView::on_button_press_event(ev);

	Glib::RefPtr < Gtk::TreeSelection > selection =
	    this->get_selection();
	Gtk::TreeModel::iterator iter = selection->get_selected();

	if (!selection->count_selected_rows())
		return result;

	Gtk::TreeModel::Path path(iter);

	Gtk::TreeViewColumn * tvc;

	int cx, cy;

	/** get_path_at_pos() 是为确认鼠标是否在选择行上点击的*/
	if (!this->get_path_at_pos
	    ((int) ev->x, (int) ev->y, path, tvc, cx, cy))
		return FALSE;

	Glib::ustring mid = (*iter)[buddyColumns.id];

	//int type = (*iter)[buddyColumns.status];

	if ((ev->type == GDK_2BUTTON_PRESS ||
	     ev->type == GDK_3BUTTON_PRESS)) {
		printf("select %s \n",mid.c_str());

	} else if ((ev->type == GDK_BUTTON_PRESS)
		   && (ev->button == 3)) {
	}

	return result;
}
