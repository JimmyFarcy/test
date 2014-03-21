#include "first_header_include.hpp"

#include "data_manager/tree_scene/e_scene_bdd_materiaux_user_materiau.h"
#include "data_manager/tree_scene/e_scene_bdd_materiaux_user_group.h"
/** \file e_scene_bdd_materiaux_user.h
   \brief Element représentant un dossier contenant un ou plusieurs matériau et/ou un ou plusieurs groupes de matériaux
*/

/**
   \brief Element représentant un dossier contenant un ou plusieurs matériau et/ou un ou plusieurs groupes de matériaux
*/
class E_Scene_Bdd_Materiaux_User: public Element
{
public:
	E_Scene_Bdd_Materiaux_User( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Utilisateur",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_USER_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_USER_MATERIALS_CLOSE);
		insertPasteMenu=true;
		_("Utilisateur");
		if(noeudCourant!=NULL)
		{
			// On va créer les fils de notre noeudCourant
			InsertChildrens(noeudCourant->GetChildren());
		}
	}
	E_Scene_Bdd_Materiaux_User( Element* parent)
		:Element(parent,"Utilisateur",Element::ELEMENT_TYPE_SCENE_BDD_MATERIAUX_USER)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_USER_MATERIALS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_USER_MATERIALS_CLOSE);

	}

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
	void OnPaste(wxXmlNode* nodeElement)
	{
		E_Scene_Bdd_Materiaux_User_Group::SetUniqueMaterialsId(nodeElement);
		E_Scene_Bdd_Materiaux_User_Group::SetCopyMaterialsName(nodeElement);
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
	/**
	 * Méthode permettant d'ajouter un groupe de matériau dans ce dossier
	 * @param[in] nom Libelle du groupe
	 * @return Pointeur vers le nouvel élément créé
	 * @see ProjectManager::OnMenuNewMatGroup()
	 */
	
	E_Scene_Bdd_Materiaux_User_Group* AppendUserGroup(wxString nom="")
	{
		E_Scene_Bdd_Materiaux_User_Group* nouvFils=new E_Scene_Bdd_Materiaux_User_Group(this,nom);
		this->AppendFils(nouvFils);
		return nouvFils;
	}

	
	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_USERMAT, _("Nouveau matériau"),"./Bitmaps/popup_new.png"));
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_MATERIAL_GROUP, _("Créer groupe"),"./Bitmaps/popup_new.png"));
		leMenu->AppendSeparator();		
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_IMPORT_MATERIAL, _("Importer depuis un fichier")));
		Element::OnRightClic(leMenu);
	}
	/**
	 * Méthode permettant d'ajouter un matériau dans ce dossier
	 * @return Pointeur vers le nouvel élément créé
	 * @see ProjectManager::OnMenuNewUserMat()
	 */
	
	E_Scene_Bdd_Materiaux_User_Materiau* AppendUserMateriau()
	{
		E_Scene_Bdd_Materiaux_User_Materiau* nouvFils=new E_Scene_Bdd_Materiaux_User_Materiau(this);
		this->AppendFils(nouvFils);
		return nouvFils;
	}
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("usermaterial"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};