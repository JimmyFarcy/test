#include "first_header_include.hpp"

#include "data_manager/tree_core/e_core_core.h"

#ifndef __E_CORE_TLM__
#define __E_CORE_TLM__

/*! \file e_core_tlmcore.h
    \brief Element correspondant au moteur de calcul "TLM"
*/


/**
    \brief Element correspondant au moteur de calcul "TLM"
*/
class E_Core_Tlm: public E_Core_Core
{
public:

	E_Core_Tlm( Element* parent, wxXmlNode* noeudCourant)
		:E_Core_Core(parent,"TLM",ELEMENT_TYPE_CORE_TC,noeudCourant)
	{
		_("TLM");
	}

	E_Core_Tlm( Element* parent)
		:E_Core_Core(parent,"TLM",ELEMENT_TYPE_CORE_TC)
	{
		
		this->AppendFilsByType(ELEMENT_TYPE_CORE_CORE_CONFMAILLAGE);
		Element* newElement=new E_Core_Core_Bfreqselection(this);
		this->AppendFils(newElement)->Hide();


		
		
		this->AppendPropertyText("modelName","","mesh.cbin",true,true)->Hide();
		this->AppendPropertyText("exeName","","TLM.exe")->Hide();
		this->AppendPropertyText("corePath","","tlm\\")->Hide();
		this->AppendPropertyText("tetrameshFileName","","tetramesh.mbin",true,true)->Hide();
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Core_Core::SaveXMLDoc(NoeudParent);
		thisNode->SetName("tlm");
		return thisNode;
	}
};

#endif