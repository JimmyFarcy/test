#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_bdd_materiaux_user.h"
#include "e_scene_bdd_materiaux_app.h"

/** \file e_scene_bdd_materiaux.h
   \brief Element représentant le dossier de matériaux, ce dossier regroupe les matériaux utilisateur et application
*/

/**
   \brief Element représentant le dossier de matériaux, ce dossier regroupe les matériaux utilisateur et application
*/
class E_Scene_Bdd_Materiaux: public Element
{
public:
	E_Scene_Bdd_Materiaux( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Materiaux",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_ROOT_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_ROOT_MATERIALS_CLOSE);
		_("Materiaux");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER)
						this->AppendFils(new E_Scene_Bdd_Materiaux_User(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP)
						this->AppendFils(new E_Scene_Bdd_Materiaux_Application(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Bdd_Materiaux( Element* parent)
		:Element(parent,"Materiaux",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_ROOT_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_ROOT_MATERIALS_CLOSE);
		this->AppendFils(new E_Scene_Bdd_Materiaux_User(this));	
		this->AppendFils(new E_Scene_Bdd_Materiaux_Application(this));	
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("materiaux"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{

		wxXmlNode* NoeudCourant=new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"surface_absorption_enum");
		return Element::SaveXMLCoreDoc(NoeudCourant);
	}

};