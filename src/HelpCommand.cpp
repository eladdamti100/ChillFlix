#include "HelpCommand.h"
#include <sstream>
#include <iostream>

// Constructor
HelpCommand::HelpCommand() {}

// Implementation of execute()
void HelpCommand::execute(const std::string& input) {
    // Making sure only help will activate this command (allow empty spaces)
    string empty;
    istringstream stream(input);
    while (stream >> empty ) {
        return;
    }

    // Display help information
    cout << endl << "add[userid] [movieid1] [movieid2]..." << endl;
    cout << "recommend [userid] [movieid]" << endl;
    cout << "help" << endl <<endl;

}