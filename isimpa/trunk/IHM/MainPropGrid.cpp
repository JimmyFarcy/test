﻿#include "MainPropGrid.h"
#include <algorithm>
#include <wx/log.h>
#include <wx/wupdlock.h>
#include "DialogDiagramCreator.h"
#include <wx/aui/aui.h>
#include "IHM/DataWindow.h"
#include "last_cpp_include.hpp"

BEGIN_EVENT_TABLE( MainPropGrid, PropGrid )
    EVT_GRID_SELECT_CELL( MainPropGrid::OnSelectionChange )
	EVT_KEY_UP(MainPropGrid::KeyEvt )
	EVT_LEFT_UP(MainPropGrid::MouseEvt )
    EVT_GRID_CELL_CHANGE( MainPropGrid::OnCellValueChanged )
	EVT_MENU(ID_CREATE_DIAGRAM, MainPropGrid::OnBuildDiagram)
END_EVENT_TABLE()

bool GridSortPredicate(Element* lEl,Element* rEl)
{
  return *lEl<*rEl;
}

struct MainPropGridWitness : public t_outsideOperator
{
	MainPropGridWitness(MainPropGrid* _propertygrid,const int& _xmlId)
		:t_outsideOperator(),propertygrid(_propertygrid),xmlId(_xmlId),propgrid_alive(_propertygrid->alive)
	{

	}
	virtual ~MainPropGridWitness()
	{
		if(*propgrid_alive)
		{
			try
			{
				if(propertygrid->GetXmlIdElementOpen()==xmlId)
					propertygrid->CloseElement();
			}
			catch(...)
			{
				wxLogDebug("Erreur lors de l'appel de propertygrid->CloseElement()");
			}
		}
	}

	MainPropGrid* propertygrid;
	smart_ptr<bool> propgrid_alive;
	int xmlId;
};


MainPropGrid::MainPropGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:PropGrid(parent,id,pos,size,style,name),alive(new bool(true))
{
	reloadElement=false;
	CurrentElement=NULL;
	this->SetLabelAlignment(wxVERTICAL,wxALIGN_LEFT);
}

MainPropGrid::~MainPropGrid()
{
	*alive=false;
}
void MainPropGrid::RefreshValues()
{
	wxWindowUpdateLocker noUpdates(this); //Bloque la mise à jour de l'affichage
	for(int i=0;i<this->dataItems.size();i++)
	{
		this->dataItems[i].elementItem->UpdateValue(this,this->dataItems[i].rowNumber);
	}
}

void MainPropGrid::MouseEvt(wxMouseEvent& ev)
{
	if(reloadElement)
	{
		reloadElement=false;
		this->LoadElement(CurrentElement);
	}
	ev.Skip();
}
void MainPropGrid::KeyEvt(wxKeyEvent& ev)
{
	if(reloadElement)
	{
		reloadElement=false;
		this->LoadElement(CurrentElement);
	}
	ev.Skip();
}
void MainPropGrid::OnSelectionChange(wxGridEvent& ev)
{
	if(reloadElement)
	{
		reloadElement=false;
		this->LoadElement(CurrentElement);
	}
	ev.Skip();
}

void MainPropGrid::OnCellValueChanged(wxGridEvent& ev)
{
	if(CurrentElement)
	{
		//On appel l'événement de l'Element
		int rowVal=ev.GetRow();
		for(int i=0;i<this->dataItems.size();i++)
		{
			if(this->dataItems[i].rowNumber==rowVal)
			{
				this->dataItems[i].elementItem->OnValueChanged(ev,this);
				break;	// on sort de la recherche
			}
		}
		// L'element peut demander la réouverture de la feuille de propriété
		if(CurrentElement->IsAskPropReload())
		{
			reloadElement=true;
			return;
		}
		// Peut etre que la modification de ce champ a altéré d'autres champs
		// 
		RefreshValues();
	}
}

void MainPropGrid::OnBuildDiagram(wxCommandEvent& event)
{
	//Ouverture de l'interface de création de graphique
	wxAuiManager* currentManager=wxAuiManager::GetManager(this);
	if(currentManager)
	{
		DataWindow* newWindow=new DataWindow(this->GetParent() ,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_CLOSE_ON_ACTIVE_TAB | wxAUI_NB_TAB_EXTERNAL_MOVE );
		wxWindowUpdateLocker noUpdates(newWindow); //Bloque la mise à jour de l'affichage	
		
		currentManager->AddPane(newWindow, wxAuiPaneInfo().
				Caption(_("Feuille de données")+wxString(" - ")+CurrentElement->GetElementInfos().libelleElement).FloatingSize(300,200)
					  .Float().CloseButton(true).MaximizeButton(true).DestroyOnClose(true));

		//Création du dialogue
		BuildGraphSheetDialog* sgCreatorDialog=new BuildGraphSheetDialog(this->GetParent(),newWindow,wxID_ANY,_("Création d'un nouveau diagramme"));
		//Ajout des données séléctionnées
		std::vector<wxString> lblCols(currentSelection.RightCol-currentSelection.LeftCol+1);
		std::vector<wxString> lblRows(currentSelection.BottomRow-currentSelection.TopRow+1);
		std::vector<float> cellsValue(lblCols.size()*lblRows.size());
		wxInt32 zeroBaseRow=0;
		for ( int row = currentSelection.TopRow; row <= currentSelection.BottomRow; row++ )
		{
			lblRows[zeroBaseRow]=this->GetLabelValue(wxVERTICAL,row);
			wxInt32 zeroBaseCol=0;
			for ( int col = currentSelection.LeftCol; col <= currentSelection.RightCol; col++ )
			{
				if(row==currentSelection.TopRow)
					lblCols[zeroBaseCol]=this->GetLabelValue(wxHORIZONTAL,col);
				double valCell=0;
				this->GetCellValue(row,col).ToDouble(&valCell) ;//cellsRealValue[(col*this->GetRows())+row];
				cellsValue[(zeroBaseCol*lblRows.size())+zeroBaseRow]=valCell;
				zeroBaseCol++;
			}
			zeroBaseRow++;
		}
		sgCreatorDialog->LoadData(lblCols,lblRows,cellsValue);

		sgCreatorDialog->ShowModal();

		currentManager->Update();
	}
}
void MainPropGrid::DoFillMenu(wxGridEvent& ev,wxMenu* mainMenu)
{
	PropGrid::DoFillMenu(ev,mainMenu);
	//Si la séléction est au moins de 2*1 ou de 1*2 on permet d'afficher un graphique
	if((currentSelection.BottomRow-currentSelection.TopRow>=1) || (currentSelection.RightCol-currentSelection.LeftCol>=1))
	{
		mainMenu->AppendSeparator();
		mainMenu->Append(ID_CREATE_DIAGRAM,_("Créer un diagramme"));
	}
}
void MainPropGrid::CloseElement()
{
	if(CurrentElement)
	{
		this->dataItems.clear();
		this->ClearGrid();
		
		if(this->GetNumberRows()>0)
			this->DeleteRows(0,this->GetNumberRows());
		if(this->GetNumberCols()>1)
			this->DeleteCols(0,this->GetNumberCols()-1);
		this->SetColLabelValue(0,_("Valeur"));
		this->SetRowLabelSize(30);
		CurrentElement=NULL;
		this->SetLabelAlignment(wxVERTICAL,wxALIGN_LEFT);
	}
}

wxTreeItemId MainPropGrid::GetTreeIdElementOpen()
{
	return this->idCurrentElement;
}


int MainPropGrid::GetXmlIdElementOpen()
{
	return this->XmlIdElement;
}
void MainPropGrid::LoadElement(Element* elementToShowProp)
{
	wxWindowUpdateLocker noUpdates(this); //Bloque la mise à jour de l'affichage
	this->CloseElement();
	
	CurrentElement=elementToShowProp;
	this->XmlIdElement=elementToShowProp->GetXmlId();
	CurrentElement->AppendWitness(LifeTimeWitness(new MainPropGridWitness(this,CurrentElement->GetXmlId())));
	this->SetColLabelValue(0,elementToShowProp->GetColTitle(0));
	this->idCurrentElement=elementToShowProp->GetElementInfos().idElement;

	elementToShowProp->InitProp();

	std::list<Element*> filsNoeud;
	elementToShowProp->GetChildElement(filsNoeud);

	//std::sort(filsNoeud.begin( ), filsNoeud.end( ), GridSortPredicate );
	filsNoeud.sort(GridSortPredicate);

	for(std::list<Element*>::iterator itfils=filsNoeud.begin();itfils!=filsNoeud.end();itfils++)
	{
		const Element::t_elementInfo& elinfos=(*itfils)->GetElementInfos();
		if(!elinfos.hidden && elinfos.typeElement!=Element::ELEMENT_TYPE_POSITION)
		{
			E_Data* elementFils=dynamic_cast<E_Data*>((*itfils));
			if(elementFils) //Si il s'agit d'un objet dérivé de data
			{
				try
				{
					rowInfo rowToAdd;
					rowToAdd.elementItem=elementFils;
					this->AppendRows(1);
					rowToAdd.rowNumber=this->GetNumberRows()-1;
					this->dataItems.push_back(rowToAdd);
					elementFils->FillWxGrid(this);
					AutoSizeLibelle(this->GetNumberRows()-1);
				}
				catch( ... )
				{
					wxLogDebug(_("Erreur de chargement des propriétés"));
					break;
				}
			}
		}
	}
	//Redimensionnement
	AutoSizeColumns(false);	
	//AutoSizeRows(false);
	this->SetRowLabelSize(wxGRID_AUTOSIZE);
	this->SetColLabelSize(wxGRID_AUTOSIZE);
	//ForceRefresh();
	//AutoSize  (   )  ;
}