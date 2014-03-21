#include "adaptative_mesh_guide.hpp"
#include <tools/octree44_triangleElement.hpp>
#include <tools/octree44_sphereElement.hpp>
#include <map>
#include <utility>


namespace Triangulators
{

	#ifndef MIN
		#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
	#endif
	#ifndef MAX
		#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
	#endif

	#ifndef MINREF
		#define MINREF(a, b)  if(a>b) a=b;
	#endif
	#ifndef MAXREF
		#define MAXREF(a, b)  if(a<b) a=b;
	#endif
	#ifndef MINVEC
		#define MINVEC(av, bv)  MINREF(av[0],bv[0]);MINREF(av[1],bv[1]);MINREF(av[2],bv[2]);
	#endif
	#ifndef MAXVEC
		#define MAXVEC(av, bv)  MAXREF(av[0],bv[0]);MAXREF(av[1],bv[1]);MAXREF(av[2],bv[2]);
	#endif

	struct tri_t
	{
		tri_t(const vec3& _A,const vec3& _B,const vec3& _C)
			:A(_A),B(_B),C(_C)
		{}
		tri_t(){}
		vec3 A;
		vec3 B;
		vec3 C;
	};

	typedef PTR<tri_t> tri_ptr_t;
	typedef std::multimap<std::size_t,tri_ptr_t> trianglesMap_t;
	typedef trianglesMap_t::iterator trianglesMap_iterator_t;
	typedef std::pair<std::size_t,tri_ptr_t> trianglesMap_pair_t;

	struct AdaptativeMeshGuide::AdaptativeMeshGuideData_t
	{
		AdaptativeMeshGuideData_t()
		{

		}
		trianglesMap_t trianglesMap;
		PTR<octreeTool::Octree44> octreeSpace;
		vec3 minBox;
		vec3 maxBox;
	};

	AdaptativeMeshGuide::AdaptativeMeshGuide()
		:AdaptativeMeshGuideData(shared_ptr_data(new AdaptativeMeshGuideData_t))
	{


	}

	void AdaptativeMeshGuide::EndTriangleFeeding(const unsigned short maxDepth)
	{
		using namespace octreeTool;
		//
		this->AdaptativeMeshGuideData->octreeSpace=PTR<octreeTool::Octree44>(new octreeTool::Octree44(this->AdaptativeMeshGuideData->minBox,this->AdaptativeMeshGuideData->maxBox));
		for(trianglesMap_iterator_t mapit=this->AdaptativeMeshGuideData->trianglesMap.begin();mapit!=this->AdaptativeMeshGuideData->trianglesMap.end();mapit++)
		{
			tri_t& srcTri=*mapit->second.get();
			octreeTool::triangleElement newTri(srcTri.A,srcTri.B,srcTri.C);
			this->AdaptativeMeshGuideData->octreeSpace->PushNewSpaceElement(&newTri,mapit->first,maxDepth);
		}
	}


	void AdaptativeMeshGuide::AddTri(const vec3& A,const vec3& B,const vec3& C)
	{
		std::size_t idObject=this->AdaptativeMeshGuideData->trianglesMap.size();
		if(idObject==0)
			this->AdaptativeMeshGuideData->maxBox=this->AdaptativeMeshGuideData->minBox=A;

		MAXVEC(this->AdaptativeMeshGuideData->maxBox,A);
		MINVEC(this->AdaptativeMeshGuideData->minBox,A);
		MAXVEC(this->AdaptativeMeshGuideData->maxBox,B);
		MINVEC(this->AdaptativeMeshGuideData->minBox,B);
		MAXVEC(this->AdaptativeMeshGuideData->maxBox,C);
		MINVEC(this->AdaptativeMeshGuideData->minBox,C);
		this->AdaptativeMeshGuideData->trianglesMap.insert(trianglesMap_pair_t(idObject,tri_ptr_t(new tri_t(A,B,C))));
	}
	struct ClosestPointResult_t
	{
		decimal distance;
		vec3 position;
	};
	bool ClosestSortPredicate(const Candidate_t& left,const Candidate_t& right)
	{
		return left.first<right.first;
	}
	void AdaptativeMeshGuide::SortByDistance(ClosestCandidates_t& foundPositions)
	{
		foundPositions.sort(ClosestSortPredicate);
		//std::sort(foundPositions.begin(),foundPositions.end(),&ClosestSortPredicate);

	}

	bool AdaptativeMeshGuide::GetClosestPoint(const vec3& OriginPoint,const decimal& maxDist,ClosestCandidates_t& foundPositions)
	{
		using namespace octreeTool;
		sphereElement testZone(OriginPoint,maxDist);
		std::vector<elementSize> candidates;
		this->AdaptativeMeshGuideData->octreeSpace->GetAllCollisionCandidates(testZone,candidates);
		bool foundSomething(false);
		for(std::vector<elementSize>::iterator itCandidates=candidates.begin();itCandidates!=candidates.end();itCandidates++)
		{
			trianglesMap_iterator_t tri_it=this->AdaptativeMeshGuideData->trianglesMap.find(*itCandidates);
			if(tri_it!=this->AdaptativeMeshGuideData->trianglesMap.end())
			{
				decimal pfs;
				decimal pft;
				decimal distance;
				tri_t& curTriangle(*(tri_it->second.get()));
				distance=ClosestDistanceBetweenDotAndTriangle(curTriangle.A,
					curTriangle.B,
					curTriangle.C,
					OriginPoint,
					&pfs,&pft);
				if(distance<maxDist)
				{
					foundSomething=true;
					vec3 position=curTriangle.A+(curTriangle.B-curTriangle.A)*pfs+(curTriangle.C-curTriangle.A)*pft;
					foundPositions.push_back(Candidate_t(distance,position));
				}
			}
		}

		#ifdef _DEBUG
		if(!foundSomething)
			printf("rejeté ! \n");
		#endif
		return foundSomething;
	}

	/*
	bool AdaptativeMeshGuide::GetClosestPoint(const vec3& OriginPoint,const decimal& maxDist,ClosestCandidates_t& foundPositions)
	{
		bool foundSomething(false);

		//for(std::vector<elementSize>::iterator itCandidates=candidates.begin();itCandidates!=candidates.end();itCandidates++)
		for(trianglesMap_iterator_t tri_it=this->AdaptativeMeshGuideData->trianglesMap.begin();tri_it!=this->AdaptativeMeshGuideData->trianglesMap.end();tri_it++)
		{
			//trianglesMap_iterator_t tri_it=this->AdaptativeMeshGuideData->trianglesMap.find(*itCandidates);
			if(tri_it!=this->AdaptativeMeshGuideData->trianglesMap.end())
			{
				decimal pfs;
				decimal pft;
				decimal distance;
				tri_t& curTriangle(*(tri_it->second.get()));
				distance=ClosestDistanceBetweenDotAndTriangle(curTriangle.A,
					curTriangle.B,
					curTriangle.C,
					OriginPoint,
					&pfs,&pft);
				if(distance<maxDist)
				{
					foundSomething=true;
					vec3 position=curTriangle.A+(curTriangle.B-curTriangle.A)*pfs+(curTriangle.C-curTriangle.A)*pft;
					foundPositions.push_back(Candidate_t(distance,position));
				}
			}
		}

		#ifdef _DEBUG
		if(!foundSomething)
			printf("rejeté ! \n");
		#endif
		return foundSomething;
	}
	*/
};
