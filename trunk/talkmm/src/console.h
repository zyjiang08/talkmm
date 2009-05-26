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
#include "talk/login/status.h"


class CallClient;
class MainWindow;

enum {
	MSG_START,
	MSG_INPUT,
	MSG_CALL,
	MSG_CALL_ANSWER,
	MSG_CALL_HANGUP,
	MSG_FILE_CANCEL,
	MSG_FILE_ANSWER,
	MSG_FILE_SETDIR,
};

class Console:public talk_base::MessageHandler {
      public:
	Console(talk_base::Thread * thread, CallClient * client,
		MainWindow * win);
	virtual void OnMessage(talk_base::Message * msg);
	void SetPrompt(const char *prompt) {
		prompt_ =
		    prompt ? std::string(prompt) : std::string("talkmm");
	} void SetPrompting(bool prompting) {
		prompting_ = prompting;
		if (prompting)
			printf("\n(%s) ", prompt_.c_str());
	}
	bool prompting() {
		return prompting_;
	}

	void Close();
	void Send(const char *str);
	void Send(const std::string & str);
	std::string Receive();
	void Print(const char *str);
	void Print(const std::string & str);
	void Printf(const char *format, ...);
	void OnSignOn();
	void OnSignError(const std::string& error);
	//void RosterPresence(const std::string& jid);
	void OnRosterPresence(const buzz::Status & status_);
	void OnRecuMessage(const std::string & from,
			   const std::string & message);
	void SendMessage(const std::string & to,
			 const std::string & message);
	void OnFileRecu(const std::string & from,
			const std::string & file);
	void OnIncomingCall(const std::string & from);
	void OnHangupCall(const std::string & from);
	void OnFileTransferStatue(const std::string& type,const std::string& statue,const std::string& jid);
	void OnCallStatue(const std::string& jid,const std::string& statue);
	//void OnFileProgress(const std::string& jid, const std::string& file,float percent);
	void OnFileProgress(const std::string& jid,const std::string& file,
				     float percent, const std::string& describe);
	void SetRecvFileDir(const std::string& dir);


	void AnswerFile(const std::string& accept = "true");
	void AnswerCall(const std::string& accept = "true");
	void MakeCallTo(const std::string & to);
	void HangupCall(const std::string & to);

	void SendFile(const std::string & to, const std::string & file);
	void CancelSendFile(const std::string& to);
	void SendStatus(int,const std::string& status);

      private:
	CallClient * client_;
	MainWindow *main_window;
	talk_base::Thread * client_thread_;
	void StartConsole();
	void ParseLine(std::string & str);
	std::string prompt_;
	bool prompting_;

};

#endif				// CRICKET_EXAMPLES_CALL_CONSOLE_H__
