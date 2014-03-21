﻿#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_groupesurfaces_groupe.h"
#include <wx/log.h>
/** \file e_scene_groupesurfaces.h
   \brief Cet élément contient les groupes de surfaces de la scène
*/

/**
   \brief Cet élément contient les groupes de surfaces de la scène
*/
class E_Scene_Groupesurfaces: public Element
{
public:
	E_Scene_Groupesurfaces( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Surfaces",Element::ELEMENT_TYPE_SCENE_GROUPESURFACES,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACES_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACES_CLOSE);
		_("Surfaces");
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

					if(typeEle==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
					{
						this->AppendFils(new E_Scene_Groupesurfaces_Groupe(currentChild,this));
					}
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACES_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACES_CLOSE);
		return NoeudParent;
	}
	E_Scene_Groupesurfaces( Element* parent)
		:Element(parent,"Surfaces",Element::ELEMENT_TYPE_SCENE_GROUPESURFACES)
	{
	}

	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="")
	{
		if(etypefils==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
		{
			if(libelle=="")
				return this->AppendFils(new E_Scene_Groupesurfaces_Groupe(this));
			else
				return this->AppendFils(new E_Scene_Groupesurfaces_Groupe(this,libelle));
		}
		return Element::AppendFilsByType(etypefils,libelle);
	}
	/** On empeche la destruction du groupe si il y a une surface ou plus dans le groupe
	*/
	bool DeleteElementByTreeId(wxTreeItemId idElement)
	{
		Element* grFils=this->GetElementByTreeId(idElement);
		if(grFils)
		{
			if(grFils->GetElementInfos().typeElement==ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
			{
				E_Scene_Groupesurfaces_Groupe* eGroupe=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>(grFils);
				if(!eGroupe->IsEmpty())
				{
					wxLogInfo(_("Un groupe peut être détruit seulement s'il est vide !"));
					return true;
				}
			}
		}
		return Element::DeleteElementByTreeId(idElement);
	}
	/*
	 * Cette surcharge supprime tout les groupes qui on recu l'ordre de supprimer leurs faces.

	void DeleteAllElementByTypeR(ELEMENT_TYPE typeElementToDelete)
	{
		Element::DeleteAllElementByTypeR(typeElementToDelete);
		if(typeElementToDelete==ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE_VERTEX)
			Element::DeleteAllElementByTypeR(ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE);
	}
	*/
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("sgroupes"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
	/**
	 * Parcourt cet élément et les éléments fils à la recherche de la face
	 * @param[in] face numéro de face
	 * @param[in] group numéro de groupe ( Indice du groupe du modèle 3D pas l'élément de groupe )
	 * @return Indice de l'élément face ou groupe correspondant aux paramètres
	 * @see E_Scene_Groupesurfaces_Groupe::GetIdElementByFaceAndGroup()
	 */
	wxTreeItemId GetIdElementByFaceAndGroup(long face,long group)
	{
		wxTreeItemId emptyId;
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			if((*itfils)->GetElementInfos().typeElement==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
			{
				E_Scene_Groupesurfaces_Groupe* groupe=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>((*itfils));
				if(groupe)
				{
					wxTreeItemId idFace=groupe->GetIdElementByFaceAndGroup(face,group);
					if(idFace.IsOk())
						return idFace;
				}
			}
		}
		return emptyId;
	}

	/**
	 * Parcourt cet élément et les éléments fils et supprime les groupes vides
	 */
	void ClearEmptyGroup()
	{
		std::list<wxTreeItemId> itemToDelete;
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			if((*itfils)->GetElementInfos().typeElement==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
			{
				E_Scene_Groupesurfaces_Groupe* groupe=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>((*itfils));
				if(groupe)
				{
					if(groupe->IsEmpty())
					{
						itemToDelete.push_back(groupe->GetElementInfos().idElement);
					}
				}
			}
		}
		for(std::list<wxTreeItemId>::iterator ititem=itemToDelete.begin();ititem!=itemToDelete.end();ititem++)
			this->DeleteElementByTreeId(*ititem);
	}
	/**
	 * Cette méthode permet de générer un tableau correspondant à l'association matériau-faces du projet
	 * @param[out] matFacesAssociations Tableau[group][face]=idMaterial
	 **/
	void GetMaterialsLink( std::vector<std::vector<ApplicationConfiguration::t_PropFace> > &matFacesAssociations)
	{
		//Pour chaque groupe de faces
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			E_Scene_Groupesurfaces_Groupe* groupe=dynamic_cast<E_Scene_Groupesurfaces_Groupe*>((*itfils));
			if(groupe)
			{
				groupe->GetMaterialsLink(matFacesAssociations);
			}
		}
	}

	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_SURFACE_GROUP, _("Ajouter un groupe"),"./Bitmaps/popup_new.png"));
		Element::OnRightClic(leMenu);
	}
};
