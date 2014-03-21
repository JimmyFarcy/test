#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_encombrements_encombrement_rendu.h
   \brief Propriétés de rendu d'un encombrement
*/
#ifndef __ELEMENT_FITTING_FITTING_RENDERING_H__
#define __ELEMENT_FITTING_FITTING_RENDERING_H__
/**
   \brief Propriétés de rendu d'un encombrement
	
   Propriétés de rendu en rapport avec l'encombrement
*/
class E_Scene_Encombrements_Encombrement_Rendu: public Element
{
private:
	void InitLineRenderingProp()
	{
		std::vector<wxString> modes;
		modes.push_back("Volume");
		modes.push_back("Bordures");
		this->AppendPropertyList("rendermode","Mode de rendu",modes,0);
		_("Volume");
		_("Bordures");
		_("Mode de rendu");
	}
	void InitProperties()
	{
		this->AppendPropertyColor("couleur","Couleur",GetRandValue()*255,GetRandValue()*255,GetRandValue()*255);
		_("Couleur"); //Pour generer le fichier de langues automatiquement
		this->AppendPropertyBool("showlabel","Afficher le libellé",false);
		_("Afficher le libellé");
		if(this->pere && this->pere->GetElementInfos().typeElement!=Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT)
		{
			this->AppendPropertyDecimal("obj_transp","Opacité",.5f,false,2,true,true,1,0);
			_("Opacité");
			InitLineRenderingProp();
		}
	}
public:
	E_Scene_Encombrements_Encombrement_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
		if(parent && parent->GetElementInfos().typeElement!=Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT && !this->IsPropertyExist("rendermode"))
			InitLineRenderingProp();
	}

	E_Scene_Encombrements_Encombrement_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		InitProperties();
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		return NoeudParent;
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};
#endif