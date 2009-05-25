#ifndef MVC_H_
#define MVC_H_


#include <iostream>

using namespace std;

class Talkmm;

namespace CLogin
{
typedef Talkmm Handler;

namespace View
{
typedef bool (Handler::*Func)(const string& f_name, const string& f_passwd);
//typedef bool (Handler::*Func)(string f_name, string f_passwd, string f_server, int f_port);
}

namespace Model
{
typedef void (Handler::*Func)();
}
}

#endif
