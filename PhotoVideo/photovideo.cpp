#include "pch.h"

#include "photovideo.h"

#include <iostream>
#include <sstream>
#include <cctype>
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
	wxButton* b = new wxButton(dlg, wxID_ANY, _("Photo/Video"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	b->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PhotoVideo::OnButton), NULL, this
	);

	box->Add(b, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void PhotoVideo::OnButton(wxCommandEvent& e)
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

void PhotoVideo::ShowStreamFrame(wxTimerEvent &event)
{
	const cv::String windowName("Tello stream");
	cv::namedWindow(windowName);
	cv::Mat frame;
	_videoCapture->read(frame);
	imshow(windowName, frame);
}