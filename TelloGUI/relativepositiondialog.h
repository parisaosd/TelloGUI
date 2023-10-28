#pragma once
#include "itellocontrol.hpp"

#include <wx/wx.h>
#include <wx/spinctrl.h>

class RelativePositionDialog : public wxFrame
{
public:
    RelativePositionDialog(wxWindow* parent, std::shared_ptr<ITelloControl> telloControl);
private:
    DECLARE_CLASS(RelativePositionDialog)

    std::shared_ptr<ITelloControl> _telloControl;
    wxSpinCtrl* _x;
    wxSpinCtrl* _y;
    wxSpinCtrl* _z;
    wxSpinCtrl* _speed;

    wxButton* goButton();
    void OnGoButtonClick(wxCommandEvent& e);
};