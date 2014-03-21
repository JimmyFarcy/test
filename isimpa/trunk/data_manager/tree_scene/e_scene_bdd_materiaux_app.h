#include "first_header_include.hpp"

#include "data_manager/tree_scene/e_scene_bdd_materiaux_app_materiau.h"
#include "data_manager/tree_scene/e_scene_bdd_materiaux_app_group.h"
#include "data_manager/appconfig.h"

/** \file e_scene_bdd_materiaux_app.h
   \brief Element représentant un dossier contenant un ou plusieurs matériau et/ou un ou plusieurs groupes de matériaux
*/

/**
   \brief Element représentant un dossier contenant un ou plusieurs matériau et/ou un ou plusieurs groupes de matériaux
*/
class E_Scene_Bdd_Materiaux_Application: public Element
{
public:
  /*!
   *  \callgraph
   */

	E_Scene_Bdd_Materiaux_Application( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Référence",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP,noeudCourant)
	{
		_("Référence");

		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_APPLICATION_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_APPLICATION_MATERIALS_CLOSE);
		wxXmlNode* noeudCfg=ApplicationConfiguration::GetAppMateriauNode();

		//On initialise les id des éléments
		if(noeudCfg!=NULL)
		{
			wxXmlNode* currentChild;
			currentChild = noeudCfg->GetChildren();
			// On va créer les fils de notre noeudCourant
			wxString propValue;
			while(currentChild!=NULL)
			{
				if(currentChild->GetPropVal("eid",&propValue))
				{
					long typeEle;
					propValue.ToLong(&typeEle);
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_MATERIAU || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_MATERIAU)
						this->AppendFils(new E_Scene_Bdd_Materiaux_App_Materiau(currentChild,this));
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_GROUP || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP)
						this->AppendFils(new E_Scene_Bdd_Materiaux_App_Group(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Bdd_Materiaux_Application( Element* parent)
		:Element(parent,"Référence",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_APPLICATION_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_APPLICATION_MATERIALS_CLOSE);
	}

	


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDocWithoutChildren(NoeudParent);
		thisNode->SetName("appmateriaux"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}

	

};