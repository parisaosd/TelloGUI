#include "pch.h"

#include "photovideoplugin.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <ctime>
#include <thread>

PhotoVideoPlugin::PhotoVideoPlugin(std::shared_ptr<ITelloControl> telloControl)
{
	_telloControl = telloControl;
}

wxWindow* PhotoVideoPlugin::GetGUI(wxWindow* parent)
{
    _parent = parent;
	wxWindow* dlg = new wxWindow(parent, wxID_ANY);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* bStream = new wxButton(dlg, wxID_ANY, _("Camera"));
	wxButton* bScreenshot = new wxButton(dlg, wxID_ANY, _("Screenshot"));
	wxButton* bStartVideoRecording = new wxButton(dlg, wxID_ANY, _("Start recording"));
	wxButton* bStopVideoRecording = new wxButton(dlg, wxID_ANY, _("Stop recording"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	bStream->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideoPlugin::OnStreamButton), NULL, this
	);
	bScreenshot->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideoPlugin::OnScreenshotButton), NULL, this
	);
	bStartVideoRecording->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideoPlugin::OnStartRecordingButton), NULL, this
	);
	bStopVideoRecording->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideoPlugin::OnStopRecordingButton), NULL, this
	);

	box->Add(bStream, 0, wxALIGN_CENTER | wxALL, 5);
	box->Add(bScreenshot, 0, wxALIGN_CENTER | wxALL, 5);
	box->Add(bStartVideoRecording, 0, wxALIGN_CENTER | wxALL, 5);
	box->Add(bStopVideoRecording, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void PhotoVideoPlugin::OnStreamButton(wxCommandEvent& e)
{
	_telloControl->streamon();
	static const int INTERVAL = 1;
	auto timer = new wxTimer(this, 5);
	timer->Start(INTERVAL);
	Connect(5, wxEVT_TIMER, wxTimerEventHandler(PhotoVideoPlugin::ShowStreamFrame));
}

void PhotoVideoPlugin::OnScreenshotButton(wxCommandEvent& e)
{
	if (_telloControl->saveScreenshotJpeg(std::to_string(std::time(0))))
	{
		wxMessageBox(wxT("Screenshot saved!"));
	}
	else
	{
		wxMessageBox(wxT("Could not save a screenshot. CHeck if stream is running."));
	}
}

void PhotoVideoPlugin::OnStartRecordingButton(wxCommandEvent& e)
{
	wxMessageBox(wxT("Not implemented."));
}

void PhotoVideoPlugin::OnStopRecordingButton(wxCommandEvent& e)
{
	wxMessageBox(wxT("Not implemented."));
}

void PhotoVideoPlugin::ShowStreamFrame(wxTimerEvent& e)
{
	const cv::String windowName("Tello stream");
	cv::namedWindow(windowName);
	imshow(windowName, _telloControl->getVideoFrame());
}