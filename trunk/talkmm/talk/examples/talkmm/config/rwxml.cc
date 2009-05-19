#include <iostream>
#include <string>
#include <sstream>
#include "tinyxml.h"
#include "rwxml.h"

//using namespace std;

DealConf::DealConf()
{
}

string DealConf::EncodeUserInfo(string text)
{
	//Encrypt the text here...
	
	return text;
}

string DealConf::DecodeUserInfo(string text)
{
	//Decrypt the text here...
	
	return text;
}

int DealConf::WriteXML(const string username, const string password)
{
	TiXmlDocument doc("./config.xml"); 			// 建立一个XML文件
	TiXmlDeclaration Declaration("1.0","gb2312", "yes"); 	// 声明XML的属性
	doc.InsertEndChild(Declaration); 			// 写入基本的XML头结构

	TiXmlElement* InfoRoot = NULL;
	TiXmlNode * InfoNode = NULL;
	TiXmlElement * element = NULL;
	TiXmlText * text = NULL;

	InfoRoot = new TiXmlElement( "UserInfo" );
	InfoNode = doc.InsertEndChild(*InfoRoot);
        InfoRoot = InfoNode->ToElement();

	//Add username.
	if(username.size() != 0){
		element = new TiXmlElement("username");
		string username_t = EncodeUserInfo(username);
		text = new TiXmlText(username_t.c_str());
		element->LinkEndChild(text);
		InfoNode = InfoRoot->InsertEndChild(*element);
	}

	//Add password.
	if(password.size() != 0){
		element = new TiXmlElement("password");
		string password_t = EncodeUserInfo(password);
		text = new TiXmlText(password_t.c_str());
		element->LinkEndChild(text);
		InfoNode = InfoRoot->InsertEndChild(*element);
	}

#ifdef _DEBUG_LOGIN
	doc.Print();	
#endif
	doc.SaveFile( "./.config.xml" );
    
	return 0 ;
}


int DealConf::ReadXML()
{
    TiXmlDocument xmlDoc("./config.xml");
    if(xmlDoc.LoadFile() == false)
	    return -1;
   
    TiXmlElement* xmlRootElement = 0 ;
    TiXmlElement* xmlSubElement = 0 ;
    TiXmlNode * pNode = NULL;
   
    pNode = xmlDoc.FirstChild("UserInfo");
    xmlRootElement = pNode->ToElement();
   
    if(xmlRootElement)
    {
        pNode = xmlRootElement->FirstChild("username");

	if(pNode != 0){
        	xmlSubElement = pNode->ToElement();
		username_r = xmlSubElement->GetText();
	}
        //cout << xmlSubElement->Value() << endl;
        //cout << xmlSubElement->GetText() << endl;
    }
    else
    {
        cout << "找不到根元素" << endl ;
	return -2;
    }
   
    if(xmlRootElement)
    {
        pNode = xmlRootElement->FirstChild("password");

	if(pNode != 0){
        	xmlSubElement = pNode->ToElement();
		password_r = xmlSubElement->GetText();
	}
        //cout << xmlSubElement->Value() << endl;
        //cout << xmlSubElement->GetText() << endl;
    }
    else
    {
        cout << "找不到根元素" << endl ;
	return -2;
    }

    return 0 ;
}

#ifdef _TEST
int main(int argc, char *argv[])
{
    cout << "开始测试!" <<endl;

    DealConf dealconf;

    string username = "string.tang@gmail.com";
    string password = "1984";
   
    dealconf.WriteXML(username, password);
    dealconf.ReadXML();
    cout << "UserName: " << dealconf.username_r << endl;
    cout << "Password: " << dealconf.password_r << endl;

    cout << "结束测试!" << endl ;
   
    return 0;
}
#endif
