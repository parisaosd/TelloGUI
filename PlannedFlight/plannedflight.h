#pragma once
#include "pch.h"
#include "iplugin.hpp"

//this will be our actual plugin.
class PlannedFlight : public IPlugin
{
public:
	PlannedFlight();
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButton(wxCommandEvent& e);
};