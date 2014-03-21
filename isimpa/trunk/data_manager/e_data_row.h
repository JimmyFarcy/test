﻿#include "first_header_include.hpp"

#include "data_manager/e_data.h"
#include <algorithm>
#ifndef __ELEMENT_ROW__
#define __ELEMENT_ROW__

/** \file e_data_row.h
   \brief Classe spécialisant E_Data afin de représenter une ligne comportant un ou plusieurs éléments
*/

/**
	\brief Classe spécialisant E_Data afin de représenter une ligne comportant un ou plusieurs éléments
	@see MainPropGrid

    L'utilisation de cet élément est seulement nécéssaire si l'on veut utiliser plus d'une colonne dans la feuille de propriétés d'un élément.
*/
class E_Data_Row: public E_Data
{
public:
	E_Data_Row( wxXmlNode* noeudCourant ,  Element* parent,Element::ELEMENT_TYPE etype=ELEMENT_TYPE_ROW)
		:E_Data(parent,"Unnamedprop","",etype,noeudCourant)
	{
	}

	/**
	 *	@param parent Element parent
	 *	@param[in] dataName Nom du champ ( non visible par l'utilisateur)
	 *	@param[in] dataLabel Libellé de la ligne
	 *	@param[in] etype Type de ligne ( par défaut ligne standard )
	 *  @see E_Data_Row_BandeFreq
	 *  @see E_Data_Row_BandeMateriau
	 */
		E_Data_Row( Element* parent, wxString dataName,wxString dataLabel,Element::ELEMENT_TYPE etype=ELEMENT_TYPE_ROW)
		:E_Data(parent,dataName,dataLabel,etype)
	{
	}
	/**
	 * @return Etat des droits de modification de l'utilisateur. Vrai=en lecture seule
	 */
	virtual bool IsReadOnly(int col=-1)
	{
		if(col==-1)
		{
			if(col<this->fils.size())
			{
				std::list<Element*>::iterator itfils=this->fils.begin();
				for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
				{
					E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
					if(dataFils)
					{
						if(dataFils->IsReadOnly())
							return true;
					}
				}
				return false;
			}
		}else if(col<this->fils.size())
		{
			std::list<Element*>::iterator itfils=this->fils.begin();
			for(int itcounter=0;itcounter<col;itcounter++)
				itfils++;
			E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
			if(dataFils)
				return dataFils->IsReadOnly();
		}
		return true;
	}
	virtual void SetReadOnly(bool readonly=true,int col=0) 
	{
		if(col>=0)
		{
			if(col<this->fils.size())
			{
				std::list<Element*>::iterator itfils=this->fils.begin();
				for(int itcounter=0;itcounter<col;itcounter++)
					itfils++;
				E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
				dataFils->SetReadOnly(readonly,col);
			}
		}else{
			for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
			{
				E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
				if(dataFils)
				{
					dataFils->SetReadOnly(readonly,col);
				}
			}
		}
	}
	virtual void FillWxGrid(wxGrid* gridToFeed,int col=0)
	{
		//std::sort(this->fils.begin( ), this->fils.end( ), OrderById );
		this->fils.sort(OrderById);
		std::size_t nbfils(this->fils.size());
		if(gridToFeed->GetCols()<nbfils)
			gridToFeed->AppendCols(nbfils-gridToFeed->GetCols());

		int i=0;
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
			if(dataFils)
			{
				dataFils->FillWxGrid(gridToFeed,i);
				gridToFeed->SetColLabelValue(i,dataFils->GetPropertyLabel());
			}
			i++;
		}
		E_Data::FillWxGrid(gridToFeed,-1);
	}
	virtual void UpdateValue( wxGrid* gridCtrl, int row, int col=0)
	{
		E_Data::UpdateValue(gridCtrl,row,col);
		int i=0;
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
			if(dataFils)
			{
				dataFils->UpdateValue(gridCtrl,row,i);
			}
			i++;
		}
	}
	virtual void OnValueChanged(wxGridEvent& ev,wxGrid* gridCtrl)
	{
		int row=ev.GetRow();
		int col=ev.GetCol();
		if(col<this->fils.size())
		{
			
			std::list<Element*>::iterator itfils=this->fils.begin();
			for(int itcounter=0;itcounter<col;itcounter++)
				itfils++;
			E_Data* dataFils=dynamic_cast<E_Data*>(*itfils);
			if(dataFils)
			{
				dataFils->OnValueChanged(ev,gridCtrl); 
			}
		}
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		return E_Data::SaveXMLDoc(NoeudParent);
	}
	virtual const wxString GetElementNameForOrder() const
	{
		return this->elementInfo.libelleElement;
	}
private:
	
	static bool OrderById(Element* lEl,Element* rEl)
	{
		return lEl->GetElementInfos().xmlIdElement<rEl->GetElementInfos().xmlIdElement;
	}
};

#endif