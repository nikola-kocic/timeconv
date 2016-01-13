#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/spinctrl.h>

#include <vector>

#include "timeutils.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    wxSpinCtrl *m_timeInput;
    wxStaticText *m_timeOutput;
    wxChoice *m_cb_timeUnit;
    std::vector<TimeUnit> m_units;
    milliseconds getInputTime();
    void updateTime();
    void OnInputChange(wxSpinEvent& event);
    void OnTimeUnitChange(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
