#include "pch.h"

#include "photovideo.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <ctime>
#include <thread>

PhotoVideo::PhotoVideo(std::shared_ptr<ITelloControl> telloControl)
{
	_telloControl = telloControl;
}

wxWindow* PhotoVideo::GetGUI(wxWindow* parent)
{
    _parent = parent;
	wxWindow* dlg = new wxWindow(parent, wxID_ANY);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* bStream = new wxButton(dlg, wxID_ANY, _("Camera"));
	wxButton* bScreenshot = new wxButton(dlg, wxID_ANY, _("Screenshot"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	bStream->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideo::OnStreamButton), NULL, this
	);
	bScreenshot->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideo::OnScreenshotButton), NULL, this
	);

	box->Add(bStream, 0, wxALIGN_CENTER | wxALL, 5);
	box->Add(bScreenshot, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void PhotoVideo::OnStreamButton(wxCommandEvent& e)
{
	_telloControl->streamon();
	static const int INTERVAL = 1;
	auto timer = new wxTimer(this, 5);
	timer->Start(INTERVAL);
	Connect(5, wxEVT_TIMER, wxTimerEventHandler(PhotoVideo::ShowStreamFrame));
}

void PhotoVideo::OnScreenshotButton(wxCommandEvent& e)
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

void PhotoVideo::ShowStreamFrame(wxTimerEvent& e)
{
	const cv::String windowName("Tello stream");
	cv::namedWindow(windowName);
	imshow(windowName, _telloControl->getVideoFrame());
}