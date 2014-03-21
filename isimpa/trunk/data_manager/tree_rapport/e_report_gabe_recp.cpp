﻿#include "e_report_gabe_recp.h"
#include "IHM/simpleGraphManager.h"
#include <wx/aui/auibook.h>
#include <wx/wupdlock.h>
#include "data_manager/appconfig.h"
#include "last_cpp_include.hpp"

E_Report_Gabe_Recp::E_Report_Gabe_Recp(Element* parent,wxString Nom,wxString Path)
	:E_Report_Gabe(parent,Nom,Path,ELEMENT_TYPE_REPORT_GABE_RECP)
{
	_("soundpressure"); //Libellé du fichier standard
}

E_Report_Gabe_Recp::E_Report_Gabe_Recp(Element* parent,wxXmlNode* nodeElement)
	:E_Report_Gabe(parent,nodeElement,ELEMENT_TYPE_REPORT_GABE_RECP)
{

}

void E_Report_Gabe_Recp::OnRightClic(wxMenu* leMenu)
{
	leMenu->Append(GetMenuItem(leMenu,IDEVENT_RECP_COMPUTE_ACOUSTIC_PARAMETERS,_("Calculer les paramètres acoustiques")));
	E_Report_Gabe::OnRightClic(leMenu);
}

bool E_Report_Gabe_Recp::GetArrayData(wxWindow* auiBookWin,wxString& arrayTitle,std::vector<wxString>& lblCols,std::vector<wxString>& lblRows,std::vector<wxString>& cells,std::vector<float>& cellsValue)
{
	bool ok=E_Report_Gabe::GetArrayData(NULL,arrayTitle,lblCols,lblRows,cells,cellsValue);
	const float p_0=1/pow((float)(20*pow(10.f,(int)-6)),(int)2);
	/////////////////////////////////////////////////////
	//Post traitement
	// J/m3 -> dB
	arrayTitle+=_(" (dB)");
	lblCols.push_back(_("Global"));
	lblRows.push_back(_("Total"));
	int nbrow=lblRows.size();
	int nbcol=lblCols.size();
	int nbrow_src=nbrow-1;
	int nbcol_src=nbcol-1;

	std::vector<float> tmpcellsValue=std::vector<float>(nbrow*nbcol);
	cells=std::vector<wxString>(nbrow*nbcol);

	for(int idrow=0;idrow<nbrow_src;idrow++)
	{
		for(int idcol=0;idcol<nbcol_src;idcol++)
		{
			tmpcellsValue[(idcol*nbrow)+idrow]=cellsValue[(idcol*nbrow_src)+idrow];
			//cells[(idcol*nbrow)+idrow]="";
		}
	}
	cellsValue=tmpcellsValue;

	
	//////////////////////////////////////
	//Cumul sur les lignes
	std::vector<wxFloat32> schroederGraph(nbrow-1); //Création du tableau qui va contenir les valeurs cumulé

	for(int idrow=0;idrow<nbrow-1;idrow++)
	{
		float totPression=0.f;
		for(int idcol=0;idcol<nbcol-1;idcol++)
		{
			float* wVal=&cellsValue[((idcol)*nbrow)+idrow];
			if(*wVal!=0)
			{
				totPression+=(*wVal);
			}
		}
		if(totPression>0)
		{
			schroederGraph[idrow]=totPression;
			cellsValue[((nbcol-1)*nbrow)+idrow]=totPression;
		}else{
			cellsValue[((nbcol-1)*nbrow)+idrow]=0;
		}
	}
	
	//Par la méthode de schroeder, compilation des pressions

	float sumW=0;
	for(int idStep=nbrow-2;idStep>=0;idStep--)
	{
			sumW+=schroederGraph[idStep];
			schroederGraph[idStep]=sumW;		
	}

	//////////////////////////////////////
	//Cumul sur les colonnes

	for(int idcol=0;idcol<nbcol;idcol++)
	{
		float totPression=0.f;
		
		for(int idrow=0;idrow<nbrow-1;idrow++)
		{
			float* wVal=&cellsValue[((idcol)*nbrow)+idrow];
			if(*wVal!=0)
			{
				totPression+=(*wVal);
			}
		}
		if(totPression>0)
		{
			cellsValue[((idcol)*nbrow)+nbrow-1]=totPression;
		}else{
			cellsValue[((idcol)*nbrow)+nbrow-1]=0;
		}
	}

	//////////////////////////////////////
	// Conversion en db
	for(int idrow=0;idrow<nbrow;idrow++)
	{
		for(int idcol=0;idcol<nbcol;idcol++)
		{
			float* wVal=&cellsValue[((idcol)*nbrow)+idrow];
			float dbVal=10*log10f((*wVal)*p_0);
			(*wVal)=dbVal;
			cells[(idcol*nbrow)+idrow]=wxString::Format("%.1f",dbVal); //Précision de 1 chiffre aprés la virgule
		}
	}
	for(int idrow=0;idrow<nbrow-1;idrow++)
	{
		float dbVal=10*log10f(schroederGraph[idrow]*p_0);
		schroederGraph[idrow]=dbVal;
	}

	//Intervertir les lignes et les colonnes
	std::vector<wxString> tmpNewCols=lblRows;
	std::vector<wxString> tmpNewRows=lblCols;
	std::vector<wxString> tmpCells(cells.size());
	std::vector<float> tmpCellsVal(cellsValue.size());
	for(int idrow=0;idrow<nbrow;idrow++)
	{
		for(int idcol=0;idcol<nbcol;idcol++)
		{
			tmpCellsVal[((idrow)*nbcol)+idcol]=cellsValue[((idcol)*nbrow)+idrow];
			tmpCells[((idrow)*nbcol)+idcol]=cells[((idcol)*nbrow)+idrow];
		}
	}
	lblRows=tmpNewRows;
	lblCols=tmpNewCols;
	cellsValue=tmpCellsVal;
	cells=tmpCells;

	/////////////////////////////////////////////////////////////////////////
	// Création du graphique Niveau sonore en fonction des bandes de fréquences
	wxAuiNotebook* noteBookWin=dynamic_cast<wxAuiNotebook*>(auiBookWin);
	if(noteBookWin)
	{
		wxWindowUpdateLocker lockWin(noteBookWin);
		using namespace sgSpace;

		MainSimpleGraphWindow* graphPage;
		//Ajout des données au graphique
		int nbrowel=lblRows.size();
		int nbcolel=lblCols.size();
		
		graphPage=new MainSimpleGraphWindow(noteBookWin,-1);
		wxString gabeFolder;
		this->BuildFullPath(gabeFolder);
		graphPage->SetDefaultSaveGraphSavePath(gabeFolder);

		noteBookWin->AddPage(graphPage,_("Spectre"));
		SG_Element_List* drawingEl;
		//Ajout du spectre total
		if(true)
		{
			int idcol=nbcolel-1;
			drawingEl=new SG_Element_List(graphPage,lblCols[idcol]);
			drawingEl->el_style.SetDrawingMethod(DRAWING_METHOD_COLS);
			drawingEl->el_style.SetPen(wxWHITE_PEN);
			drawingEl->el_style.SetBrush(&wxBrush(*wxBLACK,wxFDIAGONAL_HATCH ));
			for(int idrow=0;idrow<nbrowel-1;idrow++)
			{
				drawingEl->PushValue(cellsValue[(idcol*nbrowel)+idrow]);
			}
		}
		

		//////////////////
		// Ajout des axes
		SG_Element_Axis* axeEly=new SG_Element_Axis(graphPage,wxVERTICAL,0.f,"dB ");
		axeEly->el_style.SetDrawingMethod(DRAWING_METHOD_COLS); //Ainsi le style de l'axe dépend de la méthode de dessin général
		SG_Element_Axis_Labeled* axeElx=new SG_Element_Axis_Labeled(graphPage,wxHORIZONTAL,1,"");
		axeElx->el_style.SetTextRotation(90);
		axeElx->el_style.SetDrawingMethod(DRAWING_METHOD_COLS); //Ainsi le style de l'axe dépend de la méthode de dessin général
		for(int idrow=0;idrow<lblRows.size()-1;idrow++)
		{
			axeElx->PushLabel(lblRows[idrow]);
		}

		//Ajout de la légende
		new SG_Legend(graphPage,LEGEND_PLACEMENT_HORIZONTAL,-1,wxSizerFlags(0).Align(wxALIGN_RIGHT));

		//////////////
		graphPage->ZoomFit();
		graphPage->LoadConfig(ApplicationConfiguration::GetFileConfig(),ApplicationConfiguration::CONST_GRAPH_CONFIG_PATH,true);

		


		//////////////////////////////////////////////
		//2 eme graph

		// Ajout de l'onglet
		graphPage=new MainSimpleGraphWindow(noteBookWin,-1);
		graphPage->SetDefaultSaveGraphSavePath(gabeFolder);
		noteBookWin->AddPage(graphPage,arrayTitle);

		// Ajout des 2 axes
		new SG_Element_Axis(graphPage,wxVERTICAL,0.f,"dB ");
		new SG_Element_Axis(graphPage,wxHORIZONTAL,0.f,"ms");

		//Ajout de la légende
		new SG_Legend(graphPage,LEGEND_PLACEMENT_HORIZONTAL,-1,wxSizerFlags(0).Align(wxALIGN_RIGHT));

		//Ajout Toute bande
		for(int idrow=nbrowel-1;idrow<nbrowel;idrow++)
		{
			SG_Element_Data* drawingElDat=new SG_Element_Data(graphPage,lblRows[idrow],nbcolel-1);
			drawingElDat->el_style.SetDrawingMethod(DRAWING_METHOD_ECHOGRAM);
			drawingElDat->el_style.SetPen(&wxPen(*wxGREEN,1,wxSOLID));

			bool lastIsZeroVal=false;
			for(int idcol=0;idcol<nbcolel-1;idcol++)
			{
				char  *stopstring;
				unsigned long xVal =strtoul(lblCols[idcol].c_str(),&stopstring,10);
				wxInt32 indice=(idcol*nbrowel)+idrow;
				drawingElDat->PushValue(xVal,cellsValue[indice]);
			}
		}
		if(true)
		{
			SG_Element_Data* drawingElDat=new SG_Element_Data(graphPage,_("Décroissance lissée"),nbcolel-1);
			drawingElDat->el_style.SetDrawingMethod(DRAWING_METHOD_LINE);
			drawingElDat->el_style.SetPen(&wxPen(*wxBLACK,2,wxSOLID));
			//Ajout de schroeder
			for(int idcol=0;idcol<nbcolel-1;idcol++)
			{
				char  *stopstring;
				unsigned long xVal =strtoul(lblCols[idcol].c_str(),&stopstring,10);
				drawingElDat->PushValue(xVal,schroederGraph[idcol]);
			}
		}
		graphPage->ZoomFit();
		graphPage->LoadConfig(ApplicationConfiguration::GetFileConfig(),ApplicationConfiguration::CONST_GRAPH_CONFIG_PATH,true);
	}

	return ok;
}

bool E_Report_Gabe_Recp::OpenFileInGrid()
{
	return false;
}