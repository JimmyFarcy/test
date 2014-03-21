#include "first_header_include.hpp"

#include "data_manager/e_data.h"

#ifndef __ELEMENT_BOOLEAN__
#define __ELEMENT_BOOLEAN__
/** \file e_data_bool.h
   \brief Classe spécialisant E_Data afin de représenter une valeur booléene
*/

/**
	\brief Classe spécialisant E_Data afin de représenter une valeur booléene
	@see MainPropGrid
*/
class E_Data_Bool: public E_Data
{
protected:
	bool elementValue;
	wxMenuItem* linkedMenuEl;	/**< Element de menu lié à cette valeur */  
public:
	E_Data_Bool( wxXmlNode* noeudCourant ,  Element* parent,ELEMENT_TYPE _elementType=Element::ELEMENT_TYPE_BOOL)
		:E_Data(parent,"Unnamedprop","",_elementType,noeudCourant)
	{
		linkedMenuEl=NULL;
		wxString propVal;
		//Affecte la valeur de l'element
		long lval;
		if(noeudCourant->GetPropVal("value",&propVal))
		{
			propVal.ToLong(&lval);
			elementValue=lval;
		}
	}

	/**
	* @see Element::AppendPropertyBool()
	*/
		E_Data_Bool( Element* parent, wxString dataName,wxString dataLabel, bool defaultDataValue,ELEMENT_TYPE _elementType=Element::ELEMENT_TYPE_BOOL)
		:E_Data(parent,dataName,dataLabel,_elementType)
	{
		linkedMenuEl=NULL;
		elementValue=defaultDataValue;
	}

	/**
	 * Cette méthode permet d'établir un lien entre cet élément et un élément du menu
	 * @param _linkedMenuEl Pointeur vers l'élément du menu
	 */
	void LinkMenu(wxMenuItem* _linkedMenuEl)
	{
		linkedMenuEl=_linkedMenuEl;
		linkedMenuEl->Check(elementValue);
	}


 
	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		E_Data::FillWxGrid(gridToFeed,col);
		int row=gridToFeed->GetNumberRows()-1;
		gridToFeed->SetCellEditor(row, col, new wxGridCellBoolEditor());
		gridToFeed->SetCellRenderer(row,col,new wxGridCellBoolRenderer());
		SetGridValue(gridToFeed,row,col);
	}

	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		if(!readOnly)
		{
			wxString sValue=gridCtrl->GetCellValue(ev.GetRow(),ev.GetCol());
			this->SetValue(sValue);
		}
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		thisNode->DeleteProperty("value");
		wxString sval;
		sval<<elementValue;
		thisNode->AddProperty("value",sval);		
		return thisNode;
	}


	void UpdateValue( wxGrid* gridCtrl, int row, int col=0)
	{
		E_Data::UpdateValue(gridCtrl,row,col);
		if(gridCtrl->GetCellValue(row,col)!=BoolToString(elementValue))
			SetGridValue(gridCtrl,row,col);
	}

	/**
	 * Permet de modifier la valeur de l'élément
	 * @param newValue Nouvelle valeur booléene de l'élément
	 */
	void SetValue(bool newValue)
	{
		if(newValue!=this->elementValue)
		{
			this->elementValue=newValue;
			this->Modified(this);
			if(linkedMenuEl!=NULL)
				linkedMenuEl->Check(elementValue);
		}
	}
	
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		if(exportToCore)
		{
			NoeudParent->DeleteProperty(this->elementInfo.libelleElement);
			if(elementValue)
				NoeudParent->AddProperty(this->elementInfo.libelleElement,"1");
			else
				NoeudParent->AddProperty(this->elementInfo.libelleElement,"0");

		}
		return NoeudParent;
	}
	/**
	 * Permet d'extraire la valeur de l'élément
	 * @return Valeur booléene de l'élément
	 */
	bool GetValue()
	{
		return elementValue;
	}
private:
	void SetGridValue(wxGrid* gridCtrl, int row, int col)
	{
		gridCtrl->SetCellValue(row,col,BoolToString(elementValue));
	}
	void SetValue(wxString newValue)
	{
		SetValue(StringToBool(newValue));
	}

	wxString BoolToString(bool val)
	{
		if(val)
			return "1";
		else
			return "";
	}


	bool StringToBool(wxString sval)
	{
		if(sval=="" || sval=="0")
			return false;
		else
			return true;
	}
};

#endif