/*
 * DataBaseClient.cpp
 *
 *  Created on: 21-Apr-2020
 *      Author: sudarshan
 */

#include "DataBaseClient.h"

DataBaseClient::DataBaseClient(Connection &connection, Path& path, const char *name):ObjectProxy(connection,path,name){
	// TODO Auto-generated constructor stub
}

DataBaseClient::~DataBaseClient() {
	// TODO Auto-generated destructor stub
}

int DataBaseClient::AddClient_p(ClientInfo info) {
	::DBus::Struct< std::string, int32_t> _info;
	_info ={info.name,info.id};
	return AddClient(_info);
}

int DataBaseClient::RemoveClient_p(str_t name, int passcode) {
	return RemoveClient(name,passcode);
}

int DataBaseClient::UpdateMenuList_p(int passwrd, MenuInfo elements) {
	::DBus::Struct< int32_t, int32_t, std::string, std::string > ele;
	ele={elements.menuNum,elements.clientId,elements.menuName,elements.details};
	return UpdateMenuList(passwrd,ele);
}

int DataBaseClient::DisplayActiveClients_p() {
    auto count = GetClientListSize();
    for(auto i=0;i<count;i++){
    	auto _client = GetClientInfo();
    	ClientInfo client ={_client._1,_client._2};
    	std::cout<<"Client name : "<<client.name<<"     Id : "<<client.id<<"\n";
    }
    return 0;
}

int DataBaseClient::DisplayMenuList_p() {
	auto count = GetMenuListSize();
	for(auto i=0;i<count;i++){
		auto _menu = GetMenuInfo();
		MenuInfo menu={_menu._1,_menu._2,_menu._3,_menu._4};
		std::cout<<"Menu name : "<<menu.menuName<<"\nMenu Id : "<<menu.menuNum<<"\nClient Id : "<<menu.clientId<<"\nMenu Content : "<<menu.details<<"\n\n";
	}
	return 0;
}
