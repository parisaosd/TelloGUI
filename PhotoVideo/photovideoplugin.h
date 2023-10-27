#pragma once
#include "pch.h"
#include "iplugin.hpp"

#include <opencv2/opencv.hpp>
#include <memory>

#include "../Tello/itellocontrol.hpp"


class PhotoVideoPlugin : public IPlugin
{
public:
	PhotoVideoPlugin(std::shared_ptr<ITelloControl> telloControl);
	virtual wxWindow* GetGUI(wxWindow* parent);

private:
	std::shared_ptr<ITelloControl> _telloControl;
	wxWindow* _parent;
	wxTimer* _timer;
	std::atomic<bool> _isRecordingOn;
	cv::VideoWriter _videoWriter;

	void OnStreamButton(wxCommandEvent& e);
	void OnScreenshotButton(wxCommandEvent& e);
	void OnStartRecordingButton(wxCommandEvent& e);
	void OnStopRecordingButton(wxCommandEvent& e);
	void ShowStreamFrame(wxTimerEvent& e);
};