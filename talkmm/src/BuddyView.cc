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
#include "TreeViewTooltips.h"
#include "pixmaps.h"

BuddyView::BuddyView(MainWindow & f_parent):
		m_parent(f_parent)
                , m_filterText("")
{
	set_headers_visible(false);
	set_border_width(5);
	set_has_tooltip();
	set_name("talkmm_blist_treeview");

	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_MOTION_MASK | 
		   Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | 
		   Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK);

	m_treestore = TreeModelDnd::create(buddyColumns);
	//set_model(m_treestore);
        m_treemodelfilter = Gtk::TreeModelFilter::create(m_treestore);
        m_treemodelfilter->set_visible_func(sigc::mem_fun(*this, &BuddyView::
                                            list_visible_func));
        set_model(m_treemodelfilter);

	append_column("ICON", buddyColumns.icon);
	//set_show_expanders(false); //gtkmm 2.12

	Gtk::TreeView::Column * col = Gtk::manage(new Gtk::TreeView::Column("iCalk"));
	col->pack_start(m_rendtext);

#ifdef GLIBMM_PROPERTIES_ENABLED
        m_rendtext.property_ellipsize() = Pango::ELLIPSIZE_END;
#endif
	col->add_attribute(m_rendtext.property_markup(), buddyColumns.nickname);
	col->set_resizable(true);
	col->set_expand();

	this->append_column(*col);
	this->append_column("Voip", buddyColumns.audioicon);

        m_treestore->
        set_default_sort_func(sigc::
                              mem_fun(*this,
                                      &BuddyView::on_sort_compare));
        m_treestore->
        set_sort_column_id(Gtk::TreeSortable::DEFAULT_SORT_COLUMN_ID,
                           Gtk::SORT_ASCENDING);
	/*
	   this->signal_enter_notify_event().connect(sigc::mem_fun(
	   *this,&BuddyView::on_enter_event));
	 */
        m_tooltips = new TreeViewTooltips(this);
	this->set_tooltip_window( *m_tooltips);
	this->signal_query_tooltip().connect(sigc::mem_fun(*this,&BuddyView::on_tooltip_show));
	show_all_children();
}

BuddyView::~BuddyView()
{
	delete m_tooltips;
}

Gtk::TreeModel::iterator BuddyView::getListIter(Gtk::TreeModel::Children children, const Glib::ustring & id)
{
	/*查找好友列表项 */
	return find_if(children.begin(), children.end(), bind2nd(CompareBuddy(buddyColumns), id));
}

bool BuddyView::remove(const Glib::ustring & id) 
{
        Gtk::TreeModel::Children children = m_treestore->children();
        Gtk::TreeModel::iterator listiter;
	listiter = getListIter(children,id);
	printf("remove %s \n",id.c_str());
	if(listiter != children.end()){
		m_treestore->erase(*listiter);
	}
	return true;
}

void BuddyView::add(const std::string & jid_str,const std::string& name,const std::string& status,int show,bool call) 
{
        Gtk::TreeModel::iterator listiter = m_treestore->append();
	(*listiter)[buddyColumns.id] = jid_str;

	if(show>=5)
		(*listiter)[buddyColumns.icon] = getPix16("online.png");
	else
		(*listiter)[buddyColumns.icon] = getPix16("dnd.png");
	if(call)
		(*listiter)[buddyColumns.audioicon] = getPix16("call.png");


	if(!status.empty()){
		char* marktext = g_markup_printf_escaped(
				"%s\n<span color='dim grey'><small>%s</small></span>",
				name.c_str(),status.c_str());
		(*listiter)[buddyColumns.nickname] = marktext;
		g_free(marktext);
	}
	else
		(*listiter)[buddyColumns.nickname] = name;


	this->expand_all();
}

void BuddyView::refreshBuddyStatus(const std::string & jid,const std::string& name,const std::string& status,int show,bool call)
{
	Gtk::TreeModel::Children children = m_treestore->children();
	Gtk::TreeModel::iterator iter ;
	iter = getListIter(children, jid);

	if(iter == children.end()){
		add(jid,name,status,show,call);
		return;
	}

	if(1==show){
		remove(jid);
		return;
	}
	if(show>=5)
		(*iter)[buddyColumns.icon] = getPix16("online.png");
	else
		(*iter)[buddyColumns.icon] = getPix16("dnd.png");

	if(!status.empty()){
		char* marktext = g_markup_printf_escaped(
				"%s\n<span color='dim grey'><small>%s</small></span>",
				name.c_str(),status.c_str());
		(*iter)[buddyColumns.nickname] = marktext;
		g_free(marktext);
	}
	if(call)
		(*iter)[buddyColumns.audioicon] = getPix16("call.png");

}

bool BuddyView::on_button_press_event(GdkEventButton * ev)
{
	bool result = Gtk::TreeView::on_button_press_event(ev);

	Glib::RefPtr < Gtk::TreeSelection > selection = this->get_selection();
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

	if ((ev->type == GDK_2BUTTON_PRESS || ev->type == GDK_3BUTTON_PRESS)) {
		printf("select %s \n",mid.c_str());
		m_parent.open_session(mid);
	} else if ((ev->type == GDK_BUTTON_PRESS)
		   && (ev->button == 3)) {
	}

	return result;
}


int BuddyView::on_sort_compare(const Gtk::TreeModel::iterator & a,
                               const Gtk::TreeModel::iterator & b)
{
        int result;
#if 0

        if ((result =
                                (*a)[buddyColumns.status] - (*b)[buddyColumns.status]) == 0) {
                Glib::ustring an = (*a)[buddyColumns.nickname];
                Glib::ustring bn = (*b)[buddyColumns.nickname];
                result = an.lowercase().compare(bn.lowercase());
        }
#endif
                Glib::ustring an = (*a)[buddyColumns.nickname];
                Glib::ustring bn = (*b)[buddyColumns.nickname];
                result = an.lowercase().compare(bn.lowercase());

        return result;
}

void BuddyView::set_filter_text(const Glib::ustring& text)
{
        m_filterText = text;
        m_treemodelfilter->refilter();

}

bool BuddyView::list_visible_func(const Gtk::TreeIter& iter)
{

        Glib::ustring email = (*iter)[buddyColumns.id];
        Glib::ustring name = (*iter)[buddyColumns.nickname];
        //int type = (*iter)[buddyColumns.status];

        if (m_filterText.empty())
                return true;
        else if (email.lowercase().find(m_filterText.lowercase()) != Glib::ustring::npos)
                return true;
        else if (name.lowercase().find(m_filterText.lowercase()) != Glib::ustring::npos)
                return true;

        return false;

}

bool BuddyView::on_tooltip_show(int x,int y, bool key_mode,const Glib::RefPtr<Gtk::Tooltip>& tooltip)
{
        Gtk::TreeModel::Path path;
        Gtk::TreeViewColumn * column;

        int cell_x, cell_y;

        if (this->get_path_at_pos(x, y, path, column, cell_x,cell_y)){
                Gtk::TreeModel::iterator iter = this->get_model()->get_iter(path);

                if (!iter)
                        return false;

                Glib::ustring jid = (*iter)[buddyColumns.id];
		Glib::ustring msg = (*iter)[buddyColumns.nickname];
		m_tooltips->setLabel(jid+"\n"+msg);

		return true;
	}

	return false;
}
