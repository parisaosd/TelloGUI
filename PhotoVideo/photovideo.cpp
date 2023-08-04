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

	_videoCapture = new cv::VideoCapture("udp://@0.0.0.0:11111");
	_videoCapture->set(cv::CAP_PROP_BUFFERSIZE, 0);

	const cv::String windowName("Tello stream");
	cv::namedWindow(windowName);

	static const int INTERVAL = 1;
	auto timer = new wxTimer(this, 5);
	timer->Start(INTERVAL);

	Connect(5, wxEVT_TIMER, wxTimerEventHandler(PhotoVideo::ShowStreamFrame));
}

void PhotoVideo::OnScreenshotButton(wxCommandEvent& e)
{
	if (_videoCapture == nullptr || !_videoCapture->isOpened())
	{
		return;
	}
	cv::imwrite(std::to_string(std::time(0)) + ".jpg", _latestFrame);
	wxMessageBox(wxT("Screenshot saved!"));
}

void PhotoVideo::ShowStreamFrame(wxTimerEvent &event)
{
	const cv::String windowName("Tello stream");
	cv::namedWindow(windowName);
	cv::Mat frame;
	_videoCapture->read(frame);
	_latestFrame = frame;
	imshow(windowName, frame);
}