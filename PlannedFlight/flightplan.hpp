//
//  flightplan.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 15.04.23.
//

#ifndef flightplan_hpp
#define flightplan_hpp

#include "../Tello/itellocontrol.hpp"
#include "flightPlanValidator.hpp"

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class FlightPlan
{
public:
    FlightPlan(const char* filePath, std::shared_ptr<ITelloControl> telloControl);
    ~FlightPlan();
    bool execute();
    void stop();
    
private:
    string* filePath;
    vector<std::string> parse();
    std::shared_ptr<ITelloControl> telloControl;
    std::shared_ptr<FlightPlanValidator> flightPlanValidator;
    atomic<bool> _emergencyStop;
    std::vector<string> _commands;
};

#endif /* flightplan_hpp */
