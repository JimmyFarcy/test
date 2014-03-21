﻿#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "e_scene_recepteurss_recepteur.h"
#include "e_scene_recepteurss_recepteurcoupe.h"

/** \file e_scene_recepteurss.h
   \brief Element dossier contenant la liste des récepteurs surfaciques de la scène.
*/

/**
   \brief Element dossier contenant la liste des récepteurs surfaciques de la scène.
*/

class E_Scene_Recepteurss: public Element
{
public:
	E_Scene_Recepteurss( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Récepteurs surfaciques",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS,noeudCourant)
	{
		insertPasteMenu=true;
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACE_RECEIVERS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACE_RECEIVERS_CLOSE);
		_("Récepteurs surfaciques");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR)
						this->AppendFils(new E_Scene_Recepteurss_Recepteur(currentChild,this));
					else if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE)
						this->AppendFils(new E_Scene_Recepteurss_RecepteurCoupe(currentChild,this));
				}
				currentChild = currentChild->GetNext();
			}
		}
	}
	E_Scene_Recepteurss( Element* parent)
		:Element(parent,"Récepteurs surfaciques",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS)
	{
		insertPasteMenu=true;
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACE_RECEIVERS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACE_RECEIVERS_CLOSE);

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
				
				if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR)
				{
					this->AppendFils(new E_Scene_Recepteurss_Recepteur(currentChild,this));
					somethingAdded=true;
				}else if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE){
					this->AppendFils(new E_Scene_Recepteurss_RecepteurCoupe(currentChild,this));
					somethingAdded=true;
				}
			}
			currentChild = currentChild->GetNext();
		}
		return somethingAdded;
	}
	
	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="")
	{
		if(etypefils==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR)
		{
			if(libelle=="")
				return this->AppendFils(new E_Scene_Recepteurss_Recepteur(this));
			else
				return this->AppendFils(new E_Scene_Recepteurss_Recepteur(this,libelle));
		}else if(etypefils==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEURCOUPE)
		{
			if(libelle=="")
				return this->AppendFils(new E_Scene_Recepteurss_RecepteurCoupe(this));
			else
				return this->AppendFils(new E_Scene_Recepteurss_RecepteurCoupe(this,libelle));
		}
		return NULL;
	}


	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"recepteurss");
		Element::SaveXMLCoreDoc(thisNode);
		return thisNode;
	}

	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_RECEPTEUR_S, _("Nouveau récepteur surfacique de scène"),"./Bitmaps/popup_new.png"));
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_RECEPTEUR_S_COUPE, _("Nouveau récepteur surfacique en coupe"),"./Bitmaps/popup_new.png"));
		Element::OnRightClic(leMenu);
	}
	void OnPaste(wxXmlNode* nodeElement)
	{
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
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("recepteurss"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};