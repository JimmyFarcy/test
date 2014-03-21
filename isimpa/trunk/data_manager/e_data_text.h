#include "first_header_include.hpp"

#include "data_manager/e_data.h"

#ifndef __ELEMENT_TEXT__
#define __ELEMENT_TEXT__

/** \file e_data_text.h
   \brief Classe spécialisant E_Data afin de représenter un champ texte
*/

/**
	\brief Classe spécialisant E_Data afin de représenter un champ texte
*/
class E_Data_Text: public E_Data
{
private:
	wxString textElement;
public:
	E_Data_Text( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data(parent,"Unnamedprop","",Element::ELEMENT_TYPE_TEXT,noeudCourant)
	{
		wxString propVal;
		//Affecte la couleur de l'element
		if(noeudCourant->GetPropVal("textValue",&propVal))
			textElement=propVal;
		if(noeudCourant->GetPropVal("readonly",&propVal))
			readOnly=true;
	}

	/**
	 *	@param parent Element parent
	 *	@param[in] dataName Nom du champ ( non visible par l'utilisateur)
	 *	@param[in] dataLabel Libellé de la ligne
	 *	@param[in] defaultDataValue Type de ligne ( par défaut ligne standard )
	 *	@param[in] _readOnly Champ en lecture seule
	 *  @see Element::AppendPropertyText()
	 */
	E_Data_Text( Element* parent, wxString dataName,wxString dataLabel, wxString defaultDataValue="",bool _readOnly=false)
		:E_Data(parent,dataName,dataLabel,Element::ELEMENT_TYPE_TEXT)
	{
		textElement=defaultDataValue;
		readOnly=_readOnly;
	}
	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		int row=gridToFeed->GetNumberRows()-1;
		E_Data::FillWxGrid(gridToFeed,col);
		gridToFeed->SetCellValue(row,col,textElement);
	}
	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		if(!readOnly)
		{
			textElement=gridCtrl->GetCellValue(ev.GetRow(),ev.GetCol());
			this->Modified(this);
		}
	}


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		thisNode->DeleteProperty("textValue");
		thisNode->AddProperty("textValue",textElement);
		return thisNode;
	}
	/**
	 * Affecte une nouvelle valeur
	 * @param[in] newValue Nouvelle valeur à inserer
	 * @see Element::UpdateStringConfig()
	 */
	void SetValue(wxString newValue)
	{
		if(newValue!=this->textElement)
		{
			this->textElement=newValue;
			this->Modified(this);
		}
	}
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		if(exportToCore)
		{
			NoeudParent->DeleteProperty(this->elementInfo.libelleElement);
			NoeudParent->AddProperty(this->elementInfo.libelleElement,textElement);
		}
		return NoeudParent;
	}
	/**
	 * Obtenir la valeur de l'élément
	 * @return Valeur du champ
	 * @see Element::GetStringConfig()
	 */
	wxString GetValue()
	{
		return this->textElement;
	}
private:
};

#endif