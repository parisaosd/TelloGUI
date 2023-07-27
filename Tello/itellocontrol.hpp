#pragma once

#include <string>

class ITelloControl
{
public:
    virtual char* genericCommand(const char* message) = 0;

	virtual int batteryLevel() = 0;
	virtual int speed() = 0;
    virtual int time() = 0;
    virtual int wifi() = 0;
    virtual bool takeoff() = 0;
    virtual bool land() = 0;
    virtual bool streamon() = 0;
    virtual bool streamoff() = 0;
    virtual bool emergency() = 0;

    virtual bool up(int x) = 0;
    virtual bool down(int x) = 0;
    virtual bool left(int x) = 0;
    virtual bool right(int x) = 0;
    virtual bool forward(int x) = 0;
    virtual bool back(int x) = 0;
    virtual bool cwx(int x) = 0;
    virtual bool ccw(int x) = 0;
    virtual bool flip(std::string x) = 0;
    virtual bool goXYZSpeed(int x, int y, int z, int speed) = 0;
    virtual bool stop() = 0;
};