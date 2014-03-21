#include "bin.h"
#include "Core/mathlib.h"

namespace formatCoreBIN
{
	//Types du fichier
	typedef unsigned short bShort;
	typedef uint32_t bInt;
	typedef int32_t bsInt;
	typedef char bString;
	typedef float bFloat;
	typedef uint32_t bLong;
	typedef bool bBool;
	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryNode {
		bShort nodeType;
		bLong firtSon;
		bLong nextBrother;
	};

	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryVertices {
		bLong nbVertex;
	};

	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryVertex {
		bFloat x;
		bFloat y;
		bFloat z;
	};

	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryGroup {
		bString groupName[255];
		bInt nbFace;
	};

	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryFace {
		bInt a;
		bInt b;
		bInt c;
		bInt idMaterial;	/*!< Identifiant du mat�riau associ� � la face */
		bsInt idRs;			/*!< Identifiant du r�cepteur surfacique (aucun -1) */
		bsInt idEn;			/*!< Identifiant de l'encombrement (aucun -1)*/
	};

	/*!
	 *	\brief Cette structure d�finit une section de donn�es du fichier Binaire
	 */
	struct binaryHeader{
		bInt majorVersion; //Version du format
		bInt minorVersion;
	};

	CformatBIN::CformatBIN()
	{

	}

	CformatBIN::~CformatBIN()
	{

	}

    bool CformatBIN::ImportBIN(ioModel &modelImport, const char *strFileName)
	{

		using namespace std;
		char strMessage[255] = {0};
		fstream binFile (strFileName, ios::in | ios::binary);
		if(!binFile.is_open())
			return false;

		binaryHeader enteteFichier;
		binFile.read((char*)&enteteFichier, sizeof (binaryHeader));
		//La version du format se trouve dans enteteFichier

		this->ProcessNode(binFile,modelImport);


		binFile.close();
		return true;
	}

	bool CformatBIN::ExportBIN(const char *strFileName ,ioModel &modelImport)
	{
		//Namespace
		using namespace std;
		//Initialisations
		unsigned long nbVertex=modelImport.vertices.size();

		//Declarations
		unsigned long sizeVERTICES=(nbVertex*sizeof(binaryVertex))+sizeof(binaryNode)+sizeof(binaryVertices);
		//Sauvegarde du mod�le 3D
		fstream binFile (strFileName, ios::out | ios::binary);

		//*************************
		//Ecriture de l'entete du fichier
		binaryHeader fileHeader;
		fileHeader.majorVersion=1;
		fileHeader.minorVersion=0;
		binFile.write((char*)&fileHeader,sizeof(binaryHeader));

		//*************************
		//Ecriture du noeud VERTICE
		binaryVertices verticeGroup={0};
		//Compte le nombre de vertex
		verticeGroup.nbVertex=nbVertex;
		this->writeNode(binFile,NODE_TYPE_VERTICES,0,sizeVERTICES);
		binFile.write((char*)&verticeGroup,sizeof(binaryVertices));
		//Ecriture des vertices
		for(unsigned long v=0; v < nbVertex; v++)
		{
			binaryVertex currentVertex={modelImport.vertices[v][0],modelImport.vertices[v][1],modelImport.vertices[v][2]};
			binFile.write((char*)&currentVertex,sizeof(binaryVertex));
		}

		//*************************
		//Ecriture du noeud GROUP

		binaryGroup groupNode;
		groupNode.nbFace=modelImport.faces.size();
		//Calcul de la taille du groupe en octets
		unsigned long sizeGROUP=0;
		//Ecriture dans le fichier
		this->writeNode(binFile,NODE_TYPE_GROUP,0,sizeGROUP);
		binFile.write((char*)&groupNode,sizeof(binaryGroup));
		for(unsigned long f=0; f < groupNode.nbFace ;f++)
		{
			binaryFace faceElement;
			faceElement.a=modelImport.faces[f].a;
			faceElement.b=modelImport.faces[f].b;
			faceElement.c=modelImport.faces[f].c;
			faceElement.idRs=modelImport.faces[f].idRs;
			faceElement.idEn=modelImport.faces[f].idEn;
			faceElement.idMaterial=modelImport.faces[f].idMat;
			binFile.write((char*)&faceElement,sizeof(binaryFace));
		}

		binFile.close();

		return true;

	}

	float CformatBIN::GetSurfAire( const ioModel& model, const int& indiceface )
	{
		ivec3 sommets(model.faces[indiceface].a,model.faces[indiceface].b,model.faces[indiceface].c);
		return GetAireTriangle(model.vertices[sommets.a].v,(float*)model.vertices[sommets.b].v,(float*)model.vertices[sommets.c].v);
	}
	bool CformatBIN::ProcessNode(std::fstream &binFile,ioModel &modelImport)
	{ //Lecture d'un noeud du fichier binaire
		binaryNode elementNode;
		elementNode.nextBrother=1;
		while(!binFile.eof() && elementNode.nextBrother!=0)
		{
			binFile.read((char*)&elementNode, sizeof (binaryNode));
			switch(elementNode.nodeType)
			{
				case NODE_TYPE_VERTICES:
					this->ProcessNodeVertices(binFile,modelImport);
					break;
				case NODE_TYPE_GROUP:
					this->ProcessNodeGroup(binFile,modelImport);
					break;
				default:
					return false;
					break;
			}
			if(elementNode.nextBrother!=0)
				binFile.seekg(elementNode.nextBrother);
		}

		return true;
	}

	bool CformatBIN::ProcessNodeVertices(std::fstream &binFile,ioModel &modelImport)
	{
		binaryVertices elementNode={0};
		binaryVertex vertexElement;
		if(!binFile.is_open() || binFile.eof())
			return false;
		binFile.read((char*)&elementNode, sizeof (binaryVertices));
		modelImport.vertices.reserve(elementNode.nbVertex);
		for(unsigned long v=0;v<elementNode.nbVertex;v++)
		{
			binFile.read((char*)&vertexElement, sizeof (binaryVertex));
			modelImport.vertices.push_back(t_pos(vertexElement.x,vertexElement.y,vertexElement.z));
		}
		return true;
	}

	bool CformatBIN::ProcessNodeGroup(std::fstream &binFile,ioModel &modelImport)
	{
		binaryGroup elementNode;
		binaryFace faceElement;
		if(!binFile.is_open() || binFile.eof())
			return false;
		binFile.read((char*)&elementNode, sizeof (binaryGroup));
		modelImport.faces.reserve(elementNode.nbFace);

		for(unsigned long f=0;f<elementNode.nbFace;f++)
		{
			binFile.read((char*)&faceElement, sizeof (binaryFace));
			ioFace nvFace;
			nvFace.a=faceElement.a;
			nvFace.b=faceElement.b;
			nvFace.c=faceElement.c;
			nvFace.idMat=faceElement.idMaterial;
			nvFace.idRs=faceElement.idRs;
			nvFace.idEn=faceElement.idEn;
			modelImport.faces.push_back(nvFace);
		}
		return true;
	}

	void CformatBIN::writeNode(std::fstream &binFile,CformatBIN::NODE_TYPE nodeType,std::size_t nodeHeadSize,std::size_t nodeSize)
	{
		binaryNode currentNode;
		currentNode.nodeType=nodeType;
		currentNode.firtSon=(long)binFile.tellp()+nodeHeadSize;
		currentNode.nextBrother=(long)binFile.tellp()+nodeSize;
		if(nodeHeadSize==0)
			currentNode.firtSon=0;
		if(nodeSize==0)
			currentNode.nextBrother=0;
		binFile.write((char*)&currentNode,sizeof(binaryNode));
	}

}
