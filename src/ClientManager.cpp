/*
 * ClientManager.cpp
 *
 *  Created on: 20-Apr-2020
 *      Author: sudarshan
 */

#include "ClientManager.h"

ClientManager::ClientManager(Connection &connection, Path& path, const char *name):m_db(nullptr),m_currentClientName(""),m_ClientCnt(0),m_CurrentClientId(0) {
	// TODO Auto-generated constructor stub
	m_db=new DataBaseClient(connection,path,name);
}

ClientManager::~ClientManager() {
	// TODO Auto-generated destructor stub
	this->DestroyClient(m_currentClientName,123);
	delete m_db;
	m_db=nullptr;
}

int ClientManager::CreateClient(str_t name) {
	m_ClientCnt++;
	m_currentClientName=name;
	auto id =m_ClientCnt+getUniqueId();
	if(id<=1)return -1;
	m_CurrentClientId=id;
	Client_Info info = {name,id};
	return m_db->AddClient_p(info);
}

int ClientManager::DestroyClient(str_t name, int passcode) {
	return m_db->RemoveClient_p(name,passcode);
}

int ClientManager::DisplayActiveClients() {
	return m_db->DisplayActiveClients_p();
}

int ClientManager::DisplayMenuList() {
	return m_db->DisplayMenuList_p();
}

int ClientManager::DeleteMenu(str_t name, int passcode) {
	return 0;
}

int ClientManager::UpdateMenuList(int passcode, MenuInfo elements) {
	elements.clientId=m_CurrentClientId;
	return m_db->UpdateMenuList_p(passcode,elements);
}

int ClientManager::getUniqueId() {
	time_t t(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	return t%100000;
}

static bool spin = true;
BusDispatcher dispatcher;

void sigFun(int sig){
	spin = false;
	dispatcher.leave();
}

int main(){
	signal(SIGTERM,sigFun);
	signal(SIGINT,sigFun);
	DBus::_init_threading();
	DBus::default_dispatcher = &dispatcher;
	DBus::Connection conn = DBus::Connection::SessionBus();

	ClientManager clientmgr(conn,SERVER_PATH,SERVER_NAME);
	std::cout<<".!!!!!!!!!.......Connected......!!!!!!!!.. \n\n";

	std::cout<<"Enter Your Name.......\n";
	str_t name;
	getline(std::cin,name);

	if(clientmgr.CreateClient(name)==0){
		std::cout<<"\nClient created Successfully...!!!\n";
	}else{
		std::cout<<"\nCould not create Client......Failed...!!!\n";
	}

	int choice=0;
	while(choice!=4){
		std::cout<<"\n\n1.......Write/Update menu .....\n"
				"2.......Display all menu Lists... \n"
				"3.......Display all clients ... \n"
				"4.......Save/Exit.......\n\n";

		std::cin>>choice;

		switch(choice){
		case 1:{
			std::cout<<"Enter a Menu name \n";
			str_t menuName;
			std::cin.ignore();
			getline(std::cin,menuName);
			int menuNum=0;

			std::cout<<"Write Menu content \n";
			str_t content;
			getline(std::cin,content);

			MenuInfo info;
			info={menuNum,0,menuName,content};

			int passcd;
			std::cout<<"Enter the passcode \n";
			std::cin>>passcd;

			if(clientmgr.UpdateMenuList(passcd,info)==0){
				std::cout<<"\nMenu list updated Successfully.....!!!!\n";
			}else{
				std::cout<<"\nMenu list update Failed..!!!... Passcode is wrong... \n";
			}
			break;
		}
		case 2:{
			std::cout<<"\n................. MENU LIST .................\n\n";
			clientmgr.DisplayMenuList();
			break;
		}
		case 3:{
			std::cout<<"\n................. CLIENT LIST .................\n\n";
			clientmgr.DisplayActiveClients();
			break;
		}
		case 4:{
			std::cout<<"Application Terminated.....Client destroyed......Menu list saved to result file...!!!!.. \n";
			return 0;
		}
		default:{
			std::cout<<"Application Abruptly Terminated..... \n";
			return 0;
		}
		}

	}

	return 0;
	//dispatcher.enter();
	//conn.disconnect();
}

