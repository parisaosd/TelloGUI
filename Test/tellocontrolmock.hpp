#pragma once

#include "../TelloGUI/iplugin.hpp"
#include "itellocontrol.hpp"

#include <string>

class TelloControlMock : public ITelloControl
{
public:
    char* genericCommand(const char* message) override;

    cv::Mat getVideoFrame() override;
    bool isStreamOn() override;
    bool saveScreenshotJpeg(std::string filename) override;

    ///Status-->Read
    int batteryLevel() override;
    int speed() override;
    int time() override;
    int wifi() override;

    bool isLanded() override;


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
    bool cw(int x) override;
    bool ccw(int x) override;
    bool flip(std::string x) override;/// X---> l,r,f,b
    bool goXYZSpeed(int x, int y, int z, int speed) override;

    bool stop() override;
};
