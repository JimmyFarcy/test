#include "first_header_include.hpp"

#include "data_manager/tree_core/e_core_core.h"

#ifndef __E_CORE_TC__
#define __E_CORE_TC__

/*! \file e_core_tccore.h
    \brief Element correspondant au moteur de calcul "Théorie classique"
*/


/**
    \brief Element correspondant au moteur de calcul "Théorie classique"
*/
class E_Core_Tc: public E_Core_Core
{
private:
	void InitExportRs(Element* confCore)
	{
		confCore->AppendPropertyBool("output_recs_byfreq","Export des récepteurs de surface par bande de fréquence",true,true);
		_("Export des récepteurs de surface par bande de fréquence");
	}
public:

	void AddConfTc()
	{
		E_Core_Core_Configuration* confCore=new E_Core_Core_Configuration(this);
		this->AppendFils(confCore);
		confCore->AppendPropertyBool("abs_atmo_calc","Calcul Absorption atmosphérique",true,true);
		InitExportRs(confCore);
	}
	E_Core_Tc( Element* parent, wxXmlNode* noeudCourant)
		:E_Core_Core(parent,"Théorie Classique (TC)",ELEMENT_TYPE_CORE_TC,noeudCourant)
	{

		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_STANDARTCORE_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_STANDARTCORE_CLOSE);
		_("Théorie Classique (TC)");
		Element* coreConf=this->GetElementByType(Element::ELEMENT_TYPE_CORE_CORE_CONFIG);
		if(!coreConf) //Maj version < 05/11/2008
		{
			AddConfTc();
		}else{
			InitExportRs(coreConf);
		}
	}

	E_Core_Tc( Element* parent)
		:E_Core_Core(parent,"Théorie classique",ELEMENT_TYPE_CORE_TC)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_STANDARTCORE_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_STANDARTCORE_CLOSE);

		this->AppendFilsByType(ELEMENT_TYPE_CORE_CORE_CONFMAILLAGE);
		AddConfTc();
		Element* newElement=new E_Core_Core_Bfreqselection(this);
		this->AppendFils(newElement)->Hide();
		this->AppendPropertyText("direct_recepteurSOutputName","",wxString("folder_ChampDirect")+wxFileName::GetPathSeparator(),true,true)->Hide();
		this->AppendPropertyText("sabine_recepteurSOutputName","",wxString("folder_Sabine")+wxFileName::GetPathSeparator(),true,true)->Hide();
		this->AppendPropertyText("eyring_recepteurSOutputName","",wxString("folder_Eyring")+wxFileName::GetPathSeparator(),true,true)->Hide();
		_("folder_ChampDirect");
		_("folder_Sabine");
		_("folder_Eyring");
		_("main_calculation");



		this->AppendPropertyText("modelName","","mesh.cbin",true,true)->Hide();
		this->AppendPropertyText("exeName","","TheorieClassique.exe")->Hide();
		this->AppendPropertyText("corePath","",wxString("theorie_classique")+wxFileName::GetPathSeparator())->Hide();
		this->AppendPropertyText("tetrameshFileName","","tetramesh.mbin",true,true)->Hide();
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Core_Core::SaveXMLDoc(NoeudParent);
		thisNode->SetName("tc");
		return thisNode;
	}
};

#endif
