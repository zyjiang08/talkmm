/* ccgo: settings.cc
 *
 * Copyright 2002,2003 Chun-Chung Chen <cjj@u.washington.edu>
 *
 * This program is free software; you can redistribute it and'or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include "settings.hh"
#include "ccgo.hh"
#include <gconfmm/init.h>
#include <gtkmm/stock.h>
#include <iostream>

using namespace talkmm;

Settings talkmm::settings;

const std::string Settings::main_path = "/apps/talkmm";

const int Settings::version_serial = 6;

Settings::Settings()
{
}

void Settings::init()
{
	Gnome::Conf::init();
	client = Gnome::Conf::Client::get_default_client();
	set_default();
}

void Settings::set_default()
{
	client->add_dir(main_path);
	int v = client->get_int(main_path + "/version-serial");
	if (v < version_serial) { // setup defaults

		if (v < 2) client->set(main_path + "/dump-igs", false);
		if (v < 2) client->set(main_path + "/leak-raw", true);
		if (v < 3) client->set(main_path + "/client-time-control", true);

		if (v < 3) client->set(main_path + "/pop-players-on-tell", true);
		if (v < 3) client->set(main_path + "/pop-players-on-stats", true);
		if (v < 3) client->set(main_path + "/pop-players-on-match", true);

		if (v < 3) client->set(main_path + "/get-stats-on-pop", false);

		if (v < 3) client->set(main_path + "/show-coordinate", true);

		if (v < 3) client->set(main_path + "/picture-stone", true);
		if (v < 3) client->set(main_path + "/picture-board", true);

		if (v < 3) client->set(main_path + "/image-path", Glib::ustring(CCGO_DEFAULT_IMAGEDIR));
		if (v < 3) client->set(main_path + "/igs-telnet", Glib::ustring("telnet igs.joyjoy.net 6969"));
		if (v < 3) client->set(main_path + "/igs-direct", true);
		if (v < 3) client->set(main_path + "/igs-host", Glib::ustring("igs.joyjoy.net"));
		if (v < 3) client->set(main_path + "/igs-port", 6969);

		if (v < 3) client->set(main_path + "/white-program-path", Glib::ustring(CCGO_DEFAULT_BINDIR) + "/gnugo");
		if (v < 3) client->set(main_path + "/black-program-path", Glib::ustring(CCGO_DEFAULT_BINDIR) + "/gnugo");
		if (v < 3) client->set(main_path + "/default-name", Glib::ustring("guest"));
		if (v < 3) client->set(main_path + "/default-pass", Glib::ustring(""));
		if (v < 3) client->set(main_path + "/who-filter", Glib::ustring("5d-9p"));
		if (v < 3) client->set(main_path + "/igs-win-width", 300);
		if (v < 3) client->set(main_path + "/igs-win-height", 200);
		if (v < 3) client->set(main_path + "/igs-gamelist-width", 200);
		if (v < 3) client->set(main_path + "/igs-gamelist-height", 300);
		if (v < 3) client->set(main_path + "/igs-playerlist-width", 400);
		if (v < 3) client->set(main_path + "/igs-playerlist-height", 300);
		if (v < 3) client->set(main_path + "/igs-show-width", 320);
		if (v < 3) client->set(main_path + "/igs-show-height", 360);

		if (v < 5) client->set(main_path + "/part-win-width", 360);
		if (v < 5) client->set(main_path + "/part-win-height", 400);

		if (v < 4) client->set(main_path + "/match-board-size", 19);
		if (v < 4) client->set(main_path + "/match-main-time", 1);
		if (v < 4) client->set(main_path + "/match-byo-time", 10);

		if (v < 6) client->set(main_path + "/gtk-win-width", 310);
		if (v < 6) client->set(main_path + "/gtk-win-height", 350);
		if (v < 6) client->set(main_path + "/gtk-win-paned", 250);

		client->set(main_path + "/version-serial", version_serial);
	}

	dump_igs = client->get_bool(main_path + "/dump-igs");
	leak_raw = client->get_bool(main_path + "/leak-raw");
	client_time_control = client->get_bool(main_path + "/client-time-control");

	pop_players_on_tell = client->get_bool(main_path + "/pop-players-on-tell");
	pop_players_on_stats = client->get_bool(main_path + "/pop-players-on-stats");
	pop_players_on_match = client->get_bool(main_path + "/pop-players-on-match");

	get_stats_on_pop = client->get_bool(main_path + "/get-stats-on-pop");

	show_coordinate = client->get_bool(main_path + "/show-coordinate");
	picture_stone = client->get_bool(main_path + "/picture-stone");
	picture_board = client->get_bool(main_path + "/picture-board");

	image_path = client->get_string(main_path + "/image-path");

	igs_direct = client->get_bool(main_path + "/igs-direct");
	igs_telnet = client->get_string(main_path + "/igs-telnet");
	igs_host = client->get_string(main_path + "/igs-host");
	igs_port = client->get_int(main_path + "/igs-port");
}

void Settings::reset()
{
	client->set(main_path + "/version-serial", 0);
	client->remove_dir(main_path);
	set_default();
}

void Settings::command_line(int argc, char * argv[], char * envp[])
{
	for (int i = 0; i < argc; i ++) {
		std::string a(argv[i]);
		if (a == "dump_igs") {
			dump_igs = true;
		}
	}
}

const std::string Settings::get_string(const std::string & k)
{
	return client->get_string(main_path + "/" + k);
}

void Settings::set_string(const std::string & k, const std::string & n)
{
	client->set(main_path + "/" + k, Glib::ustring(n));
}

int Settings::get_int(const std::string & k)
{
	return client->get_int(main_path + "/" + k);
}

void Settings::set_int(const std::string & k, int i)
{
	client->set(main_path + "/" + k, i);
}

bool Settings::get_option(Options o)
{
	switch (o) {
	case OPT_DUMP_IGS:
		return dump_igs;
	case OPT_LEAK_RAW:
		return leak_raw;
	case OPT_CLIENT_TIME_CONTROL:
		return client_time_control;

	case OPT_POP_PLAYERS_ON_TELL:
		return pop_players_on_tell;
	case OPT_POP_PLAYERS_ON_STATS:
		return pop_players_on_stats;
	case OPT_POP_PLAYERS_ON_MATCH:
		return pop_players_on_match;

	case OPT_GET_STATS_ON_POP:
		return get_stats_on_pop;

	case OPT_SHOW_COORDINATE:
		return show_coordinate;
	case OPT_PICTURE_STONE:
		return picture_stone;
	case OPT_PICTURE_BOARD:
		return picture_board;

	case OPT_IGS_DIRECT:
		return igs_direct;
	}
	return false;
}

void Settings::set_option(Options o, bool b)
{
	switch (o) {
	case OPT_DUMP_IGS:
		if (dump_igs == b) return;
		dump_igs = b;
		client->set(main_path + "/dump-igs", b);
		break;
	case OPT_LEAK_RAW:
		if (leak_raw == b) return;
		leak_raw = b;
		client->set(main_path + "/leak-raw", b);
		break;
	case OPT_CLIENT_TIME_CONTROL:
		if (client_time_control == b) return;
		client_time_control = b;
		client->set(main_path + "/client-time-control", b);
		break;

	case OPT_POP_PLAYERS_ON_TELL:
		if (pop_players_on_tell == b) return;
		pop_players_on_tell = b;
		client->set(main_path + "/pop-players-on-tell", b);
		break;
	case OPT_POP_PLAYERS_ON_STATS:
		if (pop_players_on_stats == b) return;
		pop_players_on_stats = b;
		client->set(main_path + "/pop-players-on-stats", b);
		break;
	case OPT_POP_PLAYERS_ON_MATCH:
		if (pop_players_on_match == b) return;
		pop_players_on_match = b;
		client->set(main_path + "/pop-players-on-match", b);
		break;

	case OPT_GET_STATS_ON_POP:
		if (get_stats_on_pop == b) return;
		get_stats_on_pop = b;
		client->set(main_path + "/get-stats-on-pop", b);
		break;

	case OPT_SHOW_COORDINATE:
		if (show_coordinate == b) return;
		show_coordinate = b;
		client->set(main_path + "/show-coordinate", b);
		break;
	case OPT_PICTURE_STONE:
		if (picture_stone == b) return;
		picture_stone = b;
		client->set(main_path + "/picture-stone", b);
		break;
	case OPT_PICTURE_BOARD:
		if (picture_board == b) return;
		picture_board = b;
		client->set(main_path + "/picture-board", b);
		break;
	case OPT_IGS_DIRECT:
		if (igs_direct == b) return;
		igs_direct = b;
		client->set(main_path + "/igs-direct", b);
		break;
	}
}

const std::string & Settings::get_image_path()
{
	return image_path;
}

void Settings::set_image_path(const std::string & s)
{
	image_path = s;
	client->set(main_path + "/image-path", Glib::ustring(s));
}

const std::string & Settings::get_igs_telnet()
{
	return igs_telnet;
}

void Settings::set_igs_telnet(const std::string & s)
{
	igs_telnet = s;
	client->set(main_path + "/igs-telnet", Glib::ustring(s));
}

const std::string & Settings::get_igs_host()
{
	return igs_host;
}

void Settings::set_igs_host(const std::string & s)
{
	igs_host = s;
	client->set(main_path + "/igs-host", Glib::ustring(s));
}

int Settings::get_igs_port()
{
	return igs_port;
}

void Settings::set_igs_port(int p)
{
	igs_port = p;
}
