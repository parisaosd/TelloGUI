#include "pch.h"
#include "plannedflight.h"

PlannedFlight::PlannedFlight()
{
}

wxWindow* PlannedFlight::GetGUI(wxWindow* parent)
{
	wxWindow* dlg = new wxWindow(parent, wxID_ANY);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* b = new wxButton(dlg, wxID_ANY, _("Planned flight"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	b->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(PlannedFlight::OnButton), NULL, this
	);

	box->Add(b, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void PlannedFlight::OnButton(wxCommandEvent& e)
{
	//wxMessageBox(_("Doing some action"));
}