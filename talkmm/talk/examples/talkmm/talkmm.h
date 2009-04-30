/*
 * =====================================================================================
 *
 *       Filename:  talkmm.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年04月25日 09时16分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  first_name last_name (fl), fl@my-company.com
 *        Company:  my-company
 *
 * =====================================================================================
 */


#ifndef _TALK_MM_H_
#define _TALK_MM_H_

#include <time.h>
#include <iomanip>
#include <map>
#include "talk/base/logging.h"
#include "talk/base/physicalsocketserver.h"
#include "talk/base/ssladapter.h"
#include "talk/xmpp/xmppclientsettings.h"
#include "talk/login/xmppthread.h"
#include "talk/login/xmppauth.h"
#include "callclient.h"
#include "console.h"

class MainWindow;

struct RosterItem {
  buzz::Jid jid;
  buzz::Status::Show show;
  std::string status;
  bool file_cap;
  bool phone_cap;
    
};

class Talkmm : public sigslot::has_slots<> {

	public:
		Talkmm();
		~Talkmm();
		bool OnLogin(const std::string& f_username,const std::string& f_pass);

	public:
		void OnStateChange(buzz::XmppEngine::State state);
		void OnStatusUpdate(const buzz::Status& status);
		void InitPresence();
		void OnTexteRecu(const std::string& iconset, const std::string& from, const std::string& texte);
		void SendTexte(const std::string& name, const std::string& texte);
		void AnswerFile(bool accept=true);
		void AnswerCall(bool accept=true);
	private:
		typedef std::map<std::string,RosterItem> RosterMap;
		RosterMap* m_roster;
		XmppPump m_pump;
		buzz::Jid m_jid;
		buzz::XmppClientSettings m_xcs;
		talk_base::InsecureCryptStringImpl m_pass;
		talk_base::PhysicalSocketServer m_ss;
		CallClient* m_callclient;
		Console* m_console;
		talk_base::Thread* main_thread;
		talk_base::Thread* console_thread;

		/** presence status about online,alway, leave .etc */
		buzz::PresencePushTask* m_presence_push;
		buzz::ChatClient* m_chatclient;
		MainWindow* main_window;











};


#endif // _TALK_MM_H_

