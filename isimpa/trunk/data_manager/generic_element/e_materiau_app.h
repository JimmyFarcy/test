#include "first_header_include.hpp"

#include "e_gammefrequence.h"


#ifndef __SPEC__APPMAT__
#define __SPEC__APPMAT__


/** \file e_materiau_app.h
   \brief Spécialisation de E_Materiau

   Ce spectre ne peut pas être modifié par l'utilisateur
*/

/**
   \brief Spécialisation de E_Materiau

   Ce spectre ne peut pas être modifié par l'utilisateur
	@see E_Scene_Bdd_Materiaux_App_Materiau
*/
class E_Materiau_App: public E_Materiau
{
public:
	E_Materiau_App( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Materiau(parent,"Matériau application",Element::ELEMENT_TYPE_MATERIAU_APP,noeudCourant)
	{
		_("Matériau application");
		const std::vector<ApplicationConfiguration::t_freq> tabfreq=ApplicationConfiguration::GetAllFrequencies();
		//Les champs de saisies sont en lectures seules pour les matériaux d'application
		for(int i=0;i<tabfreq.size();i++)
		{
			this->SetReadOnlyConfig(wxString::Format("%i",tabfreq[i]),true,-1); //-1 toute la ligne
		}
	}
	virtual wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Materiau::SaveXMLDoc(NoeudParent);
		thisNode->SetName("materiau"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};

#endif