#include "AddCommand.h"

// Constructor implementation
AddCommand::AddCommand(Movies& moviesRef, Users& usersRef, DataManagement& dataManagementRef)
    : movies(moviesRef), users(usersRef), dataManagement(dataManagementRef){}

// Implementation of the execute method
void AddCommand::execute(const std::string& input) {
    long int userID;
    string moviesIDs;
        
    if (input.empty()) {
        return;
    }

    istringstream stream(input);

    // Validate user ID
    if (!(stream >> userID) || !users.CheckIfUserID_OK(userID)) {
        //cout << "Invalid input. User ID must be a positive integer." << endl;
        return;
    }

    //cout << "User ID: " << userID << endl; // (DEBUG)

    // Collect and validate movie IDs
    string movieID;
    bool validCommand = false;

    while (stream >> movieID) {
        validCommand = true; // At least one movie ID is required
                
        try {
            long int movieIDInt = stoi(movieID);
            if (!movies.isMovieValid(movieIDInt)) {
               // cout << "Error: Invalid movie ID entered: " << movieID << endl;
                return;
            }
            moviesIDs += movieID + " ";
        } catch (const exception& e) {
           // cout << "Exception cause: " << movieID << " Cause: " << e.what() << endl;
            return;
        }
    }

    if (!validCommand) {
        // Command must contain at least one movie ID
        return;
    }
     
        // Add movies to the user's list
        users.AddMoviesToUser(userID, moviesIDs);

        // Update the user-movie file
        dataManagement.updateUserMoviesFile(userID);

        // Print updated user-movie data (DEBUG)
     //   users.PrintUser_Movies(); 
}
