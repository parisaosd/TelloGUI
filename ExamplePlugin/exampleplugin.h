#pragma once
#include "pch.h"
#include "iplugin.hpp"

//this will be our actual plugin.
class ExamplePlugin : public IPlugin
{
public:
	ExamplePlugin();
	void PerformTasks();
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButton(wxCommandEvent& e);
};