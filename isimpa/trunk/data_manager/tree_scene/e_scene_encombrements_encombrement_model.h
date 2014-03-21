﻿#include "first_header_include.hpp"

#include "e_scene_groupesurfaces_groupe.h"
#include "e_scene_encombrements_encombrement_rendu.h"
#include "data_manager/drawable_element.h"
#include "e_scene_encombrements_encombrement_proprietes.h"
#include "data_manager/generic_element/e_gammeabsorption.h"

/** \file e_scene_encombrements_encombrement_model.h
   \brief Cet élément est un volume d'encombrement défini à partir de la scène par l'utilisateur
*/

/**
   \brief Cet élément est un volume d'encombrement défini à partir de la scène par l'utilisateur

   Cet encombrement est défini par des faces de la scène.
   L'utilisateur fait un glisser-déposer des faces qui doivent être considérées comme la limite d'un encombrement
*/
class E_Scene_Encombrements_Encombrement_Model: public E_Drawable
{

private:

	bool IsVertexGroupEmpty()
	{
		Element* targ=this->GetElementByType(ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE);
		if(targ)
		{
			E_Scene_Groupesurfaces_Groupe* grpE=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>(targ);
			return grpE->IsEmpty();
		}
		return true;
	}
	void InitEncombrementProp()
	{
		this->elementInfo.userDestroyable=true;
	}
public:
	E_Scene_Encombrements_Encombrement_Model( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Drawable(parent,"Encombrement",Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FITTING_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FITTING_CLOSE);
		this->elementInfo.userDestroyable=true;
		_("Encombrement");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES)
					{
						this->AppendFils(new E_Scene_Encombrements_Encombrement_Proprietes(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
					{
						this->AppendFils(new E_Scene_Groupesurfaces_Groupe(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_GAMMEABSORPTION)
					{
						this->AppendFils(new E_GammeAbsorption(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_RENDU)
					{
						this->AppendFils(new E_Scene_Encombrements_Encombrement_Rendu(currentChild,this));
					}	
				}
				currentChild = currentChild->GetNext();
			}
		}
		if(this->GetElementByType(ELEMENT_TYPE_POSITION)==NULL) //maj version < 4/11/2008
		{
			this->AppendPropertyPosition("volpos",_("Intérieur du volume"),vec3(),true);
			wxLogWarning(_("Pour l'encombrement de scène nommé %s veuillez définir le point au centre de l'encombrement"),this->elementInfo.libelleElement);
		}
	}

	E_Scene_Encombrements_Encombrement_Model( Element* parent,wxString nom=wxString::Format(_("Encombrement %i"),ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement+1))
		:E_Drawable(parent,nom,Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_FITTING_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_FITTING_CLOSE);
		this->elementInfo.userDestroyable=true;
		this->AppendFils(new E_Scene_Encombrements_Encombrement_Proprietes(this));
		this->AppendFils(new E_Scene_Groupesurfaces_Groupe(this,"Surface",true));
		this->AppendFils(new E_GammeAbsorption(this));
		this->AppendFils(new E_Scene_Encombrements_Encombrement_Rendu(this));
		this->AppendPropertyPosition("volpos",_("Intérieur du volume"),vec3(),true);
		wxLogWarning(_("Pour l'encombrement de scène nommé %s veuillez définir le point au centre de l'encombrement"),this->elementInfo.libelleElement);
		_("Surface");
		InitEncombrementProp(); 
	}

	void DrawItem( vec4 unitizeValue )
	{
		if(this->GetElementByType(ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES)->GetBoolConfig("useforcalculation"))
		{
			Element* elRendu=this->GetElementByType(Element::ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_RENDU);
			if(elRendu!=NULL && elRendu->GetBoolConfig("showlabel"))
			{
				//On va dessiner le point au sein du volume
				vec3 position=coordsOperation::CommonCoordsToGlCoords(unitizeValue,this->GetPositionConfig("volpos"));
				vec3 couleurElement(125,125,0);
				labelInfo.clear();
				AddText(" "+this->elementInfo.libelleElement,position,couleurElement);
				this->DrawPoint( position,couleurElement,5);
			}
		}
	}
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		if(this->GetElementByType(ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES)->GetBoolConfig("useforcalculation"))
		{
			wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"encombrement");
			thisNode->AddProperty("id",Convertor::ToString(elementInfo.xmlIdElement));
			Element::SaveXMLCoreDoc(thisNode);
			return thisNode;
		}else{
			return NoeudParent;
		}	
	}

	void OnBeginLabelEdit(wxTreeEvent& treeEvent)
	{
		//On autorise l'edition en surchargeant l'événement
	}
	 
	void OnEndLabelEdit(wxTreeEvent& treeEvent)
	{
		if(treeEvent.GetLabel()!="")
		{
			this->elementInfo.libelleElement=treeEvent.GetLabel();
			this->Modified(this); //Indique le l'element a été modifié
		}
	}

	bool GetMaillageVolumeInfos(t_el_vol_infos& drawableElementInformations)
	{
		if(this->GetElementByType(ELEMENT_TYPE_SCENE_ENCOMBREMENTS_ENCOMBREMENT_PROPRIETES)->GetBoolConfig("useforcalculation"))
		{
			drawableElementInformations.dotInsideVol=this->GetPositionConfig("volpos");
			Element* grpFaceElement=this->GetElementByType(ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE);
			if(grpFaceElement)
			{
				E_Scene_Groupesurfaces_Groupe* groupeEl=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>(grpFaceElement);
				std::vector<t_faceIndex> grpFaces;
				groupeEl->GetFaces(grpFaces);
				if(grpFaces.size()>0)
				{
					drawableElementInformations.firstFace=grpFaces[0];
				}
				return true;
			}else{
				return false;
			}
		}else{
			return E_Drawable::GetMaillageVolumeInfos(drawableElementInformations);
		}
	}


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("encombrement"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};