#include "first_header_include.hpp"

#include "e_gammefrequence.h"

/** \file e_gammefrequence_app.h
   \brief Classe spécialisant e_gammefrequence

    Represente un type de source provenant de la base de données de l'application
*/

/**
   \brief Classe spécialisant e_gammefrequence

    Represente un type de source provenant de la base de données de l'application
*/

class E_GammeFrequence_App: public E_GammeFrequence
{
public:
	E_GammeFrequence_App( wxXmlNode* noeudCourant ,  Element* parent)
		:E_GammeFrequence(parent,"Spectre application",Element::ELEMENT_TYPE_GAMMEFREQ_APP,noeudCourant)
	{
		_("Spectre application");
	}
	

	void InitProp()
	{
		
		ignoreNextUpdate=true;
		this->SetReadOnlyAllConfig(true,-1);
		ignoreNextUpdate=false;
		
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		if(!this->ExportMode)
			return NoeudParent;
		else
			return E_GammeFrequence::SaveXMLDoc(NoeudParent);
	}
};