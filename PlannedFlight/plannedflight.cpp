#include "pch.h"
#include "plannedflight.h"

#include "flightplan.hpp"

#include <wx/dialog.h>
#include <wx/textfile.h>

#include <iostream>
#include <sstream>
#include <cctype>

PlannedFlight::PlannedFlight(std::shared_ptr<ITelloControl> telloControl)
{
	_telloControl = telloControl;
}

wxWindow* PlannedFlight::GetGUI(wxWindow* parent)
{
	delete gui;
	gui = new wxWindow(parent, wxID_ANY);
	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* b = new wxButton(gui, wxID_ANY, _("Planned flight"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	b->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PlannedFlight::OnButton), NULL, this
	);

	box->Add(b, 0, wxALIGN_CENTER | wxALL, 5);
	gui->SetSizer(box);
	gui->Layout();
	return gui;
}

void PlannedFlight::OnButton(wxCommandEvent& e)
{
	wxFileDialog* openFileDialog = new wxFileDialog(gui, _("Open fligh plan file"), "", "",
		"TXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog->ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// proceed loading the file chosen by the user;
	// this can be done with e.g. wxWidgets input streams:
	//wxTextFile tfile;
	//tfile.Open(openFileDialog->GetPath());

	FlightPlan flightPlan(openFileDialog->GetPath(), _telloControl);

	std::stringbuf sbuf(std::ios::out); // create a stringbuf
	auto oldbuf = std::cout.rdbuf(std::addressof(sbuf)); // associate the stringbuf with std::cout

	flightPlan.execute();

	std::cout.rdbuf(oldbuf); // restore cout's original buffer
	std::string output = sbuf.str(); // get a copy of the underlying string
	//wxMessageBox(tfile.GetFirstLine());
	wxMessageBox(output);	
}