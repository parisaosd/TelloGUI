#define TEST

#pragma once
#include <wx/wx.h>
#include "itellocontrol.hpp"


#ifdef TEST
#include "../Test/tellocontrolmock.hpp"
#else
#include <tellocontrol.hpp>
#endif // TEST

class HostFrame : public wxFrame
{
    wxBoxSizer* box;
public:
    HostFrame();
    virtual ~HostFrame();
private:
    DECLARE_CLASS(HostFrame)
    wxPanel* dummy;
    wxBitmapButton* arrowButton(wxString pic, wxString toolTip);
    wxBitmapButton* emptyButton();
    void OnDoit(wxCommandEvent& e);
    DECLARE_EVENT_TABLE()
#ifdef TEST
    std::shared_ptr<ITelloControl> _telloControl;
#else
    std::shared_ptr<TelloControl> _telloControl;
#endif
};

