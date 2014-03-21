#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_userprefitem.hpp"
#include "e_userprefitemisotemplate.hpp"

#ifndef __E_USERPREFNODE__
#define __E_USERPREFNODE__
/*! \file e_userprefnode.hpp
    \brief Correspond à l'élément de noeud des préférences utilisateurs
*/
/**
	\brief Correspond à l'élément de noeud des préférences utilisateurs

	Cette classe permet de placer les paramètres dans des catégories
*/
class E_UserPreferenceNode: public Element
{
public:
	E_UserPreferenceNode(Element* parent,wxString Nom, wxXmlNode* nodeElement=NULL)
		:Element(parent,Nom,ELEMENT_TYPE_USER_PREFERENCE_NODE,nodeElement)
	{
		
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FOLDER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FOLDER);
		// Ajout des fils
		AppendSons(nodeElement);
	}
	E_UserPreferenceNode(Element* parent,wxString Nom,ELEMENT_TYPE _type ,wxXmlNode* nodeElement=NULL)
		:Element(parent,Nom,_type,nodeElement)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FOLDER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FOLDER);
		AppendSons(nodeElement);
	}
	void AppendSons(wxXmlNode* nodeElement)
	{
		if(nodeElement)
		{
			wxXmlNode* currentChild;
			currentChild = nodeElement->GetChildren();
			wxString propValue;
			while(currentChild!=NULL)
			{
				if(currentChild->GetPropVal("eid",&propValue))
				{
					long typeEle;
					propValue.ToLong(&typeEle);
					switch(typeEle)
					{
						case ELEMENT_TYPE_USER_PREFERENCE_NODE:
							this->AppendFils(new E_UserPreferenceNode(this,"",currentChild));
							break;
						case ELEMENT_TYPE_USER_PREFERENCE_ITEM:
							this->AppendFils(new E_UserPreferenceItem(this,"",currentChild));
							break;
						case ELEMENT_TYPE_USER_PREFERENCE_ITEM_ISOTEMPLATE:
							this->AppendFils(new E_UserPreferenceItemIsoTemplate(this,"",currentChild));
					};
				}
				currentChild = currentChild->GetNext();
			}
		}
	}
	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="")
	{
		if(etypefils==ELEMENT_TYPE_USER_PREFERENCE_NODE)
		{
			E_UserPreferenceNode* econf=new E_UserPreferenceNode(this,libelle);
			this->AppendFils(econf);
			return econf;
		}else if(etypefils==ELEMENT_TYPE_USER_PREFERENCE_ITEM){
			return this->AppendFils(new E_UserPreferenceItem(this,libelle));
		}else if(etypefils==ELEMENT_TYPE_USER_PREFERENCE_ITEM_ISOTEMPLATE){
			return this->AppendFils(new E_UserPreferenceItemIsoTemplate(this,libelle));
		}else{
			return Element::AppendFilsByType(etypefils,libelle);
		}
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prefnode"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};

#endif