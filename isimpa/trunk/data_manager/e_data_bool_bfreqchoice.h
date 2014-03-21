#include "first_header_include.hpp"

#include "data_manager/e_data_bool.h"

#ifndef __ELEMENT_BOOLEAN__BFREQ__
#define __ELEMENT_BOOLEAN__BFREQ__
/** \file e_data_bool_bfreqchoice.h
   \brief Classe spécialisant E_Data_Bool afin de représenter une valeur booléene de choix de bande de fréquence
*/

/**
   \brief Classe spécialisant E_Data_Bool afin de représenter une valeur booléene de choix de bande de fréquence
	@see MainPropGrid
*/
class E_Data_Bool_Bfreq: public E_Data_Bool
{
public:
	E_Data_Bool_Bfreq( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data_Bool( noeudCourant ,  parent,ELEMENT_TYPE_BOOL_BFREQ)
	{
	}

	E_Data_Bool_Bfreq( Element* parent, wxString dataName,wxString dataLabel, bool defaultDataValue)
		:E_Data_Bool( parent, dataName,dataLabel,defaultDataValue,ELEMENT_TYPE_BOOL_BFREQ)
	{
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* NoeudCourant=new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"bfreq");
		NoeudCourant->AddProperty("freq",this->elementInfo.libelleElement);
		
		if(elementValue)
			NoeudCourant->AddProperty("docalc","1");
		else
			NoeudCourant->AddProperty("docalc","0");

		return NoeudParent;
	}

};

#endif