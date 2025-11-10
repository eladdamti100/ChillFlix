# Netflix 
Netflix Recommendation System

Overview
This project is a simple command-line application designed to simulate a basic movie recommendation system. It allows users to:

Add a list of movies to a user's profile.
Request movie recommendations based on a user's preferences.
Display a help menu for available commands.
The system is implemented in C++ and includes various modules for handling commands, user data, and movie management.

File Structure:

UML 
![UML](https://github.com/user-attachments/assets/542b0953-948b-48b4-9d18-7a2e8ed66b52)

Main.cpp: Entry point for the application.
AddCommand.cpp/h: Handles adding movies to a user's profile.
ConsoleMenu.cpp/h: Manages interaction with the user.
RecommendCommand.cpp/h: Generates movie recommendations.
HelpCommand.cpp/h: Provides help documentation for commands.
DataManagement.cpp/h: Manages data storage and retrieval.
Users.cpp/h: Stores information about available users and their watchlist.
Movies.cpp/h: Stores information about available movies (right now only check if movie valid).
Tests/: Contains unit tests for various modules.

Installation and Compilation

To compile the project, ensure you have a C++17-compatible compiler (e.g., g++) installed on your system. Follow these steps:

1.Navigate to the src directory:

cd src

2.Compile the project:

docker build -t netflix -f Dockerfile ..

3.Run the compiled executable:

for main app: docker run -it --name netflix netflix
![צילום מסך 2024-12-05 163126](https://github.com/user-attachments/assets/00261906-292a-4090-9b20-0e6a74afda27)


In order to run the app with the data saved from previous executions, you need to execute the following command: docker start -ai netflix

for main tests: docker run --rm netflix ./CommandTests
![צילום מסך 2024-12-05 153029](https://github.com/user-attachments/assets/0d8adc10-ff7b-400a-8477-850b54ce72e5)


How to Use:
The application supports the following commands:

Add movies to a user profile:
add [userid] [movieid1] [movieid2] ...

Get movie recommendations:
recommend [userid] [movieid]

View help menu:
help


Notes

Ensure all required .cpp and .h files are in the same directory for successful compilation.
Additional unit tests are available in the Tests directory to validate functionality.
For issues or suggestions, feel free to contact the developer.









