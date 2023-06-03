#include "pch.h"
#include "exampledateplugin.h"
#include <wx/datetime.h>



ExampleDatePlugin::ExampleDatePlugin()
{
}

wxWindow* ExampleDatePlugin::GetGUI(wxWindow* parent)
{
	wxWindow* dlg = new wxWindow(parent, wxID_ANY);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* b = new wxButton(dlg, wxID_ANY, _("Action"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	b->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(ExampleDatePlugin::OnButton), NULL, this
	);

	box->Add(b, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void ExampleDatePlugin::OnButton(wxCommandEvent& e)
{
	//wxMessageBox(_("Doing some action"));
	wxMessageBox(wxDateTime().Now().Format());
}