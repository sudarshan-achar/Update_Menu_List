/*
 * ClientManager.h
 *
 *  Created on: 20-Apr-2020
 *      Author: sudarshan
 */

#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include <cstdio>
#include <cstring>
#include "DataBaseClient.h"

using namespace com::example;
using namespace DBus;

Path SERVER_PATH = "/com/example/UpdateList";
static const char* SERVER_NAME = "com.example.UpdateList";

#include <chrono>

class ClientManager {
public:
	ClientManager(Connection &connection, Path& path, const char *name);
	virtual ~ClientManager();
	ClientManager(const ClientManager &other)=delete;
	ClientManager(ClientManager &&other)=delete;
	ClientManager& operator=(const ClientManager &other)=delete;
	ClientManager& operator=(ClientManager &&other)=delete;

public:
	int CreateClient(str_t name);
	int DestroyClient(str_t name, int passcode);
	int DisplayActiveClients();
	int DisplayMenuList();
	int DeleteMenu(str_t name, int passcode);
	int UpdateMenuList(int passcode,MenuInfo elements);

private:
	int getUniqueId();

private:
	int m_ClientCnt;
	int m_CurrentClientId;
	str_t m_currentClientName;
	DataBaseClient *m_db;
};

#endif /* CLIENTMANAGER_H_ */
