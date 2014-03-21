#include "coreinitialisation.h"

#include "tools/octree44.hpp"
#include "tools/octree44_dotElement.hpp"



class testAlgo
{
public:
	testAlgo(){}
	bool sendCollisionCandidatesMethod(const octreeTool::elementSize& staticCandidateIndex)
	{
		return false;
	}


};




int main(int argc, char* argv[])
{
	/*
	using namespace octreeTool;
	spaceElementContainer myContainer;
	Octree44 MyOctree(myContainer,8);


	dotElement dotTest;
	testAlgo testOctr;
	spaceElement* elementATester=&dotTest;




	typedef testAlgo CallClass;
	CALLBACK_METHOD = NULL;
	sendCollisionCandidatesMethod=&testAlgo::sendCollisionCandidatesMethod;

	/*
	MyOctree.GetDynamicCollisionCandidates<testAlgo>(
		*elementATester,
		&testOctr,
		sendCollisionCandidatesMethod
		);
	MyOctree.GetDynamicCollisionCandidates<testAlgo>(
		*elementATester,
		&testOctr,
		&testAlgo::sendCollisionCandidatesMethod
		);
		*/

	return 0;
}
