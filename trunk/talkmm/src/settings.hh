/* ccgo: settings.cc
 * 
 * Copyright 2002,2003 Chun-Chung Chen <cjj@u.washington.edu>
 * 
 * This program is free software; you can redistribute it and'or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef SETTINGS_HH
#define SETTINGS_HH
#include <string>
#include <gconfmm/client.h>
namespace talkmm
{
	class Settings
	{
		Glib::RefPtr<Gnome::Conf::Client> client;

		static const std::string main_path;
		static const int version_serial;

		bool dump_igs;
		bool leak_raw;
		bool client_time_control;

		bool pop_players_on_tell;
		bool pop_players_on_stats;
		bool pop_players_on_match;

		bool get_stats_on_pop;

		bool show_coordinate;
		bool picture_stone;
		bool picture_board;

		std::string image_path;
		bool igs_direct;
		std::string igs_telnet;
		std::string igs_host;
		int igs_port;
	public:
		enum Options {
			OPT_DUMP_IGS,
			OPT_LEAK_RAW,
			OPT_CLIENT_TIME_CONTROL,

			OPT_POP_PLAYERS_ON_TELL,
			OPT_POP_PLAYERS_ON_STATS,
			OPT_POP_PLAYERS_ON_MATCH,

			OPT_GET_STATS_ON_POP,

			OPT_SHOW_COORDINATE,
			OPT_PICTURE_STONE,
			OPT_PICTURE_BOARD,

			OPT_IGS_DIRECT
		};

		Settings();
		void init();
		void set_default();
		void reset();
		void command_line(int, char * [], char * []);

		const std::string get_string(const std::string &);
		void set_string(const std::string &, const std::string &);

		int get_int(const std::string &);
		void set_int(const std::string &, int);

		bool get_option(Options);
		void set_option(Options, bool);

		const std::string & get_image_path();
		void set_image_path(const std::string &);

		const std::string & get_igs_telnet();
		void set_igs_telnet(const std::string &);

		const std::string & get_igs_host();
		void set_igs_host(const std::string &);

		int get_igs_port();
		void set_igs_port(int);
	};

	extern Settings settings;
}
#endif // SETTINGS_HH
