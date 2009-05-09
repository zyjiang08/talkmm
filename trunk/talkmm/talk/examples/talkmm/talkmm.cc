/*
 * =====================================================================================
 *
 *       Filename:  talkmm.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年04月25日 09时24分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  first_name last_name (fl), fl@my-company.com
 *        Company:  my-company
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "MainWindow.h"
#include "talkmm.h"

bool debug=false;

Talkmm::Talkmm():m_roster(new RosterMap)
		 ,m_presence_push(NULL)
		 ,m_chatclient(NULL)
{
	if (debug)
	    talk_base::LogMessage::LogToDebug(talk_base::LS_VERBOSE);

	//Init SSL.
	talk_base::InitializeSSL();

	//Create thread and set it as the current thread.
	main_thread = new talk_base::Thread(&m_ss);
	talk_base::ThreadManager::SetCurrent(main_thread);

	m_callclient = new CallClient(m_pump.client());

	//Create the main window included three notebooks' tabs.
	main_window = new MainWindow(this);
	main_window->signal_on_login(this, &Talkmm::OnLogin);

	int port=0;
	m_console = new Console(main_thread, m_callclient,main_window);
	m_callclient->SetConsole(m_console);
	console_thread = new talk_base::Thread(&m_ss);

	m_pump.client()->SignalStateChange.connect(this, &Talkmm::OnStateChange);
}

Talkmm::~Talkmm()
{
	delete m_callclient;
	delete m_console;
	delete main_thread;
	delete console_thread;
	delete m_chatclient;
	delete main_window;
	delete m_roster;

}

bool Talkmm::OnLogin(const std::string& f_username,const std::string& f_pass)
{
	m_jid = buzz::Jid(f_username);
	std::string& password = m_pass.password();
	password = f_pass;
	if (!m_jid.IsValid() || m_jid.node() == "") {
		printf("Invalid JID. JIDs should be in the form user@domain\n");
		m_console->Send("loggedout\n");
		return false;
	}
	m_xcs.set_user(m_jid.node());
	m_xcs.set_resource("call");
	m_xcs.set_host(m_jid.domain());
	m_xcs.set_use_tls(true);
	m_xcs.set_pass(talk_base::CryptString(m_pass));
	m_xcs.set_server(talk_base::SocketAddress("talk.google.com", 5222));
	printf("Logging in as %s\n", m_jid.Str().c_str());
	console_thread->Start();
	console_thread->Post(m_console, MSG_START);
	m_pump.DoLogin(m_xcs, new XmppSocket(true), NULL);
	main_thread->Start();
	//main_thread->Run();
	
	return true;
}

void Talkmm::OnStateChange(buzz::XmppEngine::State state) {
  switch (state) {
  case buzz::XmppEngine::STATE_START:
    m_console->Print("connecting...");
    m_console->Send("loggingin\n");
    break;

  case buzz::XmppEngine::STATE_OPENING:
    m_console->Print("logging in...");
    break;

  case buzz::XmppEngine::STATE_OPEN:
    m_console->Print("talkmm has==========logged in...");
    m_console->Send("loggedin\n");
    m_callclient->InitPhone();
    this->InitPresence();
    m_callclient->InitPresence();
    m_console->OnSignOn();
    break;

  case buzz::XmppEngine::STATE_CLOSED:
    //buzz::XmppEngine::Error error = m_pump.client()->GetError(NULL);
    //m_pump.client()->Stop();
    //m_console->Print("logged out..." + strerror(error));
    m_console->Send("loggedout\n");
    //cout << "logged out...hia hia." << strerror(error) << endl;
    
    main_window->main_notebook = dynamic_cast < Gtk::Notebook * > (main_window->main_xml->get_widget("main_notebook"));
    main_window->main_notebook->set_current_page(main_window->LOGIN_INIT); //设置当前状态为登录
   
    //talk_base::Thread *thread = talk_base::ThreadManager::CurrentThread();
    //thread->Stop();
    //break;
    //exit(0);
  }
}

/*
RosterItem Talkmm::FindRoster(const std::string& f_jid)
{
	RosterMap::const_iterator iter = m_roster.find(f_jid);
	if(iter == m_roster.end())
		return NULL;
	return (*iter).second;
}
*/


const RosterItem& Talkmm::GetRoster(const std::string& f_jid)
{

    RosterMap::const_iterator iter = m_roster->find(f_jid);
    if (iter != m_roster->end()){
	return (*iter).second;
    }

}
void Talkmm::OnStatusUpdate(const buzz::Status& status)
{
	RosterItem item;
  	item.jid = status.jid();
  	item.show = status.show();
	item.online = status.available();
  	item.status = status.status();
  	item.file_cap = status.fileshare_capability()?1:0;
  	item.phone_cap = status.phone_capability()?1:0;

  	std::string key = item.jid.Str();
  	/** i want to change a method to insert roster, please fixed me */
  	(*m_roster)[key] = item;
	m_console->RosterPresence(key);


#if 0
    RosterMap::iterator iter = m_roster->find(key);
    if (iter != m_roster->end()){
	printf("add buddy %s presence\n",key.c_str());
	if(status.available())
		m_console->RosterPresence(key);
    }

  size_t pos = key.find("/");
  std::string str = key.substr(0, pos);;
  str += status.available()?"<online\n":"<offline\n";
  m_console->Send(str);

  m_console->Printf("Adding to All roster: %s", key.c_str());
  (*all_roster_)[key] = item;

  if (status.available() && status.fileshare_capability()){
    m_console->Printf("Adding to file roster: %s", key.c_str());
    (*file_roster_)[key] = item;
  }//if
  else{
    RosterMap::iterator iter = file_roster_->find(key);
    if (iter != file_roster_->end()){
      file_roster_->erase(iter);
      m_console->Printf("Removing from file roster: %s", key.c_str());
    }//if
  }//else

  if(status.available()){
    m_console->Printf("Adding to available roster: %s", key.c_str());
    (*enligne_roster_)[key] = item;
  }//if
  else{
    RosterMap::iterator iter = enligne_roster_->find(key);
    if (iter != enligne_roster_->end()){
      enligne_roster_->erase(iter);
      m_console->Printf("Removing from available roster: %s", key.c_str());
    }//if
  }//else


  if (status.available() && status.phone_capability()) {
     m_console->Printf("Adding to phone roster: %s", key.c_str());
    (*roster_)[key] = item;
  } else {
    RosterMap::iterator iter = roster_->find(key);
    if (iter != roster_->end()){
      roster_->erase(iter);
      m_console->Printf("Removing from phone roster: %s", key.c_str());
    }//if
  }
#endif
}


void Talkmm::InitPresence() 
{
  
  buzz::XmppClient* xmpp_client_ = m_pump.client();
  m_presence_push = new buzz::PresencePushTask(xmpp_client_);
  m_presence_push->SignalStatusUpdate.connect(
    this, &Talkmm::OnStatusUpdate);
  //m_presence_push->SignalStatusUpdate.connect(
  //  _current_sending_fileclient, &FileShareClient::OnStatusUpdate);
  m_presence_push->Start();

  buzz::Status my_status;
  my_status.set_jid(xmpp_client_->jid());
  my_status.set_available(true);
  my_status.set_show(buzz::Status::SHOW_ONLINE);
  my_status.set_priority(0);
  my_status.set_know_capabilities(true);
  my_status.set_phone_capability(true);
  my_status.set_fileshare_capability(true);
  my_status.set_is_google_client(true);
  my_status.set_version("1.0.0.66");

  buzz::PresenceOutTask* presence_out_ =
      new buzz::PresenceOutTask(xmpp_client_);
  presence_out_->Send(my_status);
  presence_out_->Start();

  m_chatclient = new buzz::ChatClient(xmpp_client_);
  m_chatclient->SignalTexteRecu.connect(this, &Talkmm::OnTexteRecu);
  //_current_sending_fileclient->OnSignon(port_allocator_, session_manager_, NULL, session_manager_task_);
}


/** on recive message */
void Talkmm::OnTexteRecu(const std::string& iconset, const std::string& from, const std::string& texte)
{
	std::string str;
	str += from;
	str += std::string("(");
	str += iconset;
	str += std::string(") said: ");
	str += texte;
	this->m_console->Print(str);
	std::string message = "message###";
	message += from;
	message += "###";
	message += texte;
	message += "\n";
	this->m_console->Print(message);
	m_console->RecuMessage(from,texte);
	

}

void Talkmm::SendTexte(const std::string& name, const std::string& texte)
{
    m_chatclient->envoyerTexte(name, texte);

}

void Talkmm::AnswerFile(bool accept)
{
	m_callclient->OnAnswerFile(accept);
}

void Talkmm::AnswerCall(bool accept)
{
	m_callclient->OnAnswerCall(accept);
}

void Talkmm::SendFile(const std::string& to,const std::string& filename)
{
	m_callclient->SendFile(to,filename);
}
