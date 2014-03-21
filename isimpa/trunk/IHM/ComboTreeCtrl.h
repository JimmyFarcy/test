#include "first_header_include.hpp"

#include <wx/treectrl.h>
#include <wx/combo.h>
#include "data_manager/element.h"
#include <list>
#ifndef __COMBOTREECTRL_H__
#define __COMBOTREECTRL_H__


/** 
 * @file ComboTreeCtrl.h
 * @brief Vue en arbre dans une liste déroulante. Utilisé pour afficher les matériaux disponibles.
 */

/**
 * @brief Vue en arbre dans une liste déroulante. Utilisé pour afficher les matériaux disponibles.
 */
class ComboTreeCtrl : public wxTreeCtrl, public wxComboPopup
{
	public :
	

    virtual void Init();

    virtual bool Create( wxWindow* parent );

    virtual void OnShow();

    virtual wxSize GetAdjustedSize( int minWidth,
                                    int WXUNUSED(prefHeight),
                                    int maxHeight );

    virtual wxWindow *GetControl();

    // Associe un numero d'élément avec un pointeur d'élément
	// Cet élément devient alors sélectionnable par l'utilisateur
    wxTreeItemId Associate(const wxTreeItemId& newElId,Element* newEl);

    virtual void SetStringValue( const wxString& s );
	virtual void SetCurrent( Element* selected );

    virtual wxString GetStringValue() const;
	virtual Element* GetElementSelection() const;

	//virtual void GetActiveFilter(std::vector<Element::ELEMENT_TYPE>& filter);
	virtual bool ElementFitWithFilter(Element* el);
	virtual void AddActiveFilter(Element::ELEMENT_TYPE newFilter);
    //
    // Popup event handlers
    //

    // Mouse hot-tracking
    void OnMouseMove(wxMouseEvent& event);

    // On mouse left, set the value and close the popup
    void OnMouseClick(wxMouseEvent& event);

	virtual void OnPopup();
protected:
	struct cont_El
	{
		cont_El(Element* _element,wxTreeItemId _elementId):elementLink(_element),elementId(_elementId){}
		Element* elementLink;
		wxTreeItemId elementId;
	};
	std::vector<cont_El> loadedElements;
	std::list<Element::ELEMENT_TYPE> currentFilter;
    wxTreeItemId        m_value; // current item index
    wxTreeItemId        m_itemHere; // hot item in popup
private:
    DECLARE_EVENT_TABLE()
};

#endif