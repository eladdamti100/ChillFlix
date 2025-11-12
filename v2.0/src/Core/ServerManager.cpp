#include "ServerManager.h"

#define BUFFER_SIZE 4096

ServerManager::ServerManager(int port, IMenu* menu, const map<string, ICommand*>& commands) 
    : port(port), serverSocket(-1), menu(menu), commands(commands) {}

ServerManager::~ServerManager() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}
// Function to split the received message into commandKey and remainingInput
void splitMessage(const std::string& receivedMessage, std::string& commandKey, std::string& remainingInput) {
    istringstream messageStream(receivedMessage);

    // Extract the command key (first word)
    if (!(messageStream >> commandKey)) {
        commandKey.clear(); // If no command key, clear it
    }

    // Extract the remaining input
    getline(messageStream, remainingInput);

    // Trim leading space from the remaining input
    if (!remainingInput.empty() && remainingInput[0] == ' ') {
        remainingInput.erase(0, 1);
    }
}

void ServerManager::handleClient(int clientSocket, App* app) {
    char buffer[BUFFER_SIZE] = {0};

    while (true) {
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Receive command from the client
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        
        if (bytesRead <= 0) {
            // Client disconnected
            cout << "Client disconnected." << endl;
            break;  // Exit the loop if the client disconnects
        }

        // Convert the received string to a C++ string
        string receivedMessage(buffer);

        // Variables for the split message
        string commandKey;
        string remainingInput;

        // Split the received message
        splitMessage(receivedMessage, commandKey, remainingInput);

        // If command is empty, ontinue waiting for input
        if (commandKey.empty()) {
            //cout << "Empty command received." << endl;
            string errorResponse = StatusHandler::getStatusMessage(400);
            send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
            continue;  // Don't exit, continue waiting for more input
        }

        string response;
        // Execute the corresponding command if it exists
        if (commands.find(commandKey) != commands.end()) {
            response = commands[commandKey]->execute(remainingInput);
            // If return value is empty but the command is good
            if (response.empty()) {
                //cout << "Command executed successfully, no response to send." << std::endl;
                string errorResponse = StatusHandler::getStatusMessage(404);
                send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
            } else {
                // Send the valid response
                send(clientSocket, response.c_str(), response.size(), 0);
            }
        } else {
            // If the command does not exist, send an error response
            string errorResponse = StatusHandler::getStatusMessage(400);
            send(clientSocket, errorResponse.c_str(), errorResponse.size(), 0);
        }
    }

    close(clientSocket);  // Close the client connection after the loop ends
}

void ServerManager::start(App* app) {

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        return;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        return;
    }

    cout << "Server is listening on port " << port << endl;

    // Accept and handle client connections
    while (true) {

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        cout << "New connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;

        // Create a new thread to handle the client
        thread clientThread(&ServerManager::handleClient, this, clientSocket, app);
        clientThread.detach(); // Detach the thread to allow independent handling
    }

    close(serverSocket); // Close the server socket
}