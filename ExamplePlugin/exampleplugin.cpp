#include "pch.h"
#include "exampleplugin.h"

ExamplePlugin::ExamplePlugin()
{
}

void ExamplePlugin::PerformTasks()
{
	//wxMessageBox(_("I would if I could..."));
}

wxWindow* ExamplePlugin::GetGUI(wxWindow* parent)
{
	wxWindow* dlg = new wxWindow(parent, wxID_ANY);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	wxButton* b = new wxButton(dlg, wxID_ANY, _("Action"));
	//Use connect in this case as static event tables won't work
	//As Plugin is derived from wxEvtHandler you can catch events in this Plugin
	b->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(ExamplePlugin::OnButton), NULL, this
	);

	box->Add(b, 0, wxALIGN_CENTER | wxALL, 5);
	dlg->SetSizer(box);
	dlg->Layout();
	return dlg;
}

void ExamplePlugin::OnButton(wxCommandEvent& e)
{
	wxMessageBox(_("Doing some action"));
}