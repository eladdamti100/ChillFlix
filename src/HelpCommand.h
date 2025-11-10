#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "ICommand.h"          // Base ICommand interface
#include <iostream>
#include <string>
using namespace std;

class HelpCommand : public ICommand {
public:
    // Constructor
    HelpCommand();

    // Overriding execute() method from ICommand
    void execute(const std::string& input) override;
};

#endif // HELPCOMMAND_H