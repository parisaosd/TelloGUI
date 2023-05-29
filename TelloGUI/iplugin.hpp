#pragma once
#include <wx/wx.h>

//the plugin interface (a.k.a. abstract class)
//our plugin will contain GUI in itself - therefore we need to make it extend wxEvtHandler (or wxDialog for that matter)
class IPlugin : public wxEvtHandler
{
public:
	virtual void PerformTasks() = 0;
	virtual wxWindow* GetGUI(wxWindow* parent) = 0;
};


