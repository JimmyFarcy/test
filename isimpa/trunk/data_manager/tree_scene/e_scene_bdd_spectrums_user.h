#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/generic_element/e_gammefrequence_user.h"
/** \file e_scene_bdd_spectrums_user.h
   \brief Element représentant un dossier contenant un ou plusieurs spectres et/ou un ou plusieurs groupes de spectres
*/

/**
   \brief Element représentant un dossier contenant un ou plusieurs spectres et/ou un ou plusieurs groupes de spectres
*/
class E_Scene_Bdd_Spectrums_User: public Element
{
public:
	E_Scene_Bdd_Spectrums_User( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Utilisateur",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_USER,noeudCourant)
	{
		insertPasteMenu=true;
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_USER_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_USER_SPECTRUMS_CLOSE);
		_("Utilisateur");
		if(noeudCourant!=NULL)
		{
			wxXmlNode* currentChild;
			currentChild = noeudCourant->GetChildren();
			// On va créer les fils de notre noeudCourant
			InsertChildrens(currentChild);
		}
	}

	E_Scene_Bdd_Spectrums_User( Element* parent)
		:Element(parent,"Utilisateur",Element::ELEMENT_TYPE_SCENE_BDD_SPECTRUMS_USER)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_USER_SPECTRUMS_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_USER_SPECTRUMS_CLOSE);
		insertPasteMenu=true;
	}

	
	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_NEW_USERFREQ, _("Nouveau spectre"),"./Bitmaps/popup_new.png"));
		Element::OnRightClic(leMenu);
	}

	bool InsertChildrens(wxXmlNode* currentChild)
	{
		bool somethingAdded(false);
		wxString propValue;
		while(currentChild!=NULL)
		{
			if(currentChild->GetPropVal("eid",&propValue))
			{
				long typeEle;
				propValue.ToLong(&typeEle);
				if(typeEle==Element::ELEMENT_TYPE_GAMMEFREQ_USER || typeEle==Element::ELEMENT_TYPE_GAMMEFREQ_APP)
				{
					this->AppendFils(new E_GammeFrequence_User(currentChild,this));
					somethingAdded=true;
				}
			}
			currentChild = currentChild->GetNext();
		}
		return somethingAdded;
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
	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="")
	{
		
		if(etypefils==Element::ELEMENT_TYPE_GAMMEFREQ_USER)
			return this->AppendFils(new E_GammeFrequence_User(this));
		return Element::AppendFilsByType(etypefils,libelle);
	}
	
	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("userspectre"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}


};