//
//  tellocontrol.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 07.04.23.
//

#ifndef tellocontrol_hpp
#define tellocontrol_hpp

#include "udpclient.hpp"
#include "itellocontrol.hpp"
#include "state.hpp"

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

class TelloControl : public ITelloControl
{
public:
    TelloControl();
    char* genericCommand(const char* message) override;
    
    ///Status-->Read
    int batteryLevel() override;
    int speed() override;
    int time() override;
    int wifi() override;
    
    
    ///new Control ------->>>>> check the space between letters in commands ? 
    bool takeoff() override;
    bool land() override;
    bool streamon() override;
    bool streamoff() override;
    bool emergency() override;
    
    bool up(int x) override;
    bool down(int x) override;
    bool left(int x) override;
    bool right(int x) override;
    bool forward(int x) override;
    bool back(int x) override;
    bool cwx(int x) override;
    bool ccw(int x) override;
    bool flip(string x) override;/// X---> l,r,f,b
    bool goXYZSpeed(int x, int y, int z, int speed) override;
    
    bool stop() override;
    
    bool executeFlightPlan(const char* filePath);
    
    
private:
    std::shared_ptr<State> state;
    std::shared_ptr<UdpClient> udpClient;
    bool boolResult(char* const input);

};

#endif /* tellocontrol_hpp */
