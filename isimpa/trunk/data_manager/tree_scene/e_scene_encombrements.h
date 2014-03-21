#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_encombrements_encombrement_model.h"
#include "e_scene_encombrements_encombrement_cuboide.h"
/** \file e_scene_encombrements.h
   \brief Element représentant un dossier contenant un ou plusieurs encombrements
*/

/**
   \brief Element représentant un dossier contenant un ou plusieurs encombrements
*/
class E_Scene_Encombrements: public Element
{
public:
	E_Scene_Encombrements( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Encombrements",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS,noeudCourant)
	{
		
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FITTINGS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FITTINGS_CLOSE);
		_("Encombrements");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT)
					{
						this->AppendFils(new E_Scene_Encombrements_Encombrement_Model(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_CUBOIDE)
					{
						this->AppendFils(new E_Scene_Encombrements_Encombrement_Cuboide(currentChild,this));
					}

				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Encombrements( Element* parent)
		:Element(parent,"Encombrements",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FITTINGS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FITTINGS_CLOSE);

	}
	
	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="")
	{
		if(etypefils==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT)
		{
			if(libelle=="")
				return this->AppendFils(new E_Scene_Encombrements_Encombrement_Model(this));
			else
				return this->AppendFils(new E_Scene_Encombrements_Encombrement_Model(this,libelle));
		}else if(etypefils==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_CUBOIDE)
		{
			if(libelle=="")
				return this->AppendFils(new E_Scene_Encombrements_Encombrement_Cuboide(this));
			else
				return this->AppendFils(new E_Scene_Encombrements_Encombrement_Cuboide(this,libelle));
		}
		return Element::AppendFilsByType(etypefils,libelle);
	}
	

	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_ENCOMBREMENT, _("Définir encombrement scène"),"./Bitmaps/popup_new.png"));
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_ENCOMBREMENT_CUBOIDE, _("Nouvel encombrement cuboïde"),"./Bitmaps/popup_new.png"));
		Element::OnRightClic(leMenu);
	}

	// Sauvegarde des informations à destination des moteurs de calculs

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"encombrement_enum");
		Element::SaveXMLCoreDoc(thisNode);
		return thisNode;
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("encombrements"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};