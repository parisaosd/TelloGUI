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
#include <chrono>
#include <thread>

using namespace std;

TelloControl::TelloControl()
{
    using namespace std::chrono_literals;
    state = std::make_shared<State>();
    udpClient = std::make_shared<UdpClient>(_strdup("192.168.10.1"), 8889);
    int attempts = 5;
    while(attempts>0){
        if(boolResult(udpClient->send(_strdup("command")))){
            state->setOnline(true);
            break;
        }
        attempts--;
        std::this_thread::sleep_for(2000ms);
        if (attempts==0) {
            state->setOnline(false);
        }
    }
}

char* TelloControl::genericCommand(const char* message)
{
    return udpClient->send(message);
}
//This method returns only one frame at a time using openCv library
cv::Mat TelloControl::getVideoFrame()
{
    if (_videoCapture == nullptr) {
        _videoCapture = std::make_shared<cv::VideoCapture>("udp://@0.0.0.0:11111");
        _videoCapture->set(cv::CAP_PROP_BUFFERSIZE, 0);
        //We set the buffer size through this constant. 0 means frames are not being buffered and are processed immediately after being captured
        //Effectively turning off buffering by setting cv::CAP_PROP_BUFFERSIZE to 0. This means frames 
        //are not buffered and not immediatly processed which helps to minimize the delay between capturing and processing them because latency
        //is crucial in handling the media data from drone's camera.
    }
    cv::Mat frame;
    _videoCapture->read(frame);
    _latestFrame = frame;
    return frame;
}
//The stream status is a constant which is initialy set to False and it can change by ????????
bool TelloControl::isStreamOn()
{
    return state->getStreamStatus();
}

//This method is used to save a screenshot of the latest frame captured from a video stream to a JPEG file.
//Where the value of -latestFrame is assigned ? 
bool TelloControl::saveScreenshotJpeg(std::string filename)
{
    //!isStreamOn():If the streamOn is True that stream is not on, (Negation of the isStreamOn() value
    //_videoCapture == nullptr : meaning that the video capture instance is not properly initialized
    //!_videoCapture->isOpened():checks if the _videoCapture instance is not opened, indicating that it's not capturing any video stream.
    if (!isStreamOn() || _videoCapture == nullptr || !_videoCapture->isOpened())
    {
        return false;
    }
    //imwrite is an openCV function which saves the _latestFrame.
    //It appends .jpg to the provided filename and uses _latestFrame as the image data to save
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

bool TelloControl::isOnline()
{
    return state->getOnline();
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

//This method should be checked 
bool TelloControl::flip(string x)
{
    if (x=="l"||x=="r"||x=="f"||x=="b"){
        auto command = std::string("flip ") + x;
        return boolResult(udpClient->send(command.data()));
    }else{
        throw std::invalid_argument("Flip directions should be l(Left),r(Righ),b(Back),f(Forward)");
    }
}
// this method should be checked 
bool TelloControl::goXYZSpeed(int x, int y, int z, int speed)
{
   /* if (x < -500 || x > 500 || y < -500 || y > 500 || z < -500 || z > 500 || speed >= 100) {
        auto command = std::string("go ") + std::to_string(x) + std::to_string(x) + std::to_string(z) + std::to_string(speed);
        return boolResult(udpClient->send(command.data()));
    }
    else {
        throw std::invalid_argument("Invalid range for x,y,z and speed");
    }
    }*/
    //return true;
    if (((x >= -500) && (y >= -500) && (z >= -500) && (speed) > 10) || ((x <= -500) && (y <= -500) && (z <= -500) && (speed) < 100)) {
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
    //Compare the input value with "Ok" 
}
