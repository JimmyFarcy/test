#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_recepteurss_recepteurcoupe_proprietes.h
   \brief Element correspondant à la configuration d'un récepteur de surface
*/

/**
   \brief Element correspondant à la configuration d'un récepteur de surface
   @see E_Scene_Recepteurss_Recepteur
*/
class E_Scene_Recepteurss_RecepteurCoupe_Proprietes: public Element
{
private:

	void AddActiveProp()
	{
		this->AppendPropertyBool("enabled","Activé",true,false);
		_("Activé");
	}
	void InitProperties()
	{
		this->AppendPropertyText("description","Description","");
		this->AppendPropertyDecimal("resolution","Résolution (m)", .5f,false,2,false,true,0,.05f,true);
		AddActiveProp();
		_("Description");
		_("Résolution (m)");
	}
public:
	E_Scene_Recepteurss_RecepteurCoupe_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Propriétés");
		if(!this->IsPropertyExist("enabled"))
			AddActiveProp();
	}

	E_Scene_Recepteurss_RecepteurCoupe_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE_PROPRIETES)
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