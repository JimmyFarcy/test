#include "first_header_include.hpp"

#include "data_manager/generic_element/e_materiau_app.h"
#include "data_manager/tree_scene/e_scene_bdd_materiaux_propmateriau.h"
#include "data_manager/tree_scene/e_scene_bdd_materiaux_rendermateriau.h"


#ifndef __APPMAT__
#define __APPMAT__

/** \file e_scene_bdd_materiaux_app_materiau.h
   \brief Element représentant un matériau, les surfaces vont tirer leurs propriétés de réflexion de ce type de matériau
*/

/**
   \brief Element représentant un matériau, les surfaces vont tirer leurs propriétés de réflexion de ce type de matériau
*/

class E_Scene_Bdd_Materiaux_App_Materiau: public Element
{
public:
	E_Scene_Bdd_Materiaux_App_Materiau( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Application",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_MATERIAU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_MATERIAL_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_MATERIAL_CLOSE);
		_("Application");
		if(noeudCourant!=NULL)
		{
			wxXmlNode* currentChild;
			currentChild = noeudCourant->GetChildren();
			// On va créer les fils de notre noeudCourant
			wxString propValue;
			while(currentChild!=NULL)
			{
				if(currentChild->GetPropVal("eid",&propValue))
				{
					long typeEle;
					propValue.ToLong(&typeEle);
					if(typeEle==Element::ELEMENT_TYPE_MATERIAU_USER || typeEle==Element::ELEMENT_TYPE_MATERIAU_APP)
						this->AppendFils(new E_Materiau_App(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_PROPMATERIAU)
						this->AppendFils(new E_Scene_Bdd_Materiaux_PropertyMaterial(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_MATERIAU_RENDER)
						this->AppendFils(new E_Scene_Bdd_Materiaux_RenderMaterial(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("appmateriau"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}



	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		//Traitement spécial car seulement les matériaux utilisés sont exportés vers le code de calcul
		//On utilise le noeud XML créé par le spectre comme noeud pour les éléments fils (autre que le spectre)
		Element* spectrumMaterial=this->GetElementByType(ELEMENT_TYPE_MATERIAU_APP);
		if(spectrumMaterial)
		{
			std::size_t spectrumid(spectrumMaterial->GetXmlId());
			wxXmlNode* spectrumNode=spectrumMaterial->SaveXMLCoreDoc(NoeudParent);
			if(spectrumNode!=NoeudParent) //Si le matériau est utilisé par le projet
			{
				for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
				{
					if((*itfils)->GetXmlId()!=spectrumid)
						(*itfils)->SaveXMLCoreDoc(spectrumNode);
				}
			}
		}
		return NoeudParent;
	}
};

#endif