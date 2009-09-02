/*
 * =====================================================================================
 *
 *       Filename:  xwebkit.cc
 *
 *    Description:  webkit for show message wdiget
 *
 *        Version:  1.0
 *        Created:  2009年05月22日 11时52分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include <sys/stat.h>
#include <string.h>
#include "xwebkit.h"
#include <cstdio>
#include <webkit/webkit.h>


XWebkit::XWebkit(const std::string& from):
		 header_html(NULL),
		 footer_html(NULL),
		 template_html(NULL),
		 incoming_content_html(NULL),
		 outgoing_content_html(NULL),
		 incoming_next_content_html(NULL),
		 outgoing_next_content_html(NULL),
		 status_html(NULL),
		 style_dir (NULL),
		 template_path (NULL),
		 css_path (NULL),
		 template_html_len(0),
		 header_html_len(0),
		 footer_html_len(0),
		 incoming_content_html_len(0),
		 outgoing_content_html_len(0),
		 incoming_next_content_html_len(0),
		 outgoing_next_content_html_len(0),
		 status_html_len(0),
		 basestyle_css_len(0)
		 ,old_flags(MESSAGE_NULL)

{
	
	  size_t pos = from.find("@");
	  m_id = from.substr(0, pos);;
	  
	//tbutton = Gtk::manage(new Gtk::Button("test"));
	//tbutton->signal_clicked().connect(sigc::mem_fun(*this,&XWebkit::on_button_clicked));

	webkit_ = webkit_web_view_new(); 
	Gtk::Widget* kit = Glib::wrap(webkit_);
	
	pack_start(*Gtk::manage(kit), true, true);
	//pack_start(*tbutton,false,false);

	init_webkit();
	show_all();
}

XWebkit::~XWebkit()
{
	g_free(template_html);
	g_free(header_html);
	g_free(footer_html);
	g_free(incoming_content_html);
	g_free(outgoing_content_html);
	g_free(incoming_next_content_html);
	g_free(outgoing_next_content_html);
	g_free(status_html);
	g_free(style_dir);
	g_free(template_path);
	g_free(css_path);
	g_free(basestyle_css);
	printf("delete XWebkit \n");
	gtk_widget_destroy(webkit_);
}

bool XWebkit::init_webkit()
{
	char *header, *footer;
	char *template_;	
	char *file;
	const char* message_style="renkoo.AdiumMessageStyle";

	style_dir = g_build_filename(purple_user_dir(), "message_styles", message_style, NULL);
	template_path = g_build_filename(style_dir, "Contents", "Resources",
						"Template.html", NULL);

	printf("template_path  = %s\n",template_path);
	if (!g_file_get_contents(template_path, &template_html,
					&template_html_len, NULL)) {
		purple_debug_info("WebKit", "No custom Template.html, falling back"
						" to default Template.html\n");
		g_free(template_path);
		purple_debug_info("WebKit", "Using default Template.html\n");
		template_path = g_build_filename(purple_user_dir(), "message_styles", "Template.html", NULL);
		if (!g_file_get_contents(template_path, &template_html,
						&template_html_len, NULL)) {
			purple_debug_info("WebKit","Can't open default "
							"Template.html!\n");
			g_free(style_dir); style_dir = NULL;
			g_free(template_path); template_path = NULL;
			return false;
		}
	} else {
		purple_debug_info("WebKit", "Using custom Template.html\n");
	}

	file = g_build_filename(style_dir, "Contents", "Resources",
				"Header.html", NULL);
	if(!g_file_get_contents(file, &header_html, &header_html_len, NULL)) {
		purple_debug_info("WebKit","No Header.html\n");
	}
	g_free(file);
	file = g_build_filename(style_dir, "Contents", "Resources",
				"Footer.html", NULL);
	if(!g_file_get_contents(file, &footer_html, &footer_html_len, NULL)) {
		purple_debug_info("WebKit","No Footer.html\n");
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources", "Incoming",
				"Content.html", NULL);
	if (!g_file_get_contents(file, &incoming_content_html,
					&incoming_content_html_len, NULL)) {
		purple_debug_info("WebKit", "Can't open Incoming/Content.html\n");
		g_free(style_dir); style_dir = NULL;
		g_free(template_path); template_path = NULL;
		g_free(header_html); header_html = NULL;
		g_free(footer_html); footer_html = NULL;
		g_free(file);
		return false;
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources", "Incoming",
				"NextContent.html", NULL);
	if (!g_file_get_contents(file, &incoming_next_content_html,
					&incoming_next_content_html_len, NULL)) {
		incoming_next_content_html = g_strdup(incoming_content_html);
		incoming_next_content_html_len = incoming_content_html_len;
		purple_debug_info("WebKit", "No Incoming/NextContent.html\n");
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources", "Outgoing",
				"Content.html", NULL);
	if (!g_file_get_contents(file, &outgoing_content_html,
					&outgoing_content_html_len, NULL)) {
		outgoing_content_html = g_strdup(incoming_content_html);
		outgoing_content_html_len = incoming_content_html_len;
		purple_debug_info("WebKit", "No Outgoing/Content.html\n");
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources", "Outgoing",
				"NextContent.html", NULL);
	if (!g_file_get_contents(file, &outgoing_next_content_html,
				  &outgoing_next_content_html_len, NULL)) {
		outgoing_next_content_html = g_strdup(outgoing_content_html);
		outgoing_next_content_html_len = outgoing_content_html_len;
		purple_debug_info("WebKit", "No Outgoing/NextContent.html\n");
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources",
				"Status.html", NULL);
	if (!g_file_get_contents(file, &status_html, &status_html_len, NULL)) {
		purple_debug_info("WebKit", "Can't open Status.html\n");
		g_free(style_dir); style_dir = NULL;
		g_free(template_path); template_path = NULL;
		g_free(header_html); header_html = NULL;
		g_free(footer_html); footer_html = NULL;
		g_free(incoming_content_html); incoming_content_html = NULL;
		g_free(incoming_next_content_html); incoming_next_content_html = NULL;
		g_free(outgoing_content_html); outgoing_content_html = NULL;
		g_free(outgoing_next_content_html); outgoing_next_content_html = NULL;
		g_free(file);
		return false;
	}
	g_free(file);

	file = g_build_filename(style_dir, "Contents", "Resources",
					"main.css", NULL);
	if(!g_file_get_contents(file, &basestyle_css, &basestyle_css_len, NULL)) {
		purple_debug_info("WebKit", "Can't open main.css!\n");
	}

	/** this can set other css file*/
	css_path = g_build_filename(style_dir, "Contents", "Resources",
					"main.css", NULL);
	//css_path = g_build_filename(style_dir, "Contents", "Resources","Variant",
	//				"Green on Steel.css", NULL);
	purple_debug_info("WebKit", "css_path: %s\n", css_path);


	header = replace_header_tokens(header_html, header_html_len);
	footer = replace_header_tokens(footer_html, footer_html_len);
	template_ = replace_template_tokens(template_html,
				template_html_len + header_html_len,
				header, footer);
	//printf("######### %s\n",template_);
//	webkit_web_view_load_string(WEBKIT_WEB_VIEW(webkit_), template_,
//				"text/html", "UTF-8", template_path);



	char *dir = get_dir_for_tempfile();
	mkdir(dir, 0755);
	g_free(dir);

	char *filename = get_full_path_for_tempfile();
	FILE *fp = fopen(filename, "w");
	fwrite(template_, strlen(template_), sizeof (char), fp);
	fclose(fp);
	g_free(filename);

	char *url = get_file_uri_for_tempfile();
	webkit_web_view_open(WEBKIT_WEB_VIEW(webkit_), url);
	g_free(url);

}

void XWebkit::webkit_write_conv(const char*name,const char* alias,
		const char* message, MessageFlags flags,time_t mtime)
{
	char *message_html;
	char *msg;
	const char *func = "appendMessage";
	switch(flags){
		case MESSAGE_SYSTEM:
			message_html=status_html;
			break;
		case MESSAGE_SEND:
			if(old_flags == MESSAGE_SEND){
				message_html=outgoing_next_content_html;
				func = "appendNextMessage";
			}
			else{
				message_html = outgoing_content_html;
			}
			break;
		case MESSAGE_RECV:
			if(old_flags == MESSAGE_RECV){
				message_html = incoming_next_content_html;
				func = "appendNextMessage";
			}
			else
				message_html=incoming_content_html;
			break;
		default:
			message_html=status_html;
			break;
	}
	msg = replace_message_tokens(message_html,0,name,alias,message,flags,mtime);
	char* escape = escape_message(msg);
	char* script = g_strdup_printf("%s(\"%s\")", func, escape);

	//printf(" ###### %s\n",escape);
	//char* test_ = "appendMessage(\"test script\")";
	//webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webkit_), test_);
	webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webkit_), script);
	old_flags = flags;

	g_free(msg);
	g_free(script);
	g_free(escape);

}

char* XWebkit::replace_message_tokens(char* text,gsize len,const char* name,
		const char* alias,const char* message,MessageFlags flags, time_t mtime)
{

	GString *str = g_string_new_len(NULL, len);
	char *cur = text;
	char *prev = cur;

	purple_debug_info("WebKit","replace_message_tokens\n");

	while ((cur = strchr(cur, '%'))) {
		char *replace = NULL;
		char *fin = NULL;
			
		if (!strncmp(cur, "%message%", strlen("%message%"))) {
			replace = g_strdup(message);
		} else if (!strncmp(cur, "%messageClasses%",
				    strlen("%messageClasses%"))) {
			replace = g_strdup(flags == MESSAGE_SEND ? "outgoing" :
				  flags == MESSAGE_RECV ? "incoming" :
				  "event");
		} else if (!strncmp(cur, "%shortTime%", strlen("%shortTime%"))) {
			replace = g_strdup(purple_utf8_strftime("%H:%M", NULL));
		} else if (!strncmp(cur, "%time", strlen("%time"))) {
			char *format = NULL;
			if (*(cur + strlen("%time")) == '{') {
				char *start = cur + strlen("%time") + 1;
				char *end = strstr(start, "}%");
				if (!end) /* Invalid string */
					continue;
				format = g_strndup(start, end - start);
				fin = end + 1;
			}
			if(format) {
				replace = g_strdup(purple_utf8_strftime(format, NULL));
			} else {
				replace = g_strdup(purple_utf8_strftime("%X",NULL));
			}
			g_free(format);
		} else if (!strncmp(cur, "%userIconPath%",
					strlen("%userIconPath%"))) {
			if (flags == MESSAGE_SEND) {
				if (replace == NULL || !g_file_test(replace,
							G_FILE_TEST_EXISTS)) {
					replace = g_build_filename(style_dir,
								"Contents",
								"Resources",
								"Outgoing",
								"buddy_icon.png",
								NULL);
				}
				purple_debug_info("WebKit", "userIconPath, outgoing = \"%s\"\n", replace);
			} else if (flags == MESSAGE_RECV) {
				if (replace == NULL || !g_file_test(replace, G_FILE_TEST_EXISTS)) {
					replace = g_build_filename(style_dir,
								"Contents",
								"Resources",
								"Incoming",
								"buddy_icon.png",
								NULL);
				}
				purple_debug_info("WebKit", "userIconPath, incoming = \"%s\"\n", replace);
			}
		} else if (!strncmp(cur, "%senderScreenName%",
					strlen("%senderScreenName%"))) {
			replace = g_strdup(name);
		} else if (!strncmp(cur, "%sender%", strlen("%sender%"))) {
			replace = g_strdup(alias);
		} else if (!strncmp(cur, "%service%", strlen("%service%"))) {
			replace = g_strdup("talkmm");
		} else {
			cur++;
			continue;
		}

		/* Here we have a replacement to make */
		g_string_append_len(str, prev, cur - prev);
		g_string_append(str, replace);

		g_free(replace);

		/* And update the pointers */
		if (fin) {
			prev = cur = fin + 1;	
		} else {
			prev = cur = strchr(cur + 1, '%') + 1;
		}

	}
	
	/* And wrap it up */
	g_string_append(str, prev);
	return g_string_free(str, FALSE);


}


char* XWebkit::replace_header_tokens(char *text, gsize len)
{
	GString *str = g_string_new_len(NULL, len);
	char *cur = text;
	char *prev = cur;
	char *full_icon_path = NULL;

	purple_debug_info("WebKit","replace_header_tokens\n");

	if (text == NULL)
		return NULL;

	while ((cur = strchr(cur, '%'))) {
		char *replace = NULL;
		char *fin = NULL;

  		if (!strncmp(cur, "%chatName%", strlen("%chatName%"))) {
				//replace = g_strdup("chat-mm");
				replace = g_strdup(m_id.c_str());
  		} else if (!strncmp(cur, "%sourceName%",
					strlen("%sourceName%"))) {
			replace = g_strdup("lerosua");
  		} else if (!strncmp(cur, "%destinationName%",
					strlen("%destinationName%")) ||
				!strncmp(cur, "%destinationDisplayName%",
					strlen("%destinationDisplayName%"))) {
				replace = g_strdup("lerosua");
  		} else if (!strncmp(cur, "%incomingIconPath%", strlen("%incomingIconPath%"))) {
			if (replace == NULL || !g_file_test(replace, G_FILE_TEST_EXISTS)) {
				replace = g_build_filename(style_dir,
							"Contents",
							"Resources",
							"incoming_icon.png",
							NULL);
			}
			purple_debug_info("WebKit", "userIconPath, incoming = \"%s\"\n", replace);
 		} else if (!strncmp(cur, "%outgoingIconPath%", strlen("%outgoingIconPath%"))) {
			if (replace == NULL || !g_file_test(replace,
						G_FILE_TEST_EXISTS)) {
				replace = g_build_filename(style_dir,
							"Contents",
							"Resources",
							"outgoing_icon.png",
							NULL);
			}
			purple_debug_info("WebKit", "userIconPath, outgoing = \"%s\"\n", replace);
  		} else if (!strncmp(cur, "%timeOpened",
					strlen("%timeOpened"))) {
			char *format = NULL;
			if (*(cur + strlen("%timeOpened")) == '{') {
				char *start = cur + strlen("%timeOpened") + 1;
				char *end = strstr(start, "}%");
				if (!end) /* Invalid string */
					continue;
				format = g_strndup(start, end - start);
				fin = end + 1;
			} 
			replace = g_strdup(purple_utf8_strftime(format ? format : "%X", NULL));
			g_free(format);
		} else {
			continue;
		}

		/* Here we have a replacement to make */
		g_string_append_len(str, prev, cur - prev);
		g_string_append(str, replace);

		g_free(replace);

		/* And update the pointers */
		if (fin) {
			prev = cur = fin + 1;	
		} else {
			prev = cur = strchr(cur + 1, '%') + 1;
		}
	}
	
	/* And wrap it up */
	g_string_append(str, prev);
	return g_string_free(str, FALSE);
}


char* XWebkit::replace_template_tokens(char *text, int len, char *header, char *footer) 
{
	GString *str = g_string_new_len(NULL, len);

	char **ms = g_strsplit(text, "%@", 6);

	purple_debug_info("WebKit","replace_template_tokens\n");

	if (ms[0] == NULL || ms[1] == NULL || ms[2] == NULL || ms[3] == NULL ||
	    ms[4] == NULL/* || ms[5] == NULL*/) {
		purple_debug_info("WebKit","Error in template_!\n");
		g_strfreev(ms);
		g_string_free(str, TRUE);
		return NULL;
	}

	g_string_append(str, ms[0]);
	/* Root directory for the message style */
	g_string_append(str, style_dir);
	g_string_append(str, ms[1]);

	if(ms[5] != NULL) {
		/* Things are like in default template_ */
		if (basestyle_css) {
			/* main.css */
			g_string_append(str, basestyle_css);
		}
		g_string_append(str, ms[2]);

		if (css_path) {
			/* Variant path */
			g_string_append(str, css_path);
		}
		g_string_append(str, ms[3]);

		if (header) {
			/* Header html */
			g_string_append(str, header);
		}
		g_string_append(str, ms[4]);

		if (footer) {
			/* Footer html */
			g_string_append(str, footer);
		}
		g_string_append(str, ms[5]);
	} else {
		/* No place for basestyle_css, seen this in custom templates */
		if (css_path) {
			/* Variant path */
			g_string_append(str, css_path);
		}
		g_string_append(str, ms[2]);

		if (header) {
			/* Header html */
			g_string_append(str, header);
		}
		g_string_append(str, ms[3]);

		if (footer) {
			/* Footer html */
			g_string_append(str, footer);
		}
		g_string_append(str, ms[4]);
	}
	
	g_strfreev(ms);
	return g_string_free(str, FALSE);
}



size_t XWebkit::purple_internal_strftime(char *s, size_t max, const char *format, const struct tm *tm)
{
	const char *start;
	const char *c;
	char *fmt = NULL;

	/* Yes, this is checked in purple_utf8_strftime(),
	 * but better safe than sorry. -- rlaager */
	g_return_val_if_fail(format != NULL, 0);

	/* This is fairly efficient, and it only gets
	 * executed on Windows or if the underlying
	 * system doesn't support the %z format string,
	 * for strftime() so I think it's good enough.
	 * -- rlaager */
	for (c = start = format; *c ; c++)
	{
		if (*c != '%')
			continue;

		c++;

	}

	if (fmt != NULL)
	{
		size_t ret;

		if (*start)
		{
			char *tmp = g_strconcat(fmt, start, NULL);
			g_free(fmt);
			fmt = tmp;
		}

		ret = strftime(s, max, fmt, tm);
		g_free(fmt);

		return ret;
	}

	return strftime(s, max, format, tm);
}

const char *
XWebkit::purple_utf8_strftime(const char *format, const struct tm *tm)
{
	static char buf[128];
	char *locale;
	GError *err = NULL;
	int len;
	char *utf8;

	g_return_val_if_fail(format != NULL, NULL);

	if (tm == NULL)
	{
		time_t now = time(NULL);
		tm = localtime(&now);
	}

	locale = g_locale_from_utf8(format, -1, NULL, NULL, &err);
	if (err != NULL)
	{
		fprintf(stderr, "Format conversion failed in purple_utf8_strftime(): %s\n", err->message);
		g_error_free(err);
		locale = g_strdup(format);
	}

	/* A return value of 0 is either an error (in
	 * which case, the contents of the buffer are
	 * undefined) or the empty string (in which
	 * case, no harm is done here). */
	if ((len = purple_internal_strftime(buf, sizeof(buf), locale, tm)) == 0)
	{
		g_free(locale);
		return "";
	}

	g_free(locale);

	utf8 = g_locale_to_utf8(buf, len, NULL, NULL, &err);
	if (err != NULL)
	{
		fprintf(stderr, "Result conversion failed in purple_utf8_strftime(): %s\n", err->message);
		g_error_free(err);
	}
	else
	{
		g_strlcpy(buf, utf8, sizeof(buf));
		g_free(utf8);
	}

	return buf;
}

/* Returns the argument passed to -c IFF it was present, or ~/.purple. */
const char * XWebkit::purple_user_dir(void)
{
	return  g_build_filename(g_get_home_dir(), ".purple", NULL);
}


void XWebkit::test()
{
//	char* path = g_build_filename(style_dir, "Contents", "Resources", "main.css", NULL);
//	char* script = g_strdup_printf("setStylesheet(\"baseStyle\", \"%s\")", path);
//	g_free(path);
//	webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webkit_), script);
//	g_free(script);

	webkit_write_conv("lerosua","lerosua@gmail.com","test for talkmm",MESSAGE_RECV,time(0));
	webkit_write_conv("wind","xihels@gmail.com","reply for you",MESSAGE_SEND,time(0));
}

//void XWebkit::add_message(const std::string& name, const std::string& mail,const std::string& msg, MessageFlags MSG_TYPE)
void XWebkit::add_message(const char* name, const char* mail,const char* msg, MessageFlags MSG_TYPE)
{

	//webkit_write_conv(name.c_str(),mail.c_str(),msg.c_str(),MSG_TYPE,time(0));
	webkit_write_conv(name,mail,msg,MSG_TYPE,time(0));
}
void XWebkit::purple_debug_info(const char* category,const char* fmt, ...)
{
	return;
	char* arg_s=NULL;
	va_list args;
	g_return_if_fail(fmt !=NULL);
	va_start(args,fmt);
	arg_s = g_strdup_vprintf(fmt,args);
	g_print("%s\n",arg_s);

	va_end(args);


}



char* XWebkit::escape_message(char *text)
{
	GString *str = g_string_new(NULL);
	char *cur = text;
	int smileylen = 0;

	purple_debug_info("WebKit","escape_message\n");

	while (cur && *cur) {
		switch (*cur) {
		case '\\':
			g_string_append(str, "\\\\");	
			break;
		case '\"':
			g_string_append(str, "\\\"");
			break;
		case '\r':
			g_string_append(str, "<br/>");
			break;
		case '\n':
			break;
		default:
				g_string_append_c(str, *cur);
				break;
		}
		cur++;
	}
	return g_string_free(str, FALSE);
}



char* XWebkit::get_dir_for_tempfile()
{
	return g_strconcat("/tmp/webkit-talkmm-", getenv("USER"), NULL);
}


char* XWebkit::get_full_path_for_tempfile()
{
	//const char *name = "test_test.org.html";
	char *name = get_filename_for_template();
	char *dir = get_dir_for_tempfile();
	char *path = g_strconcat(dir, "/", name, NULL);
	g_free(name);
	g_free(dir);
	return path;
}


char* XWebkit::get_file_uri_for_tempfile()
{
	char *name = get_filename_for_template();
	char *dir = get_dir_for_tempfile();
	char *escaped = g_uri_escape_string 
		(name, G_URI_RESERVED_CHARS_ALLOWED_IN_USERINFO, TRUE);
	char *result = g_strconcat("file://", dir, "/", escaped, NULL);

	g_free(name);
	g_free(dir);
	g_free(escaped);
	return result;
}


char* XWebkit::get_filename_for_template()
{

	char *name = g_uri_escape_string 
		(m_id.c_str(), G_URI_RESERVED_CHARS_ALLOWED_IN_USERINFO, TRUE);
	char *tmp =  g_strconcat(name , ".html", NULL);
	g_free(name);
	return tmp;
}

void XWebkit::on_button_clicked()
{
	test();
}
