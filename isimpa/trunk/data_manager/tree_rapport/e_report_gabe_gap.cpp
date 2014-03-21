#include "e_report_gabe_gap.h"
#include "IHM/simpleGraphManager.h"
#include <wx/aui/auibook.h>
#include <wx/wupdlock.h>
#include "data_manager/appconfig.h"
#include <input_output/gabe/gabe.h>
#include "last_cpp_include.hpp"

E_Report_Gabe_Gap::E_Report_Gabe_Gap(Element* parent,wxString Nom,wxString Path)
	:E_Report_Gabe(parent,Nom,Path,ELEMENT_TYPE_REPORT_GABE_GAP)
{
	_("advParams"); //Libellé du fichier standart
}

E_Report_Gabe_Gap::E_Report_Gabe_Gap(Element* parent,wxXmlNode* nodeElement)
	:E_Report_Gabe(parent,nodeElement,ELEMENT_TYPE_REPORT_GABE_GAP)
{

}

void E_Report_Gabe_Gap::OnRightClic(wxMenu* leMenu)
{
	leMenu->Append(GetMenuItem(leMenu,IDEVENT_RECP_COMPUTE_ADVANCED_ACOUSTIC_PARAMETERS,_("Calculer les paramètres acoustiques")));
	E_Report_Gabe::OnRightClic(leMenu);
}

bool E_Report_Gabe_Gap::GetArrayData(wxWindow* auiBookWin,wxString& arrayTitle,std::vector<wxString>& lblCols,std::vector<wxString>& lblRows,std::vector<wxString>& cells,std::vector<float>& cellsValue)
{
	const float p_0=1/pow((float)(20*pow(10.f,(int)-6)),(int)2);
	using namespace formatGABE;
	int nbsubfreq=3;
	wxString filePath;
	BuildFullPath(filePath);
	GABE gReader(filePath);
	formatGABE::GABE_Data_Integer* indexCol;
	formatGABE::GABE_Data_Integer* lstFreq;
	formatGABE::GABE_Data_Float* lstFloatParam;
	if(!gReader.GetCol(0,&indexCol))
		return false;
	if(!gReader.GetCol(indexCol->GetValue(2),&lstFreq))
		return false;
	if(!gReader.GetCol(indexCol->GetValue(0),&lstFloatParam))
		return false;

	arrayTitle=_("Niveau sonore latéral");
	////////////////////////
	// Construction des libellés des lignes, bandes de fréquences
	int nbfreq=indexCol->GetValue(5);
	lblRows.reserve(nbfreq*nbsubfreq);
	for(int idfreq=0;idfreq<nbfreq;idfreq++)
	{
		lblRows.push_back(wxString(lstFreq->GetStringEquiv(idfreq))+_(" Hz"));
		lblRows.push_back(wxString(lstFreq->GetStringEquiv(idfreq))+_(" Hz")+_(" (E*cos theta)"));
		lblRows.push_back(wxString(lstFreq->GetStringEquiv(idfreq))+_(" Hz")+_(" (E*cos² theta)"));
	}
	////////////////////////
	// Construction des libellés des colonnes, Temps
	float timeStep=lstFloatParam->GetValue(0)*1000; //Recuperation de deltaT
	float firstTimeStep=lstFloatParam->GetValue(1)*1000; //Recuperation de t0
	int nbtimeStep=indexCol->GetValue(7);
	lblCols.reserve(nbtimeStep);
	for(int idstep=0;idstep<nbtimeStep;idstep++)
	{
		float currentTimeStep=firstTimeStep+idstep*timeStep;
		lblCols.push_back(Convertor::ToString((int)currentTimeStep)+_(" ms"));
	}
	////////////////////////
	// Affectation des niveaux sonores (dB)
	int currentIndexCol=indexCol->GetValue(4);
	int colWpStep=indexCol->GetValue(6);
	int nbrow=lblRows.size();
	int nbcol=lblCols.size();
	cells.insert(cells.begin(),nbrow*nbcol,"");
	cellsValue.insert(cellsValue.begin(),nbrow*nbcol,0.);
	int idrow=0;
	for(int idfreq=0;idfreq<nbfreq;idfreq++)
	{
		for(int idsubcol=0;idsubcol<nbsubfreq;idsubcol++)
		{
			formatGABE::GABE_Data_Float* colWpVal;
			if(!gReader.GetCol(currentIndexCol+idsubcol,&colWpVal))
				return false;
			for(int idstep=0;idstep<nbtimeStep;idstep++)
			{
				idrow=(idfreq*nbsubfreq)+idsubcol;
				float dbVal=10*log10f(colWpVal->GetValue(idstep)*p_0);
				cells[(idstep*nbrow)+(idrow)]=wxString::Format("%.1f",dbVal); //Précision de 1 chiffre aprés la virgule
				cellsValue[(idstep*nbrow)+(idrow)]=dbVal;				
			}
		}
		currentIndexCol+=colWpStep;
	}
	return true;
}

bool E_Report_Gabe_Gap::OpenFileInGrid()
{
	return false;
}