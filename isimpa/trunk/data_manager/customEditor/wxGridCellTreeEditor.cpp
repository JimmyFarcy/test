﻿#include "wxGridCellTreeEditor.h"
#include "last_cpp_include.hpp"






wxGridCellTreeEditor::wxGridCellTreeEditor(Element* _rootItem,Element* _defaultSelection,const std::list<Element::ELEMENT_TYPE>& elementFilter)
:wxGridCellEditor(),rootItem(_rootItem),currentSelection(_defaultSelection),currentFilters(elementFilter)
{

}

void wxGridCellTreeEditor::BeginEdit(int row, int col, wxGrid* grid)
{
    wxASSERT_MSG(m_control,
                 wxT("The wxGridCellEditor must be created first!"));

    wxEvtHandler* evtHandler = NULL;
    if (m_control)
        evtHandler = m_control->GetEventHandler();

    m_startValue = grid->GetTable()->GetValue(row, col);

   // find the right position, or default to the first if not found
    Combo()->SetValue(m_startValue);

    Combo()->SetInsertionPointEnd();
    Combo()->SetFocus();

}
bool wxGridCellTreeEditor::EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString *newval)
{
	ComboTreeCtrl* popupCtrlTree=dynamic_cast<ComboTreeCtrl*>( Combo()->GetPopupControl());
	if(popupCtrlTree)
	{
		Element* newSelection=popupCtrlTree->GetElementSelection();
		wxString value = Combo()->GetValue();
		*newval=value;
		if ( currentSelection == newSelection )
			return false;

		currentSelection=newSelection;
		grid->GetTable()->SetValue(row, col, value);

		return true;
	}else{
		return false;
	}
}

Element* wxGridCellTreeEditor::GetSelection()
{
	return currentSelection;
}

/*
    bool wxGridCellTreeEditor::EndEdit(int row, int col, const wxGrid *grid,
                         const wxString& oldval, wxString *newval)
	{
		if(oldval!=GetValue())
		{
			*newval=GetValue();
			return true;
		}else{
			return false;
		}
	}
	*/

    void wxGridCellTreeEditor::ApplyEdit(int row, int col, wxGrid* grid)
	{
		grid->SetCellValue(row,col,GetValue());
	}

void wxGridCellTreeEditor::PaintBackground(const wxRect& rectCell,
                                             wxGridCellAttr * attr)
{
    // as we fill the entire client area, don't do anything here to minimize
    // flicker

    // TODO: It doesn't actually fill the client area since the height of a
    // combo always defaults to the standard.  Until someone has time to
    // figure out the right rectangle to paint, just do it the normal way.
    wxGridCellEditor::PaintBackground(rectCell, attr);
}

wxGridCellEditor *wxGridCellTreeEditor::Clone() const
{
	return new wxGridCellTreeEditor(rootItem,currentSelection,currentFilters);
}

void wxGridCellTreeEditor::Create(wxWindow *parent,wxWindowID id,wxEvtHandler *evtHandler)
{
    wxGenericComboCtrl* NewControl = new wxGenericComboCtrl(parent, id, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxCB_READONLY);

	ComboTreeCtrl* popupCtrlTree=new ComboTreeCtrl();

	for(std::list<Element::ELEMENT_TYPE>::iterator itfilter=currentFilters.begin();itfilter!=currentFilters.end();itfilter++)
		popupCtrlTree->AddActiveFilter(*itfilter);
	NewControl->SetPopupControl(popupCtrlTree);

	rootItem->FillWxTree(popupCtrlTree,popupCtrlTree->AddRoot("root"));
	if(currentSelection)
		popupCtrlTree->SetCurrent(currentSelection);
	
	m_control=NewControl;
    wxGridCellEditor::Create(parent, id, evtHandler);
}

ComboTreeCtrl* wxGridCellTreeEditor::GetTree()
{
	return (ComboTreeCtrl*)Combo()->GetPopupControl();
}
void wxGridCellTreeEditor::Reset(void)
{

    Combo()->SetValue(m_startValue);
    Combo()->SetInsertionPointEnd();
}


wxString wxGridCellTreeEditor::GetValue() const
{
  return Combo()->GetValue();
}
