#include "first_header_include.hpp"

#include "data_manager/element.h"


#ifndef _CORE_CONF_
#define _CORE_CONF_




/*! \file e_core_core_config.h
    \brief Element de configuration générique des moteurs de calculs
*/
/**
	@brief Element de configuration générique des moteurs de calculs
*/
class E_Core_Core_Configuration: public Element
{
public:
	E_Core_Core_Configuration( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_CORE_CORE_CONFIG,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
		_("Propriétés");
	}

	E_Core_Core_Configuration( Element* parent)
		:Element(parent,"Propriétés",Element::ELEMENT_TYPE_CORE_CORE_CONFIG)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_CONFIGURATION);
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("configuration"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
	/**
		Initialisation des propriétés communes à tout les coeurs de calcul (celles lues par lib_interface
	*/
	void InitProperties()
	{
		
		AppendPropertyDecimal("duree_simulation","Durée de la simulation (s)",2,false,8,false,true,0,0.0001f,true);
		AppendPropertyDecimal("pasdetemps","Pas de temps (s)",0.01f,false,8,false,false,0,0,true);
		_("Durée de la simulation (s)");
		_("Pas de temps (s)");
	}
	
};

#endif