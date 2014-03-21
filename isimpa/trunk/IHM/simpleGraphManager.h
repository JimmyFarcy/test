#include "first_header_include.hpp"

#include "simpleGraph.h"
#include <wx/confbase.h>

/**
 * @file simpleGraphManager.h
 * @brief Classe de rendu 2D de données graphiques
 *
 * Basé sur wxWidgets ce contrôle permet l'affichage de données graphiques.
 * Cette surcharge ajoute des fonctionnalitées avancés tel que la personalisation du graphique par l'utilisateur via un menu et de nouvelles interfaces.
 */

#ifndef __SIMPLEGRAPH_MANAGER__
#define __SIMPLEGRAPH_MANAGER__

namespace sgSpace
{ 
	enum ID_MSGW
	{
		ID_MSGW_ZOOMFIT=50,
		ID_MSGW_EXPORT,
		ID_MSGW_EXPORT_SAVE_AS,
		ID_MSGW_EXPORT_SAVE_AS_POSTSCRIPT_FILE,
		ID_MSGW_EXPORT_TO_CLIPBOARD,
		ID_MSGW_EXPORT_TO_PRINTER,
		ID_MSGW_CONFIGURATION,
		ID_MSGW_FILTER,
		ID_MSGW_FILTER_SELECT_ALL,
		ID_MSGW_FILTER_UNSELECT_ALL,
		ID_MSGW_FILTER_CHECK_FIRST,
		ID_MSGW_FILTER_CHECK_LAST=500
	};

	/**
	 * Cette surchage permet des fonctions étendues lors du clic bouton droit dans la zone de graphique.
	 */
	class MainSimpleGraphWindow : public simpleGraph
	{
	public:

		MainSimpleGraphWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr);

		
		void OnRightUp( wxMouseEvent &event );

		/**
		 * Charge le style du graphique selon un élément de configuration
		 * @param configManager Gestionnaire de configuration ( Peut être n'importe quelle classe hérité de wxConfigBase )
		 * @param cfgPathName Nom de la clé à consulter
		 */
		virtual bool LoadConfig( wxConfigBase* configManager, const wxString& cfgPathName, bool saveModifications = false);
		/**
		 * Sauvegarde le style du graphique dans un élément de configuration. Les echelles ne sont pas sauvegardées.
		 * @param configManager Gestionnaire de configuration ( Peut être n'importe quelle classe hérité de wxConfigBase )
		 * @param cfgPathName Nom de la clé à utiliser
		 */
		virtual bool SaveConfig( wxConfigBase* configManager, const wxString& cfgPathName );

		void SetDefaultSaveGraphSavePath(const wxString& defPath) { defaultGraphSavePath=defPath; }
	protected:
		void OnZoomFitMenu(wxCommandEvent& event);
		void OnShowGraphParameters(wxCommandEvent& event);
		void OnExportToImageFile(wxCommandEvent& event);
		void OnExportToImageToClipboard(wxCommandEvent& event);
		void OnSwitchCurveVisibility(wxCommandEvent& event);
		void OnHideAllCurves(wxCommandEvent& event);
		void OnShowAllCurves(wxCommandEvent& event);

		wxBitmap GetAreaBitmap();
		DECLARE_EVENT_TABLE()
		bool updateConfigOnChange;
		wxString cfgPathToUpdate;
		wxConfigBase* cfgManagerToUpdate;
		wxString defaultGraphSavePath;
	};
}

#endif