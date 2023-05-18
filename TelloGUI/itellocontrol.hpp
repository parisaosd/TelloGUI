#pragma once

class ITelloControl
{
public:
	virtual int batteryLevel() = 0;
	virtual int speedLevel() = 0;
};