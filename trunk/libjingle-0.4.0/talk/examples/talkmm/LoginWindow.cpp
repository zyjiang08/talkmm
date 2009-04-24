// generated 2005/6/24 0:15:11 CST by xihels@163.com
//


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
//#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gdkmm/pixbufloader.h>
#include <gtkmm/table.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <gtkmm/expander.h>
#else //
#include <gtkmm/handlebox.h>
#endif //

#include "LoginWindow.h"
#include "MainWindow.h"
#include <sstream>
#include <stdlib.h>

using namespace std;


LoginWindow::LoginWindow(MainWindow& _parent): parent(_parent)
{  
    Gtk::Window *loginWindow = this;
    gmm_data = new GlademmData(get_accel_group());



    Gtk::Label *labelAccount = 
	Gtk::manage(new class Gtk::Label("<b>账号(_A)</b>", true));
    Gtk::Label *labelPasswd = 
	Gtk::manage(new class Gtk::Label("<b>密码(_P)</b>", true));


    entryPasswd = Gtk::manage(new class Gtk::Entry());
    entryAccount = Gtk::manage(new class Gtk::Entry());



    Gtk::Table *tableLogin = Gtk::manage(new class Gtk::Table(2, 2, false));
    Gtk::Button *buttonCancel = Gtk::manage(new class Gtk::Button("取消(_C)", true));

    buttonConnect = Gtk::manage(new class Gtk::Button("连接(_O)", true));

    Gtk::HBox *hboxAction = Gtk::manage(new class Gtk::HBox(false, 0));
    Gtk::VBox *vboxMain = Gtk::manage(new class Gtk::VBox(false, 0));

    labelAccount->set_alignment(0,0.5);
    labelAccount->set_use_markup(true);

    labelPasswd->set_alignment(0,0.5);
    labelPasswd->set_use_markup(true);
    labelPasswd->set_mnemonic_widget(*entryPasswd);

    entryAccount->set_max_length(10);
    entryPasswd->set_visibility(false);
    entryPasswd->set_max_length(16);
    entryPasswd->set_text("");



    tableLogin->set_border_width(10);
    tableLogin->set_row_spacings(5);
    tableLogin->set_col_spacings(5);
    tableLogin->attach(*labelAccount, 0, 1, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
    tableLogin->attach(*labelPasswd, 0, 1, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
    tableLogin->attach(*entryAccount, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::FILL, 0, 0);
    tableLogin->attach(*entryPasswd, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);

    buttonCancel->set_relief(Gtk::RELIEF_HALF);

    buttonConnect->set_relief(Gtk::RELIEF_HALF);
    buttonConnect->set_flags(Gtk::CAN_DEFAULT);

    hboxAction->pack_start(*buttonCancel);
    hboxAction->pack_start(*buttonConnect);

    vboxMain->pack_start(*tableLogin);
    vboxMain->pack_start(*hboxAction, Gtk::PACK_SHRINK, 0);

    loginWindow->set_title("登录");
    loginWindow->set_modal(false);
    loginWindow->property_window_position().set_value(Gtk::WIN_POS_CENTER_ALWAYS);
    loginWindow->set_resizable(false);
    loginWindow->property_destroy_with_parent().set_value(false);
    loginWindow->add(*vboxMain);

    //buttonConnect->set_sensitive(false);
    loginWindow->show_all();

    buttonCancel->add_accelerator("clicked",
	    gmm_data->getAccelGroup(), GDK_Escape, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
    buttonConnect->add_accelerator("clicked",
	    gmm_data->getAccelGroup(), GDK_Return, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
    buttonConnect->add_accelerator("clicked",
	    gmm_data->getAccelGroup(), GDK_KP_Enter, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);


    buttonConnect->signal_clicked().connect(
		    sigc::mem_fun(*this,&LoginWindow::on_loginWindow_ok));

    buttonCancel->signal_clicked().connect(
		    sigc::mem_fun(*this, &LoginWindow::on_loginWindow_cancel));
}

LoginWindow::~LoginWindow()
{
    delete gmm_data;
}

bool LoginWindow::on_delete_event(GdkEventAny*)
{
    parent.on_loginWindow_cancel();
}

void LoginWindow::on_loginWindow_cancel()
{
}

void LoginWindow::on_loginWindow_ok()
{
	parent.login();
	this->hide();

}
