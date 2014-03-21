#include "first_header_include.hpp"

#include "data_manager/element.h"

#ifndef __ELEMENT_RENDER_MATERIAL__
#define __ELEMENT_RENDER_MATERIAL__

/** \file e_scene_bdd_materiaux_rendermateriau.h
   \brief Element représentant le rendu d'un matériau
*/

/**
   \brief Element représentant le rendu d'un matériau
*/
class E_Scene_Bdd_Materiaux_RenderMaterial: public Element
{
public:
	E_Scene_Bdd_Materiaux_RenderMaterial( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu 3D",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_MATERIAU_RENDER,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu 3D");
		this->SetDrawable();
	}
	E_Scene_Bdd_Materiaux_RenderMaterial( Element* parent)
		:Element(parent,"Rendu 3D",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_MATERIAU_RENDER)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		this->AppendPropertyColor("mat_color","Couleur",GetRandValue()*255,GetRandValue()*255,GetRandValue()*255);
		_("Rendu");
		this->SetDrawable();
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("matcolor"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};

#endif