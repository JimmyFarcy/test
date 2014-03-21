#include "first_header_include.hpp"

#include "data_manager/tree_scene/e_scene_bdd_materiaux_app_materiau.h"

/** \file e_scene_bdd_materiaux_app_group.h
   \brief Element représentant un dossier de matériaux, ce dossier peut contenir un dossier de meme type ou un matériau
*/

/**
   \brief Element représentant un dossier de matériaux, ce dossier peut contenir un dossier de meme type ou un matériau
*/
class E_Scene_Bdd_Materiaux_App_Group: public Element
{
public:
	E_Scene_Bdd_Materiaux_App_Group( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Groupe",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_GROUP,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_APPLICATION_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_APPLICATION_MATERIALS_CLOSE);
		_("Groupe");
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
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_GROUP || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP)
						this->AppendFils(new E_Scene_Bdd_Materiaux_App_Group(currentChild,this));
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_MATERIAU || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_MATERIAU)
						this->AppendFils(new E_Scene_Bdd_Materiaux_App_Materiau(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("appgroup"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}

	

};