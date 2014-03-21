/**
 * @file computations.hpp 
 * @brief Ces m�thodes regroupent les m�thodes permettant l'adaptation d'un mod�le non conforme � tetgen.
 */
#include "input_output/poly.h"
#include "input_output/progressioninfo.h"
#include <tools/octree44.hpp>
#include <tools/octree44_triangleElement.hpp>


#ifndef __MESH_COMPUTATIONS__
#define __MESH_COMPUTATIONS__


class OctreeResult
{
	public:
		OctreeResult(octreeTool::elementSize _exception):exception(_exception){};
	bool DotTriangleCollisionTest(const octreeTool::elementSize& staticCandidateIndex)
	{
		if(exception<staticCandidateIndex)
			results.push_back(staticCandidateIndex);
		return true;
	}
	std::vector<octreeTool::elementSize> results;
	octreeTool::elementSize exception;
};



class meshOperation
{
private:



	unsigned int stat_NbFaceSplitting;
	unsigned int stat_DestroyedFaces;
	unsigned int stat_NbPointsMerged;
	formatPOLY::t_model modelData;
	octreeTool::spaceElementContainer lstFaces;
	octreeTool::Octree44* modelOctree;
	
	int FindFaceWithSommet( const ivec3& sommetsSearch );
	//Retourne -1 si aucun point correspondant
	int FindIndexWithPosition( const vec3& position );
	//return vrai si la division a eu lieu
	//addedFaceOne -1 ou idface (si ins�r�)
	//addedFaceTwo -1 ou idface (si ins�r�)
	bool SplitTriangleByThree( formatPOLY::t_face& triangleToSplit , const int& splitCentre,int* addedFaceOne,int* addedFaceTwo  );

	//return faux si aucun traitement effectu�
	bool OnCollisionDetectedSplitIt( formatPOLY::t_face& triangleOne, formatPOLY::t_face& triangleTwo, const vec3& position );
	bool OnCollisionDetectedDestroyIt( formatPOLY::t_face& triangleOne, formatPOLY::t_face& triangleTwo, const vec3& position );
	void PushNewFace(const formatPOLY::t_face& newFace);
	void ReBuildOctree();
	bool coplanarIntersection(int idface,int idfaceTest);
public:
	meshOperation(const char* polyFileName);
	~meshOperation();

	void mergeVertices();
	/**
	 * Correction d'une erreur dans le mod�le
	 * @return Vrai si le mod�le a �t� modifi� � cause de collision ou de superposition de triangles
	 */
	bool MeshReconstruction();
	/**
	 * Supprime les triangles qui rentrent en intersection
	 */
	bool MeshDestroyIntersectingTriangles();
	/**
	 *  Supprime les faces ayant une aire �gale � 0 m�
	 */
	void DestroyNoAreaFaces();
	//Les faces d�finies dans la structure en tant que faces � tester sont transf�r�es dans la liste des faces standart.
	void TransferUserFaceToGlobalFaces();
	bool MeshDestroyCoplanarFaces();
	void ShowStats();
	void Save(const char* polyFileName);
	bool IsOk();
};


#endif