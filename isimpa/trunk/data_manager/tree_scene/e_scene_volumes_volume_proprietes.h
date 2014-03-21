#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_volumes_volume_proprietes.h
   \brief Element correspondant à la configuration d'un volume
*/

/**
   \brief Element correspondant à la configuration d'un volume
*/
class E_Scene_Volumes_Volume_Proprietes: public Element
{
public:
	E_Scene_Volumes_Volume_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Propriétés");
	}

	E_Scene_Volumes_Volume_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME_PROPRIETES)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		this->AppendPropertyBool("fcompute_mean_free_path","Calculer libre parcourt moyen",true,true);
		this->AppendPropertyDecimal("mean_free_path","Libre parcourt moyen",1,true,2,false,true,0,.01f,true);
		_("Calculer libre parcourt moyen");
		_("Libre parcourt moyen");
	}

	void Modified(Element* eModif)
	{
		t_elementInfo filsInfo=eModif->GetElementInfos();
		if(filsInfo.libelleElement=="fcompute_mean_free_path")
		{
			this->SetReadOnlyConfig("mean_free_path",this->GetBoolConfig("fcompute_mean_free_path"));
		}
		Element::Modified(eModif);
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prop"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};