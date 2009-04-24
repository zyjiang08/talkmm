// generated 2005/6/24 0:15:11 CST by xihels@163.com
//
#ifndef _LOGINDIALOG_HH
#  define _LOGINDIALOG_HH

#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  

    Glib::RefPtr<Gtk::AccelGroup> accgrp;
    public:

    GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
    {  
    }

    Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
    {  return accgrp;
    }
};
#endif //GLADEMM_DATA

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>



class MainWindow;
class LoginWindow : public Gtk::Window
{  
    public:	
		
	LoginWindow(MainWindow& _parent);
	~LoginWindow();
	void on_loginWindow_cancel();
	void on_loginWindow_ok();

    private:
	bool on_delete_event(GdkEventAny*);

    private:
	GlademmData *gmm_data;
	Gtk::Entry * entryAccount;
	Gtk::Entry * entryPasswd;
	Gtk::Button * buttonConnect;

	
	MainWindow& parent;
};

#endif
