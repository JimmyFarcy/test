#include "first_header_include.hpp"

#include "e_report_file.h"
#include "data_manager/appconfig.h"
#include <wx/log.h>
#ifndef __ELEMENT_FILENAME_PARTVISU__
#define __ELEMENT_FILENAME_PARTVISU__



/** \file e_report_partvisualisation.h
 *  \brief Classe représentant un ensemble d'enregistrements de positions de particules
 */

/**
 *	\brief Classe représentant un ensemble d'enregistrements de positions de particules
 */
class E_Report_ParticulesVisualisation: public E_Report_File
{
private:
	unsigned int userChoiceFreq;
public:
	/**
	 *	Constructeur de création
	 * @param parent Element parent
	 * @param Nom			Nom de l'élément (libellé dans l'arbre du projet). @ref traductiontuto "Ne pas traduire le libellé".
	 * @param Path Chemin d'accès au fichier depuis l'executable de l'interface
	 */
	E_Report_ParticulesVisualisation(Element* parent,wxString Nom,wxString Path)
		:E_Report_File(parent,"Visualisation particules",Path,ELEMENT_TYPE_REPORT_PARTVISUALISATION)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_DISK_PARTICLE);

	}

	/**
	 *	Constructeur XML
	 * @param parent Element parent
	 * @param nodeElement	Noeud XML si création depuis un fichier XML, sinon Pointeur nul (par défaut)
	 */
	E_Report_ParticulesVisualisation(Element* parent,wxXmlNode* nodeElement)
		:E_Report_File(parent,"Visualisation particules","",ELEMENT_TYPE_REPORT_PARTVISUALISATION,nodeElement)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_DISK_PARTICLE);
		_("Visualisation particules");
	}




	void OnRightClic( wxMenu* leMenu )
	{
		
		wxMenu* subMenuLoadSimu = new wxMenu;
		subMenuLoadSimu->Append(GetMenuItem(subMenuLoadSimu,IDEVENT_LOAD_PARTICLE_SIMULATION,_("En particules")));
		subMenuLoadSimu->Append(GetMenuItem(subMenuLoadSimu,IDEVENT_LOAD_PARTICLE_SIMULATION_PATH,_("En rayons")));
		leMenu->Append(GetMenuItem(leMenu,-1,_("Charger la simulation"),subMenuLoadSimu));
		E_Report_File::OnRightClic(leMenu);
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Report_File::SaveXMLDoc(NoeudParent);
		thisNode->SetName("partfile"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};




#endif