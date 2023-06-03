//
//  flightplan.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 15.04.23.
//
#include "pch.h"
#include "flightplan.hpp"
//#include "flightPlanValidator.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>


using namespace std;

///what is the right side ????
FlightPlan::FlightPlan(const char* filePath,TelloControl &telloControl) : telloControl(telloControl)
{
    FlightPlan::filePath = new string(filePath);
    flightPlanValidator = std::make_shared<FlightPlanValidator>();
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
    return commands;
}

/// Itterating through array of commands and calling the generic SDK command for each element of the array
bool FlightPlan::execute()
{
    
    const auto commands = parse();
    cout<<"Executing flight plan. Number of commands: "<<commands.size()<<endl;
    for (string command : commands)
    {
        if(flightPlanValidator->isValid(command))
        {
            auto result = telloControl.genericCommand(command.data());
            if (strcmp(result, "ok") != 0)
            {
                return false;
            }
        }
    }
    return true;
}



