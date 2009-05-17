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

Talkmm::Talkmm()
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

	m_console = new Console(main_thread, m_callclient,main_window);
	m_callclient->SetConsole(m_console);
	main_window->set_console(m_console);
	console_thread = new talk_base::Thread(&m_ss);

	console_thread->Start();
	console_thread->Post(m_console, MSG_START);
	main_thread->Start();
}

Talkmm::~Talkmm()
{
	delete m_callclient;
	delete m_console;
	delete main_thread;
	delete console_thread;
	delete main_window;

}

void Talkmm::DisConnect()
{
	//m_pump.DoDisconnect();
	//printf("stop main_thread\n");
	//main_thread->Stop();
	
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
	m_xcs.set_resource("talkmm");
	m_xcs.set_host(m_jid.domain());
	m_xcs.set_use_tls(true);
	m_xcs.set_pass(talk_base::CryptString(m_pass));
	m_xcs.set_server(talk_base::SocketAddress("talk.google.com", 5222));
	printf("Logging in as %s\n", m_jid.Str().c_str());
	m_pump.DoLogin(m_xcs, new XmppSocket(true), NULL);
	//main_thread->Start();
	//main_thread->Run();
	
	return true;
}


