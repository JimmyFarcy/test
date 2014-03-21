#include "wxGridCellColorEditor.h"
#include <wx/colordlg.h>
#include "last_cpp_include.hpp"

// ----------------------------------------------------------------------------
// wxGridCellColorEditor
// ----------------------------------------------------------------------------
void wxGridCellColorEditor::BeginEdit(int row, int col, wxGrid* grid)
{
    wxASSERT_MSG(m_control, wxT("The wxGridCellEditor must be created first!"));

	wxColor currentValue = grid->GetCellBackgroundColour(row, col);

	wxColourData valeurCouleur;
	valeurCouleur.SetColour(currentValue);
	wxColourDialog ctrlChoixCouleur(grid,&valeurCouleur);

	if(ctrlChoixCouleur.ShowModal()==wxID_OK)
	{
		valeurCouleur=ctrlChoixCouleur.GetColourData();
		grid->SetCellBackgroundColour(row,col,valeurCouleur.GetColour());
		wxGridCellTextEditor::BeginEdit(row,col,grid);
	}
}

void wxGridCellColorEditor::Show(bool show, wxGridCellAttr *attr)
{
	wxGridCellTextEditor::Show(show,attr);
	m_control->Hide();
}


    bool wxGridCellColorEditor::EndEdit(int row, int col, const wxGrid *grid,
                         const wxString& oldval, wxString *newval)
	{
		return true;
	}
