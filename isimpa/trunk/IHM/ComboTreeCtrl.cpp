#include "ComboTreeCtrl.h"
#include "last_cpp_include.hpp"


BEGIN_EVENT_TABLE(ComboTreeCtrl, wxTreeCtrl)
    EVT_MOTION(ComboTreeCtrl::OnMouseMove)
    // NOTE: Left down event is used instead of left up right now
    //       since MSW wxTreeCtrl doesn't seem to emit left ups
    //       consistently.
    EVT_LEFT_DOWN(ComboTreeCtrl::OnMouseClick)
END_EVENT_TABLE()

void ComboTreeCtrl::Init()
{
}

bool ComboTreeCtrl::Create( wxWindow* parent )
    {
        return wxTreeCtrl::Create(parent,1,
                                  wxPoint(0,0),wxDefaultSize,
                                  wxTR_HIDE_ROOT|wxTR_HAS_BUTTONS|
                                  wxTR_SINGLE|wxTR_LINES_AT_ROOT|
                                  wxSIMPLE_BORDER);
    }

void ComboTreeCtrl::OnShow()
    {
        // make sure selected item is visible
        if ( m_value.IsOk() )
            EnsureVisible(m_value);
    }

wxSize ComboTreeCtrl::GetAdjustedSize( int minWidth,
                                    int WXUNUSED(prefHeight),
                                    int maxHeight )
    {
        return wxSize(wxMax(200,minWidth),wxMin(125,maxHeight));
    }

wxWindow *ComboTreeCtrl::GetControl() { return this; }

Element* ComboTreeCtrl::GetElementSelection() const
{
	for(int idEl=0;idEl<loadedElements.size();idEl++)
	{
		if(loadedElements[idEl].elementId==m_value)
			return loadedElements[idEl].elementLink;
	}
	return NULL;	
}


wxTreeItemId ComboTreeCtrl::Associate(const wxTreeItemId& newElId,Element* newEl)
{
	loadedElements.push_back(cont_El(newEl,newElId));
	return newElId;
}

void ComboTreeCtrl::SetCurrent( Element* selected )
{
	wxTreeItemId found;

	for(int idEl=0;idEl<loadedElements.size() && !found.IsOk();idEl++)
	{
		if(loadedElements[idEl].elementLink==selected)
			found=loadedElements[idEl].elementId;
	}
	if(found.IsOk() )
	{
        m_value = m_itemHere = found;
		wxTreeCtrl::SelectItem(found,true);
		this->m_combo->SetValue( this->GetStringValue() );
	}
}
void ComboTreeCtrl::SetStringValue( const wxString& s )
{
	this->m_combo->SetValue( this->GetStringValue() );
}

bool ComboTreeCtrl::ElementFitWithFilter(Element* el)
{
	for(std::list<Element::ELEMENT_TYPE>::iterator it=currentFilter.begin();it!=currentFilter.end();it++)
		if(el->IsFittingWithThisType(*it))
			return true;
	return false;
}
void ComboTreeCtrl::AddActiveFilter(Element::ELEMENT_TYPE newFilter)
{
	currentFilter.push_back(newFilter);
}
void ComboTreeCtrl::OnPopup()
{
    if ( m_value.IsOk() )
        return wxTreeCtrl::SelectItem(m_value,true);
}
wxString ComboTreeCtrl::GetStringValue() const
{
    if ( m_value.IsOk() )
        return wxTreeCtrl::GetItemText(m_value);
    return wxEmptyString;
}

//
// Popup event handlers
//

// Mouse hot-tracking
void ComboTreeCtrl::OnMouseMove(wxMouseEvent& event)
{
    int resFlags;
    wxTreeItemId itemHere = HitTest(event.GetPosition(),resFlags);
    if ( itemHere.IsOk() && (resFlags & wxTREE_HITTEST_ONITEMLABEL) )
    {
        wxTreeCtrl::SelectItem(itemHere,true);
        m_itemHere = itemHere;
    }
    event.Skip();
}

// On mouse left, set the value and close the popup
void ComboTreeCtrl::OnMouseClick(wxMouseEvent& event)
{
    int resFlags;
    wxTreeItemId itemHere = HitTest(event.GetPosition(),resFlags);
    if ( itemHere.IsOk() && (resFlags & wxTREE_HITTEST_ONITEMLABEL) )
    {
        m_itemHere = itemHere;
        m_value = itemHere;
        Dismiss();
		wxPostEvent(this,wxCommandEvent(wxEVT_COMMAND_COMBOBOX_SELECTED ,m_combo->GetId()));
    }
    event.Skip();
}