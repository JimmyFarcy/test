#include "data_group_info.h"
#include <fstream>
#include "last_cpp_include.hpp"

namespace formatGRPINFO
{

bool DGIBIN::ExportBIN(const char *strFileName,exchangeMainData &mainData)
{
	//Namespace
	using namespace std;

	//Declarations

	//Sauvegarde du modèle 3D
	fstream binFile (strFileName, ios::out | ios::binary);
	
	//*************************
	//Ecriture de l'entete du fichier
	binFile.write((char*)&mainData.header,sizeof(t_FileHeader));
	//*************************
	//Ecriture des faces
	binFile.write((char*)mainData.tabFaces,sizeof(binface)*mainData.header.quantFace);

	binFile.close();	
	return true;
}

bool  DGIBIN::ImportBIN(const char *strFileName,exchangeMainData &mainData)
{
	//Namespace
	using namespace std;

	//Declarations

	//Sauvegarde du modèle 3D
    fstream binFile (strFileName, ios::in | ios::binary);
	
	//*************************
	//Lecture de l'entete du fichier
	binFile.read((char*)&mainData.header,sizeof(t_FileHeader));
	mainData.tabFaces = new binface[mainData.header.quantFace];
	//*************************
	//Lecture des faces
	binFile.read((char*)mainData.tabFaces,sizeof(binface)*mainData.header.quantFace);

	binFile.close();	

	return true;
}

} //fin namespace