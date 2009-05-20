/*
* =====================================================================================
*
*       Filename:  BuddyView.h
*
*    Description:  显示好友列表的控件
*
*        Version:  1.0
*        Created:  2007年06月28日 19时01分59秒 CST
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  wind (xihe) lerosua, xihels@gmail.com lerosua@gmail.com
*        Company:  Cyclone Team
*
* =====================================================================================
*/

#ifndef _BUDDY_VIEW_H_
#define _BUDDY_VIEW_H_

#include <gtkmm.h>
#include <libglademm/xml.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/tooltip.h>
#include <assert.h>
#include <functional>
#include <vector>
#include <sigc++/connection.h>
#include "TreeModelDnd.h"
#include "MainWindow.h"

using namespace std;

class TreeViewTooltips;

/**
 * @brief  用于显示好友列表的控件.继承Gtk::TreeView
 * @author lerosua@gmail.com
 *
 */

class BuddyView:public Gtk::TreeView {

      public:
	BuddyView(MainWindow & parent_);
	~BuddyView();

	/**添加好友进列表*/

	void add(const std::string & jid,const std::string& name,const std::string& status="",int show=5,bool call=false);

	/**删除列表中的好友显示*/
	bool remove(const Glib::ustring & id);

	/**更新好友状态*/
	void refreshBuddyStatus(const std::string & jid,const std::string& name,const std::string& status="",int show=5,bool call=false);

	void set_filter_text(const Glib::ustring& text);

	/**
         * @brief 获取TreeModel里的ID
         * @param iter TreeView里的某行
         * @return 返回此行的ID
         */
	Glib::ustring getIDfromIter(Gtk::TreeModel::iterator iter) {
		return (*iter)[buddyColumns.id];
	}
	/** 以ID号获取到TreeView里的某行指针*/
	Gtk::TreeModel::iterator getListIter(Gtk::TreeModel::Children children, const Glib::ustring & id);

      protected:
	bool on_button_press_event(GdkEventButton *);
	bool list_visible_func(const Gtk::TreeIter& iter);
	bool on_tooltip_show(int,int,bool,const Glib::RefPtr<Gtk::Tooltip>&);

      private:
	MainWindow & m_parent;

	Glib::RefPtr < TreeModelDnd > m_treestore;
	Glib::RefPtr < Gtk::TreeModelFilter> m_treemodelfilter;

	BuddyColumns buddyColumns;
	TreeViewTooltips* m_tooltips;
	Gtk::CellRendererText m_rendtext;
	Glib::ustring m_filterText;

      private:
	/** 比较好友*/

	struct CompareBuddy:public binary_function < Gtk::TreeModel::Row, const Glib::ustring, bool > {
		explicit CompareBuddy(const BuddyColumns &column_):column(column_) {
		} bool operator () (const Gtk::TreeRow & lhs, const Glib::ustring & var) const {
			return lhs[column.id] == var;
		} const BuddyColumns & column;
	};

	/** TreeView的排序函数*/
	int on_sort_compare(const Gtk::TreeModel::iterator & a, const Gtk::TreeModel::iterator & b);
};

#endif	// _BUDDY_VIEW_H_
