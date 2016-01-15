#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>

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
    wxTextCtrl *m_timeOutput;
    wxChoice *m_cb_timeUnit;
    wxToggleButton *m_pin;
    std::vector<TimeUnit> m_units;
    milliseconds getInputTime();
    void updateTime();
    void OnInputParamsChange(wxCommandEvent& event);
    void OnToggleOnTop(wxCommandEvent& event);
};
