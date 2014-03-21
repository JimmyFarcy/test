#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_volumes_volume_rendu.h
   \brief Element correspondant au rendu d'un volume
*/

/**
   \brief Element correspondant au rendu d'un volume
*/
class E_Scene_Volumes_Volume_Rendu: public Element
{
public:
	E_Scene_Volumes_Volume_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
	}

	E_Scene_Volumes_Volume_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		this->AppendPropertyColor("volcolor","Couleur du volume",GetRandValue()*255,GetRandValue()*255,GetRandValue()*255);
		_("Couleur du volume");
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};