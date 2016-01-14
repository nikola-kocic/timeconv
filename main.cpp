#include "mainwindow.h"
#include "timeutils.h"

enum
{
    ID_TimeInput
    , ID_TimeOutput
    , ID_CB_TimeUnit
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_SPINCTRL(ID_TimeInput, MyFrame::OnInputChange)
EVT_CHOICE(ID_CB_TimeUnit, MyFrame::OnTimeUnitChange)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Time Conv", wxPoint(50, 50), wxSize(230, 100));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
    , m_units({
        TimeUnit::milliseconds
        , TimeUnit::centiseconds
        , TimeUnit::deciseconds
        , TimeUnit::seconds})
{
    this->SetBackgroundColour(wxNullColour);
    m_timeInput = new wxSpinCtrl(this, ID_TimeInput, "0", wxDefaultPosition, wxSize(100, 20));
    m_timeInput->SetMax(INT_MAX);
    m_timeOutput = new wxTextCtrl(this, ID_TimeOutput, "0' 00'' 000", wxPoint(0, 30), wxSize(100, 20));
    m_timeOutput->SetEditable(false);

    wxArrayString choices;
    for (const auto &unit : m_units)
    {
        choices.push_back(TimeUnitToString(unit));
    }
    m_cb_timeUnit = new wxChoice(this, ID_CB_TimeUnit, wxPoint(110, 0), wxSize(100, 20), choices);
    m_cb_timeUnit->SetSelection(0);
}


milliseconds MyFrame::getInputTime()
{
    const int value = m_timeInput->GetValue();
    const int unitIndex = m_cb_timeUnit->GetSelection();
    if (unitIndex == wxNOT_FOUND)
    {
        return milliseconds(0);
    }

    const TimeUnit unit = m_units[unitIndex];
    switch (unit)
    {
    case TimeUnit::milliseconds:
        return milliseconds(value);
    case TimeUnit::centiseconds:
        return centiseconds(value);
    case TimeUnit::deciseconds:
        return deciseconds(value);
    case TimeUnit::seconds:
        return seconds(value);
    }
    return milliseconds(0);
}

void MyFrame::updateTime()
{
    const auto ms = getInputTime();
    const std::string s = MinSecMs(ms).to_string();
    m_timeOutput->SetValue(s);
}

void MyFrame::OnInputChange(wxSpinEvent& event)
{
    updateTime();
}

void MyFrame::OnTimeUnitChange(wxCommandEvent& event)
{
    updateTime();
}
