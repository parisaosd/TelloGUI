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
    wxBitmapButton* arrowButton(wxString pic, wxString toolTip, wxObjectEventFunction function = nullptr);
    wxBitmapButton* emptyButton();
    void LoadPlugins();
    void OnButtonUpClick(wxCommandEvent& e);

    std::shared_ptr<ITelloControl> _telloControl;
};

