#include "first_header_include.hpp"

#include "e_report_file.h"

#ifndef __ELEMENT_FILE_UNKNOWN__
#define __ELEMENT_FILE_UNKNOWN__



/** \file e_report_unknown_file.h
 *  \brief Classe représentant un fichier non reconnu par PSPS mais reconnu par le système d'exploitation
 */

/**
 *	\brief Classe représentant un fichier non reconnu par PSPS mais reconnu par le système d'exploitation
 */
class E_Report_Unknown: public E_Report_File
{
public:
	/**
	 * Structure décrivant le type
	 */

	/**
	 *	Constructeur de création
	 * @param parent Element parent
	 * @param Nom			Nom de l'élément (libellé dans l'arbre du projet). @ref traductiontuto "Ne pas traduire le libellé".
	 * @param Path Chemin d'accès au fichier depuis l'executable de l'interface
	 */
	E_Report_Unknown(Element* parent,wxString Nom,wxString Path);

	/**
	 *	Constructeur XML
	 * @param parent Element parent
	 * @param nodeElement	Noeud XML si création depuis un fichier XML, sinon Pointeur nul (par défaut)
	 */
	E_Report_Unknown(Element* parent,wxXmlNode* nodeElement);

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);
	/**
	 * Test l'extension du fichier passé en paramètre afin de déterminer si le système d'exploitation courant connait un logiciel compatible avec cette extension
	 *
	 * @return Vrai si un élément E_Report_Unknown peut etre créé avec ce fichier.
	 */
	static bool ExtKnownByCurrentOs(const wxString& fileName);

	virtual void FillWxTree(wxTreeCtrl* treeToFeed=NULL,const wxTreeItemId& parentId=wxTreeItemId());

	void OpenFile();
	
};




#endif