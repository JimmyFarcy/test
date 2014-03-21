#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteurss_recepteur_rendu.h
   \brief Element correspondant à la configuration de rendu 3D d'un récepteur de surface
*/

/**
   \brief Element correspondant à la configuration de rendu 3D d'un récepteur de surface
   @see E_Scene_Recepteurss_Recepteur
*/
class E_Scene_Recepteurss_Recepteur_Rendu: public Element
{
public:
	E_Scene_Recepteurss_Recepteur_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
	}

	E_Scene_Recepteurss_Recepteur_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};