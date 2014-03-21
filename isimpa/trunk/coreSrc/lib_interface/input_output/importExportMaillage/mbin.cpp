#include "mbin.h"
#include <fstream>
#include "Core/mathlib.h"

namespace formatMBIN
{


	/**
	 * @brief Structure d'entete du fichier
	 */
	struct t_FileHeader
	{
		Longb quantTetra;
		Longb quantNodes;
	};
trimeshmodel CMBIN::LoadMesh(const char *strFileName)
{
	trimeshmodel modelret;
	bintetrahedre *tabTetra=NULL;
	t_binNode *tabNodes=NULL;
	unsigned int sizeTetra=0;
	unsigned int sizeNodes=0;
	if(ImportBIN(strFileName,&tabTetra,&tabNodes,sizeTetra,sizeNodes))
	{
		modelret.nodes.reserve(sizeNodes);
		for( unsigned int idnode=0;idnode<sizeNodes;idnode++)
			modelret.nodes.push_back(tabNodes[idnode]);
		modelret.tetrahedres.reserve(sizeTetra);
		for( unsigned int idtetra=0;idtetra<sizeTetra;idtetra++)
			modelret.tetrahedres.push_back(tabTetra[idtetra]);
	}
	delete[] tabTetra;
	delete[] tabNodes;
	return modelret;
}

void CMBIN::SaveMesh(const char *strFileName,trimeshmodel& trimesh)
{
	unsigned int sizeTetra=trimesh.tetrahedres.size();
	unsigned int sizeNodes=trimesh.nodes.size();
	bintetrahedre *tabTetra=new bintetrahedre[sizeTetra];
	t_binNode *tabNodes=new t_binNode[sizeNodes];

	for( unsigned int idnode=0;idnode<sizeNodes;idnode++)
		tabNodes[idnode]=trimesh.nodes[idnode];
	for( unsigned int idtetra=0;idtetra<sizeTetra;idtetra++)
		tabTetra[idtetra]=trimesh.tetrahedres[idtetra];

	ExportBIN(strFileName,&tabTetra,&tabNodes,sizeTetra,sizeNodes);

	delete[] tabTetra;
	delete[] tabNodes;
}

bool CMBIN::ExportBIN(const char *strFileName,bintetrahedre **tabTetra,t_binNode **tabNodes,unsigned int sizeTetra,unsigned int sizeNodes)
{
	//Namespace
	using namespace std;

	//Declarations

	//Sauvegarde du modèle 3D
	fstream binFile (strFileName, ios::out | ios::binary);

	//*************************
	//Ecriture de l'entete du fichier
	t_FileHeader fileHeader;
	fileHeader.quantNodes=sizeNodes;
	fileHeader.quantTetra=sizeTetra;
	binFile.write((char*)&fileHeader,sizeof(t_FileHeader));
	//*************************
	//Ecriture des noeuds
	binFile.write((char*)*tabNodes,sizeof(t_binNode)*sizeNodes);
	//*************************
	//Ecriture des tetrahèdres
	binFile.write((char*)*tabTetra,sizeof(bintetrahedre)*sizeTetra);

	binFile.close();
	return true;
}

bool  CMBIN::ImportBIN(const char *strFileName,bintetrahedre **tabTetra,t_binNode **tabNodes,unsigned int &sizeTetra,unsigned int &sizeNodes)
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
		t_FileHeader fileHeader;
		memset(&fileHeader,0,sizeof(t_FileHeader));
		binFile.read((char*)&fileHeader,sizeof(t_FileHeader));
		sizeNodes=fileHeader.quantNodes;
		sizeTetra=fileHeader.quantTetra;
		//*************************
		//Lecture des noeuds
		*tabNodes=new t_binNode[sizeNodes];
		binFile.read((char*)*tabNodes,sizeof(t_binNode)*sizeNodes);
		//*************************
		//Lecture des tetrahèdres
		*tabTetra=new bintetrahedre[sizeTetra];
		binFile.read((char*)*tabTetra,sizeof(bintetrahedre)*sizeTetra);

		binFile.close();
		return true;
	}else{
		return false;
	}
}

 double CMBIN::ComputeVolume(trimeshmodel& trimesh)
 {
	double res=0;
	std::size_t sizeTetra=trimesh.tetrahedres.size();
	for( std::size_t idtetra=0;idtetra<sizeTetra;idtetra++)
	{
		ivec4 isommets((const long *)(trimesh.tetrahedres[idtetra].sommets));
		vec3 sommets[4];
		for(short i=0;i<4;i++)
			sommets[i]=trimesh.nodes[isommets[i]].node;
		res+=CalcTetraVolume(sommets[0],sommets[1],sommets[2],sommets[3]);
	}
	return res;
 }
} //fin namespace
