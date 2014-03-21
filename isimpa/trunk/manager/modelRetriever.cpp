#include "modelRetriever.hpp"
#include <tools/octree44_triangleElement.hpp>
#include <tools/octree44_dotElement.hpp>
#include <tools/octree44_sphereElement.hpp>
#include <Core/mathlib.h>
#include "last_cpp_include.hpp"


class DotTriangleTest
{

public:
	DotTriangleTest(octreeTool::coordPrecision _dot[3],octreeTool::spaceElementContainer* _faces,const float& _epsilon)
		:epsilon(_epsilon),foundDist(2*_epsilon)
	{
		isCandidatesIncludeDot=false;
		COPYVEC(_dot,dot);
		faces=_faces;
	}
	bool CheckCandidate(const octreeTool::elementSize& staticCandidateIndex)
	{
		float ecart=0;
		using namespace octreeTool;
		triangleElement* candidate=dynamic_cast<triangleElement*>(faces->at(staticCandidateIndex));
		if(candidate) //Si le candidat est bien un triangle
		{
			float dist=ClosestDistanceBetweenDotAndTriangle(vec3(candidate->GetSommetX(0),candidate->GetSommetY(0),candidate->GetSommetZ(0)),
				vec3(candidate->GetSommetX(1),candidate->GetSommetY(1),candidate->GetSommetZ(1)),
				vec3(candidate->GetSommetX(2),candidate->GetSommetY(2),candidate->GetSommetZ(2)),
				dot,NULL,NULL);
			/*
			if(DotIsInVertex(dot,vec3(candidate->GetSommetX(0),candidate->GetSommetY(0),candidate->GetSommetZ(0)),
				vec3(candidate->GetSommetX(1),candidate->GetSommetY(1),candidate->GetSommetZ(1)),
				vec3(candidate->GetSommetX(2),candidate->GetSommetY(2),candidate->GetSommetZ(2)),
				&ecart) && ecart<BARELY_EPSILON)
				*/
			if(dist<epsilon)
			{
				if(dist<foundDist)
					foundDist=dist;
				isCandidatesIncludeDot=true;
				//return false; On continue pour trouver la distance la plus proche
			}
		}
		return true;
	}
	bool dotIsInGroup(float& distance)
	{
		distance=foundDist;
		return isCandidatesIncludeDot;
	}
private:
	bool isCandidatesIncludeDot;
	float epsilon;
	float foundDist;
	octreeTool::coordPrecision dot[3];
	octreeTool::spaceElementContainer* faces;
};


ModelRetriever::ModelRetriever()
{
	//1er groupe
	groupes.push_back(groupe_octree());
}

void ModelRetriever::AddFace(octreeTool::coordPrecision sommetA[3],octreeTool::coordPrecision sommetB[3],octreeTool::coordPrecision sommetC[3])
{
	using namespace octreeTool;
	groupes.rbegin()->faces.push_back(new triangleElement(sommetA,sommetB,sommetC));
}
int ModelRetriever::CloseGroup()
{
	groupes.rbegin()->octreeModel=new octreeTool::Octree44(groupes.rbegin()->faces,6);
	groupes.push_back(groupe_octree());
	return groupes.size()-2;
}

void ModelRetriever::GetGroupByDotCoord(octreeTool::coordPrecision dot[3],std::vector<octreeTool::elementSize>& outputGroupIndices,std::vector<float>& outputDistance,const float& epsilon)
{
	//Pour chaque groupe on lance un test de collision point->triangle
	using namespace octreeTool;
	using namespace std;
	sphereElement dotEl(dot,epsilon);
	spaceElement* testElement=&dotEl;
	ModelRetrieverIterator groupIterator;
	elementSize idgroupe=0;
	float distance;
	for( groupIterator = groupes.begin(); groupIterator != groupes.end(); groupIterator++ )
	{
		if(groupIterator->octreeModel)
		{
			DotTriangleTest collisionManager(dot,&(groupIterator->faces),epsilon);
			groupIterator->octreeModel->GetDynamicCollisionCandidates<DotTriangleTest>(*testElement,&collisionManager,&DotTriangleTest::CheckCandidate);
			if(collisionManager.dotIsInGroup(distance))
			{
				outputGroupIndices.push_back(idgroupe);
				outputDistance.push_back(distance);
			}
		}
		idgroupe++;
	}
}

