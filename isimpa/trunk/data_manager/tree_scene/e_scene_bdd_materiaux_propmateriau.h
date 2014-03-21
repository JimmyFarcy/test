#include "first_header_include.hpp"

#include "data_manager/element.h"

#ifndef __ELEMENT_PROPERTY_MATERIAL__
#define __ELEMENT_PROPERTY_MATERIAL__

/** \file e_scene_bdd_materiaux_propmateriau.h
   \brief Element représentant les propriétés d'un matériau
*/

/**
   \brief Element représentant les propriétés d'un matériau
*/
class E_Scene_Bdd_Materiaux_PropertyMaterial: public Element
{
public:
	
	void AddSideProperty()
	{
		std::vector<wxString> choices;
		choices.push_back(_("Unilatéral"));
		choices.push_back(_("Bilatéral"));
		this->AppendPropertyList("side_material",_("Sens de prise en compte"),choices,1,false,1,std::vector<int>(),true);
	}

	E_Scene_Bdd_Materiaux_PropertyMaterial( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Description du matériau",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_PROPMATERIAU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Description du matériau");
		if(!this->IsPropertyExist("side_material"))
		{
			AddSideProperty();
		}
	}
	E_Scene_Bdd_Materiaux_PropertyMaterial( Element* parent)
		:Element(parent,"Description du matériau",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_PROPMATERIAU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		this->AppendPropertyDecimal("masse_volumique","Masse volumique (Kg/m3)",0,false,4,false,false,0,0,true);
		this->AppendPropertyDecimal("resistivite","Résistivité (cgs)",100000,false,4,false,false,0,0,true);
		this->AppendPropertyText("description","Description","");
		this->AppendPropertyText("reference","Référence","");
		AddSideProperty();
		_("Référence");
		_("Description");
		_("Masse volumique (Kg/m3)");
		_("Résistivité (cgs)");
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("property"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};

#endif