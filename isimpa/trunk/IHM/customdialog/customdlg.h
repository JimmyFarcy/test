#include "first_header_include.hpp"


#ifndef __CUSTDIALOG_G__
#define __CUSTDIALOG_G__
#include <vector>
#include <wx/dialog.h>

/*! \file customdlg.h
 *    @brief Boite de dialogue contenant un ou plusieurs champs de saisie
 */

/**
 * @brief Boite de dialogue contenant un ou plusieurs champs de saisie
 *
 * Surcharge de wxDialog afin de créer une boite de dialogue contenant un ou plusieurs champs texte
 * Son utilisation est simple :
 *	-On déclare
 *	-On ajoute des champs via la méthode wxCustomEntryDialog::AddTextControl()
 *	-On affiche via la méthode wxCustomEntryDialog::Show()
 *	-On récupere les valeurs via wxCustomEntryDialog::GetValues()
 * 
 */
class wxCustomEntryDialog : public wxDialog
{
public:
	/**
	 * Constructeur
	 * @param parent Fenêtre parente
	 * @param message Message de la fenêtre
	 * @param caption Titre de la fenêtre
	 * @param pos Position de la fenêtre
	 */
    wxCustomEntryDialog(wxWindow *parent,
                        const wxString& message,
                        const wxString& caption,
                        const wxPoint& pos = wxDefaultPosition);

	/**
	 * Ajouter un champ dans la fenêtre
	 * @param label Libellé du champ
	 * @param defaultvalue Valeur d'origine du champ
	 */
	void AddTextControl(     const wxString& label,
                        const wxString& defaultvalue
						);
	
	/**
	 * Ajouter un champ de liste dans la fenêtre
	 * @param label Libellé du champ
	 * @param defaultvalue Valeur d'origine du champ
	 * @param Values Valeur sélectionnable
	 */
	void AddListBox( const wxString& label,
		const wxString& defaultValue,
		const wxArrayString& Values);
	/**
	 * Charge les valeurs dans le tableau passé en paramètre
	 * @param[out] values Tableau de chaîne de caractères.Ce tableau est alimenté dans l'ordre d'appel de AddTextControl()
	 */
	void GetValues(std::vector<wxString> &values);
    // implementation only
	/** Evenement de validation
	*/
    void OnOK(wxCommandEvent& event);
	/** Evenement d'annulation
	*/
    void OnCancel(wxCommandEvent& event);

private:

	enum CUSTOM_DIALOG_CTRLS
	{
		CUSTOM_DIALOG_CTRLS_GRID
	};

private:
    DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(wxCustomEntryDialog)
    DECLARE_NO_COPY_CLASS(wxCustomEntryDialog)
};

#endif // __NUMDLGH_G__
