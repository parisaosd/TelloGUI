//#define TEST
#include "hostframe.h"

#include "iplugin.hpp"
#ifdef TEST
#include "../Test/tellocontrolmock.hpp"
#else
#include "../Tello/tellocontrol.hpp"
#endif // TEST
#include <wx/dynlib.h>
#include <wx/file.h>
#include "plannedflightplugin.h"
#include "photovideoplugin.h"
#include "relativepositiondialog.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

const int SPACER_SIZE = 35;

IMPLEMENT_CLASS(HostFrame, wxFrame)

HostFrame::~HostFrame() {}

HostFrame::HostFrame() : wxFrame(NULL, wxID_ANY, "Tello")
{
    freopen("GuiLog.txt", "w", stdout);
    wxInitAllImageHandlers();
#ifdef TEST
    _telloControl = std::make_shared<TelloControlMock>();
#else
    _telloControl = std::make_shared<TelloControl>();
#endif // TEST

    pluginsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);  

    int batteryLevel = 0;
    if (_telloControl->isOnline()) {
        batteryLevel = _telloControl->batteryLevel();
    }

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* hboxToolbar = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* hboxMain = new wxBoxSizer(wxVERTICAL);


    //Battery 
    wxStaticText* batteryLabel = new wxStaticText(this, 0, " Battery Level: ");
    wxStaticText* batteryLabelValue = new wxStaticText(this, 0, wxString::Format(wxT("%d"), batteryLevel));

    hboxToolbar->Add(batteryLabel);
    hboxToolbar->Add(batteryLabelValue);

    // to create buttons in tool bar ?????????????????????????????????????????????? 

    //Connection status
    wxString connectionStatus = "offline";
    if (_telloControl->isOnline()) {
        connectionStatus = "connected";
    }
    wxStaticText* connectionLabel = new wxStaticText(this, 0, "  Wi-fi connection: ");
    wxStaticText* connectionValue = new wxStaticText(this, 0, connectionStatus);

    hboxToolbar->Add(connectionLabel);
    hboxToolbar->Add(connectionValue);

    wxGridSizer* gs = new wxGridSizer(5, 11, 0, 0);

    // row 1 
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-up.png", "Move up", wxCommandEventHandler(HostFrame::OnButtonUpClick)));
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-up.png", "Move forward", wxCommandEventHandler(HostFrame::OnButtonForwardClick)));
    gs->AddSpacer(SPACER_SIZE);
    //row 2


    gs->Add(arrowButton("arrow-left.png", "Move left", wxCommandEventHandler(HostFrame::OnButtonLeftClick)));
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-right.png", "Move right", wxCommandEventHandler(HostFrame::OnButtonRightClick)));
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-left.png", "Turn left", wxCommandEventHandler(HostFrame::OnButtonTurnLeftClick)));
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-right.png", "Turn right", wxCommandEventHandler(HostFrame::OnButtonTurnRightClick)));

    //row 3
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-down.png", "Move down", wxCommandEventHandler(HostFrame::OnButtonDownClick)));
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->Add(arrowButton("arrow-down.png", "Move back", wxCommandEventHandler(HostFrame::OnButtonBackClick)));
    gs->AddSpacer(SPACER_SIZE);

    //row 4
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);
    gs->AddSpacer(SPACER_SIZE);

    //row 5
    gs->Add(toRelativePositionButton());

    hboxMain->Add(gs);
    vbox->Add(hboxToolbar);
    vbox->Add(hboxMain);

    vbox->Add(pluginsPanel);

    this->SetSizer(vbox);
    this->SetMinSize(wxSize(400, 350));

    LoadPlugins();
}

void HostFrame::OnButtonUpClick(wxCommandEvent& e)
{
    std::thread t([this]()
        {
            if (_telloControl->isLanded())
            {
                _telloControl->takeoff();
            }
            else
            {
                _telloControl->up(20);
            }
        });
    t.detach();
}

void HostFrame::OnButtonDownClick(wxCommandEvent& e)
{
    std::thread t([this]()
        {
            if (_telloControl->isLanded())
            {
                _telloControl->land();
            }
            else
            {
                _telloControl->down(20);
            }
        });
    t.detach();
}

void HostFrame::OnButtonLeftClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->left(20); });
    t.detach();
}

void HostFrame::OnButtonRightClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->right(20); });
    t.detach();
}

void HostFrame::OnButtonTurnRightClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->cw(20); });
    t.detach();
}

void HostFrame::OnButtonTurnLeftClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->ccw(20); });
    t.detach();
}

void HostFrame::OnButtonForwardClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->forward(20); });
    t.detach();
}

void HostFrame::OnButtonBackClick(wxCommandEvent& e)
{
    std::thread t([this]() { _telloControl->back(20); });
    t.detach();
}

void HostFrame::OnButtonToRelativePositionClick(wxCommandEvent& e)
{
    wxFrame* dialog = new RelativePositionDialog(this, _telloControl);
    dialog->Show(true);
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

wxButton* HostFrame::toRelativePositionButton() {
    auto button = new wxButton(this, -1, "Move to relative position...");
    button->Connect(wxID_ANY,
        wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(HostFrame::OnButtonToRelativePositionClick), NULL, this
    );
    return button;
}

void HostFrame::LoadPlugins()
{
    std::vector<IPlugin*> plugins = 
    {
        //TODO All Plugins depend on OpenCV - this can be improved by splitting video functionality from controlling the drone.
        new PhotoVideoPlugin(_telloControl),
        new PlannedFlightPlugin(_telloControl)
    };

    wxBoxSizer* s = new wxBoxSizer(wxVERTICAL);

    for(IPlugin* plugin : plugins)
    {
        wxWindow* w = plugin->GetGUI(this->pluginsPanel);
        s->Add(w, 0, wxALL | wxALIGN_CENTER, 5);
    }
    pluginsPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    pluginsPanel->SetSizer(s);
    pluginsPanel->Layout();
}