/*
 * DataBaseClient.h
 *
 *  Created on: 21-Apr-2020
 *      Author: sudarshan
 */

#ifndef DATABASECLIENT_H_
#define DATABASECLIENT_H_

#include "types.h"
#include "proxy_d.h"

using namespace com::example;
using namespace DBus;

/*
 *
 */
class DataBaseClient : public UpdateList_proxy, public IntrospectableProxy, public ObjectProxy{
public:
	DataBaseClient(Connection &connection, Path& path, const char *name);
	virtual ~DataBaseClient();
	DataBaseClient(const DataBaseClient &other)=delete;
	DataBaseClient(DataBaseClient &&other)=delete;
	DataBaseClient& operator=(const DataBaseClient &other)=delete;
	DataBaseClient& operator=(DataBaseClient &&other)=delete;

public:
	int AddClient_p(ClientInfo info);
	int RemoveClient_p(str_t name, int passcode);
	int DisplayActiveClients_p();
	int DisplayMenuList_p();
	int UpdateMenuList_p(int passwrd,MenuInfo elements);

};

#endif /* DATABASECLIENT_H_ */
