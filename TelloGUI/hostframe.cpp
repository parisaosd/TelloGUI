#define TEST
#include "hostframe.h"

#include "iplugin.hpp"
#include "../ExamplePlugin/exampleplugin.h"

#include <wx/dynlib.h>
#include <wx/file.h>


enum
{
    ID_DOIT = 1
};
IMPLEMENT_CLASS(HostFrame, wxFrame)

BEGIN_EVENT_TABLE(HostFrame, wxFrame)
EVT_BUTTON(ID_DOIT, HostFrame::OnDoit)
END_EVENT_TABLE()

HostFrame::~HostFrame() {}

HostFrame::HostFrame() : wxFrame(NULL, wxID_ANY, "Tello")
{
    wxInitAllImageHandlers();
#ifdef TEST
    _telloControl = std::make_shared<TelloControlMock>();
#else
    _telloControl = std::make_shared<TelloControl>();
#endif // TEST

    dummy = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 200));
    box = new wxBoxSizer(wxVERTICAL);
    wxButton* b = new wxButton(this, ID_DOIT, _("Doit"));
    box->Add(b, 0, wxEXPAND, 0);
    box->Add(dummy, 1, wxEXPAND, 5);    

    int batteryLevel = _telloControl->batteryLevel();
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* hboxToolbar = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* hboxMain = new wxBoxSizer(wxVERTICAL);


    //Battery 
    wxStaticText* batteryLabel = new wxStaticText(this, 0, "Battery Level: ");
    wxStaticText* batteryLabelValue = new wxStaticText(this, 0, wxString::Format(wxT("%d"), batteryLevel));

    hboxToolbar->Add(batteryLabel);
    hboxToolbar->Add(batteryLabelValue);

    // to create buttons in tool bar ?????????????????????????????????????????????? 

    //Speed 
    int speedLevel = _telloControl->batteryLevel();
    wxStaticText* speedLabel = new wxStaticText(this, 0, "Speed Level: ");
    wxStaticText* speedLabelValue = new wxStaticText(this, 0, wxString::Format(wxT("%d"), speedLevel));

    hboxToolbar->Add(speedLabel);
    hboxToolbar->Add(speedLabelValue);

    //wxGridSizer* gs = new wxGridSizer(3, 3, 0, 0);
    wxGridSizer* gs = new wxGridSizer(3, 11, 0, 0);



    // row 1 
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-up.png", "Move up"));
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-up.png", "Move up"));
    gs->Add(emptyButton());
    //row 2


    gs->Add(arrowButton("arrow-left.png", "Move left"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-right.png", "Move right"));
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-left.png", "Move left"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-right.png", "Move right"));

    //row 3
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-down.png", "Move down"));
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-down.png", "Move down"));
    gs->Add(emptyButton());


    hboxMain->Add(gs);
    vbox->Add(hboxToolbar);
    vbox->Add(hboxMain);

    vbox->Add(box);

    this->SetSizer(vbox);
}

wxBitmapButton* HostFrame::arrowButton(wxString pic, wxString toolTip) {
    wxBitmap bitmap;
    bitmap.LoadFile(pic, wxBITMAP_TYPE_PNG);
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);

    // how to change the background color of the arrows??????????????????????????????????--> the other approach did not work 

    button->SetToolTip(toolTip);
    return button;
}

wxBitmapButton* HostFrame::emptyButton() {
    wxBitmap bitmap;
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);
    button->SetBackgroundColour(wxColour(255, 255, 255)); // set the background colour to white

    return button;
}

void HostFrame::OnDoit(wxCommandEvent& e)
{
    ExamplePlugin* examplePlugin = new ExamplePlugin();

    //call some method in it
    examplePlugin->PerformTasks();
    //we will append the gui from the plugin into the panel's sizer
    wxBoxSizer* s = new wxBoxSizer(wxVERTICAL);
    wxWindow* w = examplePlugin->GetGUI(this->dummy);
    s->Add(w, 0, wxALL | wxALIGN_CENTER, 5);
    dummy->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    dummy->SetSizer(s);
    dummy->Layout();
}