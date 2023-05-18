#define TEST

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/bmpbuttn.h>
#include <memory>
#include <wx/grid.h>
#include <wx/menu.h>

#include "itellocontrol.hpp"

#ifdef TEST
#include "../Test/tellocontrolmock.hpp"
#else
#include <tellocontrol.hpp>
#endif // TEST

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    wxBitmapButton* arrowButton(wxString pic, wxString toolTip);
    wxBitmapButton* emptyButton();
#ifdef TEST
    std::shared_ptr<ITelloControl> _telloControl;
#else
    std::shared_ptr<TelloControl> _telloControl;
#endif
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);

    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Tello")
{
    wxInitAllImageHandlers();
#ifdef TEST
    _telloControl = std::make_shared<TelloControlMock>();
#else
    _telloControl = std::make_shared<TelloControl>();
#endif // TEST


   // to create menu  bar 


   

    int batteryLevel = _telloControl->batteryLevel();
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    //wxBoxSizer* vbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hboxToolbar = new wxBoxSizer(wxHORIZONTAL);
   //wxBoxSizer* hboxMain = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hboxMain = new wxBoxSizer(wxVERTICAL);
   // wxBoxSizer* hboxMain2 = new wxBoxSizer(wxHORIZONTAL);

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
    wxGridSizer* gs = new wxGridSizer(  3, 11, 0, 0);

   /* gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-up.png","Move up"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-left.png", "Move left"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-right.png", "Move right"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-down.png", "Move down"));
    gs->Add(emptyButton());

    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());
    gs->Add(emptyButton());

    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-up.png", "Move up"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-left.png", "Move left"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-right.png", "Move right"));
    gs->Add(emptyButton());
    gs->Add(arrowButton("arrow-down.png", "Move down"));
    gs->Add(emptyButton()); */

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

    /*hboxMain->Add(gs);
    vbox2->Add(hboxToolbar);
    vbox2->Add(hboxMain);*/


    this->SetSizer(vbox);
    /*this->SetSizer(vbox);*/
}

wxBitmapButton* MyFrame::arrowButton(wxString pic, wxString toolTip ) {
    wxBitmap bitmap;
    bitmap.LoadFile(pic, wxBITMAP_TYPE_PNG);
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);
    
    // how to change the background color of the arrows??????????????????????????????????--> the other approach did not work 

    button->SetToolTip(toolTip);
    return button;
}

wxBitmapButton* MyFrame::emptyButton() {
    wxBitmap bitmap;
    wxBitmapButton* button = new wxBitmapButton(this, -1, bitmap, wxPoint(0, 0), wxSize(35, 35), 0);
    button->SetBackgroundColour(wxColour(255, 255, 255)); // set the background colour to white

    return button;
}

