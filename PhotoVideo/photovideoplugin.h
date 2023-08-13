#pragma once
#include "pch.h"
#include "iplugin.hpp"

#include <opencv2/opencv.hpp>

#include "../Tello/itellocontrol.hpp"

//this will be our actual plugin.
class PhotoVideoPlugin : public IPlugin
{
public:
	PhotoVideoPlugin(std::shared_ptr<ITelloControl> telloControl);
	virtual wxWindow* GetGUI(wxWindow* parent);

private:
	std::shared_ptr<ITelloControl> _telloControl;
	wxWindow* _parent;

	void OnStreamButton(wxCommandEvent& e);
	void OnScreenshotButton(wxCommandEvent& e);
	void ShowStreamFrame(wxTimerEvent& e);
};