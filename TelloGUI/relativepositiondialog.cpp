#include "relativepositiondialog.h"

IMPLEMENT_CLASS(RelativePositionDialog, wxFrame)

RelativePositionDialog::RelativePositionDialog(wxWindow* parent, std::shared_ptr<ITelloControl> telloControl) : wxFrame(parent, wxID_ANY, "Move to relative position")
{
	_telloControl = telloControl;
	wxGridSizer* gs = new wxGridSizer(5, 2, 0, 0);
	_x = new wxSpinCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -500, 500);
	_y = new wxSpinCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -500, 500);
	_z = new wxSpinCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -500, 500);
	_speed = new wxSpinCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 100, 10);

	gs->Add(new wxStaticText(this, 0, " X: "));
	gs->Add(_x);
	gs->Add(new wxStaticText(this, 0, " Y: "));
	gs->Add(_y);
	gs->Add(new wxStaticText(this, 0, " Z: "));
	gs->Add(_z);
	gs->Add(new wxStaticText(this, 0, " Speed: "));
	gs->Add(_speed);
	gs->Add(goButton());
	this->SetSizer(gs);
}

wxButton* RelativePositionDialog::goButton() {
	auto button = new wxButton(this, -1, "Go");
	button->Connect(wxID_ANY,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(RelativePositionDialog::OnGoButtonClick), NULL, this
	);
	return button;
}

void RelativePositionDialog::OnGoButtonClick(wxCommandEvent& e)
{
	_telloControl->goXYZSpeed(_x->GetValue(), _y->GetValue(), _z->GetValue(), _speed->GetValue());
}