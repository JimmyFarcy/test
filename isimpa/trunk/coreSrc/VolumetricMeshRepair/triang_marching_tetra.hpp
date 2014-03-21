#include "triangulator.hpp"

#ifndef __TRIANGULATOR__MARCHING_TETRA__
#define __TRIANGULATOR__MARCHING_TETRA__

namespace Triangulators
{
	class MarchingTetraTriangulator : BaseTriangulator
	{
		public:
			MarchingTetraTriangulator():BaseTriangulator() {};
			
			void Triangulate(ScalarFieldBuilders::ScalarFieldCreator& inData);
	};
}

#endif