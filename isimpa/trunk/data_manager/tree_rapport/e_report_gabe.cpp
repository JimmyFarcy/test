#include "e_report_gabe.h"
#include <input_output/gabe/gabe.h>
#include "data_manager/e_data_row.h"
#include <wx/log.h>
#include "last_cpp_include.hpp"
E_Report_Gabe::E_Report_Gabe(Element* parent,wxString Nom,wxString Path,ELEMENT_TYPE etype)
	:E_Report_File(parent,Nom,Path,etype)
{
	SetIcon(GRAPH_STATE_ALL,GRAPH_DISK_GABE);
}

E_Report_Gabe::E_Report_Gabe(Element* parent,wxXmlNode* nodeElement,ELEMENT_TYPE etype)
	:E_Report_File(parent,"Unnamed Array File","",etype,nodeElement)
{
	SetIcon(GRAPH_STATE_ALL,GRAPH_DISK_GABE);
}

wxXmlNode* E_Report_Gabe::SaveXMLDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = E_Report_File::SaveXMLDoc(NoeudParent);
	thisNode->SetName("arrayfile"); // Nom de la balise xml ( pas d'espace autorise )
	return thisNode;
}

bool E_Report_Gabe::IsFittingWithThisType( const ELEMENT_TYPE& typeTest )
{
	if(typeTest==ELEMENT_TYPE_REPORT_GABE)
		return true;
	else
		return E_Report_File::IsFittingWithThisType(typeTest);
}
bool E_Report_Gabe::GetArrayData(wxWindow* auiBookWin,wxString& arrayTitle,std::vector<wxString>& lblCols,std::vector<wxString>& lblRows,std::vector<wxString>& cells,std::vector<float>& cellsValue)
{
	blockUpdateNotification=true;
	wxString fullPath;
	this->BuildFullPath(fullPath);
	//////////////////////////////
	// Initialisation
	cells.clear();
	lblCols.clear();
	lblRows.clear();
	//////////////////////////////
	//Ouverture du fichier binaire

	using namespace formatGABE;
	GABE binImport(fullPath);
	int cols=binImport.GetCols();
	if(cols==0)
		return false;
	//Lecture du libelle des lignes
	GABE_Data_ShortString* dataLbl;
	binImport.GetCol(0,&dataLbl);
	
	int nbCellsRow=0;
	for(int idcol=0;idcol<cols;idcol++)
		if(binImport[idcol])
			if(binImport[idcol]->GetSize()>nbCellsRow)
				nbCellsRow=binImport[idcol]->GetSize();

	lblRows=std::vector<wxString>(nbCellsRow);
	int firstDataColIndex;
	if(dataLbl)
	{
		firstDataColIndex=1;
		for(int idrow=0;idrow<nbCellsRow;idrow++)
			lblRows[idrow]=(*dataLbl)[idrow]->strData;
		arrayTitle=wxString(_(this->elementInfo.libelleElement))+", "+wxString((*dataLbl).GetLabel());
	}else{
		firstDataColIndex=0;
		for(int idrow=0;idrow<nbCellsRow;idrow++)
			lblRows[idrow]=Convertor::ToString(idrow+1);
		arrayTitle=_(this->elementInfo.libelleElement);
	}

	lblCols=std::vector<wxString>(cols-firstDataColIndex);
	int nbCellsCol=lblCols.size();
	cells=std::vector<wxString>(nbCellsCol*nbCellsRow);
	cellsValue=std::vector<float>(nbCellsCol*nbCellsRow);

	for(int idcol=firstDataColIndex;idcol<cols;idcol++)
	{
		GABE_Object* newCol=binImport[idcol];
		if(newCol)
		{
			int rows=newCol->GetSize();			 
			lblCols[idcol-firstDataColIndex]=newCol->GetLabel();
			for(int idrow=0;idrow<rows;idrow++)
			{	
				cells[((idcol-firstDataColIndex)*rows)+idrow]=(*newCol).GetStringEquiv(idrow);
			}
			//Si cette colonne de données peut être interprété en nombre décimal
			GABE_Data_Float* floatCol;
			if(binImport.GetCol(idcol,&floatCol))
			{
				for(int idrow=0;idrow<rows;idrow++)
				{	
					cellsValue[((idcol-firstDataColIndex)*rows)+idrow]=*(*floatCol)[idrow];
				}
			}
			//Si cette colonne de données peut être interprété en nombre entier
			GABE_Data_Integer* intCol;
			if(binImport.GetCol(idcol,&intCol))
			{
				for(int idrow=0;idrow<rows;idrow++)
				{	
					cellsValue[((idcol-firstDataColIndex)*rows)+idrow]=(float)*(*intCol)[idrow];
				}
			}
		}else{
			return false;
		}
	}
	return true;
}


bool E_Report_Gabe::OpenFileInGrid()
{
	return true;
}