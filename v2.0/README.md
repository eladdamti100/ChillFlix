# Netflix-part-2

## Overview

This project is a server-client-based movie management application. The server processes commands and interacts with multiple clients through socket-based communication. The clients send structured commands to the server to perform operations such as managing user profiles, adding or removing movies, and requesting data. Each command follows a standardized format to ensure consistent and efficient communication.

The server and clients communicate efficiently to handle requests and responses accurately.

## Installation and Compilation

To compile the project, ensure you have a C++17-compatible compiler (e.g., g++) installed on your system. Follow these steps:

### Navigate to the src directory:

##### cd src

### Compile the project:

##### docker build -t netflix -f Dockerfile ..

### Running the Server

To run the server, use the following command:

##### docker run --name netflix netflix ./Netflix 6969

or use:

##### docker run -p 6969:6969 --name netflix netflix ./Netflix 6969
(To expose the port to the host for external access)

The 6969 is the port number the server will listen on. You can replace it with any other port number as needed.

![image](https://github.com/user-attachments/assets/2c089dd3-57f4-44e9-aca1-e9007c8dd145)

to run it again after the first run, use the following command:

##### docker start -i netflix

### Running the Client

To run the client, follow these steps:

##### Open a new terminal.

Navigate to the src directory:

##### cd src

Run the client with the following command:

##### docker run -it --rm netflix python3 ClientManager.py 172.17.0.2 6969

Replace 172.17.0.2 with the IP address of the server. 

use this command when the server run to find the server ip; docker inspect netflix | Select-String "IPAddress" 

Replace 6969 with the port number the server is listening on.

![image](https://github.com/user-attachments/assets/0ee120c4-e709-4628-8c84-0eeb87e935a9)

##### You can use this command to open multiple clients by running it in separate terminals.

![image](https://github.com/user-attachments/assets/b4089801-c375-4a1d-8bc1-cb6ad882755f)

### Running the Tests

To run the main tests, use the following command:

##### docker run --rm netflix ./CommandTests

This will execute the predefined test suite for the application.

![image](https://github.com/user-attachments/assets/00d7c6ef-c964-4567-90c3-6ddda31c0c0b)

### How to Use

The application supports the following commands:

##### POST, arguments: [userid] [movieid1] [movieid2] ...

Add movies to a user profile. This command is valid only if the user does not already exist. A successful command returns:

201 Created

##### PATCH, arguments: [userid] [movieid1] [movieid2] ...

Add movies to an existing user profile. This command is valid only if the user already exists. A successful command returns:

204 No Content

##### DELETE, arguments: [userid] [movieid1] [movieid2] ...

Remove movies from a user profile. A successful command returns:

204 No Content

##### GET, arguments: [userid] [movieid]

Get movie recommendations for a user. A successful command returns:

200 Ok

[recommendations]

##### help

View a list of all available commands. This command has no arguments.

## Design Decisions Regarding Open-Closed Principle

#### The project was implemented with the Open-Closed Principle in mind, ensuring that the code is open for extension but closed for modification. Here is how we addressed this principle when implementing the project:

### Adding New Commands:

The implementation uses an abstract class ICommand for all commands. This abstraction allows us to add new commands (e.g., POST, PATCH, GET, DELETE) without modifying existing code.

Each command implements the execute() function, which ensures new functionality can be added easily while adhering to a common interface.

For example:

POSTCommand: Adds a new user with movies.

PATCHCommand: Updates an existing user profile.

DELETECommand: Removes movies from a user's profile.

New commands can be introduced by simply creating a new class that inherits from ICommand and implementing its behavior.

### Console Input vs Socket Communication:

In the previous part of the project, the ConsoleMenu class handled all user input through the console. To adapt to socket-based communication, we introduced a ServerManager class that replaces the console implementation.

This was achieved without changing the core logic for handling commands. The separation of input/output management ensures that adding new input sources (e.g., sockets) does not affect command execution.

### Output Changes:

The project uses a centralized StatusHandler class to generate status messages (e.g., 201 Created, 204 No Content, 400 Bad Request).

By centralizing the output handling, changes to status messages were implemented without modifying the logic of individual commands.

### Reusability of User and Movie Data:

The DataManagement and Users classes were reused from the previous implementation with minimal changes.

We introduced a function in the Users class to check if a user already exists, enabling the implementation of the PATCH command.

Additionally, we added functionality to delete movies from a user's watchlist to support the DELETE command.

These changes were isolated and did not interfere with the overall structure, ensuring adherence to the Open-Closed Principle.

## File Structure:

### UML:
![uml part 2](https://github.com/user-attachments/assets/db33f55a-b89d-4da8-a522-6eb595698e32)


##### Main.cpp: Entry point for the application.

##### Commands/POSTCommand.cpp/h: Handles adding movies to a user's profile. The command is valid only if the user does not already exist.

##### Commands/PATCHCommand.cpp/h: Updates movies for an existing user. The command is valid only if the user already exists.

##### Commands/DELETECommand.cpp/h: Deletes specified movies from a user's profile.

##### Commands/GETCommand.cpp/h: Retrieves movie data or recommendations for a user.

##### Commands/HelpCommand.cpp/h: Provides help documentation for commands.

##### Core/ServerManager.cpp/h: Manages the server-side communication and command handling.

##### Core/ClientManager.py: Client-side script for sending commands to the server.

##### Models/DataManagement.cpp/h: Manages data storage, user profiles, and movie entries.

##### Models/Users.cpp/h: Manages user profiles, including watchlists.

##### Models/Movies.cpp/h: Stores and validates movie information.

##### Tests/: Contains unit tests for various modules.

##### Utilities/StatusHandler.cpp/h: Handles status responses sent from the server.

## General Example of Running the Code

![image](https://github.com/user-attachments/assets/aa12e571-62c3-47f2-bbb4-cd02325372cb)

### Notes

Ensure all required .cpp and .h files are in the same directory for successful compilation. Additional unit tests are available in the Tests directory to validate functionality. For issues or suggestions, feel free to contact the developer.
