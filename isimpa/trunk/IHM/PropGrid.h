#include "first_header_include.hpp"

#include <wx/grid.h>
#include <wx/menu.h>

/*! \file PropGrid.h
    \brief Classe d'affichage des propriétés

	Affiche sous forme d'une grille des données
*/
#ifndef __PROPGRID__
#define __PROPGRID__

/**
 * 
 *  \brief Classe d'affichage des propriétés
 *
 *	Affiche sous forme d'une grille des données
 */

class PropGrid: public wxGrid
{
protected:
	void setCellValueWithEvt(int row,int col,const wxString& val);
	typedef enum EVENT_MENU
	{
		ID_COPIER,
		ID_COLLER,
		ID_COPY_ON_ROW,
		ID_COPY_ON_COLUMN,
		EVENT_MENU_LAST
	};
	struct t_selection
	{
		t_selection():TopRow(0),LeftCol(0),BottomRow(0),RightCol(0){};
		int TopRow;
		int LeftCol;
		int BottomRow;
		int RightCol;
	};
	t_selection currentSelection;
	void OnRightClic(wxGridEvent& ev);
	virtual void DoFillMenu(wxGridEvent& ev,wxMenu* mainMenu);

	void Copy(wxCommandEvent& event);
	void Paste(wxCommandEvent& event);

	virtual void CopyOnRow(wxCommandEvent& event);
	virtual void CopyOnColumn(wxCommandEvent& event);

	void OnRangeSelected( wxGridRangeSelectEvent& ev );
	void OnCellSelected( wxGridEvent& ev );
	void OnLostFocus( wxFocusEvent& ev);
    DECLARE_EVENT_TABLE()
	
	bool allowPaste;
public:
	/**
	 * Constructeur
	 * @param parent Fenêtre parente
	 * @param id Indice de la fenêtre
	 * @param pos Position de la fenêtre 
	 * @param size Taille de la fenêtre
	 * @param style Style de la fenêtre
	 * @param name Libellé de la fenêtre
	 */
	PropGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr);
	/**
	 * Redimensionne les colonne selon le libellé de la ligne row
	 */
	void AutoSizeLibelle( int row );
};
#endif