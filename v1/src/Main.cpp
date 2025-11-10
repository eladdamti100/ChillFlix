#include "ConsoleMenu.h"
#include "App.h"
#include "Movies.h"
#include "Users.h"
#include "DataManagement.h"
#include "AddCommand.h"
#include "RecommendCommand.h"
#include "HelpCommand.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {

    // Map to hold user ID and a set of movie IDs that the user has watched
    map<int, unordered_set<int>> userMovies;
    
    // Create main components
    Movies movies;
    Users users;
    DataManagement dataManagement(userMovies) ;


    // Load data
    dataManagement.LoadUsersData();
    users.LoadUsersData(userMovies);

    // Create menu
    ConsoleMenu menu;

    // Create commands map
    map<string, ICommand*> commands;

    // Create and add commands
    ICommand* addCommand = new AddCommand(movies, users, dataManagement);
    commands["add"] = addCommand;
    
    // for future changes to add the recommend commend
    ICommand* recommendCommand = new RecommendCommand(movies, users, dataManagement);
    commands["recommend"] = recommendCommand;

    ICommand* helpCommand = new HelpCommand();
    commands["help"] = helpCommand;
    

    // Create app
    App app(&menu, commands);

    // Run the app
    app.run();

    // Clean up
    delete addCommand;
    delete recommendCommand;
    delete helpCommand;

    return 0;
}