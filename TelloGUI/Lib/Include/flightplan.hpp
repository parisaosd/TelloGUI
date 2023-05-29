//
//  flightplan.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 15.04.23.
//

#ifndef flightplan_hpp
#define flightplan_hpp

#include "tellocontrol.hpp"
#include "flightPlanValidator.hpp"

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


class FlightPlan
{
public:
    FlightPlan(const char* filePath,TelloControl &telloControl);
    ~FlightPlan();
    bool execute();
    
private:
    string* filePath;
    vector<std::string> parse();
    TelloControl& telloControl;///???? is it the address of telloControl object????
    std::shared_ptr<FlightPlanValidator> flightPlanValidator;
};

#endif /* flightplan_hpp */
