#include "first_header_include.hpp"

#include <wx/panel.h>
#include <wx/propdlg.h>
#include <wx/generic/propdlg.h>
#include <vector>
#include "simpleGraphEnumerators.h"

#ifndef __DIALOG_DIAGRAM_CREATOR__
#define __DIALOG_DIAGRAM_CREATOR__

/**
 * @brief Fenetre de configuration d'ajout de graphique
 */
class BuildGraphSheetDialog : public wxPropertySheetDialog
{
	DECLARE_CLASS(BuildGraphSheetDialog)
public:
	BuildGraphSheetDialog(wxWindow* parent,wxWindow* auiNotebookParent, wxWindowID id,
                   const wxString& title,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& sz = wxDefaultSize);
	void LoadData(std::vector<wxString>& lblCols,std::vector<wxString>& lblRows,std::vector<float>& cellsValue);
	/**
	 * Optionnel, Dossier où sont stocké les données du graphique.
	 */
	void SetDataFolder(const wxString& grid_folder) { dataFolder=grid_folder;}
protected:
	void OnOK(wxCommandEvent& event);

	std::vector<wxString> cols;
	std::vector<wxString> rows;
	std::vector<float> curveValues;

	wxPanel* CreateMainSettingsPage(wxWindow* parent);
	sgSpace::StyleArray drawingMethodStyles;
	wxString dataFolder;
private:
	wxWindow* auiNotebook;
	DECLARE_EVENT_TABLE()
};

#endif
