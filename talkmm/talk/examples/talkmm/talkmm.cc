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

#include "talkmm.h"
//#include "MainWindow.h"

bool debug=false;

Talkmm::Talkmm()
{

	if (debug)
	    talk_base::LogMessage::LogToDebug(talk_base::LS_VERBOSE);
	talk_base::InitializeSSL();

	m_client = new CallClient(m_pump.client());
	main_thread = new talk_base::Thread(&m_ss);
	talk_base::ThreadManager::SetCurrent(main_thread);
	int port=0;
	m_console = new Console(main_thread, m_client, port);
	m_client->SetConsole(m_console);
	console_thread = new talk_base::Thread(&m_ss);

	//main_window = new MainWindow();
	//main_window->signal_on_login(this,&Talkmm::on_login);

}

Talkmm::~Talkmm()
{

}

bool Talkmm::on_login(const std::string& f_username,const std::string& f_pass)
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
	
