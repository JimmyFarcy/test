#include "first_header_include.hpp"

#include "data_manager/e_data_row.h"
#include "manager/stringTools.h"
#include "data_manager/appconfig.h" //pour les valeurs de pondération

#ifndef __ELEMENT_ROW_FREQ__
#define __ELEMENT_ROW_FREQ__

#define PRECISION_DB 2
/** \file e_data_row_bandefreq.h
   \brief Classe spécialisant E_Data_Row afin de faire le lien entre dB et dbA en fonction de la pondération
*/

/**
	\brief Classe spécialisant E_Data_Row afin de faire le lien entre dB et dbA en fonction de la pondération

	Il compose l'element e_gamme_frequence.
	@see E_GammeFrequence
	@see MainPropGrid
*/
class E_Data_Row_BandeFreq: public E_Data_Row
{
protected:
	bool ignoreNextUpdate;
public:
	E_Data_Row_BandeFreq( wxXmlNode* noeudCourant ,  Element* parent,Element::ELEMENT_TYPE etype=ELEMENT_TYPE_ROW_BFREQ)
		:ignoreNextUpdate(true),
		E_Data_Row( noeudCourant ,  parent,etype)
	{
		//Maj depuis version 1.1.5 et inférieur
		if(etype==ELEMENT_TYPE_ROW_BFREQ && this->IsPropertyExist("att"))
		{
			SetPonderationState(false);
			this->DeleteElementByXmlId(this->GetElementByLibelle("att")->GetXmlId(),true);
			this->DeleteElementByXmlId(this->GetElementByLibelle("lw")->GetXmlId(),true);
			SetPonderationState(true);
		}
		ignoreNextUpdate=false;
	}

	
	/**
	 *	@param parent Element parent
	 *	@param[in] dataName Nom du champ ( non visible par l'utilisateur)
	 *	@param[in] dataLabel Libellé de la ligne
	 *	@param[in] _ponderation Valeur de la pondération entre dB et dB(A)
	 *  @see E_GammeFrequence
	 */
	E_Data_Row_BandeFreq( Element* parent, const wxString& dataName,const wxString& dataLabel,Element::ELEMENT_TYPE etype=ELEMENT_TYPE_ROW_BFREQ)
		:E_Data_Row( parent, dataName, dataLabel,etype)
	{
		SetPonderationState(false);
		AppendPropertyDecimal("db","dB",0,false,PRECISION_DB,false,false,0,0,true);
		AppendPropertyDecimal("dba","dB(A)",0,false,PRECISION_DB);
		SetPonderationState(true);
		_("dB");
		_("dB(A)");
	}

	/*
	 * Cette méthode permet de bloquer/activer la ponderation dB->dB(A) et inverse
	 * @param doPonderation Vrai si la ponderation sera effectué lors de la mise à jour d'un des champs
	 */
	virtual void SetPonderationState( bool doPonderation )
	{
		if(doPonderation)
		{
			PonderationFromDb();
		}
		ignoreNextUpdate=!doPonderation;
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* NoeudCourant=new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"bfreq");
		NoeudCourant->AddProperty("freq",this->elementInfo.libelleElement);
		return Element::SaveXMLCoreDoc(NoeudCourant);
	}
protected:
	virtual void Modified(Element* eModif)
	{
		const t_elementInfo& filsInfo=eModif->GetElementInfos();
		if(!ignoreNextUpdate)
		{
			if(filsInfo.libelleElement=="db")
			{
				ignoreNextUpdate=true;
				PonderationFromDb();
			}else if(filsInfo.libelleElement=="dba"){
				ignoreNextUpdate=true;
				PonderationFromDbA();
			}
			E_Data_Row::Modified(eModif);
			ignoreNextUpdate=false;
		}	
	}
	
	void PonderationFromDb()
	{
		this->UpdateDecimalConfig("dba",this->GetDecimalConfig("db")+ApplicationConfiguration::GetPonderationVal(this->elementInfo.libelleElement));
	}

	void PonderationFromDbA()
	{
		this->UpdateDecimalConfig("db",this->GetDecimalConfig("dba")-ApplicationConfiguration::GetPonderationVal(this->elementInfo.libelleElement)); //todo ponderation
	}
};

#endif