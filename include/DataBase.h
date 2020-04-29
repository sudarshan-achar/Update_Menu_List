/*
 * DataBase.h
 *
 *  Created on: 20-Apr-2020
 *      Author: sudarshan
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "types.h"
#include "adaptor_d.h"
#include <vector>
#include <iterator>

using namespace com::example;
using namespace DBus;

Path SERVER_PATH = "/com/example/UpdateList";
static const char* SERVER_NAME = "com.example.UpdateList";


class DataBase : public  UpdateList_adaptor , public IntrospectableAdaptor, public ObjectAdaptor{
public:
	DataBase(Connection &connection);
	virtual ~DataBase();
	DataBase(const DataBase &other)=delete;
	DataBase(DataBase &&other)=delete;
	DataBase& operator=(const DataBase &other)=delete;
	DataBase& operator=(DataBase &&other)=delete;

public:
	int AddClient_A(ClientInfo info);
	int RemoveClient_A(str_t name, int passcode);
	int UpdateMenuList_A(int passwrd,MenuInfo elements);
	int GetClientListSize_A();
	int GetMenuListSize_A();
	ClientInfo GetClientInfo_A();
	MenuInfo GetMenuInfo_A();

public:
	//Adaptor function

    int32_t AddClient(const ::DBus::Struct< std::string, int32_t >& info);
    int32_t RemoveClient(const std::string& name, const int32_t& passcode);
    int32_t UpdateMenuList(const int32_t& password, const ::DBus::Struct< int32_t, int32_t, std::string, std::string >& elements);
    int32_t GetClientListSize();
    int32_t GetMenuListSize();
	::DBus::Struct< std::string, int32_t > GetClientInfo();
	::DBus::Struct< int32_t, int32_t, std::string, std::string > GetMenuInfo();

private:
	int appendMenu(MenuInfo);

private:
	std::vector<ClientInfo> m_Clientlist;
	std::vector<MenuInfo> m_MenuList;

private:
	int m_passcode;
	int m_menuNum;
	int m_index;
};

#endif /* DATABASE_H_ */
