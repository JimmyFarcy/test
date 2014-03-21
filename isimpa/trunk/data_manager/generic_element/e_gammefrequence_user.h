#include "first_header_include.hpp"

#include "e_gammefrequence.h"


/** \file e_gammefrequence_user.h
   \brief Classe spécialisant e_gammefrequence

    Représente le spectre personalisé utilisateur (modifiable)
*/

/**
   \brief Classe spécialisant e_gammefrequence 

    Représente le spectre personalisé utilisateur (modifiable)
*/

class E_GammeFrequence_User  : public E_GammeFrequence
{
public:
	E_GammeFrequence_User( wxXmlNode* noeudCourant ,  Element* parent)
		:E_GammeFrequence(parent,"Spectre utilisateur",Element::ELEMENT_TYPE_GAMMEFREQ_USER,noeudCourant)
	{
		
		this->elementInfo.userDestroyable=true;
		_("Spectre utilisateur");
	}

	E_GammeFrequence_User( Element* parent)
		:E_GammeFrequence(parent,"Spectre utilisateur",Element::ELEMENT_TYPE_GAMMEFREQ_USER)
	{
		this->elementInfo.userDestroyable=true;
		InitProperties();
	}



	void InitProp()
	{
		ignoreNextUpdate=true;
		this->SetReadOnlyAllConfig(false,-1);
		ignoreNextUpdate=false;
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
	virtual wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_GammeFrequence::SaveXMLDoc(NoeudParent);
		thisNode->SetName("frequences"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};