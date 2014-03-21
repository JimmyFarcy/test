#include "first_header_include.hpp"

#include "data_manager/e_data.h"
#ifndef __ELEMENT_COLOR__
#define __ELEMENT_COLOR__
#include "data_manager/customEditor/wxGridCellColorEditor.h"

/** \file e_data_color.h
   \brief Classe spécialisant E_Data afin de représenter une valeur de couleur
*/

/**
	\brief Classe spécialisant E_Data afin de représenter une valeur de couleur
	@see MainPropGrid
*/


class E_Data_Color: public E_Data
{
protected:
	wxColour valeurEl;
public:
	E_Data_Color( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data(parent,"Unnamedprop","",Element::ELEMENT_TYPE_COLOR,noeudCourant)
	{

		//Creation de la couleur à partir du document XML
		wxString propRed;
		wxString propGreen;
		wxString propBlue;

		
		if(noeudCourant->GetPropVal("r",&propRed) && noeudCourant->GetPropVal("g",&propGreen)
			&& noeudCourant->GetPropVal("b",&propBlue))
		{
			long rVal;
			long gVal;
			long bVal;
			propRed.ToLong(&rVal);
			propGreen.ToLong(&gVal);
			propBlue.ToLong(&bVal);
			wxColour nvCouleur( rVal,gVal,bVal);
			valeurEl=nvCouleur;
		}
	}
	/**
	 * @see Element::AppendPropertyColor()
	 * @param parent Element parent
	 * @param dataName Nom du champ ( non visible par l'utilisateur)
	 * @param dataLabel Libellé du champ
	 * @param defaultColor Valeur par défaut
	 */
	E_Data_Color( Element* parent, wxString dataName,wxString dataLabel, wxColor defaultColor)
		:E_Data(parent,dataName,dataLabel,Element::ELEMENT_TYPE_COLOR)
	{
		valeurEl=defaultColor;
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		wxString compR;
		wxString compG;
		wxString compB;
		compR<<((int)valeurEl.Red());
		compG<<((int)valeurEl.Green());
		compB<<((int)valeurEl.Blue());
		thisNode->DeleteProperty("r");
		thisNode->AddProperty("r",compR);
		thisNode->DeleteProperty("g");
		thisNode->AddProperty("g",compG);
		thisNode->DeleteProperty("b");
		thisNode->AddProperty("b",compB);

		return thisNode;
	}

	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		E_Data::FillWxGrid(gridToFeed,col);
		int row=gridToFeed->GetNumberRows()-1;
		gridToFeed->SetCellEditor(row, col, new wxGridCellColorEditor());
		gridToFeed->SetCellBackgroundColour(row,col,valeurEl);
	}

	/**
	 * Retourne la valeur RGB de l'élément sous forme d'un vecteur (0-255,0-255,0-255) 
	 * @return Valeur vec3 correspondant à la composante rouge vert bleu
	 */
	vec3 GetValue()
	{
		return vec3(valeurEl.Red(),valeurEl.Green(),valeurEl.Blue());
	}
	void SetValue(const wxColor& newColor)
	{
		if(newColor!=valeurEl)
		{
			valeurEl=newColor;
			Modified(this);
		}
	}
	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		int row=ev.GetRow();
		int col=ev.GetCol();
		SetValue(gridCtrl->GetCellBackgroundColour(row,col));
	}

};

#endif