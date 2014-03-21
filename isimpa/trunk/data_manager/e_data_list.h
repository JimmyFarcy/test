﻿#include "first_header_include.hpp"
#include <wx/log.h>
#include "data_manager/e_data.h"
#include <wx/tokenzr.h>
#include "manager/stringTools.h"
#ifndef __ELEMENT_LIST__
#define __ELEMENT_LIST__

/** \file e_data_list.h
   \brief Classe spécialisant E_Data afin de représenter une liste de valeur ( choix unique )
*/

/**
	\brief Classe spécialisant E_Data afin de représenter une liste de valeur ( choix unique )
	@see MainPropGrid
*/
class E_Data_List: public E_Data
{
protected:
	std::vector<wxString> eList;	/*!< Tableau contenant la liste des valeurs possibles */
	std::vector<int> iList;			/*!< Indice correspondant à la chaîne de caractère*/
	long currentChoice;				/*!< Indice de l'element choisi dans le tableau de valeur */
	wxString currentLibel;
public:
	E_Data_List( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data(parent,"Unnamedprop","",Element::ELEMENT_TYPE_LIST,noeudCourant)
	{


		//Creation de la liste à partir du document XML
		wxString propValue;

		if(noeudCourant->GetPropVal("nb",&propValue))
		{
			long nbVal;
			propValue.ToLong(&nbVal);
			if(noeudCourant->GetPropVal("choice",&propValue))
				propValue.ToLong(&currentChoice);
			wxXmlNode* currentChild = noeudCourant->GetChildren();
			while(currentChild!=NULL)
			{
				if(currentChild->GetName()=="enumeration")
				{
					if(currentChild->GetPropVal("id",&propValue))
					{
						long id;
						propValue.ToLong(&id);
						if(currentChild->GetPropVal("value",&propValue))
						{

							eList.push_back(propValue);
							iList.push_back(id);
						}

					}
				}
				currentChild = currentChild->GetNext();
			}
			 SetValue(currentChoice);
		}
	}


	/**
	 *	@see Element::AppendPropertyList()
	 *	@param parent Element parent
	 *	@param[in] dataName Nom du champ ( non visible par l'utilisateur)
	 *	@param[in] dataLabel Libellé du champ
	 *	@param[in] _eList Liste des valeurs de sélection possibles
	 *  @param[in] _iList Liste des indices correspondant aux valeurs.
	 *	@param[in] defaultChoice Valeur par défaut
	 *	@param[in] asTitle Ce champ doit-il être visible en premier dans la liste des propriétés
	 *	@param[in] hSize Combien de cellules ce champ va occuper
	 */
	E_Data_List( Element* parent, wxString dataName,wxString dataLabel, std::vector<wxString> &_eList,std::vector<int> &_iList,long defaultChoice, bool asTitle=false, int hSize=1)
		:E_Data(parent,dataName,dataLabel,Element::ELEMENT_TYPE_LIST,NULL,asTitle,hSize)
	{
		iList=_iList;
		eList=_eList;
		if(iList.size()!=_eList.size())
			wxLogDebug(_("Le tableau d'indices ne correspond pas au tableau de valeurs !"));
		SetValue(defaultChoice);
	}

	const std::vector<wxString>& GetItemsLabel() const
	{
		return eList;
	}

	const std::vector<int>& GetItemsId() const
	{
		return iList;
	}
	void AppendItem(const wxString& itemLabel,const int& itemId)
	{
		eList.push_back(itemLabel);
		iList.push_back(itemId);
	}
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		if(exportToCore)
		{
			NoeudParent->DeleteProperty(this->elementInfo.libelleElement);
			NoeudParent->AddProperty(this->elementInfo.libelleElement,Convertor::ToString((int)currentChoice));
		}
		return NoeudParent;
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		wxString tmpVal;
		thisNode->DeleteProperty("nb");
		tmpVal<<eList.size();
		thisNode->AddProperty("nb",tmpVal);
		tmpVal="";
		thisNode->DeleteProperty("choice");
		tmpVal<<currentChoice;
		thisNode->AddProperty("choice",tmpVal);
		wxXmlNode* cChild=thisNode->GetChildren();
		while(cChild!=NULL)
		{
			thisNode->RemoveChild(cChild);
			delete cChild;
			cChild=thisNode->GetChildren();
		}
		if(iList.size()==eList.size())
		{
			for(long id=0;id<eList.size();id++)
			{
				wxXmlNode* nouvEnum=new wxXmlNode(thisNode,wxXML_ELEMENT_NODE,"enumeration");
				nouvEnum->AddProperty("id",Convertor::ToString(iList[id]));
				nouvEnum->AddProperty("value",eList[id]);
			}
		}

		return thisNode;
	}

	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		E_Data::FillWxGrid(gridToFeed,col);
		int row=gridToFeed->GetNumberRows()-1;
		smart_ptr_ar<wxString> choices=new wxString[eList.size()];
		for(long id=0;id<eList.size();id++)
			choices[id]=_(eList[id]); //traduction de chaque élément
		gridToFeed->SetCellEditor(row, col, new wxGridCellChoiceEditor(eList.size(),choices.get()));
		SetGridValue(gridToFeed,row,col);
	}
	void UpdateValue( wxGrid* gridCtrl, int row, int col=0)
	{
		E_Data::UpdateValue(gridCtrl,row,col);
		if(gridCtrl->GetCellValue(row,col)!= currentLibel)
			SetGridValue(gridCtrl,row,col);
	}
	/**
	 * Mettre à jour la valeur du champ
	 * @return Entier, indice désignant l'élément par défaut.
	 * @see Element::GetListConfig()
	 */
	int GetChoice()
	{
		return currentChoice;
	}
	/**
	 * Mettre à jour la valeur du champ
	 * @param[in] NewChoice Entier, indice désignant le nouvel élément par défaut.Si l'indice est invalide aucune modification est effectuée.
	 * @see Element::UpdateListConfig()
	 */
	void SetValue(int NewChoice,wxString libel="")
	{
		currentChoice=NewChoice;
		if(libel=="")
		{
			for(long id=0;id<iList.size();id++)
			{
				if(currentChoice==iList[id])
				{
					if(id<eList.size())
					{
						currentLibel=_(eList[id]);
					}
				}
			}
		}else{
			currentLibel=libel;
		}
	}
	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		wxString sValue=gridCtrl->GetCellValue(ev.GetRow(),ev.GetCol());
		//On va chercher l'indice de cette valeur
		for(long id=0;id<eList.size();id++)
		{
			if(_(eList[id])==sValue)
			{
				if(iList.size()>id)
				{
					SetValue(iList[id],sValue);
				}else{
					wxLogInfo(_("Valeur non autorisée"));
				}
				Modified(this);
				return;
			}
		}
		ev.Veto();
	}
private:

	void SetGridValue( wxGrid* gridToFeed, int row, int col=0)
	{
		E_Data::FillWxGrid(gridToFeed,col);
		gridToFeed->SetCellValue(row, col, currentLibel);
	}
};

#endif
