#include "first_header_include.hpp"


#ifndef __DIALOG_IMPORT_SCENE__
#define __DIALOG_IMPORT_SCENE__

#include <wx/dialog.h>

/*! \file customdlg.h
 *    @brief Boite de dialogue contenant un ou plusieurs champs de saisie
 */

/**
 * @brief Boite de dialogue importation de modèle 3D
 * 
 * Boite de dialogue où l'utilisateur choisi quel traitement a effectuer sur le modèle 3D à importer
 */
class sceneLoadOptionDialog : public wxDialog
{
public:
	/**
	 * Constructeur
	 * @param parent Fenêtre parente
	 * @param message Message de la fenêtre
	 * @param caption Titre de la fenêtre
	 * @param pos Position de la fenêtre
	 */
    sceneLoadOptionDialog(wxWindow *parent,
                        const wxString& message,
                        const wxString& caption,
                        const wxString& defaultMeshParams,
                        const wxPoint& pos = wxDefaultPosition);

	
	/** Evenement de validation
	*/
    void OnOK(wxCommandEvent& event);
	/** Evenement d'annulation
	*/
    void OnCancel(wxCommandEvent& event);
	void OnCheckMeshModel(wxCommandEvent& evt);
	void OnLauchRemeshWizard(wxCommandEvent& evt);
	void OnCheckRestoreGroups(wxCommandEvent& evt);

	wxString GetMeshParameters();
	bool IsMeshRepair();
	bool IsMeshSurface();
	bool IsKeepExistingFaceLinks();
	/**
	 * @return Distance maximale de lien avec les anciens groupes en m.
	 */
	float GetEpsilonLinkingFaceGroup();
	/**
	 * L'utilisateur veut il executer l'operation de remaillage du modèle
	 */
	bool IsRemeshModel();


private:
	wxTextCtrl* txt_ParamMesh;
	wxCheckBox* cb_TryToRepairMesh;
	wxCheckBox* cb_TryToMeshSurface;
	wxCheckBox* cb_KeepExistingFaceLinks;
	wxCheckBox* cb_RemeshModel;

	wxString epsilonValue;
    DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(sceneLoadOptionDialog)
    DECLARE_NO_COPY_CLASS(sceneLoadOptionDialog)
};

#endif // __NUMDLGH_G__
