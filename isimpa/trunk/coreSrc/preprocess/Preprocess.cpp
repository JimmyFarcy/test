// Preprocess.cpp : définit le point d'entrée pour l'application console.
//
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

#include "computations.hpp"
#include <string>
#include <iostream>
#include "coreString.h"
#define MESH_CORRECTION_MAX 100

int MainProcess(int argc, char* argv[])
{
	progressionInfo progressManager(3);
	using namespace std;
	//**************************************************
	//Verification des arguments
	string pathFichier;
	if(argc>1)
	{
		pathFichier.append(argv[1]);
		for(int idarg=2;idarg<argc;idarg++)
		{
			pathFichier.append(" ");
			pathFichier.append(argv[idarg]);
		}
	}else{
		cout<<"The path of the mesh file must be specified !"<<endl;
		return 1;
	}


	meshOperation operationClass(pathFichier.c_str());
	if(!operationClass.IsOk())
	{
		cout<<"The mesh file cant be found !"<<endl;
		return 1;
	}
	int repairTries=0;

	////////////////////////////////////////////
	// Fusion des sommets proches
	progressOperation* progressOp=new progressOperation(progressManager.GetMainOperation());
	operationClass.DestroyNoAreaFaces();
	operationClass.mergeVertices();
	progressManager.OutputCurrentProgression();
	delete progressOp;
	//////////////////////////////////////////
	// Suppression des faces coplanaires
	while(operationClass.MeshDestroyCoplanarFaces() && repairTries<=MESH_CORRECTION_MAX)
	{
		repairTries++;
	}
	

	if(repairTries<MESH_CORRECTION_MAX)
	{
		operationClass.TransferUserFaceToGlobalFaces();
		#ifndef _DEBUG
			operationClass.Save(pathFichier.c_str());
		#endif
	}

#ifdef _DEBUG
	CoreString nameFile;
	nameFile="merged_"+pathFichier;
	operationClass.Save(nameFile.c_str());
#endif
	std::cout<<"Coplanar correction step and vertices merging step has finished."<<std::endl;
	repairTries=0;



	while(operationClass.MeshReconstruction() && repairTries<=MESH_CORRECTION_MAX)
	{
		#ifdef _DEBUG
			nameFile="step_"+CoreString::FromInt(repairTries)+"_"+pathFichier;
			operationClass.Save(nameFile.c_str());
		#endif
		repairTries++;
	}

	/*
	std::cout<<"Suppression des faces en intersection en cours."<<std::endl;
	while(operationClass.MeshDestroyIntersectingTriangles() && repairTries<=MESH_CORRECTION_MAX)
	{
		std::cout<<"Redemmarage."<<std::endl;
		#ifdef _DEBUG
			nameFile="step_"+CoreString::FromInt(repairTries)+"_"+pathFichier;
			operationClass.Save(nameFile.c_str());
		#endif
		repairTries++;
	}
	*/

	if(repairTries<MESH_CORRECTION_MAX)
	{
	    operationClass.ShowStats();
		#ifndef _DEBUG
			operationClass.Save(pathFichier.c_str());
		#else
			operationClass.Save("final_step.poly"); 
			char c;
			cin >> c;
		#endif
	}else{
				std::cout<<"Mesh reparation has been aborted. The algorithm enter into an infinite loop. Try to stick coplanar faces or destroy manually."<<std::endl;
	}

	return 0;
}


int main(int argc, char* argv[])
{
	MainProcess(argc,argv);

	#ifdef _DEBUG
		_CrtDumpMemoryLeaks(); //Affiche les fuites mémoires
	#endif

	return 0;
}