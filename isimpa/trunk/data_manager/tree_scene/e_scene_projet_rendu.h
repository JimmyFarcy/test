#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_projet_rendu_origine.h"

/** \file e_scene_projet_rendu.h
 *   \brief Element dossier contenant les élément de configuration du rendu 3D
 */

/**
 *   \brief Element dossier contenant les élément de configuration du rendu 3D
 */
class E_Scene_Rendu: public Element
{
public:
	E_Scene_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_PROJET_RENDU,noeudCourant)
	{
		
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_RENDERING_FOLDER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_RENDERING_FOLDER_CLOSE);
		_("Rendu");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_PROJET_RENDU_ORIGINE)
						this->AppendFils(new E_Scene_Rendu_Origine(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_PROJET_RENDU)
	{
		
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_RENDERING_FOLDER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_RENDERING_FOLDER_CLOSE);
		this->AppendFils(new E_Scene_Rendu_Origine(this));	
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};