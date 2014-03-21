#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteursp_recepteur_rendu.h
   \brief Element correspondant à la configuration de rendu 3D d'un récépteur ponctuel
*/

/**
   \brief Element correspondant à la configuration de rendu 3D d'un récépteur ponctuel
   @see E_Scene_Recepteursp_Recepteur
*/
class E_Scene_Recepteursp_Recepteur_Rendu: public Element
{
private:

	void InitProperties()
	{
		this->AppendPropertyColor("couleur","Couleur",0,255,0);
		_("Couleur"); //Pour generer le fichier de langues automatiquement
		this->AppendPropertyBool("showlabel","Afficher le libellé",true);
		_("Afficher le libellé");
	}
public:
	E_Scene_Recepteursp_Recepteur_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
		InitProperties();
	}

	E_Scene_Recepteursp_Recepteur_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		InitProperties();
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};