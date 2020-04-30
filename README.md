# Update_Menu_List
An application which is built using D-Bus IPC/RPC mechanism to Maintain a Central Menu list (as a single server) which can be accessed by Multiple Updaters (Clients), who have the common password to update data(Menulist).

Uses dbus-c++ libraries to connect to dbus c libs (libdbus-c++ should be kept installed).
Uses dbusxx-xml2cpp tool to generate Proxy-Adapter files to use Dbus RPC techniques.
Uses Cross compilation technique Cmake (cmake needs to be installed).

Commands to compile and Run the project:

1. Clone the project contents.
2. Open terminal in Project base directory.
3. Execute below commands
   * mkdir build && cd build
   * cmake ../
   * make
4. First run the Source binary in the current terminal.
5. Open different terminals windows at the same location and run the Client binary.
6. Use 123 as passcode/password (Refer types.h).
7. Analyse output at terminal pannel as well as in result directory.
