#include "first_header_include.hpp"

#include "data_manager/element.h"

/**  \file e_scene_projet_userconfiguration.h
 *   \brief Propriétés du projet n'ayant aucune importance pour les méthodes du calcul
 * 
 *   Il s'agit d'information relatives au projet tel que le nom du projet, son auteur etc..	
 */

/**
 *   \brief Propriétés du projet n'ayant aucune importance pour les méthodes du calcul
 * 
 *   Il s'agit d'information relatives au projet tel que le nom du projet, son auteur etc..	
 * 
 */
class E_Scene_UserConfiguration: public Element
{
private:

	void InitProperties() 
	{
		this->AppendPropertyText("projectname","Nom du projet",_("Nouveau projet"));
		_("Nom du projet");
		this->AppendPropertyText("projectdesc","Description du projet","");
		_("Description du projet");
		this->AppendPropertyText("projectuser","Auteur","");
		_("Auteur");
		wxDateTime maintenant=wxDateTime::UNow();
		wxString folderDated=maintenant.Format("%d-%m-%Y %Hh%Mm");
		this->AppendPropertyText("projectdate","Date",folderDated);
		_("Date");
	}
public:
	E_Scene_UserConfiguration( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Configuration",Element::ELEMENT_TYPE_SCENE_PROJET_USERCONFIGURATION,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_PROJECT_AUTHOR);
		_("Configuration");
	}

	E_Scene_UserConfiguration( Element* parent)
		:Element(parent,"Configuration",Element::ELEMENT_TYPE_SCENE_PROJET_USERCONFIGURATION)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_PROJECT_AUTHOR);
		InitProperties();
	}

	

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("Configuration"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};