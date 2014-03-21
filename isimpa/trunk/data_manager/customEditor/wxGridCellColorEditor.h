#include "first_header_include.hpp"

#include <wx/grid.h>
#include <wx/textctrl.h>

#ifndef __COLOR_EDITOR__
#define __COLOR_EDITOR__

/*! \file wxGridCellColorEditor.h
 *  @brief Editeur de cellule de type couleur
 *  @see E_Data_Color
 */
/**
 *  @brief Editeur de cellule de type couleur
 *
 *  Lors ce que l'utilisateur désire éditer un champ couleur l'instance de cette classe associé est appelé via wxGridCellColorEditor::BeginEdit
 *  Lors ce que la grille MainPropGrid affiche ce type de champ elle appelle wxGridCellColorEditor::Show
 *  A la fin de l'édition du champ la méthode wxGridCellColorEditor::EndEdit est appelé afin de mettre à jour la cellule texte de base
 *  @see E_Data_Color
 */
class wxGridCellColorEditor : public wxGridCellTextEditor
{
public:
	/**
	 * Début d'édition du champ
	 * @param row Ligne
	 * @param col Colonne
	 * @param grid Pointeur vers le contrôle
	 */
    virtual void BeginEdit(int row, int col, wxGrid* grid); 
	/**
	 * Affichage du champ
	 * @param show "use the specified attributes to set colours/fonts for it."
	 * @param attr Attributs de la cellule associée
	 */
	virtual void Show(bool show, wxGridCellAttr *attr);

	
	/**
	 * Fin d'édition du champ
	 * @param row Ligne
	 * @param col Colonne
	 * @param grid Pointeur vers le contrôle
	 */
    virtual bool EndEdit(int row, int col, const wxGrid *grid,
                         const wxString& oldval, wxString *newval);

};

#endif