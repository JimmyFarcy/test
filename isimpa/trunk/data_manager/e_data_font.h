﻿#include "first_header_include.hpp"

#include "data_manager/e_data.h"
#include "data_manager/customEditor/wxGridCellFontEditor.h"
#ifndef __ELEMENT_FONT__
#define __ELEMENT_FONT__

/** \file e_data_font.h
 * \brief Classe spécialisant E_Data afin de représenter la sélection d'une police de caractère
 */

/**
 *	\brief Classe spécialisant E_Data afin de représenter la sélection d'une police de caractère
 *	@see MainPropGrid
 */


class E_Data_Font: public E_Data
{
protected:
	wxFont valeurEl;
public:
	E_Data_Font( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data(parent,"Unnamedprop","",Element::ELEMENT_TYPE_FONT,noeudCourant)
	{

		//Creation de la couleur à partir du document XML
		wxString fontSerialisation;
		
		if(noeudCourant->GetPropVal("font",&fontSerialisation))
		{
			valeurEl.SetNativeFontInfo(fontSerialisation);
		}
	}
	/**
	 * @see Element::AppendPropertyColor()
	 * @param parent Element parent
	 * @param dataName Nom du champ ( non visible par l'utilisateur)
	 * @param dataLabel Libellé du champ
	 * @param defaultColor Valeur par défaut
	 */
	E_Data_Font( Element* parent, wxString dataName,wxString dataLabel, wxFont defaultFont)
		:E_Data(parent,dataName,dataLabel,Element::ELEMENT_TYPE_FONT)
	{
		valeurEl=defaultFont;
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		thisNode->DeleteProperty("font");
		thisNode->AddProperty("font",valeurEl.GetNativeFontInfoDesc());

		return thisNode;
	}

	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		E_Data::FillWxGrid(gridToFeed,col);
		int row=gridToFeed->GetNumberRows()-1;
		gridToFeed->SetCellEditor(row, col, new wxGridCellFontEditor());
		gridToFeed->SetCellFont(row,col,valeurEl);
		gridToFeed->SetCellValue(row,col,valeurEl.GetNativeFontInfoUserDesc());
	}

	/**
	 * Retourne la valeur RGB de l'élément sous forme d'un vecteur (0-255,0-255,0-255) 
	 * @return Valeur vec3 correspondant à la composante rouge vert bleu
	 */
	const wxFont& GetValue()
	{
		return valeurEl;
	}
	void SetValue(const wxFont&newVal)
	{
		if(valeurEl!=newVal)
		{
			valeurEl=newVal;
			this->Modified(this);
		}
	}

	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		int row=ev.GetRow();
		int col=ev.GetCol();
		SetValue(gridCtrl->GetCellFont(row,col));	
		gridCtrl->SetCellValue(row,col,valeurEl.GetNativeFontInfoUserDesc());	
	}

};

#endif