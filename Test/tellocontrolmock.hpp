#pragma once
#include "../itellocontrol.hpp"

class TelloControlMock : public ITelloControl
{
public: 
	int batteryLevel() override;
	int speedLevel() override;
};
