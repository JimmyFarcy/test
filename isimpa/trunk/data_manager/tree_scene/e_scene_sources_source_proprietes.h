#include "first_header_include.hpp"

#include "data_manager/element.h"

/**  \file e_scene_sources_source_proprietes.h
 *   \brief Propriétés d'une source sonore ponctuelle de la scène
 */

/**
 *   \brief Propriétés d'une source sonore ponctuelle de la scène
 * 
 */
class E_Scene_Sources_Source_Proprietes: public Element
{
private:
	//v1.01
	void InitNewProperties()
	{
		this->AppendPropertyBool("enable","Source active",true);
		_("Source active");
	}
	void InitProperties()
	{
		this->AppendPropertyText("description","Description","");
		_("Description");
		std::vector<wxString> vDirectivite;
		std::vector<int> iDirectivite;
		vDirectivite.push_back("Omnidirectionnel");
		vDirectivite.push_back("Unidirectionnel");
		vDirectivite.push_back("Plan XY");
		vDirectivite.push_back("Plan YZ");
		vDirectivite.push_back("Plan XZ");
		_("Omnidirectionnel");
		_("Unidirectionnel");
		_("Plan XY");
		_("Plan YZ");
		_("Plan XZ");
		this->AppendPropertyList("directivite","Directivité",vDirectivite,DIRECTIVITE_SOURCE_OMINIDIRECTIONNEL,false,1,iDirectivite,true);
		_("Directivité");
		this->AppendPropertyDecimal("u","Direction x",1,true,2,false,false,0,0,true);
		this->AppendPropertyDecimal("v","Direction y",1,true,2,false,false,0,0,true);
		this->AppendPropertyDecimal("w","Direction z",1,true,2,false,false,0,0,true);
		_("Direction x");
		_("Direction y");
		_("Direction z");
		this->AppendPropertyDecimal("delay","Délai de déclenchement",0.f,false,4,false,true,0,0,true);
		_("Délai de déclenchement");
		InitNewProperties();
	}
public:
	enum DIRECTIVITE_SOURCE
	{
		DIRECTIVITE_SOURCE_OMINIDIRECTIONNEL,
		DIRECTIVITE_SOURCE_UNIDIRECTIONNEL,
		DIRECTIVITE_SOURCE_XY,
		DIRECTIVITE_SOURCE_YZ,
		DIRECTIVITE_SOURCE_XZ
	};
	E_Scene_Sources_Source_Proprietes( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_SOURCES_SOURCE_PROPRIETES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		ignore_count_change=true;
		if(!this->IsPropertyExist("enable"))
			InitNewProperties();
		if(this->GetBoolConfig("enable"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives++;
		ignore_count_change=false;
		_("Propriétés");
	}

	E_Scene_Sources_Source_Proprietes( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_SCENE_SOURCES_SOURCE_PROPRIETES)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		ignore_count_change=true;
		InitProperties();
		if(this->GetBoolConfig("enable"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives++;
		ignore_count_change=false;
	}
	~E_Scene_Sources_Source_Proprietes()
	{
		if(this->GetBoolConfig("enable"))
			ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives--;
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prop"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
	void Modified(Element* eModif)
	{
		t_elementInfo filsInfo=eModif->GetElementInfos();
		if(filsInfo.libelleElement=="directivite")
		{
			bool newStateCoord=false;
			if(this->GetListConfig("directivite")!=DIRECTIVITE_SOURCE_UNIDIRECTIONNEL)
			{
				newStateCoord=true;
			}else{
				newStateCoord=false;
			}
			this->SetReadOnlyConfig("u",newStateCoord);
			this->SetReadOnlyConfig("v",newStateCoord);
			this->SetReadOnlyConfig("w",newStateCoord);
		}else if(!ignore_count_change && filsInfo.libelleElement=="enable")
		{
			if(this->GetBoolConfig("enable"))
				ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives++;
			else
				ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives--;
		}
		Element::Modified(eModif);
	}
protected:
	bool ignore_count_change;
};