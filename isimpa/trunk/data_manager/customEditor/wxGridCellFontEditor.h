#include <wx/grid.h>
#include <wx/textctrl.h>

#ifndef __FONT_EDITOR__
#define __FONT_EDITOR__

/*! \file wxGridCellFontEditor.h
 *  @brief Editeur de cellule de type police de caractère
 *  @see E_Data_Font
 */
/**
 *  @brief Editeur de cellule de type police de caractère
 *
 *  Lors ce que l'utilisateur désire éditer un champ de police l'instance de cette classe associé est appelé via wxGridCellFontEditor::BeginEdit
 *  Lors ce que la grille MainPropGrid affiche ce type de champ elle appelle wxGridCellFontEditor::Show
 *  A la fin de l'édition du champ la méthode wxGridCellFontEditor::EndEdit est appelé afin de mettre à jour la cellule
 *  @see E_Data_Font
 */
class wxGridCellFontEditor : public wxGridCellTextEditor
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
	 * Fin d'édition du champ
	 * @param row Ligne
	 * @param col Colonne
	 * @param grid Pointeur vers le contrôle
	 */
    virtual bool EndEdit(int row, int col, const wxGrid *grid,
                         const wxString& oldval, wxString *newval);
	/**
	 * Affichage du champ
	 * @param show "use the specified attributes to set colours/fonts for it."
	 * @param attr Attributs de la cellule associée
	 */
	virtual void Show(bool show, wxGridCellAttr *attr);
};

#endif