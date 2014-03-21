#include "first_header_include.hpp"

#include "e_report_gabe.h"

#ifndef __ELEMENT_GABE_GAP__
#define __ELEMENT_GABE_GAP__



/** \file e_report_gabe_gap.h
 *  \brief Classe post traitement de résultats de LEF d'un récépteur ponctuel
 */

/**
 *  \brief Classe post traitement de résultats de LEF d'un récépteur ponctuel
 */
class E_Report_Gabe_Gap: public E_Report_Gabe
{
public:
	/**
	 *	Constructeur de création
	 * @param parent Element parent
	 * @param Nom			Nom de l'élément (libellé dans l'arbre du projet). @ref traductiontuto "Ne pas traduire le libellé".
	 * @param Path Chemin d'accès au fichier depuis l'executable de l'interface
	 */
	E_Report_Gabe_Gap(Element* parent,wxString Nom,wxString Path);

	/**
	 *	Constructeur XML
	 * @param parent Element parent
	 * @param nodeElement	Noeud XML si création depuis un fichier XML, sinon Pointeur nul (par défaut)
	 */
	E_Report_Gabe_Gap(Element* parent,wxXmlNode* nodeElement);

	bool GetArrayData(wxWindow* auiBookWin,wxString& arrayTitle,std::vector<wxString>& lblCols,std::vector<wxString>& lblRows,std::vector<wxString>& cells,std::vector<float>& cellsValue);

	void OnRightClic(wxMenu* leMenu);
	
	bool OpenFileInGrid();
};




#endif