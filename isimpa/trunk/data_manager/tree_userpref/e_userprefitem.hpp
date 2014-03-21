#include "first_header_include.hpp"

#include "data_manager/element.h"


#ifndef __E_USERPREFITEM__
#define __E_USERPREFITEM__
/*! \file e_userprefitem.hpp
    \brief Correspond à l'élément porteur de propriétés
*/
/**
	\brief Correspond à l'élément porteur de propriétés
	Cette classe permet de placer des propriétés
*/
class E_UserPreferenceItem: public Element
{
public:
	E_UserPreferenceItem(Element* parent,wxString Nom, wxXmlNode* nodeElement=NULL)
		:Element(parent,Nom,ELEMENT_TYPE_USER_PREFERENCE_ITEM,nodeElement)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_ITEM);
	}

	E_UserPreferenceItem(Element* parent,wxString Nom,ELEMENT_TYPE _type ,wxXmlNode* nodeElement=NULL)
		:Element(parent,Nom,_type,nodeElement)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_ITEM);
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prefitem"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};

#endif