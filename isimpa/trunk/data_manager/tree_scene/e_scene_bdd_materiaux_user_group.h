#include "first_header_include.hpp"

#include "data_manager/tree_scene/e_scene_bdd_materiaux_user_materiau.h"

/** \file e_scene_bdd_materiaux_user_group.h
   \brief Element représentant un dossier de matériaux, ce dossier peut contenir un dossier de meme type ou un matériau
*/

/**
   \brief Element représentant un dossier de matériaux, ce dossier peut contenir un dossier de meme type ou un matériau
*/
class E_Scene_Bdd_Materiaux_User_Group: public Element
{

private:

	bool InsertChildrens( wxXmlNode* currentChild )
	{
		bool somethingAdded=false;

		// On va créer les fils de notre noeudCourant
		wxString propValue;
		while(currentChild!=NULL)
		{
			if(currentChild->GetPropVal("eid",&propValue))
			{
				long typeEle;
				propValue.ToLong(&typeEle);
				if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_MATERIAU || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_MATERIAU)
				{
					this->AppendFils(new E_Scene_Bdd_Materiaux_User_Materiau(currentChild,this));
					somethingAdded=true;
				}
				if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_GROUP || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP)
				{
					this->AppendFils(new E_Scene_Bdd_Materiaux_User_Group(currentChild,this));
					somethingAdded=true;
				}
			}
			currentChild = currentChild->GetNext();
		}
		return somethingAdded;
	}
public:
	static void SetUniqueMaterialsId( wxXmlNode* nodeElement )
	{
		if(nodeElement!=NULL)
		{
			nodeElement->DeleteProperty("idmateriau");
			wxXmlNode* childElement=nodeElement->GetChildren();
			while(childElement!=NULL)
			{
				SetUniqueMaterialsId(childElement);
				childElement=childElement->GetNext();
			}
		}
	}
	static void SetCopyMaterialsName( wxXmlNode* nodeElement )
	{
		if(nodeElement!=NULL)
		{
			wxString propValue;
			if(nodeElement->GetPropVal("eid",&propValue))
			{
				long typeEle;
				propValue.ToLong(&typeEle);
				if(typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_GROUP || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_APP_MATERIAU || typeEle==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_MATERIAU)
				{
					/*
					if(nodeElement->GetPropVal("name",&propValue))
					{
						nodeElement->DeleteProperty("name");
						nodeElement->AddProperty("name",wxString::Format(_("Copie de %s"),propValue));
					}
					*/
					nodeElement->DeleteProperty("idmateriau");
				}
			}
			wxXmlNode* childElement=nodeElement->GetChildren();
			while(childElement!=NULL)
			{
				SetCopyMaterialsName(childElement);
				childElement=childElement->GetNext();
			}
		}
	}
	E_Scene_Bdd_Materiaux_User_Group( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Groupe",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_MATERIAL_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_MATERIAL_CLOSE);
		this->elementInfo.userDestroyable=true;
		insertPasteMenu=true;
		_("Groupe");
		if(noeudCourant!=NULL)
		{
			wxXmlNode* currentChild;
			InsertChildrens(noeudCourant->GetChildren());

		}
	}


	E_Scene_Bdd_Materiaux_User_Group( Element* parent,wxString nom="Groupe")
		:Element(parent,nom,Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_USER_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_USER_MATERIALS_CLOSE);
		this->elementInfo.userDestroyable=true;
		insertPasteMenu=true;
		this->Modified(this);
	}


	void OnPaste(wxXmlNode* nodeElement)
	{
		SetUniqueMaterialsId(nodeElement);
		SetCopyMaterialsName(nodeElement);
		//On ajoute les éléments compatibles
		wxXmlNode* firstChild=nodeElement->GetChildren();
		if(!InsertChildrens(firstChild))
		{
			Element::OnPaste(nodeElement);
		}
		else
		{
			Element::FillWxTree(); //ajout dans l'arbre des données
			//Indique la modification de cette branche
			this->ForceBottomModified();
			this->Modified(this);
		}

	}
	void OnEndLabelEdit(wxTreeEvent& treeEvent)
	{
		if(treeEvent.GetLabel()!="")
		{
			this->elementInfo.libelleElement=treeEvent.GetLabel();
			this->Modified(this); //Indique le l'element a été modifié
		}
	}
	void OnBeginLabelEdit(wxTreeEvent& treeEvent)
	{
		//On autorise l'edition en surchargeant l'événement
	}
	 
	/**
	 * Méthode permettant d'ajouter un matériau dans ce dossier
	 * @param[in] name Libelle du matériau
	 * @return Pointeur vers le nouvel élément créé
	 * @see ProjectManager::OnMenuNewUserMat()
	 */
	E_Scene_Bdd_Materiaux_User_Materiau* AppendUserMateriau(wxString name="")
	{
		E_Scene_Bdd_Materiaux_User_Materiau* nouvFils=new E_Scene_Bdd_Materiaux_User_Materiau(this,name);
		this->AppendFils(nouvFils);
		return nouvFils;
	}
	/**
	 * Méthode permettant d'ajouter un groupe de matériau dans ce dossier
	 * @param[in] name Libelle du groupe
	 * @return Pointeur vers le nouvel élément créé
	 * @see ProjectManager::OnMenuNewMatGroup()
	 */
	
	E_Scene_Bdd_Materiaux_User_Group* AppendUserGroup(wxString name="")
	{
		E_Scene_Bdd_Materiaux_User_Group* nouvFils=new E_Scene_Bdd_Materiaux_User_Group(this,name);
		this->AppendFils(nouvFils);
		return nouvFils;
	}
	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_USERMAT, _("Nouveau matériau"),"./Bitmaps/popup_new.png"));
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_MATERIAL_GROUP, _("Créer groupe"),"./Bitmaps/popup_new.png"));
		Element::OnRightClic(leMenu);
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("groupmat"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
	
	void BeginDrag(wxTreeEvent& treeEvent,wxTreeCtrl* tree)
	{
		treeEvent.Allow();
	}

	void EndDrag(wxTreeEvent& treeEvent,wxTreeCtrl* tree,std::vector<Element*> dragLst)
	{
		for(int i=0;i<dragLst.size();i++)
		{
			Element::t_elementInfo infosDragEl=dragLst[i]->GetElementInfos();
			if(infosDragEl.typeElement==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_GROUP && infosDragEl.idElement!=this->elementInfo.idElement)
			{
				dragLst[i]->Reparent(this);				
			}else if(infosDragEl.typeElement==Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER_MATERIAU && infosDragEl.idParent!=this->elementInfo.idElement)
			{
				dragLst[i]->Reparent(this);
			}
		}
	}

};