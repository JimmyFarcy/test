#include "first_header_include.hpp"

#include "e_report_file.h"

#ifndef __ELEMENT_FILENAME_RECEPTEURSPVISU__
#define __ELEMENT_FILENAME_RECEPTEURSPVISU__

/** \file e_report_rpi.h
 *  \brief Fichier d'animation de l'intensité des récepteurs ponctuels
 */

/**
 *	\brief Fichier d'animation de l'intensité des récepteurs ponctuels
 */
class E_Report_ReceiverPonctualIntensity: public E_Report_File
{

public:
	/**
	 *	Constructeur de création
	 * @param parent Element parent
	 * @param Nom			Nom de l'élément (libellé dans l'arbre du projet). @ref traductiontuto "Ne pas traduire le libellé".
	 * @param Path Chemin d'accès au fichier depuis l'executable de l'interface
	 */
	E_Report_ReceiverPonctualIntensity(Element* parent,wxString Nom,wxString Path)
		:E_Report_File(parent,Nom,Path,ELEMENT_TYPE_REPORT_RPI)
	{
		_("IntensityAnimation");
		_("intensity");
	}

	/**
	 *	Constructeur XML
	 * @param parent Element parent
	 * @param nodeElement	Noeud XML si création depuis un fichier XML, sinon Pointeur nul (par défaut)
	 */
	E_Report_ReceiverPonctualIntensity(Element* parent,wxXmlNode* nodeElement)
		:E_Report_File(parent,"Intensité","",ELEMENT_TYPE_REPORT_RPI,nodeElement)
	{
		_("Intensité");
	}

	void OnRightClic( wxMenu* leMenu )
	{
		leMenu->Append(GetMenuItem(leMenu,IDEVENT_LOAD_RECEPTEURSP_SIMULATION,_("Charger la simulation")));
		E_Report_File::OnRightClic(leMenu);
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Report_File::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rpi"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}	
};




#endif