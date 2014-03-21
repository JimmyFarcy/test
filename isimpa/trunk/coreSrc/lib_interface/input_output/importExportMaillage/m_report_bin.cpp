#include "m_report_bin.h"
#include <fstream>
#include <string.h>

namespace formatMRENDERBIN
{

bool REPORT_MBIN::ExportBIN(const char *strFileName,t_reportbinexchange& reportData)
{
	//Namespace
	using namespace std;

	//Declarations

	//Sauvegarde du modèle 3D
	fstream binFile (strFileName, ios::out | ios::binary);

	//*************************
	//Ecriture de l'entete du fichier
	binFile.write((char*)&reportData.data_infos,sizeof(t_FileHeader));
	//*************************
	//Ecriture des noeuds
	binFile.write((char*)reportData.nodes,sizeof(t_binNode)*reportData.data_infos.quantNodes);
	//*************************
	//Ecriture des tetrahèdres
	binFile.write((char*)reportData.tetras,sizeof(bintetrahedre)*reportData.data_infos.quantTetra);

	binFile.close();
	return true;
}

bool  REPORT_MBIN::ImportBIN(const char *strFileName,t_reportbinexchange& reportData)
{
	//Namespace
	using namespace std;

	//Declarations

	//Sauvegarde du modèle 3D
    fstream binFile (strFileName, ios::in | ios::binary);
	if(binFile.is_open())
	{
		//*************************
		//Lecture de l'entete du fichier
		memset(&reportData.data_infos,0,sizeof(t_FileHeader));
		binFile.read((char*)&reportData.data_infos,sizeof(t_FileHeader));

		if(reportData.data_infos.quantNodes>0 && reportData.data_infos.quantTetra>0)
		{
			delete[] reportData.nodes;
			delete[] reportData.tetras;
			reportData.nodes = new t_binNode[reportData.data_infos.quantNodes];
			reportData.tetras = new bintetrahedre[reportData.data_infos.quantTetra];
			//*************************
			//Lecture des noeuds
			binFile.read((char*)reportData.nodes,sizeof(t_binNode)*reportData.data_infos.quantNodes);
			//*************************
			//Lecture des tetrahèdres
			binFile.read((char*)reportData.tetras,sizeof(bintetrahedre)*reportData.data_infos.quantTetra);
			binFile.close();
		}else{
			binFile.close();
			return false;
		}
		return true;
	}else{
		return false;
	}
}

} //fin namespace
