#include "RecommendCommand.h"

// Constructor implementation
RecommendCommand::RecommendCommand(Movies& moviesRef, Users& usersRef, DataManagement& dataManagementRef)
    : movies(moviesRef), users(usersRef), dataManagement(dataManagementRef) {}

void RecommendCommand::execute(const std::string& input) {
    long int TheuserID, TheMovieID;
    
    // Clear the newMoviesToWatch vector to ensure it's empty for the new execution
    newMoviesToWatch.clear();
    
    
    if (input.empty()) {
        return;
    }

    istringstream stream(input);

    if (!(stream >> TheuserID) || !users.CheckIfUserID_OK(TheuserID)) {
       // cout << "Invalid input. User ID must be a positive integer." << endl; 
        return;
    }


    if (!(stream >> TheMovieID) || !movies.isMovieValid(TheMovieID)) { 
     //   cout << "Invalid input. Movie ID must be a positive integer." << endl;
        return;
    }

    string moreMovies;
    if(stream >> moreMovies) {
       // cout << "Invalid input. more then 1 Movie ID." << endl;
        return;
    }

    auto results = findSharedMovies(TheuserID, TheMovieID);

    //cout << "Shared movies with other users:" << endl;
    for (const auto& result : results) {
       // cout << "User ID: " << result.userID << ", Shared Movies: " << result.sharedMoviesCount << endl;
    }

    
    unordered_set<int> userMoviesSet = dataManagement.getUserMovies(TheuserID);
    if (userMoviesSet.empty()) {
      // cout << "No movies found for User ID " << TheuserID << "." << endl;
        return;
    }

    for (const auto& [userID, movies] : dataManagement.getAllUsersMovies()) {
        if (movies.find((TheMovieID)) != movies.end() && userID != TheuserID) {
        for (const auto& movieID : movies) {
            // Skip movies already watched by the target user
            if (userMoviesSet.find(movieID) != userMoviesSet.end()) {
                continue;
            }

            bool found = false;

            // Process the movie for recommendations
            for (auto& movie : newMoviesToWatch) {
                if (movie.movieID == movieID) {
                    int i = getSharedMoviesCountByUserID(results, userID);
                    movie.NumOfRecommendation += (1 * i);
                    found = true;
                    break;
                    }
                }

                if (!found) {
                    int j = getSharedMoviesCountByUserID(results, userID);
                    newMoviesToWatch.push_back(MovieData(1 * j, movieID));
                }
            }
        }
    }

    // Manual sorting (Selection Sort)
    for (int i = 0; i < newMoviesToWatch.size(); ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < newMoviesToWatch.size(); ++j) {
            //Sort them by score and if the score is the same sort the by ascending id
        if (newMoviesToWatch[j].NumOfRecommendation > newMoviesToWatch[maxIndex].NumOfRecommendation ||
            (newMoviesToWatch[j].NumOfRecommendation == newMoviesToWatch[maxIndex].NumOfRecommendation &&
            newMoviesToWatch[j].movieID < newMoviesToWatch[maxIndex].movieID)) {
            maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(newMoviesToWatch[i], newMoviesToWatch[maxIndex]);
        }
    }

    if (!newMoviesToWatch.empty()) { 
        bool printed = false;  // A flag to check if any movie is printed

        for (const auto& movie : newMoviesToWatch) {
            if (userMoviesSet.find(movie.movieID) == userMoviesSet.end() && movie.movieID != TheMovieID) {
                // Print the movie IDs 
                cout << movie.movieID << " ";
                printed = true;  // Set the flag to true when a movie is printed
            }
        }

        if (printed) {  // Only print the newline if any movie was printed
            cout << endl;
        }
    }
}


// Implementation of findSharedMovies
vector<SharedMoviesResult> RecommendCommand::findSharedMovies(long int userID, long int TheMovieID) {
    vector<SharedMoviesResult> sharedMoviesResults;

    const auto& currentUserMovies = dataManagement.getUserMovies(userID);
    if (currentUserMovies.empty()) {
       // cout << "No movies found for User ID " << userID << "." << endl;
        return sharedMoviesResults;
    }

    unordered_set<int> currentUserMoviesSet(currentUserMovies.begin(), currentUserMovies.end());

    for (const auto& [otherUserID, otherUserMovies] : dataManagement.getAllUsersMovies()) {
        // Skip the target user and users who haven't watched the target movie
        if (otherUserID == userID || otherUserMovies.find(TheMovieID) == otherUserMovies.end()) {
            continue;
        }
        
        int sharedCount = 0;
        for (int movieID : otherUserMovies) {
            if (currentUserMoviesSet.find(movieID) != currentUserMoviesSet.end()) {
                ++sharedCount;
            }
        }

        if (sharedCount > 0) {
            sharedMoviesResults.emplace_back(otherUserID, sharedCount);
        }
    }

    // Manual sorting (Bubble Sort)
    for (int i = 0; i < sharedMoviesResults.size(); ++i) {
        for (int j = 0; j < sharedMoviesResults.size() - i - 1; ++j) {
            if (sharedMoviesResults[j].sharedMoviesCount < sharedMoviesResults[j + 1].sharedMoviesCount) {
                swap(sharedMoviesResults[j], sharedMoviesResults[j + 1]);
            }
        }
    }

    return sharedMoviesResults;
}

// Implementation of getSharedMoviesCountByUserID
int RecommendCommand::getSharedMoviesCountByUserID(const vector<SharedMoviesResult>& results, int targetUserID) {
    for (const auto& result : results) {
        if (result.userID == targetUserID) {
            return result.sharedMoviesCount;
        }
    }

    //cout << "User ID: " << targetUserID << " not found." << endl;
    return -1;
}