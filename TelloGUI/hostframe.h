#pragma once
#include <wx/wx.h>
#include "itellocontrol.hpp"

class HostFrame : public wxFrame
{
    wxBoxSizer* box;
public:
    HostFrame();
    virtual ~HostFrame();
private:
    DECLARE_CLASS(HostFrame)
    wxPanel* pluginsPanel;
    wxBitmapButton* arrowButton(wxString pic, wxString toolTip);
    wxBitmapButton* emptyButton();
    void LoadPlugins();

    std::shared_ptr<ITelloControl> _telloControl;
};

