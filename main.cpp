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
    MyFrame *frame = new MyFrame("Time Conv", wxPoint(1170, 0), wxDefaultSize);
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
    m_timeInput = new wxSpinCtrl(this, ID_TimeInput, "0", wxDefaultPosition, wxDefaultSize);
    m_timeInput->SetRange(0, INT_MAX);
    m_timeInput->Bind(wxEVT_SPINCTRL, &MyFrame::OnInputParamsChange, this);
    m_timeInput->Bind(wxEVT_TEXT, &MyFrame::OnInputParamsChange, this);
    m_timeInput->Bind(wxEVT_SET_FOCUS, &MyFrame::OnInputParamsActivate, this);

    m_timeOutput = new wxTextCtrl(this, ID_TimeOutput, "00' 00'' 000", wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
    m_timeOutput->SetEditable(false);

    wxArrayString choices;
    for (const auto &unit : m_units)
    {
        choices.push_back(TimeUnitToString(unit));
    }
    m_cb_timeUnit = new wxChoice(this, ID_CB_TimeUnit, wxDefaultPosition, wxDefaultSize, choices);
    m_cb_timeUnit->SetSelection(0);
    m_cb_timeUnit->Bind(wxEVT_CHOICE, &MyFrame::OnInputParamsChange, this);

    m_pin = new wxBitmapToggleButton(this, ID_PinCtrl, *bin2c_pinoff_png, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_pin->Bind(wxEVT_TOGGLEBUTTON, &MyFrame::OnToggleOnTop, this);
    m_pin->SetToolTip("Always on top");

    auto s = new wxFlexGridSizer(2, 2, 0, 0);
    s->Add(m_timeInput);
    s->Add(m_cb_timeUnit);
    s->Add(m_timeOutput);
    s->Add(m_pin, wxSizerFlags().Right());
    SetSizerAndFit(s);
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

void MyFrame::OnInputParamsActivate(wxFocusEvent& event)
{
    event.Skip();
    m_timeInput->Bind(wxEVT_IDLE, &MyFrame::OnInputParamsIdle, this);
}

void MyFrame::OnInputParamsIdle(wxIdleEvent& event)
{
    m_timeInput->Unbind(wxEVT_IDLE, &MyFrame::OnInputParamsIdle, this);
    m_timeInput->SetSelection(-1, -1);
}

void MyFrame::OnToggleOnTop(wxCommandEvent& event)
{
    const bool bOnTop = m_pin->GetValue();
    m_pin->SetImageLabel(bOnTop ? *bin2c_pinon_png : *bin2c_pinoff_png);
    SetWindowStyleFlag(bOnTop ? (GetWindowStyleFlag() | wxSTAY_ON_TOP) : (GetWindowStyleFlag() ^ wxSTAY_ON_TOP));
}
