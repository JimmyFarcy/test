#include "first_header_include.hpp"

#include "data_manager/element.h"
/** \file e_scene_projet_configuration.h
   \brief Element représentant la configuration cachée du projet ( non renseigné par l'utilisateur )
*/

/**
   \brief Element représentant la configuration cachée du projet ( non renseigné par l'utilisateur )
*/
class E_Scene_Configuration: public Element
{
public:
	E_Scene_Configuration( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Configuration",Element::ELEMENT_TYPE_SCENE_PROJET_CONFIGURATION,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Configuration");
		if(this->GetStringConfig("urlmodel")==wxString("current")+wxFileName::GetPathSeparator()+"sceneMesh.bin") //maj version 1.0.3
			this->UpdateStringConfig("urlmodel","sceneMesh.bin");
	}

	E_Scene_Configuration( Element* parent)
		:Element(parent,"Configuration",Element::ELEMENT_TYPE_SCENE_PROJET_CONFIGURATION)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		InitProperties();
	}
	/*
	 * Ajoute les éléments de configuration tel que l'emplacement du fichier de modèle et le chemin de sauvegarde par défaut du projet
	 */
	void InitProperties()
	{
		this->AppendPropertyText("urlmodel","Fichier de modèle","",true);
		_("Fichier de modèle"); //Pour generer les fichiers de langues
		this->AppendPropertyText("urlsave","Fichier de sauvegarde","",true);
		_("Fichier de sauvegarde");
	}

	void FillWxTree(wxTreeCtrl* treeToFeed,const wxTreeItemId& parentId)
	{
		//Ne pas afficher cet élément dans l'arbre
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("Configuration"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};
