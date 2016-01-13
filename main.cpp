#include "mainwindow.h"
#include "timeutils.h"

enum
{
    ID_Hello = 1,
    ID_TimeInput = 2,
    ID_TimeOutput = 3
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TEXT(ID_TimeInput, MyFrame::OnTextEdit)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_timeInput = new wxTextCtrl(this, ID_TimeInput, "TEST", wxDefaultPosition, wxSize(100, 20));
    m_timeOutput = new wxStaticText(this, ID_TimeOutput, "0' 00'' 000", wxPoint(0, 30), wxSize(100, 20));
}


void MyFrame::OnTextEdit(wxCommandEvent& event)
{
    const int value = atoi(event.GetString());
    const auto ms = milliseconds(value);
    const std::string s = MinSecMs(ms).to_string();
    m_timeOutput->SetLabelText(s);
}
