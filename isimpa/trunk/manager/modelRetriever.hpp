#include "first_header_include.hpp"

/**
 * @file modelRetriever.hpp
 * @brief Cette classe permet d'associer les faces d'un ancien modèle avec les faces d'un nouveau modèle
 */

#include <tools/octree44.hpp> //Optimisation de la recherche de faces
#include <list>


#ifndef __TOOLS_MODEL_RETRIEVER

/**
 *
 * On définit plusieurs groupes et pour chaque groupe on insère plusieurs faces
 */

class ModelRetriever
{

private:
	struct groupe_octree
	{
		groupe_octree()
		{
			octreeModel=NULL;
		}
		~groupe_octree()
		{
			delete octreeModel;
			for(octreeTool::elementSize idface=0;idface<faces.size();idface++)
				delete faces[idface];
		}
		octreeTool::spaceElementContainer faces;
		octreeTool::Octree44* octreeModel;
	};
	
	typedef std::list<groupe_octree> ModelRetrieverVector;
	typedef ModelRetrieverVector::iterator ModelRetrieverIterator;
	ModelRetrieverVector groupes;
public:

	ModelRetriever();

	void AddFace(octreeTool::coordPrecision sommetA[3],octreeTool::coordPrecision sommetB[3],octreeTool::coordPrecision sommetC[3]);
	int CloseGroup();
	/**
	 * Donne la liste des groupes correspondant aux surfaces les plus proches de dot
	 * @param epsilon Distance maximale des surfaces d'origine
	 */
	void GetGroupByDotCoord(octreeTool::coordPrecision dot[3],std::vector<octreeTool::elementSize>& outputGroupIndices,std::vector<float>& outputDistance,const float& epsilon);
};

#endif