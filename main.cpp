#include "mainwindow.h"
#include "timeutils.h"
#include "res/res.h"

enum
{
    ID_TimeInput
    , ID_TimeOutput
    , ID_CB_TimeUnit
    , ID_PinCtrl
};

wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler());
    bin2c_init_RES_H();
    MyFrame *frame = new MyFrame("Time Conv", wxPoint(50, 50), wxSize(226, 89));
    frame->SetWindowStyleFlag(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
    , m_units({
        TimeUnit::milliseconds
        , TimeUnit::centiseconds
        , TimeUnit::deciseconds
        , TimeUnit::seconds
    })
{
    this->SetBackgroundColour(wxNullColour);
    m_timeInput = new wxSpinCtrl(this, ID_TimeInput, "0", wxDefaultPosition, wxSize(100, 20));
    m_timeInput->SetRange(0, INT_MAX);
    m_timeInput->Bind(wxEVT_SPINCTRL, &MyFrame::OnInputParamsChange, this);
    m_timeInput->Bind(wxEVT_TEXT, &MyFrame::OnInputParamsChange, this);

    m_timeOutput = new wxTextCtrl(this, ID_TimeOutput, "00' 00'' 000", wxPoint(0, 30), wxSize(100, 20), wxTE_RIGHT);
    m_timeOutput->SetEditable(false);

    wxArrayString choices;
    for (const auto &unit : m_units)
    {
        choices.push_back(TimeUnitToString(unit));
    }
    m_cb_timeUnit = new wxChoice(this, ID_CB_TimeUnit, wxPoint(110, 0), wxSize(100, 20), choices);
    m_cb_timeUnit->SetSelection(0);
    m_cb_timeUnit->Bind(wxEVT_CHOICE, &MyFrame::OnInputParamsChange, this);

    m_pin = new wxToggleButton(this, ID_PinCtrl, wxEmptyString, wxPoint(190, 30), wxSize(20, 20));
    m_pin->SetImageLabel(*bin2c_pinoff_png);
    m_pin->Bind(wxEVT_TOGGLEBUTTON, &MyFrame::OnToggleOnTop, this);
    m_pin->SetToolTip("Always on top");
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

void MyFrame::OnInputParamsChange(wxCommandEvent& event)
{
    updateTime();
}

void MyFrame::OnToggleOnTop(wxCommandEvent& event)
{
    const bool bOnTop = m_pin->GetValue();
    m_pin->SetImageLabel(bOnTop ? *bin2c_pinon_png : *bin2c_pinoff_png);
    SetWindowStyleFlag(bOnTop ? (GetWindowStyleFlag() | wxSTAY_ON_TOP) : (GetWindowStyleFlag() ^ wxSTAY_ON_TOP));
}
