#ifndef _DealConf_H
#define _DealConf_H

#include <iostream>
#include <string>

using namespace std;

class DealConf 
{
	public:
		DealConf();
		string username_w;
		string password_w;
		string username_r;
		string password_r;
		int WriteXML(const string username_w, const string password_w);
		int ReadXML();

	private:
		string EncodeUserInfo(string text);
		string DecodeUserInfo(string text);
		//int WriteXML(const string& config_filename, const string& username_w, const string& password_w);
};

#endif
