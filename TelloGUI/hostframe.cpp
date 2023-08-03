//#define TEST
#include "hostframe.h"

#include "iplugin.hpp"
#ifdef TEST
#include "../Test/tellocontrolmock.hpp"
#else
#include "../Tello/tellocontrol.hpp"
#endif // TEST
#include "../PhotoVideo/photovideo.h"
#include <wx/dynlib.h>
#include <wx/file.h>
#include "exampledateplugin.h"
#include "plannedflight.h"

#include <opencv2/opencv.hpp>
#include <iostream>

IMPLEMENT_CLASS(HostFrame, wxFrame)

HostFrame::~HostFrame() {}

HostFrame::HostFrame() : wxFrame(NULL, wxID_ANY, "Tello")
{
    wxInitAllImageHandlers();
#ifdef TEST
    _telloControl = std::make_shared<TelloControlMock>();
#else
    _telloControl = std::make_shared<TelloControl>();
#endif // TEST

    pluginsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);  

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
    gs->Add(arrowButton("arrow-up.png", "Move up", wxCommandEventHandler(HostFrame::OnButtonUpClick)));
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

    vbox->Add(pluginsPanel);

    this->SetSizer(vbox);

    LoadPlugins();
}

void HostFrame::OnButtonUpClick(wxCommandEvent& e)
{
    _telloControl->takeoff();
}

wxBitmapButton* HostFrame::arrowButton(wxString pic, wxString toolTip, wxObjectEventFunction function) {
    wxBitmap bitmap;
    bitmap.LoadFile(pic, wxBITMAP_TYPE_PNG);
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);

    // how to change the background color of the arrows??????????????????????????????????--> the other approach did not work 

    button->SetToolTip(toolTip);
    if (function != nullptr) {
        button->Connect(wxID_ANY,
            wxEVT_COMMAND_BUTTON_CLICKED,
            function, NULL, this
        );
    }
    return button;
}

wxBitmapButton* HostFrame::emptyButton() {
    wxBitmap bitmap;
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);
    button->SetBackgroundColour(wxColour(255, 255, 255)); // set the background colour to white

    return button;
}

void HostFrame::LoadPlugins()
{
    std::vector<IPlugin*> plugins = 
    {
        new PhotoVideo(_telloControl),
        new ExampleDatePlugin(),
        //Add itellocontrol  
        new PlannedFlight(_telloControl)
    };

    wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);

    for(IPlugin* plugin : plugins)
    {
        wxWindow* w = plugin->GetGUI(this->pluginsPanel);
        s->Add(w, 0, wxALL | wxALIGN_CENTER, 5);
    }
    pluginsPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    pluginsPanel->SetSizer(s);
    pluginsPanel->Layout();
}