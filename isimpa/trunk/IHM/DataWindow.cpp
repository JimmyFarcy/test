#include "DataWindow.h"
#include "data_manager/tree_rapport/e_report_gabe.h"
#include "IHM/GabeDataGrid.hpp"
#include "last_cpp_include.hpp"

/*
Evenements disponibles

	wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE
	wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED
	wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING
	wxEVT_COMMAND_AUINOTEBOOK_BUTTON
	wxEVT_COMMAND_AUINOTEBOOK_BEGIN_DRAG
	wxEVT_COMMAND_AUINOTEBOOK_END_DRAG
	wxEVT_COMMAND_AUINOTEBOOK_DRAG_MOTION
	wxEVT_COMMAND_AUINOTEBOOK_ALLOW_DND
	wxEVT_COMMAND_AUINOTEBOOK_TAB_MIDDLE_DOWN
	wxEVT_COMMAND_AUINOTEBOOK_TAB_MIDDLE_UP
	wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_DOWN
	wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_UP
	wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED
	wxEVT_COMMAND_AUINOTEBOOK_DRAG_DONE
	wxEVT_COMMAND_AUINOTEBOOK_BG_DCLICK
*/

BEGIN_EVENT_TABLE(DataWindow, wxAuiNotebook)
	EVT_AUINOTEBOOK_ALLOW_DND(wxID_ANY, DataWindow::OnAllowNotebookDnD)
	//EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_ANY, DataWindow::OnPageClosed)
	//EVT_AUINOTEBOOK_DRAG_DONE(wxID_ANY, DataWindow::OnPageDragAway)
END_EVENT_TABLE()


DataWindow::DataWindow(wxWindow* parent,
                  wxWindowID id,
                  const wxPoint& pos,
                  const wxSize& size,
                  long style)
				  :wxAuiNotebook(parent,id,pos,size,style)
{
}

void DataWindow::PushElement(Element* newElement)
{
	E_Report_Gabe* gabeElement=dynamic_cast<E_Report_Gabe*>(newElement);
	if(gabeElement)
	{
		if(!gabeElement->OpenFileInGrid()) //Si les données doivent être fourni par l'élément 
		{
			std::vector<wxString> lblCols;
			std::vector<wxString> lblRows;
			std::vector<wxString> cells;
			std::vector<float> cellsValue;
			wxString titleArray;
			if(gabeElement->GetArrayData(this,titleArray,lblCols,lblRows,cells,cellsValue))
			{
				GabeDataGrid* newSubWindow= new GabeDataGrid(this,-1);
				newSubWindow->LoadData(lblCols,lblRows,cells,cellsValue);
				newSubWindow->LockUserUpdate();
				this->AddPage(newSubWindow,titleArray,true);
			}
		}else{
			wxString pathGabe;
			gabeElement->BuildFullPath(pathGabe);
			GabeDataGrid* newSubWindow= new GabeDataGrid(this,-1);
			newSubWindow->LoadData(pathGabe);
			this->AddPage(newSubWindow,_(newElement->GetElementInfos().libelleElement),true);
		}
	}
}

void DataWindow::OnAllowNotebookDnD(wxAuiNotebookEvent& evt)
{
	evt.Allow();
}


void DataWindow::OnPageClosed(wxAuiNotebookEvent& evt)
{
	OnDataSrcChange();
	evt.Skip();
}

void DataWindow::OnDataSrcChange()
{
	if(this->GetPageCount()==0)
	{
		wxWindow* NoteBookWindowParent=this->GetParent();
		if(NoteBookWindowParent)
		{
			wxAuiFloatingFrame* parentMng=dynamic_cast<wxAuiFloatingFrame*>(NoteBookWindowParent);
			if(parentMng)
			{
				parentMng->Close();
			}else{
				wxAuiManager* currentManager=wxAuiManager::GetManager(this);
				if(currentManager)
				{
					currentManager->ClosePane(currentManager->GetPane(this));
					currentManager->Update();
				}
			}
		}
	}
}

void DataWindow::OnPageDragAway(wxAuiNotebookEvent& evt)
{
	evt.Allow();
	OnDataSrcChange();
	evt.Skip();
}