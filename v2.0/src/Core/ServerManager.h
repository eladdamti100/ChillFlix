#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "ConsoleMenu.h"
#include "App.h"
#include <string>
#include <thread>
#include <iostream>
#include <sstream>
#include <map>
#include <sstream>   // For std::istringstream
#include <cstring>   // For memset
#include "StatusHandler.h"      // For Handle with Errors
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

class ServerManager {
private:

    int port;
    int serverSocket;

    IMenu* menu;                          // Pointer to a menu object
    map<string, ICommand*> commands; // Map of command keys to ICommand objects

    void handleClient(int clientSocket, App* app);

public:
    ServerManager(int port, IMenu* menu, const map<string, ICommand*>& commands);
    ~ServerManager();
    void start(App* app);

};

#endif // SERVER_MANAGER_H