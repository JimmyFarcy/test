﻿/////////////////////////////////////////////////////////////////////////////
// Name:        customdlg.cpp
// Purpose:     Custom Entry Dialog class
// Author:      Nicolas Fortin
// Modified by:
// Created:     09.01.08
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <stdio.h>

    #include <wx/utils.h>
    #include <wx/dialog.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/intl.h>
    #include <wx/sizer.h>
#endif

#if wxUSE_STATLINE
  #include <wx/statline.h>
#endif


#include "customdlg.h"
#include "IHM/PropGrid.h"
#include "last_cpp_include.hpp"


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxCustomEntryDialog
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(wxCustomEntryDialog, wxDialog)
    EVT_BUTTON(wxID_OK, wxCustomEntryDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, wxCustomEntryDialog::OnCancel)
END_EVENT_TABLE()

IMPLEMENT_CLASS(wxCustomEntryDialog, wxDialog)

wxCustomEntryDialog::wxCustomEntryDialog(wxWindow *parent,
                                         const wxString& message,
                                         const wxString& caption,
                                         const wxPoint& pos)
                   : wxDialog(parent, wxID_ANY, caption,
				   pos, wxDefaultSize,wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxRESIZE_BORDER)
{

	this->SetMinSize(wxSize(320,320));
    wxBeginBusyCursor();

	wxBoxSizer* topsizer = new wxBoxSizer( wxVERTICAL );
#if wxUSE_STATTEXT
    // 1) text message
    topsizer->Add( CreateTextSizer( message ), 0, wxALL, 10 );
#endif

    // 2) prompt and text ctrl
	wxBoxSizer* vinputsizer = new wxBoxSizer(wxHORIZONTAL);

	//vinputsizer->SetVGap(5);
	//vinputsizer->SetHGap(5);

	topsizer->Add( vinputsizer, 1, wxEXPAND | wxTOP|wxBOTTOM, 5 );

    // 3) buttons if any
    wxSizer *buttonSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
    if ( buttonSizer )
    {
        topsizer->Add(buttonSizer, wxSizerFlags().Expand().DoubleBorder());
    }

	PropGrid* newGrid=new PropGrid(this,wxCustomEntryDialog::CUSTOM_DIALOG_CTRLS_GRID);
	vinputsizer->Add( newGrid,1,wxEXPAND);
	//newGrid->SetMinSize(wxSize(300,200));
	newGrid->AppendCols();
	newGrid->SetColLabelValue(0,_("Valeur"));
	newGrid->SetLabelAlignment(wxVERTICAL,wxALIGN_LEFT);

    SetSizer( topsizer );
    SetAutoLayout( true );

    topsizer->SetSizeHints( this );
    topsizer->Fit( this );

    Centre( wxBOTH );



    wxEndBusyCursor();
}

void wxCustomEntryDialog::AddListBox( const wxString& label,	const wxString& defaultValue,const wxArrayString& values)
{

	PropGrid* dialogGrid=wxDynamicCast(this->FindWindowById(wxCustomEntryDialog::CUSTOM_DIALOG_CTRLS_GRID),PropGrid);
	if(dialogGrid)
	{
		dialogGrid->AppendRows(1);
		std::size_t idrow(dialogGrid->GetRows()-1);
		dialogGrid->SetRowLabelValue(idrow,label);
		dialogGrid->SetCellEditor(idrow,0,new wxGridCellChoiceEditor(values));
		dialogGrid->SetCellValue(idrow,0,defaultValue);
		dialogGrid->AutoSizeColumns(false);
		dialogGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
		dialogGrid->SetColLabelSize(wxGRID_AUTOSIZE);
	}
	GetSizer()->Fit(this);
}
void wxCustomEntryDialog::AddTextControl( const wxString& label, const wxString& defaultvalue	)
{
	//todo remplacer par un wxgrid
	//wxBoxSizer *inputsizer= new wxBoxSizer( wxHORIZONTAL );

	/*
	vinputsizer->Add( new wxStaticText( this, wxID_ANY, label ), 0, wxLEFT, 10 );
	wxTextCtrl* textControl = new wxTextCtrl(this,wxID_ANY,defaultvalue);
	m_controls.push_back(textControl);
	vinputsizer->Add( textControl );
	topsizer->Fit( this );
	if(m_controls.size()==1)
	{
		textControl->SetSelection(-1, -1);
		textControl->SetFocus();
	}
	*/
	PropGrid* dialogGrid=wxDynamicCast(this->FindWindowById(wxCustomEntryDialog::CUSTOM_DIALOG_CTRLS_GRID),PropGrid);
	if(dialogGrid)
	{
		dialogGrid->AppendRows(1);
		std::size_t idrow(dialogGrid->GetRows()-1);
		dialogGrid->SetRowLabelValue(idrow,label);
		dialogGrid->SetCellValue(idrow,0,defaultvalue);
		dialogGrid->AutoSizeColumns(false);
		dialogGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
		dialogGrid->SetColLabelSize(wxGRID_AUTOSIZE);
	}
	GetSizer()->Fit(this);
}

void wxCustomEntryDialog::GetValues(std::vector<wxString> &values)
{
	PropGrid* dialogGrid=wxDynamicCast(this->FindWindowById(wxCustomEntryDialog::CUSTOM_DIALOG_CTRLS_GRID),PropGrid);
	if(dialogGrid)
	{
		values.reserve(dialogGrid->GetRows());
		for(int i=0;i<dialogGrid->GetRows();i++)
			values.push_back(dialogGrid->GetCellValue(i,0));
	}
}

void wxCustomEntryDialog::OnOK(wxCommandEvent& event)
{


    EndModal(wxID_OK);
}

void wxCustomEntryDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}


