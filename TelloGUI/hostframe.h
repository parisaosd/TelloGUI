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
    wxButton* toRelativePositionButton();
    wxButton* landButton();
    void LoadPlugins();
    void OnButtonUpClick(wxCommandEvent& e);
    void OnButtonDownClick(wxCommandEvent& e);
    void OnButtonLeftClick(wxCommandEvent& e);
    void OnButtonRightClick(wxCommandEvent& e);
    void OnButtonTurnRightClick(wxCommandEvent& e);
    void OnButtonTurnLeftClick(wxCommandEvent& e);
    void OnButtonForwardClick(wxCommandEvent& e);
    void OnButtonBackClick(wxCommandEvent& e);
    void OnButtonToRelativePositionClick(wxCommandEvent& e);
    void OnButtonLandClick(wxCommandEvent& e);
    void OnTimer(wxTimerEvent& e);
    wxTimer m_timer;
    wxStaticText* _batteryLabelValue;

    std::shared_ptr<ITelloControl> _telloControl;
};

