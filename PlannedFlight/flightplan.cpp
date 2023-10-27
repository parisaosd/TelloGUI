//
//  flightplan.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 15.04.23.
//
#include "pch.h"
#include "flightplan.hpp"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>


using namespace std;

///what is the right side ????
FlightPlan::FlightPlan(const char* filePath, std::shared_ptr<ITelloControl> telloControl) : telloControl(telloControl)
{
    FlightPlan::filePath = new string(filePath);
    flightPlanValidator = std::make_shared<FlightPlanValidator>();
    _emergencyStop = false;
    _commands = parse();
}

FlightPlan::~FlightPlan()
{
    delete filePath;
}

/// Commands in the uploaded flight plan is transferred  to an array of commands
vector<std::string> FlightPlan::parse(){
    vector<std::string> commands;
    std::string command;
    ifstream MyReadFile(filePath->c_str());
    while (getline (MyReadFile, command)) {
        commands.push_back(command);
    }
    MyReadFile.close();
    cout << "Parsed. Number of commands: " << commands.size() << endl;
    return commands;
}

/// Itterating through array of commands and calling the generic SDK command for each element of the array
bool FlightPlan::execute()
{
    _emergencyStop = false;
    for (string command : _commands)
    {
        if (_emergencyStop)
        {
            return false;
        }
        if(flightPlanValidator->isValid(command))
        {
            auto result = telloControl->genericCommand(command.data());
            if (strcmp(result, "ok") != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void FlightPlan::stop()
{
    _emergencyStop = true;
}



