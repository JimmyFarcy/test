#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteurss_recepteur_proprietes.h
   \brief Element correspondant à la configuration d'un récepteur de surface
*/

/**
   \brief Element correspondant à la configuration d'un récepteur de surface
   @see E_Scene_Recepteurss_Recepteur
*/
class E_Scene_Recepteurss_Recepteur_Proprietes: public Element
{
private:

	void InitProperties()
	{
		this->AppendPropertyText("description","Description","");
		_("Description");
	}
public:
	E_Scene_Recepteurss_Recepteur_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Propriétés");
	}

	E_Scene_Recepteurss_Recepteur_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_PROPRIETES)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		InitProperties();
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prop"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};