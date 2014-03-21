#include "first_header_include.hpp"

#include <wx/dialog.h>

#ifndef _UI_LANGUAGE_SELECTION_
#define _UI_LANGUAGE_SELECTION_

class LanguageSelector  : public wxDialog
{
public:
	/**
	 * Constructeur
	 * @param _rootLngFolder Dossier ou se trouve les sous dossiers de langue "fr","en" etc..
	 * @param _flagsFolder Dossier où se trouve les images des drapeaux
	 */
	LanguageSelector(wxWindow *parent,
                        const wxString& message,
                        const wxString& caption,
						const wxString& rootLngFolder,
						const wxString& flagsFolder,
                        const wxPoint& pos = wxDefaultPosition);
	
	/** Evenement de validation
	*/
    void OnOK(wxCommandEvent& event);
	/** Evenement d'annulation
	*/
    void OnCancel(wxCommandEvent& event);
	/**
	 * Retourne l'indice du langage sélectionné
	 * @see wxLanguage
	 */
	int GetSelectedLanguage();
protected:
    DECLARE_EVENT_TABLE()
};
#endif