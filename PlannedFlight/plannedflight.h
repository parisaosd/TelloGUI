#pragma once
#include "pch.h"
#include "iplugin.hpp"
#include "../Tello/itellocontrol.hpp"

//this will be our actual plugin.
class PlannedFlight : public IPlugin
{
public:
	PlannedFlight(std::shared_ptr<ITelloControl> telloControl);
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButton(wxCommandEvent& e);
private:
	wxWindow* gui;
	std::shared_ptr<ITelloControl> _telloControl;
};