
#ifndef __CUSTDIALOG_G__
#define __CUSTDIALOG_G__

#include <vector>
#include "wx/dialog.h"

/*! \file customdlg.h
 *
 *  @brief Boite de dialogue contenant un ou plusieurs champs de saisie
 *
 *  Ce fichier implémente la classe wxCustomEntryDialog.
 ***/

/**
 * @brief Boite de dialogue contenant un ou plusieurs champs de saisie
 *
 * Surcharge de wxDialog afin de créer une boite de dialogue contenant un ou plusieurs champs texte
 * Son utilisation est simple :
 *	- On instancie la classe
 *	- On ajoute des champs via la méthode wxCustomEntryDialog::AddTextControl()
 *	- On affiche via la méthode wxCustomEntryDialog::Show()
 *	- On récupere les valeurs via wxCustomEntryDialog::GetValues()
 * 
 *  @see MyFrame::OnCreateModel()
 *
 ***/
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
	 * @see GetValues()
	 */
	void AddTextControl(     const wxString& label,
                        const wxString& defaultvalue
						);
	/**
	 * Charge les valeurs dans le tableau passé en paramètre
	 * @param[out] values Tableau de chaines de caractères. Ce tableau est alimenté dans l'ordre d'appel de AddTextControl()
	 */
	void GetValues(std::vector<wxString> &values);

	/** Permet d'obtenir la valeur d'un champ de saisie
	 * @param[in] idChamp Indice du champ
	 * @param[out] value Valeur du champ
	 * @return Vrai si un champ correspond à l'identifiant
	 * @see GetValues()
	 */
	bool GetValue(int idChamp, wxString& value);

	/** Evenement de validation
	 *  @param event Objet lié à l'événement
	 */
    void OnOK(wxCommandEvent& event);

	/** Evenement d'annulation
	 *  @param event Objet lié à l'événement
	 */
    void OnCancel(wxCommandEvent& event);

	/** Définit les paramètres d'un champ.
	 */
	struct t_valueType
	{
		bool readOnly;		/*!< Champ lecture seule */
		bool allowNum;		/*!< Autorise la saisie de nombres */
		bool allowAlpha;	/*!< Autorise la saisie de lettres */
		bool allowChar;		/*!< Autorise la saisie de tous les charactères */
	}

	bool isModified;		/*!< Vrai si l'utilisateur a modifié un champ */
private:

	std::vector<wxTextCtrl*> m_controls;
	wxFlexGridSizer *vinputsizer;
	wxBoxSizer* topsizer;
    DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(wxCustomEntryDialog)
    DECLARE_NO_COPY_CLASS(wxCustomEntryDialog)
};

#endif // __CUSTDIALOG_G__
