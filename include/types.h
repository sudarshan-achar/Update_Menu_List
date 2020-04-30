/*
 * types.h
 *
 *  Created on: 20-Apr-2020
 *      Author: sudarshan
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <unordered_map>

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <dbus-c++/dbus.h>

constexpr int PASSCODE=123;

using  str_t = std::string;

using ClientInfo = struct Client_Info{
	str_t name;
	int id;
};

using  MenuInfo = struct Menu_Elements{
	int menuNum;
	int clientId;
	str_t menuName;
	str_t details;
};

#endif /* TYPES_H_ */
