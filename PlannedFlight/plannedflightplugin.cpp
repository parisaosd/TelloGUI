#include "pch.h"
#include "plannedflightplugin.h"

#include "flightplan.hpp"

#include <wx/dialog.h>
#include <wx/textfile.h>

#include <iostream>
#include <sstream>
#include <cctype>

PlannedFlightPlugin::PlannedFlightPlugin(std::shared_ptr<ITelloControl> telloControl)
{
	_telloControl = telloControl;
}

wxWindow* PlannedFlightPlugin::GetGUI(wxWindow* parent)
{
	delete gui;
	gui = new wxWindow(parent, wxID_ANY);
	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* buttonOpen = new wxButton(gui, wxID_ANY, _("Upload flight plan"));
	wxButton* buttonStop = new wxButton(gui, wxID_ANY, _("Stop flight plan"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	buttonOpen->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PlannedFlightPlugin::OnButtonOpen), NULL, this
	);
	buttonStop->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PlannedFlightPlugin::OnButtonStop), NULL, this
	);

	box->Add(buttonOpen, 0, wxALIGN_CENTER | wxALL, 5);
	box->Add(buttonStop, 0, wxALIGN_CENTER | wxALL, 5);
	gui->SetSizer(box);
	gui->Layout();
	return gui;
}

void PlannedFlightPlugin::OnButtonOpen(wxCommandEvent& e)
{
	wxFileDialog* openFileDialog = new wxFileDialog(gui, _("Open fligh plan file"), "", "",
		"TXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog->ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// proceed loading the file chosen by the user;
	// this can be done with e.g. wxWidgets input streams:
	//wxTextFile tfile;
	//tfile.Open(openFileDialog->GetPath());

	_flightPlan = std::make_shared<FlightPlan>(openFileDialog->GetPath(), _telloControl);

	std::thread t([this](){_flightPlan->execute();});
	t.detach();
}

void PlannedFlightPlugin::OnButtonStop(wxCommandEvent& e)
{	
	if (_flightPlan != nullptr)
	{
		_flightPlan->stop();
	}
}