#include "first_header_include.hpp"

#include <wx/aui/auibook.h>
#include "data_manager/element.h"
/**
 * @file DataWindow.h
 * @brief Fenêtre contenant un graphique ainsi que plusieurs grilles de données
 *
 */


#ifndef __DATAWINDOW__
#define __DATAWINDOW__
/**
 * @brief Fenêtre contenant un graphique ainsi que plusieurs grilles de données
 *
 */

class DataWindow : public wxAuiNotebook
{
protected:
	/**
	 * Evenement Drag&Drop d'onglet. Permet de refuser ou d'accepter l'import d'un onglet provenant d'une autre fenêtre
	 */
	void OnAllowNotebookDnD(wxAuiNotebookEvent& evt);
	/**
	 * Evenement De fermeture d'un onglet. Le graphique lié à cette fenêtre doit être mis à jour en conséquence.
	 */
	void OnPageClosed(wxAuiNotebookEvent& evt);
	/**
	 * Evenement De déplacement d'un onglet vers un autre contrôle. Le graphique lié à cette fenêtre doit être mis à jour en conséquence.
	 */
	void OnPageDragAway(wxAuiNotebookEvent& evt);
	/**
	 * Lors-ce que la source de données a été modifié (ajout/suppression d'onglet de données)
	 */
	void OnDataSrcChange();
	DECLARE_EVENT_TABLE();
public:
    DataWindow(wxWindow* parent,
                  wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxAUI_NB_DEFAULT_STYLE);
	
	/**
	 * Ajout d'une feuille de données dans le contrôle.
	 */
	void PushElement(Element* newElement);

	
};

#endif