/*
 * xxpalk call example
 * Copyright 2004--2005, Google Inc.
 *
 * Modified by XIONG Qin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CRICKET_EXAMPLES_CALL_CONSOLE_H__
#define CRICKET_EXAMPLES_CALL_CONSOLE_H__

#include <stdio.h>
#include "talk/base/thread.h"
#include "talk/base/messagequeue.h"


class CallClient;
class MainWindow;

enum {
	MSG_START,
	MSG_INPUT,
};

class Console : public talk_base::MessageHandler {
 public:
  Console(talk_base::Thread *thread, CallClient *client,MainWindow* win, int port);
  virtual void OnMessage(talk_base::Message *msg);
  void SetPrompt(const char *prompt) {
	  prompt_ = prompt ? std::string(prompt) : std::string("xxpalk");
  }
  void SetPrompting(bool prompting) {
    prompting_ = prompting;
    if (prompting)
	  printf("\n(%s) ", prompt_.c_str());
    }
  bool prompting() {return prompting_;}

  void Close();
  void Send(const char* str);
  void Send(const std::string& str);
  std::string Receive();
  void Print(const char* str);
  void Print(const std::string& str);
  void Printf(const char* format, ...);
  void OnSignOn();

  bool b_with_ui;

 private:
  CallClient *client_;
  MainWindow* main_window;
  talk_base::Thread *client_thread_;
  void StartConsole();
  void ParseLine(std::string &str);
  std::string prompt_;
  bool prompting_;
  int new_sock_fd_;
  int sock_fd_;
  
};

#endif // CRICKET_EXAMPLES_CALL_CONSOLE_H__

