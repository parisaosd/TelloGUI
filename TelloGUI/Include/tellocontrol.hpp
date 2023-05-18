//
//  tellocontrol.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 07.04.23.
//

#ifndef tellocontrol_hpp
#define tellocontrol_hpp

#include "udpclient.hpp"

#include "state.hpp"

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

class TelloControl
{
public:
    TelloControl();
    char* genericCommand(const char* message);
    
    ///Status-->Read
    int batteryLevel();
    int speed();
    int time();
    int wifi();
    
    
    ///new Control ------->>>>> check the space between letters in commands ? 
    bool takeoff();
    bool land();
    bool streamon();
    bool streamoff();
    bool emergency();
    
    bool up(int x);
    bool down(int x);
    bool left(int x);
    bool right(int x);
    bool forward(int x);
    bool back(int x);
    bool cwx(int x);
    bool ccw(int x);
    bool flip(string x);/// X---> l,r,f,b
    bool goXYZSpeed(int x, int y, int z, int speed);
    
    bool stop();
    
    bool executeFlightPlan(const char* filePath);
    
    
private:
    std::shared_ptr<State> state;
    std::shared_ptr<UdpClient> udpClient;
    bool boolResult(char* const input);

};

#endif /* tellocontrol_hpp */
