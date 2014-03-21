#include "wxGridCellFontEditor.h"
#include <wx/fontdlg.h>
#include "last_cpp_include.hpp"
// ----------------------------------------------------------------------------
// wxGridCellFontEditor
// ----------------------------------------------------------------------------
void wxGridCellFontEditor::BeginEdit(int row, int col, wxGrid* grid)
{
    wxASSERT_MSG(m_control, wxT("The wxGridCellEditor must be created first!"));

	wxFont currentValue = grid->GetCellFont(row,col);
	wxFontData valeurPolice;
	valeurPolice.SetInitialFont(currentValue);
	wxFontDialog ctrlChoixPolice(grid,valeurPolice);

	if(ctrlChoixPolice.ShowModal()==wxID_OK)
	{
		valeurPolice=ctrlChoixPolice.GetFontData();
		wxFont choosenFont=valeurPolice.GetChosenFont();
		grid->SetCellFont(row,col,choosenFont);
		grid->SetCellValue(row,col,choosenFont.GetNativeFontInfoUserDesc());
		wxGridCellTextEditor::BeginEdit(row,col,grid);
		//this->Show(true,this->GetCellAttr());
	}
}

void wxGridCellFontEditor::Show(bool show, wxGridCellAttr *attr)
{
	wxGridCellTextEditor::Show(show,attr);
	m_control->Hide();
}



/*void wxGridCellFontEditor::StartingKey(wxKeyEvent& event)
{
	//event.Skip(true);
}*/

bool wxGridCellFontEditor::EndEdit(int row, int col, const wxGrid *grid,
                         const wxString& oldval, wxString *newval)
{
    return true;
}