#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteurss_recepteurcoupe_rendu.h
   \brief Element correspondant à la configuration de rendu 3D d'un récepteur de surface
*/

/**
   \brief Element correspondant à la configuration de rendu 3D d'un récepteur de surface
   @see E_Scene_Recepteurss_Recepteur
*/
class E_Scene_Recepteurss_RecepteurCoupe_Rendu: public Element
{
public:
	E_Scene_Recepteurss_RecepteurCoupe_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
	}

	E_Scene_Recepteurss_RecepteurCoupe_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		this->AppendPropertyBool("showplane","Afficher grille",true);
		this->AppendPropertyBool("showlabels","Afficher le nom des sommets",true);
		this->AppendPropertyColor("planecolor","Couleur de la coupe",241,243,175);
		_("Afficher grille");
		_("Afficher le nom des sommets");
		_("Couleur de la coupe");
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};