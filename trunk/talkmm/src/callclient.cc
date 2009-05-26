/*
 * XXPTalk example
 * Copyright 2004--2005, Google Inc.
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

#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <libgen.h>

#include "talk/xmpp/constants.h"
#include "talk/base/helpers.h"
#include "talk/base/thread.h"
#include "talk/base/network.h"
#include "talk/base/socketaddress.h"
#include "talk/p2p/base/sessionmanager.h"
#include "talk/p2p/client/httpportallocator.h"
#include "talk/p2p/client/sessionmanagertask.h"
#include "talk/session/phone/phonesessionclient.h"
#include "talk/login/jingleinfotask.h"
#include "callclient.h"
//#include "console.h"
//#include "fileclient.h"

namespace {

	const char *DescribeStatus(buzz::Status::Show show,
				   const std::string & desc) {
		switch (show) {
		case buzz::Status::SHOW_XA:
			return desc.c_str();
		case buzz::Status::SHOW_ONLINE:
			return "online";
		case buzz::Status::SHOW_AWAY:
			return "away";
		case buzz::Status::SHOW_DND:
			return "do not disturb";
		case buzz::Status::SHOW_CHAT:
			return "ready to chat";
		default:
			return "offline";
		}
	}

}				// namespace


const char *CALL_COMMANDS =
    "Available commands:\n"
    "\n"
    "  hangup  Ends the call.\n"
    "  mute    Stops sending voice.\n"
    "  unmute  Re-starts sending voice.\n"
    "  quit    Quits the application.\n" "";

const char *RECEIVE_COMMANDS =
    "Available commands:\n"
    "\n"
    "  accept  Accepts the incoming call and switches to it.\n"
    "  reject  Rejects the incoming call and stays with the current call.\n"
    "  quit    Quits the application.\n" "";

const char *FILE_COMMANDS =
    "Available commands:\n"
    "\n"
    "  receive Accepts the incoming file and save it.\n"
    "  cancel  Rejects the incoming file.\n"
    "  quit    Quits the application.\n" "";

const char *CONSOLE_COMMANDS =
    "Available commands:\n"
    "\n"
    "  roster       Prints the phonable friends from your roster.\n"
    "  OLRoster	Prints the online friends from your roster.\n"
    "  chat	id text	Send text to roster.\n"
    "  send	id file	Send file to roster.\n"
    "  call <name>  Initiates a call to the friend with the given name.\n"
    "  quit         Quits the application.\n" "";

void CallClient::ParseLine(const std::string & line)
{
	std::vector < std::string > words;

//  console_->Print(line);
	std::string templine = line;
	std::size_t found = templine.find_first_of(' ');
	if (found == std::string::npos) {
		words.push_back(templine);
	}			//if
	int index = 0;
	while (found != std::string::npos) {
		std::string temp = templine.substr(0, found);
		words.push_back(temp);
		temp = templine.substr(found + 1, std::string::npos);
		templine = temp;
		found = templine.find_first_of(' ');
		if ((found == std::string::npos) && (templine.size() != 0)) {
			words.push_back(templine);
			break;
		}		//if
	}			//while
	/* 
	   if(words.size() == 0)
	   console_->Send("size = 0\n");
	   if(words.size() == 1)
	   console_->Send("size = 1\n");
	   if(words.size() == 2)
	   console_->Send("size = 2\n");
	   if(words.size() >2 )
	   console_->Send("size > 2\n");

	   std::string message = line;
	   message += "\n";
	   console_->Send(message);
	 */
	// Global commands
	if ((words.size() == 1) && (words[0] == "quit")) {
		console_->Print("quit");
		console_->Send("quit\n");
		exit(0);
	}			//if

	if ((words.size() == 1) && (words[0] == "roster")) {
		console_->Print("roster");
		//PrintRoster();
		console_->Send("roster\n");
		return;
	} else if ((words.size() == 1) && (words[0] == "OLRoster")) {
		console_->Print("OLRoster");
		console_->Send("OLRoster\n");
		//PrintOLRoster();
		return;
	} else if ((words.size() == 2) && (words[0] == "call")) {
		MakeCallTo(words[1]);
		return;
	} else if ((words.size() >= 3)
		   && (words[0].find("chat") != std::string::npos)
		   && (words[1].find("@gmail.com") != std::string::npos)) {
		console_->Print("chat");
		std::string texte;
		for (int i = 2; i < words.size(); i++) {
			texte += words[i];
			texte += std::string(" ");
		}		//for
		SendTexte(words[1], texte);
		return;
	} else if ((words.size() >= 3)
		   && (words[0].find("send") != std::string::npos)
		   && (words[1].find("@gmail.com") != std::string::npos)) {
		console_->Print("send");
		std::string message = "send ";
		message += words[1];
		message += " ";
		message += words[2];
		message += "\n";
		console_->Send(message);
		//SendFile(words[1], words[2]);
		return;
	} else if ((words.size() == 1) && words[0] == "receive") {
		if (incoming_file_) {
			console_->Send("acceptFile\n");
			_current_sending_fileclient->acceptFile();
		}		//if
	} else if ((words.size() == 1) && words[0] == "cancel") {
		if (sending_file_) {
			console_->Send("cancel file sending\n");
//    _current_waiting_fileclient->Cancel();
			_current_sending_fileclient->Cancel();
		}		//if
		else if (incoming_file_) {
			console_->Send("cancel receiving file\n");
			_current_sending_fileclient->Cancel();
		}
//      console_->Print(FILE_COMMANDS);
	}			//else if
	else if ((words.size() == 1) && (words[0] == "accept")) {
		if (call_ && incoming_call_) {
			console_->Send("accept call\n");
			assert(call_->sessions().size() == 1);
			call_->AcceptSession(call_->sessions()[0]);
			phone_client()->SetFocus(call_);
			incoming_call_ = false;
		}		//if 
	} else if ((words.size() == 1) && (words[0] == "reject")) {
		if (call_ && incoming_call_) {
			console_->Send("reject incomming call\n");
			call_->RejectSession(call_->sessions()[0]);
			incoming_call_ = false;
		}		//if
	} else if ((words.size() == 1) && (words[0] == "hangup")) {
		if (call_) {
			call_->Terminate();
			call_ = NULL;
			session_ = NULL;
			console_->SetPrompt(NULL);
		}		//if
	} else if ((words.size() == 1) && (words[0] == "mute")) {
		if (call_) {
			console_->Send("mute\n");
			call_->Mute(true);
		}		//if
	} else if ((words.size() == 1) && (words[0] == "unmute")) {
		if (call_) {
			console_->Send("unmute\n");
			call_->Mute(false);
		}		//if
	} else {
		console_->Send("Else\n");
		if (call_ && incoming_call_)
			console_->Print(RECEIVE_COMMANDS);
		else if (call_)
			console_->Print(CALL_COMMANDS);
		else if (incoming_file_ || sending_file_)
			console_->Print(FILE_COMMANDS);
		else
			console_->Print(CONSOLE_COMMANDS);
	}			//else

}

CallClient::CallClient(buzz::XmppClient * xmpp_client):xmpp_client_(xmpp_client)
	,call_(NULL)
	,incoming_call_(false)
	,incoming_file_(false)
	,sending_file_(false)
,_chatclient(NULL)
,presence_push_(NULL)
,_current_sending_fileclient(NULL)
,_current_waiting_fileclient(NULL)
{

	b_first_time_send_file_ = true;
	xmpp_client_->SignalStateChange.connect(this,
						&CallClient::
						OnStateChange);

	char cwd[256];
	getcwd(cwd, sizeof(cwd));
/*
  cricket::FileShareManifest *manifest = new cricket::FileShareManifest();
  _current_waiting_fileclient = new FileShareClient(xmpp_client_, buzz::JID_EMPTY, manifest, cwd);
  xmpp_client_->SignalStateChange.connect(_current_waiting_fileclient, &FileShareClient::OnStateChange);
  _current_waiting_fileclient->SignalFileReceived.connect(this, &CallClient::OnFileReceived);
  _current_waiting_fileclient->SignalFileTransferStatue.connect(this, &CallClient::OnFileTransferStatue);
  _current_waiting_fileclient->setSender(false);
//  jit->SignalJingleInfo.connect(_current_waiting_fileclient, &FileShareClient::OnJingleInfo);
*/
/*  cricket::FileShareManifest *manifest1 = new cricket::FileShareManifest();
  
  std::string file = "";
  if (talk_base::Filesystem::IsFolder(file)) {
      manifest1->AddFolder(file, get_dir_size(file.c_str()));
    } else {
      size_t size = 0;
      talk_base::Filesystem::GetFileSize(file, &size);
      manifest1->AddFile(file, size);
    }//else
*/
	_current_sending_fileclient =
	    new FileShareClient(xmpp_client_, buzz::JID_EMPTY, NULL, cwd);
	//xmpp_client_->SignalStateChange.connect(_current_sending_fileclient, &FileShareClient::OnStateChange);
	_current_sending_fileclient->SignalFileReceived.connect(this,
								&CallClient::
								OnFileReceived);
	_current_sending_fileclient->SignalFileTransferStatue.connect(this,
								      &CallClient::
								      OnFileTransferStatue);

//  _current_sending_fileclient->setSender(true);

}

CallClient::~CallClient()
{
	if(_chatclient !=NULL)
		delete _chatclient;
	if(_current_waiting_fileclient !=NULL)
		delete _current_waiting_fileclient;
	if(_current_sending_fileclient !=NULL)
		delete _current_sending_fileclient;
	if(presence_push_ !=NULL)
		delete presence_push_;

}

void CallClient::CancelSendFile(const std::string & to)
{
	//buzz::Jid found_jid = buzz::Jid(to);
	std::cout << "CancelSendFile is called" << std::endl;
	//session_->Cancel();
	if (_current_sending_fileclient) {
		_current_sending_fileclient->Cancel();
		session_ = NULL;
	}
}

void CallClient::SendFile(const std::string & to, const std::string & file)
{
	buzz::Jid found_jid = buzz::Jid(to);

	console_->Printf("send file '%s' to friend '%s'", file.c_str(),
			 found_jid.Str().c_str());

    /**peut etre ici on doit indiquer que le manifest_ est null car apparament il le supprime automatiquement 
      ** après la termine de transfer. Je ne vois pas que le manifest_ devient null, mais c'est vrais que je ne 
      ** peux plus l'utiliser... bug...
      **/
	cricket::FileShareManifest * manifest = new cricket::FileShareManifest();	//_current_sending_fileclient->getFileShareManifest();

	manifest->clear();
	if (talk_base::Filesystem::IsFolder(file)) {
		manifest->AddFolder(file, get_dir_size(file.c_str()));
	} else {
		size_t size = 0;
		char *str;
		char *str2;
		char *dir;
		char *file_name;
		str = strdup(file.c_str());
		str2 = strdup(file.c_str());
		dir = dirname(str);
		file_name = basename(str2);
		std::string s_dir(dir);
		std::string s_file(file_name);
		_current_sending_fileclient->setRootDir(s_dir);
		free(str);
		free(str2);
		talk_base::Filesystem::GetFileSize(file, &size);
		//manifest->AddFile(file, size);
		manifest->AddFile(s_file, size);
	}			//else

	_current_sending_fileclient->setManifest(manifest);
	_current_sending_fileclient->setSendToJid(found_jid);

	if (!b_first_time_send_file_) {
      /**rien à faire ici, seulement pour tester...
      **/
	}
	_current_sending_fileclient->
	    SendFile( /*found_jid.Str(), manifest */ );

}

void CallClient::OnSetFileDir(const std::string& dir)
{
	_current_sending_fileclient->setRootDir(dir);
}
void CallClient::OnFileTransferStatue(const std::string & type,
				      const std::string & statue,
				      const std::string & jid)
{
	console_->OnFileTransferStatue(type, statue, jid);

}

void CallClient::OnFileReceived(const std::string & from,
				const std::string & file,
				const std::string & no_use)
{
	incoming_file_ = true;
	console_->OnFileRecu(from, file);

}

const std::string CallClient::strerror(buzz::XmppEngine::Error err)
{
	switch (err) {
	case buzz::XmppEngine::ERROR_NONE:
		return "";
	case buzz::XmppEngine::ERROR_XML:
		return "Malformed XML or encoding error";
	case buzz::XmppEngine::ERROR_STREAM:
		return "XMPP stream error";
	case buzz::XmppEngine::ERROR_VERSION:
		return "XMPP version error";
	case buzz::XmppEngine::ERROR_UNAUTHORIZED:
		return
		    "User is not authorized (Check your username and password)";
	case buzz::XmppEngine::ERROR_TLS:
		return "TLS could not be negotiated";
	case buzz::XmppEngine::ERROR_AUTH:
		return "Authentication could not be negotiated";
	case buzz::XmppEngine::ERROR_BIND:
		return
		    "Resource or session binding could not be negotiated";
	case buzz::XmppEngine::ERROR_CONNECTION_CLOSED:
		return "Connection closed by output handler.";
	case buzz::XmppEngine::ERROR_DOCUMENT_CLOSED:
		return "Closed by </stream:stream>";
	case buzz::XmppEngine::ERROR_SOCKET:
		return "Socket error";
	default:
		return "Unknown error";
	}
}

void CallClient::OnCallDestroy(cricket::Call * call)
{
	if (call == call_) {
		call_->Terminate();
		call_ = NULL;
		session_ = NULL;
		console_->Print("call destroyed");
	}

}

void CallClient::OnJingleInfo(const std::string & relay_token,
			      const std::vector < std::string >
			      &relay_addresses,
			      const std::vector <
			      talk_base::SocketAddress > &stun_addresses)
{
	port_allocator_->SetStunHosts(stun_addresses);
	port_allocator_->SetRelayHosts(relay_addresses);
	port_allocator_->SetRelayToken(relay_token);
}

void CallClient::OnStateChange(buzz::XmppEngine::State state)
{
	switch (state) {
	case buzz::XmppEngine::STATE_START:
		console_->Print("start connect...");
		console_->Send("start connect\n");
		break;

	case buzz::XmppEngine::STATE_OPENING:
		console_->Print("connecting...");
		console_->Send("connecting ...\n");
		break;

	case buzz::XmppEngine::STATE_OPEN:
		console_->Print("logged in...");
		console_->Send("loggedin\n");
		InitPhone();
		InitPresence();
		console_->OnSignOn();
		break;

	case buzz::XmppEngine::STATE_CLOSED:
		buzz::XmppEngine::Error error = xmpp_client_->GetError(NULL);
		console_->Print("logged out..." + strerror(error));
		console_->Send("loggedout\n");
		console_->OnSignError(strerror(error));
		break;

	}
}

void CallClient::InitPhone( /*cricket::SessionManager* s */ )
{

	std::string client_unique = xmpp_client_->jid().Str();
	cricket::InitRandom(client_unique.c_str(), client_unique.size());

	worker_thread_ = new talk_base::Thread();

	port_allocator_ =
	    new cricket::HttpPortAllocator(&network_manager_, "pcp");

	session_manager_ =
	    new cricket::SessionManager(port_allocator_, worker_thread_);

	session_manager_->SignalRequestSignaling.connect(this,
							 &CallClient::
							 OnRequestSignaling);
	session_manager_->OnSignalingReady();


	session_manager_task_ =
	    new cricket::SessionManagerTask(xmpp_client_,
					    session_manager_);
	session_manager_task_->EnableOutgoingMessages();
	session_manager_task_->Start();

	buzz::JingleInfoTask * jit =
	    new buzz::JingleInfoTask(xmpp_client_);
	jit->RefreshJingleInfoNow();
	jit->SignalJingleInfo.connect(this, &CallClient::OnJingleInfo);
	jit->SignalJingleInfo.connect(_current_sending_fileclient,
				      &FileShareClient::OnJingleInfo);
	jit->Start();

	phone_client_ =
	    new cricket::PhoneSessionClient(xmpp_client_->jid(),
					    session_manager_);
	phone_client_->SignalCallCreate.connect(this,
						&CallClient::OnCallCreate);

//  const std::string type("http://www.google.com/session/phone");
//  session_manager_->AddClient(type, phone_client_);
//  _current_sending_fileclient->OnSignon(port_allocator_, session_manager_, jit);
//  _current_waiting_fileclient->OnSignon(port_allocator_, session_manager_, jit);

	_current_sending_fileclient->OnSignon(port_allocator_,
					      session_manager_, NULL,
					      session_manager_task_);
	worker_thread_->Start();
}

void CallClient::InitPresence()
{

	presence_push_ = new buzz::PresencePushTask(xmpp_client_);
	presence_push_->SignalStatusUpdate.connect(this,
						   &CallClient::
						   OnStatusUpdate);
	presence_push_->SignalStatusUpdate.
	    connect(_current_sending_fileclient,
		    &FileShareClient::OnStatusUpdate);
	presence_push_->Start();

	//buzz::Status my_status;
	my_status.set_jid(xmpp_client_->jid());
	my_status.set_available(true);
	my_status.set_show(buzz::Status::SHOW_ONLINE);
	my_status.set_priority(0);
	my_status.set_know_capabilities(true);
	my_status.set_phone_capability(true);
	my_status.set_fileshare_capability(true);
	my_status.set_is_google_client(true);
	my_status.set_version("1.0.0.66");

	buzz::PresenceOutTask * presence_out_ =
	    new buzz::PresenceOutTask(xmpp_client_);
	presence_out_->Send(my_status);
	presence_out_->Start();

	_chatclient = new buzz::ChatClient(this->xmpp_client_);
	_chatclient->SignalTexteRecu.connect(this,
					     &CallClient::OnTexteRecu);
	//_current_sending_fileclient->OnSignon(port_allocator_, session_manager_, NULL, session_manager_task_);
}

void CallClient::SetPresence(buzz::Status::Show f_show,
			     const std::string & f_status)
{


	buzz::PresenceOutTask * presence_out_ =
	    new buzz::PresenceOutTask(xmpp_client_);
	my_status.set_show(f_show);
	my_status.set_status(f_status);
	presence_out_->Send(my_status);
	presence_out_->Start();
}

void CallClient::OnRequestSignaling()
{
	session_manager_->OnSignalingReady();
}

void CallClient::OnCallCreate(cricket::Call * call)
{
	call->SignalSessionState.connect(this,
					 &CallClient::OnSessionState);
}

void CallClient::OnSessionState(cricket::Call * call,
				cricket::Session * session,
				cricket::Session::State state)
{
	buzz::Jid jid(session->remote_name());

	if (state == cricket::Session::STATE_RECEIVEDINITIATE) {
		console_->Printf("Incoming call from '%s'",
				 jid.Str().c_str());
		call_ = call;
		session_ = session;
		incoming_call_ = true;
		console_->OnIncomingCall(jid.Str());
	} else if (state == cricket::Session::STATE_SENTINITIATE) {
		console_->Print("calling...");
		console_->OnCallStatue(jid.Str(), "calling");
	} else if (state == cricket::Session::STATE_RECEIVEDACCEPT) {
		console_->Print("call answered");
		console_->OnCallStatue(jid.Str(), "answer");
	} else if (state == cricket::Session::STATE_RECEIVEDREJECT) {
		console_->Print("call not answered");
		console_->OnCallStatue(jid.Str(), "noanswer");
	} else if (state == cricket::Session::STATE_INPROGRESS) {
		console_->Print("call in progress");
		console_->OnCallStatue(jid.Str(), "talking");
	} else if (state == cricket::Session::STATE_RECEIVEDTERMINATE) {
		console_->Print("other side hung up");
		console_->OnHangupCall(jid.Str());
	}
}



void CallClient::OnStatusUpdate(const buzz::Status & status)
{
	console_->OnRosterPresence(status);
}

void CallClient::OnTexteRecu(const std::string & iconset,
			     const std::string & from,
			     const std::string & texte)
{
	console_->OnRecuMessage(from, texte);
}

void CallClient::SendTexte(const std::string & name,
			   const std::string & texte)
{
	_chatclient->envoyerTexte(name, texte);

}

void CallClient::CancelCallTo(const std::string & name)
{
	buzz::Jid callto_jid = buzz::Jid(name);
	std::cout << "Cancel CallClient::CancelCallTo " << name << std::
	    endl;

	if (call_) {
		console_->Printf("Found online friend '%s'",
				 callto_jid.Str().c_str());
		//phone_client()->SignalCallDestroy.connect(this, &CallClient::OnCallDestroy);
		phone_client()->SetFocus(call_);
		OnCallDestroy(call_);
	} else {
		console_->Send("not found the calling person\n");
	}
}

void CallClient::MakeCallTo(const std::string & name)
{
	buzz::Jid callto_jid = buzz::Jid(name);
	std::cout << "Callclient::MakeCallTo " << name << std::endl;

	phone_client()->SignalCallDestroy.connect(this,
						  &CallClient::
						  OnCallDestroy);

	if (!call_) {
		call_ = phone_client()->CreateCall();
		call_->SignalSessionState.connect(this,
						  &CallClient::
						  OnSessionState);
		session_ = call_->InitiateSession(callto_jid, NULL);
	}

	phone_client()->SetFocus(call_);
}


void CallClient::OnAnswerCall(const std::string & accept)
{

	if (call_ && incoming_call_) {
		if ("true" == accept) {
			console_->Print("accept call\n");
			assert(call_->sessions().size() == 1);
			call_->AcceptSession(call_->sessions()[0]);
			phone_client()->SetFocus(call_);
			incoming_call_ = false;
		} else {
			call_->RejectSession(call_->sessions()[0]);
			incoming_call_ = false;
		}
	}
}

void CallClient::OnAnswerFile(const std::string & accept)
{
	if (incoming_file_) {
		if ("true" == accept)
			_current_sending_fileclient->acceptFile();
		else {
			_current_sending_fileclient->Cancel();
			incoming_file_ = false;
		}
	}
}
