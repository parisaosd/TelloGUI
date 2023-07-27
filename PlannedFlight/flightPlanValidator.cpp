//
//  flightPlanValidator.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 24.04.23.
//
#include "pch.h"
#include "flightPlanValidator.hpp"
#include <iostream>
#include <regex>
#include<string.h>

using namespace std;

FlightPlanValidator::FlightPlanValidator(){}

bool FlightPlanValidator::isValid(string command){
    /// Todo... add all commands to the array
    string sdkCommands[9]={"command","battery?","speed?","time?","wifi?","takeoff","land","streamoff","streamon"};
    for (int i = 0; i < sdkCommands->size(); i++)
    {
        regex r(command + "(.*)");
        smatch match;
        if(regex_search(sdkCommands[i], match, r)){
            return true;
        }
    }
    return false;
}
