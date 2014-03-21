#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/appconfig.h"
#ifndef __ENCOMBREMENT_PROP__
#define __ENCOMBREMENT_PROP__


/** \file e_scene_encombrements_encombrement_proprietes.h
   \brief Propriétés d'un encombrement
*/

/**
   \brief Propriétés d'un encombrement

   Propriétés en rapport avec l'encombrement
*/

class E_Scene_Encombrements_Encombrement_Proprietes: public Element
{
private:

	void InitProperties()
	{
		this->AppendPropertyText(wxT("description"),wxT("Description"),wxT(""));
		_("Description");
		this->AppendPropertyBool(wxT("useforcalculation"),wxT("Encombrement actif"),true);
		_("Encombrement actif");
	}
public:
	E_Scene_Encombrements_Encombrement_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		ignore_count_change=false;
		_("Propriétés");
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement++;
		if(this->GetBoolConfig("useforcalculation"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs++;
	}

	E_Scene_Encombrements_Encombrement_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		ignore_count_change=true;
		InitProperties();
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement++;
		if(this->GetBoolConfig("useforcalculation"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs++;
		ignore_count_change=false;
	}
	~E_Scene_Encombrements_Encombrement_Proprietes()
	{
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement--;
		if(this->GetBoolConfig("useforcalculation"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs--;
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prop"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}


	void Modified(Element* eModif)
	{
		if(!ignore_count_change && eModif->GetElementInfos().libelleElement=="useforcalculation")
		{
			if(this->GetBoolConfig("useforcalculation"))
				ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs++;
			else
				ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs--;
		}
		Element::Modified(eModif);
	}
protected:
	bool ignore_count_change;
};
#endif
