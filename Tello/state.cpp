//
//  state.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 23.04.23.
//
#include "pch.h"
#include "state.hpp"

State::State(){};

void State::setLanded(bool x){
    isLanded = x;
}

bool State::getLanded(){
    return isLanded;
}
