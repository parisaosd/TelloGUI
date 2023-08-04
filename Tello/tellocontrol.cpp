//
//  tellocontrol.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 07.04.23.
//
#include "pch.h"
#include "tellocontrol.hpp"

#include "udpclient.hpp"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdexcept>

using namespace std;

TelloControl::TelloControl()
{
    udpClient = std::make_shared<UdpClient>(_strdup("192.168.10.1"), 8889);
    int attempts=5;
    while(attempts>0){
        if(boolResult(udpClient->send(_strdup("command")))){
            break;
        }
        attempts--;
        if (attempts==0) {
            throw new std::runtime_error("Cannot initiate sdk mode.");
        }
    }
    state = std::make_shared<State>();
}

char* TelloControl::genericCommand(const char* message)
{
    return udpClient->send(message);
}

cv::Mat TelloControl::getVideoFrame()
{
    if (_videoCapture == nullptr) {
        _videoCapture = std::make_shared<cv::VideoCapture>("udp://@0.0.0.0:11111");
        _videoCapture->set(cv::CAP_PROP_BUFFERSIZE, 0);
    }
    cv::Mat frame;
    _videoCapture->read(frame);
    _latestFrame = frame;
    return frame;
}

bool TelloControl::isStreamOn()
{
    return state->getStreamStatus();
}

bool TelloControl::saveScreenshotJpeg(std::string filename)
{
    if (!isStreamOn() || _videoCapture == nullptr || !_videoCapture->isOpened())
    {
        return false;
    }
    cv::imwrite(filename + ".jpg", _latestFrame);
    return true;
}

/// Status --> Read
int TelloControl::batteryLevel()
{
    return std::atoi(udpClient->send(_strdup("battery?")));
}

int TelloControl::speed()
{
    return std::atoi(udpClient->send(_strdup("speed?")));
}

int TelloControl::time()
{
    return std::atoi(udpClient->send(_strdup("time?")));
}
int TelloControl::wifi()
{
    return std::atoi(udpClient->send(_strdup("wifi?")));
}

bool TelloControl::isLanded()
{
    return state->getLanded();
}

///Control
bool TelloControl::takeoff()
{
    if (state->getLanded()){
        bool takeoff= boolResult(udpClient->send(_strdup("takeoff")));
        if (takeoff){
            state->setLanded(false);
        }
        return takeoff;
    }else{
        return false;
    }
}

bool TelloControl::land()
{
    if (state->getLanded()== false){
        bool land= boolResult(udpClient->send(_strdup("land")));
        if (land){
            state->setLanded(true);
        }
        return land;
    }else{
        return true;
    }
}

bool TelloControl::streamoff()
{
    bool result = boolResult(udpClient->send(_strdup("streamoff")));
    state->setStreamStatus(result);
    return result;
}

bool TelloControl::emergency()
{
    return false;
}

bool TelloControl::streamon()
{
    bool result = boolResult(udpClient->send(_strdup("streamon")));
    state->setStreamStatus(result);
    return result;
}

bool TelloControl::up(int x)
{
    if (state->getLanded())
    {
       takeoff();
    }
    auto command = std::string("up ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}

bool TelloControl::down(int x)
{
    auto command = std::string("down ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}

bool TelloControl::left(int x)
{
    auto command = std::string("left ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}

bool TelloControl::right(int x)
{
    auto command = std::string("right ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}
bool TelloControl::forward(int x)
{
    auto command = std::string("forward ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}
bool TelloControl::back(int x)
{
    auto command = std::string("back ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}
bool TelloControl::cw(int x)
{
    auto command = std::string("cw ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}

bool TelloControl::ccw(int x)
{
    auto command = std::string("ccw ") + std::to_string(x);
    return boolResult(udpClient->send(command.data()));
}

bool TelloControl::flip(string x)
{
    if (x=="l"||x=="r"||x=="f"||x=="b"){
        auto command = std::string("flip ") + x;
        return boolResult(udpClient->send(command.data()));
    }else{
        throw std::invalid_argument("Flip directions should be l(Left),r(Righ),b(Back),f(Forward)");
    }
}
bool TelloControl::goXYZSpeed(int x, int y, int z, int speed)
{
    //return true;
    if ((x >= -500) & (y>= -500) & (z >= -500) & (speed > 10) || (x <= -500) & (y <= -500) & (z <= -500) & (speed < 100)) {
        auto command=std::string("go ")+ std::to_string(x) + std::to_string(x)+ std::to_string(z)+ std::to_string(speed);
        return boolResult(udpClient->send(command.data()));
    }else{
        throw std::invalid_argument("Invalid range for x,y,z and speed");
    }
}

bool TelloControl::stop()
{
    return boolResult(udpClient->send(_strdup("stop")));
}

bool TelloControl::boolResult(char* const input)
{
    return strcmp(input, "ok") == 0;
}
