/*
 * Jingle talkmm example
 * Copyright 2004--2005, Google Inc.
 *
 * Modified by XIONG Qin for adding socket fonction to communicate with
 * other client 

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

#define _CRT_SECURE_NO_DEPRECATE 1

#include <cassert>
#include "talk/base/messagequeue.h"
#include "talk/base/stringutils.h"
#include "talk/examples/talkmm/console.h"
#include "talk/examples/talkmm/callclient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "string.h"
#include "MainWindow.h"

struct LockMutex {
	LockMutex() {
		gdk_threads_enter();
	} ~LockMutex() {
		gdk_threads_leave();
	}
};

Console::Console(talk_base::Thread * thread, CallClient * client, MainWindow * win):
client_thread_(thread), client_(client), prompt_(std::string("talkmm")),
prompting_(true), main_window(win)
{

}


void Console::Send(const char *str)
{
}

void Console::Send(const std::string & str)
{

}

std::string Console::Receive()
{

}

void Console::StartConsole()
{
	char buffer[256];
	std::string message;
	for (;;) {
//      fgets(buffer, sizeof(buffer), stdin);
		fgets(buffer, sizeof(buffer), stdin);
//		client_thread_->Post(this, MSG_INPUT,
//				     new talk_base::TypedMessageData <
//				     std::string > (buffer));
//
//
	}			//for
}

void Console::Close()
{
}

void Console::OnMessage(talk_base::Message * msg)
{
	talk_base::TypedMessageData < std::string > *data =
	    static_cast < talk_base::TypedMessageData <
	    std::string > *>(msg->pdata);
	switch (msg->message_id) {
	case MSG_START:
		StartConsole();
		break;
	case MSG_INPUT:
		client_->ParseLine(data->data());
		break;
	case MSG_CALL:
		client_->MakeCallTo(data->data());
		break;
	case MSG_CALL_HANGUP:
		client_->CancelCallTo(data->data());
		break;
	case MSG_FILE_CANCEL:
		client_->CancelSendFile(data->data());
		break;
	case MSG_CALL_ANSWER:
		client_->OnAnswerCall(data->data());
		break;
	case MSG_FILE_ANSWER:
		client_->OnAnswerFile(data->data());
		break;
	}
}


void Console::Print(const char *str)
{
	printf("\n%s", str);
	if (prompting_)
		printf("\n(%s) ", prompt_.c_str());
}

void Console::Print(const std::string & str)
{
	Print(str.c_str());
}

void Console::Printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	char buf[4096];
	int size = vsnprintf(buf, sizeof(buf), format, ap);
	assert(size >= 0);
	assert(size < static_cast < int >(sizeof(buf)));
	buf[size] = '\0';
	Print(buf);

	va_end(ap);
}

void Console::OnSignOn()
{
	LockMutex locked;
	main_window->on_signon();
}

void Console::OnSignError(const std::string& error)
{
	LockMutex locked;
	main_window->on_login_error(error);

}

void Console::OnRosterPresence(const buzz::Status & status_)
{
	LockMutex locked;
	main_window->on_roster_presence(status_);
}

void Console::OnFileRecu(const std::string & from,
			 const std::string & file)
{
	LockMutex locked;
	main_window->on_file_receive(from, file);
}

void Console::OnFileTransferStatue(const std::string & type,
				      const std::string & statue,
				      const std::string & jid)
{
	LockMutex locked;
	main_window->on_filetranser_statue(jid,statue);
}

void Console::OnCallStatue(const std::string& jid,const std::string& statue)
{
	LockMutex locked;
	main_window->on_calling_statue(jid,statue);

}
void Console::OnHangupCall(const std::string & from)
{
	LockMutex locked;
	main_window->on_hangup_call(from);
}

void Console::OnIncomingCall(const std::string & from)
{
	LockMutex locked;
	main_window->on_incoming_call(from);
}

void Console::OnRecuMessage(const std::string & from,
			    const std::string & message)
{
	LockMutex locked;
	main_window->on_receive_message(from, message);
}

void Console::OnFileProgress(const std::string& jid,const std::string& file,float percent, const std::string& describe)
{
	LockMutex locked;
	main_window->on_file_update_progress(jid, file, percent, describe);
}
void Console::SendMessage(const std::string & to,
			  const std::string & message)
{
	client_->SendTexte(to, message);

}

void Console::MakeCallTo(const std::string & name)
{
	client_thread_->Post(this, MSG_CALL, new talk_base::TypedMessageData < std::string > (name));
	return;
}

void Console::SendStatus(int show,const std::string& status)
{
	buzz::Status::Show show_ = (buzz::Status::Show) show;
	client_->SetPresence(show_,status);
}

void Console::SendFile(const std::string & to, const std::string & file)
{
	client_->SendFile(to, file);
}


//void Console::AnswerCall(bool accept)
void Console::AnswerCall(const std::string& accept)
{
	//client_->OnAnswerCall(accept);
	client_thread_->Post(this, MSG_CALL_ANSWER, new talk_base::TypedMessageData < std::string > (accept));
}

void Console::AnswerFile(const std::string& accept)
{
	//client_->OnAnswerFile(accept);
	client_thread_->Post(this, MSG_FILE_ANSWER, new talk_base::TypedMessageData < std::string > (accept));
}

void Console::CancelSendFile(const std::string& to)
{
	client_thread_->Post(this, MSG_FILE_CANCEL, new talk_base::TypedMessageData < std::string > (to));
}

void Console::HangupCall(const std::string & to)
{
	client_thread_->Post(this, MSG_CALL_HANGUP, new talk_base::TypedMessageData < std::string > (to));
}

