#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/generic_element/e_gammefrequence_app.h"
#include "data_manager/appconfig.h"

/** \file e_scene_bdd_spectrums_app.h
   \brief Element représentant un dossier contenant un ou plusieurs spectres et/ou un ou plusieurs groupes de spectres
*/

/**
   \brief Element représentant un dossier contenant un ou plusieurs spectres et/ou un ou plusieurs groupes de spectres
*/

class E_Scene_Bdd_Spectrums_Application: public Element
{
public:
	E_Scene_Bdd_Spectrums_Application( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Référence",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_APP,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_APPLICATION_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_APPLICATION_SPECTRUMS_CLOSE);
		_("Référence");

		wxXmlNode* noeudCfg=ApplicationConfiguration::GetAppSpectreNode();

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
					if(typeEle==Element::ELEMENT_TYPE_GAMMEFREQ_USER || typeEle==Element::ELEMENT_TYPE_GAMMEFREQ_APP)
						this->AppendFils(new E_GammeFrequence_App(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Bdd_Spectrums_Application( Element* parent)
		:Element(parent,"Référence",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_APP)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_APPLICATION_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_APPLICATION_SPECTRUMS_CLOSE);
	}


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDocWithoutChildren(NoeudParent);
		thisNode->SetName("appspectre"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}

};