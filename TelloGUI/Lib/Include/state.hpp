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
    
private:
    bool isLanded = true;

};
#endif /* state_hpp */
