#pragma once
#include "pch.h"
#include "iplugin.hpp"
#include "../Tello/itellocontrol.hpp"
#include "flightplan.hpp"

//this will be our actual plugin.
class PlannedFlightPlugin : public IPlugin
{
public:
	PlannedFlightPlugin(std::shared_ptr<ITelloControl> telloControl);
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButtonOpen(wxCommandEvent& e);
	void OnButtonStop(wxCommandEvent& e);
private:
	wxWindow* gui;
	std::shared_ptr<ITelloControl> _telloControl;
	std::shared_ptr<FlightPlan> _flightPlan;
};