#define TEST

#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/bmpbuttn.h>
#include <memory>
#include <wx/grid.h>
#include <wx/menu.h>


#include "itellocontrol.hpp"
#include "hostframe.h"

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




wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    HostFrame* frame = new HostFrame();
    frame->Show(true);

    return true;
}


