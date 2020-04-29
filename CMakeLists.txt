cmake_minimum_required(VERSION 3.2)
project(Update_Menu_List)

find_package(DBus REQUIRED)
find_package(DBusCpp REQUIRED)

include_directories(${DBUS_INCLUDE_DIR})
include_directories(${DBUS_ARCH_INCLUDE_DIR})
include_directories(${GLIB_CONFIG_INCLUDE_DIR})
include_directories(${DBUSCPP_INCLUDE_DIR})

include_directories(include)

add_executable(Client src/ClientManager.cpp src/DataBaseClient.cpp)
add_executable(Server src/DataBase.cpp)

set (LIBS
	${LIBS}
	${DBUS_LIBRARIES}
	${DBUSCPP_LIBRARY}
)

target_link_libraries(Client ${LIBS})
target_link_libraries(Server ${LIBS})
