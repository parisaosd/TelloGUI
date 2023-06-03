#pragma once
#include "pch.h"
#include "iplugin.hpp"

//this will be our actual plugin.
class ExampleDatePlugin : public IPlugin
{
public:
	ExampleDatePlugin();
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButton(wxCommandEvent& e);
};