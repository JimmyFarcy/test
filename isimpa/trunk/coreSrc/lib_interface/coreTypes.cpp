#include "coreTypes.h"
#include "input_output/importExportMaillage/mbin.h"
#include <iostream>

//////////////////////////////////////////
// t_Recepteur_P

t_Recepteur_P::t_Recepteur_P(uentier _nbfreq,	uentier _nbtimestep)
	:nbfreq(_nbfreq),nbtimestep(_nbtimestep)
{

	bruit_spectre=new t_Bruit_Freq[nbfreq];
	energy_sum=new l_decimal*[nbfreq];
	memset(energy_sum,0,sizeof(l_decimal*)*nbfreq);
	memset(bruit_spectre,0,sizeof(t_Bruit_Freq)*nbfreq);
};
t_Recepteur_P::~t_Recepteur_P()
{
	for(unsigned int idfreq=0;idfreq<nbfreq;idfreq++)
		delete[] energy_sum[idfreq];
	delete[] energy_sum;
	delete[] bruit_spectre;
}
void t_Recepteur_P::InitFreq(uentier idfreq)
{
	energy_sum[idfreq]=new l_decimal[nbtimestep];
	memset(energy_sum[idfreq],0,sizeof(l_decimal)*nbtimestep);
}

//////////////////////////////////////////
// r_Surf_Face


r_Surf_Face::r_Surf_Face()
{
	energieRecu=NULL;
	nbfreq=0;
	nbtimestep=0;
}

r_Surf_Face::~r_Surf_Face()
{
	deleteData();
}

void r_Surf_Face::deleteData()
{
	if(energieRecu && nbfreq>0)
	{
		for(uentier idfreq=0;idfreq<nbfreq;idfreq++)
			delete[] energieRecu[idfreq];
	}
	delete[] energieRecu;
	energieRecu=NULL;
}
void r_Surf_Face::InitTabFreq(uentier _nbfreq)
{
	deleteData();
	nbfreq=_nbfreq;
	energieRecu=new decimal*[nbfreq];
	memset(energieRecu,0,sizeof( decimal*)*nbfreq);
}
void r_Surf_Face::InitFreq(uentier idfreq, uentier _nbtimestep)
{
	nbtimestep=_nbtimestep;
	if(nbfreq>idfreq)
	{
		delete[] energieRecu[idfreq];
		energieRecu[idfreq]=new decimal[_nbtimestep];
		memset(energieRecu[idfreq],0,sizeof(decimal)*_nbtimestep);
	}
}

void r_Surf_Face::operator=(const r_Surf_Face& copyFrom)
{
	this->indiceSommets=copyFrom.indiceSommets;
	memcpy(this->sommets,copyFrom.sommets,sizeof(vec3)*3);
	this->InitTabFreq(copyFrom.nbfreq);
	for(uentier idfreq=0;idfreq<nbfreq;idfreq++)
	{
		if(copyFrom.energieRecu[idfreq])
		{
			this->InitFreq(idfreq,copyFrom.nbtimestep);
			memcpy(energieRecu[idfreq],copyFrom.energieRecu[idfreq],sizeof(decimal)*copyFrom.nbtimestep);
		}
	}
}
//////////////////////////////////////////
// r_Surf

r_Surf::r_Surf()
{
	faces=NULL;
	nbFaces=0;
	idRecepteurS=-1;
}


r_Surf::r_Surf(r_Surf& copyFrom)
{
	idRecepteurS=copyFrom.idRecepteurS;
	nbFaces=copyFrom.nbFaces;

	//Cr�ation � partir d'une copie
	if(copyFrom.nbFaces==0)
	{
		faces=NULL;
	}else{
		faces=new r_Surf_Face[nbFaces];
		for(uentier idface=0;idface<nbFaces;idface++)
		{
			faces[idface]=copyFrom.faces[idface];
		}
	}
}

r_Surf::~r_Surf()
{
	delete[] faces;
}

void r_Surf::InitFaces(uentier _nbFaces, uentier _nbfreq)
{
	nbFaces=_nbFaces;
	delete[] faces;
	faces=new r_Surf_Face[nbFaces];
	for(uentier idface=0;idface<nbFaces;idface++)
	{
		faces[idface].InitTabFreq(_nbfreq);
	}
}




//////////////////////////////////////////
// t_TetraMesh


bool t_TetraMesh::LoadFile(const char * fileName, t_Mesh &sceneMesh,uentier nbFreq)
{

	delete[] nodes;
	delete[] tetraedres;
	nodes=NULL;
	tetraedres=NULL;

	using namespace formatMBIN;
	bintetrahedre* tabtetra;
	t_binNode* tabNodes;

	CMBIN binImporter;
	unsigned int binsizeTetra=0;
	unsigned int binsizeNodes=0;

	binImporter.ImportBIN(fileName,&tabtetra,&tabNodes,binsizeTetra,binsizeNodes);

	if(binsizeTetra>0 && binsizeNodes>0)
	{
		this->nodesSize=binsizeNodes;
		//Copie des noeuds
		nodes=new vec3[nodesSize];
		memcpy(nodes,tabNodes,sizeof(vec3)*nodesSize);
		//Copie des tetrah�dres
		tetraedres=new t_Tetra[binsizeTetra];
		tetraedresSize=binsizeTetra;

		for(unsigned int idTetra=0;idTetra<binsizeTetra;idTetra++)
		{
			tetraedres[idTetra].index=idTetra;
			tetraedres[idTetra].idVolume=tabtetra[idTetra].idVolume;
			//Copie des sommets
			memcpy(&tetraedres[idTetra].sommets,&tabtetra[idTetra].sommets,sizeof(ivec4));
			tetraedres[idTetra].g=GetGTetra(nodes[tetraedres[idTetra].sommets.a],nodes[tetraedres[idTetra].sommets.b],nodes[tetraedres[idTetra].sommets.c],nodes[tetraedres[idTetra].sommets.d]);
			for(int idFace=0;idFace<4;idFace++)
			{
				if(tabtetra[idTetra].tetrafaces[idFace].marker>=0)
				{
					tetraedres[idTetra].faces[idFace].face_scene=&sceneMesh.pfaces[tabtetra[idTetra].tetrafaces[idFace].marker];
				}
				memcpy(&tetraedres[idTetra].faces[idFace].indiceSommets,&tabtetra[idTetra].tetrafaces[idFace].sommets,sizeof(ivec3));
				if(tabtetra[idTetra].tetrafaces[idFace].neighboor>=0)
					tetraedres[idTetra].voisins[idFace]=&tetraedres[tabtetra[idTetra].tetrafaces[idFace].neighboor];
				ivec3 cFaceSommets=tetraedres[idTetra].faces[idFace].indiceSommets;
				tetraedres[idTetra].faces[idFace].normal=FaceNormal(nodes[cFaceSommets.a],nodes[cFaceSommets.b],nodes[cFaceSommets.c]);
			}
		}

		delete[] tabtetra;
		delete[] tabNodes;
		return true;
	}else{
		std::cout<<fileName<<std::endl<<_("Tetrahedalization file is empty, the calculation can't be done !")<<std::endl;
		return false;
	}
}




const char* translate( const char* strToTranslate)
{

	return strToTranslate;
}
