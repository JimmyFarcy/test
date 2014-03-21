#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_bdd_spectrums.h"
#include "e_scene_bdd_materiaux.h"

/** \file e_scene_bdd.h
    \brief Element dossier, regroupe le dossier de base de données matériaux et spectres
*/

/**
   \brief Element dossier, regroupe le dossier de base de données utilisateur et application
*/
class E_Scene_Bdd: public Element
{
public:
	E_Scene_Bdd( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Base de données du projet",Element::ELEMENT_TYPE_SCENE_BDD,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_DATABASE_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_DATABASE_CLOSE);
		_("Base de données du projet");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS)
						this->AppendFils(new E_Scene_Bdd_Spectrums(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX)
						this->AppendFils(new E_Scene_Bdd_Materiaux(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Bdd( Element* parent)
		:Element(parent,"Base de données du projet",Element::ELEMENT_TYPE_SCENE_BDD)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_DATABASE_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_DATABASE_CLOSE);
		this->AppendFils(new E_Scene_Bdd_Spectrums(this));	
		this->AppendFils(new E_Scene_Bdd_Materiaux(this));	
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("bdd"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};