#include "first_header_include.hpp"

#include "e_materiau.h"

#ifndef __SPEC__USERMAT__
#define __SPEC__USERMAT__


/** \file e_materiau_user.h
   \brief Spécialisation de E_Materiau

   Ce spectre peut être modifié par l'utilisateur
*/

/**
   \brief Spécialisation de E_Materiau

	Ce spectre peut être modifié par l'utilisateur
	@see E_Scene_Bdd_Materiaux_User_Materiau
*/

class E_Materiau_User: public E_Materiau
{
public:
	E_Materiau_User( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Materiau(parent,"",Element::ELEMENT_TYPE_MATERIAU_USER,noeudCourant)
	{
	}

	E_Materiau_User( Element* parent)
		:E_Materiau(parent,"",Element::ELEMENT_TYPE_MATERIAU_USER)
	{
		//Ajoute l l'etat d'accès des champs
		InitProperties();
	}
	virtual wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Materiau::SaveXMLDoc(NoeudParent);
		thisNode->SetName("materiau"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};

#endif