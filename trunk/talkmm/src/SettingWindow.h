#ifndef  SETTING_WINDOW_FILE_HEADER_INC
#define  SETTING_WINDOW_FILE_HEADER_INC

#include <gtkmm.h>

#define setting_ui DATA_DIR"/setting_window.glade"

//class MsgBox;
class XWebkit;
class MainWindow;
class SettingWindow: public Gtk::Window
{
	public:
		SettingWindow(MainWindow* f_parent);
		~SettingWindow();
		void xx(const std::string& msg);

	protected:
		;
	private:
		GBuilderXML				setting_xml;
		MainWindow*				m_parent;
		std::string				m_jid;
};
#endif
