#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
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
    wxTextCtrl *m_timeInput;
    wxStaticText *m_timeOutput;
    void OnTextEdit(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
