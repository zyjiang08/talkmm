/*
 * =====================================================================================
 *
 *       Filename:  italk.cc
 *
 *    Description:  pcp测试程序--用来测试libjingle的运作
 *
 *        Version:  1.0
 *        Created:  2008年01月07日 20时33分35秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */

#include <iomanip>
#include <time.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#else
#include <direct.h>
//typedef _getcwd getcwd;
#include "talk/base/win32.h"
#endif

#include "talk/base/fileutils.h"
#include "talk/base/pathutils.h"
#include "talk/base/helpers.h"
#include "talk/base/httpclient.h"
#include "talk/base/logging.h"
#include "talk/base/physicalsocketserver.h"
#include "talk/base/ssladapter.h"
#include "talk/xmpp/xmppclientsettings.h"
#include "talk/examples/login/xmppthread.h"
#include "talk/examples/login/xmppauth.h"
#include "talk/p2p/client/httpportallocator.h"
#include "talk/p2p/client/sessionmanagertask.h"
#include "talk/session/fileshare/fileshare.h"
#include "talk/examples/login/presencepushtask.h"
#include "talk/examples/login/presenceouttask.h"
#include "talk/examples/login/jingleinfotask.h"
class Italk:public sigslot::has_slots <>, public talk_base::MessageHandler {
      public:
	Italk(buzz::XmppClient * xmppclient):xmpp_client_(xmppclient) {
	} 
	
	void OnStateChange(buzz::XmppEngine::State state) {
		switch (state) {
		case buzz::XmppEngine::STATE_START:
			std::cout << "Connecting..." << std::endl;
			break;
		case buzz::XmppEngine::STATE_OPENING:
			std::cout << "Logging in. " << std::endl;
			break;
		case buzz::XmppEngine::STATE_OPEN:
			std::cout << "Logged in as " << xmpp_client_->
			    jid().Str() << std::endl;
			OnSignon();
			break;
		case buzz::XmppEngine::STATE_CLOSED:
			std::cout << "Logged out." << std::endl;
			break;
		}
	}


  void OnStatusUpdate(const buzz::Status &status) {
    //if (status.available() && status.fileshare_capability()) {

      // A contact's status has changed. If the person we're looking for is online and able to receive
      // files, send it.
	std::cout << status.jid().Str() << " has signed on." << std::endl;
      //if (send_to_jid_.BareEquals(status.jid())) {
//	std::cout << send_to_jid_.Str() << " has signed on." << std::endl;
	//cricket::FileShareSession* share = file_share_session_client_->CreateFileShareSession();
	//share->Share(status.jid(), const_cast<cricket::FileShareManifest*>(manifest_));
	//send_to_jid_ = buzz::Jid("");
 //     }
      
   // }
  }

	void OnMessage(talk_base::Message * m) {
		ASSERT(m->message_id == MSG_STOP);
		talk_base::Thread * thread =
		    talk_base::ThreadManager::CurrentThread();
		//delete session_;
		thread->Stop();
	}

	void OnSignon(){
    std::string client_unique = xmpp_client_->jid().Str();
    cricket::InitRandom(client_unique.c_str(), client_unique.size());

    //设置监听Presence任务
    buzz::PresencePushTask *presence_push_ = new buzz::PresencePushTask(xmpp_client_);
    presence_push_->SignalStatusUpdate.connect(this, &Italk::OnStatusUpdate);
    presence_push_->Start();
    
    buzz::Status my_status;
    my_status.set_jid(xmpp_client_->jid());
    my_status.set_available(true);
    my_status.set_show(buzz::Status::SHOW_ONLINE);
    my_status.set_priority(0);
    my_status.set_know_capabilities(true);
    my_status.set_fileshare_capability(true);
    my_status.set_is_google_client(true);
    my_status.set_version("1.0.0.66");

    //设置发送Presence任务
    buzz::PresenceOutTask* presence_out_ =
      new buzz::PresenceOutTask(xmpp_client_);
    presence_out_->Send(my_status);
    presence_out_->Start();
    
    /*
    port_allocator_.reset(new cricket::HttpPortAllocator(&network_manager_, "pcp"));

    session_manager_.reset(new cricket::SessionManager(port_allocator_.get(), NULL));

    cricket::SessionManagerTask * session_manager_task = new cricket::SessionManagerTask(xmpp_client_, session_manager_.get());
    session_manager_task->EnableOutgoingMessages();
    session_manager_task->Start();
    
    buzz::JingleInfoTask *jingle_info_task = new buzz::JingleInfoTask(xmpp_client_);
    jingle_info_task->RefreshJingleInfoNow();
    jingle_info_task->SignalJingleInfo.connect(this, &Italk::OnJingleInfo);
    jingle_info_task->Start();
    
    file_share_session_client_.reset(new cricket::FileShareSessionClient(session_manager_.get(), xmpp_client_->jid(), "pcp"));
    file_share_session_client_->SignalFileShareSessionCreate.connect(this, &Italk::OnFileShareSessionCreate);
    session_manager_->AddClient(NS_GOOGLE_SHARE, file_share_session_client_.get());
    */
  }
      private:
	enum {
		MSG_STOP,
	};
	buzz::XmppClient * xmpp_client_;
};


int main(int argc, char *argv[])
{
	talk_base::InitializeSSL();	//初始化SSL，如果需要的话
	XmppPump pump;		//XMPP任务管理对象,包装了XmppClient和处理登录进XMPP服务器
	buzz::Jid jid;
	buzz::XmppClientSettings xcs;
	talk_base::InsecureCryptStringImpl pass;
	std::string username = "cycloneblog@gmail.com";
	jid = buzz::Jid(username);
	std::string passwd("cyclone123");
	pass.password() = passwd;

	xcs.set_user(jid.node());
	xcs.set_resource("italk testing");
	xcs.set_host(jid.domain());
	xcs.set_use_tls(true);

	xcs.set_pass(talk_base::CryptString(pass));
	xcs.set_server(talk_base::SocketAddress("talk.google.com", 5222));

	talk_base::PhysicalSocketServer ss;
	talk_base::Thread main_thread(&ss);	//创建线程对象
	talk_base::ThreadManager::SetCurrent(&main_thread);	//并将它设置为当前线程


	Italk italk(pump.client());
	pump.client()->SignalStateChange.connect(&italk,
						 &Italk::OnStateChange);

	pump.DoLogin(xcs, new XmppSocket(true), NULL);
	main_thread.Run();
	//pump.DoDisconnect();




	return 0;
}
