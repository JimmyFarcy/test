#include "data_manager/element.h"

/**  \file e_scene_projet_demo.h
 *   \brief Description courte de la classe
 * 
 *   Informations détaillées de la classe
 */

/**
 *   \brief Description courte de la classe
 * 
 *   Informations détaillées de la classe
 */
class E_Scene_Projet_Demo: public Element
{
public:
	E_Scene_Projet_Demo( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Demo",Element::ELEMENT_TYPE_SCENE_PROJET_DEMO,Element::GRAPH_ITEM,noeudCourant)
	{
		_("Demo");
	}

	E_Scene_Projet_Demo( Element* parent)
		:Element(parent,"Demo",Element::ELEMENT_TYPE_SCENE_PROJET_DEMO,Element::GRAPH_ITEM)
	{
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("demo"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};