#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_bdd_spectrums_user.h"
#include "e_scene_bdd_spectrums_app.h"

/** \file e_scene_bdd_spectrums.h
   \brief Element représentant le dossier de spectres, ce dossier regroupe les spectres utilisateur et application
*/

/**
   \brief Element représentant le dossier de spectres, ce dossier regroupe les spectres utilisateur et application
*/
class E_Scene_Bdd_Spectrums: public Element
{
public:
	E_Scene_Bdd_Spectrums( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Spectres",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_ROOT_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_ROOT_SPECTRUMS_CLOSE);
		_("Spectres");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_USER)
						this->AppendFils(new E_Scene_Bdd_Spectrums_User(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_APP)
						this->AppendFils(new E_Scene_Bdd_Spectrums_Application(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Bdd_Spectrums( Element* parent)
		:Element(parent,"Spectres",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_ROOT_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_ROOT_SPECTRUMS_CLOSE);
		this->AppendFils(new E_Scene_Bdd_Spectrums_User(this));	
		this->AppendFils(new E_Scene_Bdd_Spectrums_Application(this));	
	}

	
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		return NoeudParent;
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("spectrums"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};