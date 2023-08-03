#pragma once
#include "pch.h"
#include "iplugin.hpp"

#include <opencv2/opencv.hpp>

#include "../Tello/itellocontrol.hpp"

//this will be our actual plugin.
class PhotoVideo : public IPlugin
{
public:
	PhotoVideo(std::shared_ptr<ITelloControl> telloControl);
	virtual wxWindow* GetGUI(wxWindow* parent);

	void OnButton(wxCommandEvent& e);
private:
	std::shared_ptr<ITelloControl> _telloControl;
	wxWindow* _parent;
	cv::VideoCapture* _videoCapture;

	void ShowStreamFrame(wxTimerEvent& event);
};