/*
 * DataBase.cpp
 *
 *  Created on: 20-Apr-2020
 *      Author: sudarshan
 */

#include "DataBase.h"

DataBase::DataBase(Connection &connection):m_passcode(PASSCODE),m_index(0),m_menuNum(0),ObjectAdaptor(connection,SERVER_PATH) {
	system("cd ../ && rm -rf result && mkdir result");
	m_resultFile.open("../result/MenuList.txt");
	if(m_resultFile.is_open()){
		m_resultFile<<"          .........................................********  MENU LIST  ********...................................................\n\n"<<std::endl;
	}else{
		std::cout<<"Some problem in Creating Result file\n";
	}
}

DataBase::~DataBase() {
	std::cout<<"Database closed\n";
	m_resultFile.close();
}

int DataBase::AddClient_A(ClientInfo info) {
	std::cout<<"Added Client --> "<<info.id<<"  "<<info.name<<"\n";
	m_Clientlist.emplace_back(info);
	return 0;
}

int DataBase::RemoveClient_A(str_t name, int passcode) {
	if(m_passcode==passcode){
		for(auto it=m_Clientlist.begin();it<m_Clientlist.end();it++){
			if((*it).name==name){
				std::cout<<"Removed Client --> "<<(*it).id<<"  "<<(*it).name<<"\n";
				saveToResultFile((*it).id,name);
				m_Clientlist.erase(it);
				return 0;
			}
		}
		return -1;
	}
	return -1;
}

int DataBase::UpdateMenuList_A(int passwrd, MenuInfo elements) {
	if(passwrd==m_passcode){
		m_menuNum++;
		elements.menuNum=m_menuNum;
		return appendMenu(elements);
	}
	return -1;
}

int DataBase::GetClientListSize_A() {
	m_index=m_Clientlist.size();
	return m_index;
}

int DataBase::GetMenuListSize_A() {
	m_index=m_MenuList.size();
	return m_index;
}

ClientInfo DataBase::GetClientInfo_A() {
	auto ret = m_Clientlist[m_index-1];
	m_index--;
	return ret;
}

MenuInfo DataBase::GetMenuInfo_A() {
	auto ret = m_MenuList[m_index-1];
	m_index--;
	return ret;
}


//Adaptor function implementations

::DBus::Struct<std::string, int32_t> DataBase::GetClientInfo() {
	auto res = GetClientInfo_A();
	::DBus::Struct<std::string, int32_t> ret;
	ret={res.name,res.id};
	return ret;
}

::DBus::Struct<int32_t, int32_t, std::string, std::string> DataBase::GetMenuInfo() {
	auto res = GetMenuInfo_A();
	::DBus::Struct<int32_t, int32_t, std::string, std::string> ret;
	ret={res.menuNum,res.clientId,res.menuName,res.details};
	return ret;
}

int32_t DataBase::AddClient(const ::DBus::Struct<std::string, int32_t> &info) {
	ClientInfo client={info._1,info._2};
	auto res=AddClient_A(client);
	return reinterpret_cast<int32_t>(res);
}

int32_t DataBase::RemoveClient(const std::string &name,
		const int32_t &passcode) {
	auto ret=RemoveClient_A(name,passcode);
	return reinterpret_cast<int32_t>(ret);
}

int32_t DataBase::UpdateMenuList(const int32_t &password,
		const ::DBus::Struct<int32_t, int32_t, std::string, std::string> &elements) {
	MenuInfo menu={elements._1,elements._2,elements._3,elements._4};
	auto res=UpdateMenuList_A(password,menu);
	return reinterpret_cast<int32_t>(res);
}

int32_t DataBase::GetClientListSize() {
	return reinterpret_cast<int32_t>(GetClientListSize_A());
}

int32_t DataBase::GetMenuListSize() {
	return reinterpret_cast<int32_t>(GetMenuListSize_A());
}

//private functions

int DataBase::appendMenu(MenuInfo menu_Elements) {
	m_MenuList.emplace_back(menu_Elements);
	return 0;
}

int DataBase::saveToResultFile(int clientId, str_t clientName) {
	for(auto i=m_MenuList.begin();i<m_MenuList.end();i++){
		if((*i).clientId==clientId){
			if(m_resultFile.is_open()){
				m_resultFile<<"Menu Name : "<<(*i).menuName<<"\nMenu Adder : "<<clientName<<"\nMenu content : "<<(*i).details<<"\n\n"<<std::endl;
			}else{
				std::cout<<"Some problem in opening/saving file\n";
			}
			m_MenuList.erase(i);
		}
	}
	return 0;
}

BusDispatcher dispatcher;

void sigFun(int sig){
	dispatcher.leave();
}


int main(){

	signal(SIGTERM,sigFun);
	signal(SIGINT,sigFun);

	DBus::default_dispatcher = &dispatcher;
	DBus::Connection conn = DBus::Connection::SessionBus();
	conn.request_name(SERVER_NAME);

	DataBase db(conn);

	std::cout<<"Connected................................ \n";

	dispatcher.enter();
	//conn.disconnect();
	return 0;
}
