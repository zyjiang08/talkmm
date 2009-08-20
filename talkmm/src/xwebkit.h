/*
 * =====================================================================================
 *
 *       Filename:  xwebkit.h
 *
 *    Description:  webkit for show message wdiget
 *
 *        Version:  1.0
 *        Created:  2009年05月22日 11时57分27秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  lerosua@gmail.com
 *        Company:  Talkmm Team
 *
 * =====================================================================================
 */

#include <gtkmm.h>

enum MessageFlags {MESSAGE_SYSTEM,MESSAGE_SEND,MESSAGE_RECV,MESSAGE_NULL};
class XWebkit : public Gtk::Box {
	public:
		XWebkit(const std::string& f_id);
		~XWebkit();
		void test();
		bool init_webkit();
		char* replace_message_tokens(char* text,gsize len,const char* name,const char* alias,const char* message,MessageFlags flags, time_t mtime);
		char* replace_template_tokens(char *text, int len, char *header, char *footer);
		char* replace_header_tokens(char *text, gsize len);
		void webkit_write_conv(const char*name,const char* alias,
				const char* message, MessageFlags flags,time_t mtime);

		size_t purple_internal_strftime(char *s, size_t max, const char *format, const struct tm *tm);
		const char * purple_utf8_strftime(const char *format, const struct tm *tm);
		const char * purple_user_dir(void);

		char* escape_message(char *text);
		void purple_debug_info(const char* category,const char* fmt, ...);
		char* get_dir_for_tempfile();
		char* get_full_path_for_tempfile();
		char* get_filename_for_template();
		char* get_file_uri_for_tempfile();
		void on_button_clicked();
		//void add_message(const std::string& name, const std::string& mail,const std::string& msg, MessageFlags MSG_TYPE);
		void add_message(const char* name, const char* mail,const char* msg, MessageFlags MSG_TYPE);

	private:
		GtkWidget* webkit_;
		//Gtk::Button* tbutton;
		std::string m_id;
		char* header_html;
		char* footer_html;
		char* template_html;
		char* incoming_content_html;
		char* outgoing_content_html;
		char* incoming_next_content_html;
		char* outgoing_next_content_html;
		char* status_html;
		char* basestyle_css;

		gsize template_html_len;
		gsize header_html_len;
		gsize footer_html_len;
		gsize incoming_content_html_len;
		gsize outgoing_content_html_len;
		gsize incoming_next_content_html_len;
		gsize outgoing_next_content_html_len;
		gsize status_html_len;
		gsize basestyle_css_len;
		/* And their paths */
		char *style_dir ;
		char *template_path ;
		char *css_path ;
		MessageFlags old_flags;
};

