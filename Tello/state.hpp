//
//  state.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 23.04.23.
//

#ifndef state_hpp
#define state_hpp

#include <stdio.h>

class State
{
public:
    State();
    void setLanded(bool x);
    bool getLanded();
    void setStreamStatus(bool x);
    bool getStreamStatus();
    bool getOnline();
    void setOnline(bool x);
    
private:
    bool isLanded = true;
    bool isStreamOn = false;
    bool isOnline = false;
};
#endif /* state_hpp */
