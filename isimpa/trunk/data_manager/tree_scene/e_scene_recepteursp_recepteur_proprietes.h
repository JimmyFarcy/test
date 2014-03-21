#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteursp_recepteur_proprietes.h
   \brief Element correspondant à la configuration d'un récépteur ponctuel
*/

/**
   \brief Element correspondant à la configuration d'un récépteur ponctuel
   @see E_Scene_Recepteursp_Recepteur
*/
class E_Scene_Recepteursp_Recepteur_Proprietes: public Element
{
private:
	void InitDirectivite()
	{
		
		this->AppendPropertyDecimal("u","Direction x",1,false,2,false,false,0,0,true);
		this->AppendPropertyDecimal("v","Direction y",0,false,2,false,false,0,0,true);
		this->AppendPropertyDecimal("w","Direction z",0,false,2,false,false,0,0,true);
	}
	void InitProperties()
	{
		std::vector<wxString> typesrecepteursp;
		typesrecepteursp.push_back("Omnidirectionnel");
		_("Omnidirectionnel");
		this->AppendPropertyList("typereception","Type",typesrecepteursp,0);
		_("Type");
		this->AppendPropertyText("description","Description","");
		_("Description");
		InitDirectivite();
	}
public:
	E_Scene_Recepteursp_Recepteur_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Propriétés");
		if(!this->IsPropertyExist("u")) //maj versions < 06/11/2008
		{
			InitDirectivite();
		}
	}

	E_Scene_Recepteursp_Recepteur_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_PROPRIETES)
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