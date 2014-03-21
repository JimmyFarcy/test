#include "triangulator.hpp"

#ifndef __TRIANGULATOR__MARCHING_CUBE__
#define __TRIANGULATOR__MARCHING_CUBE__

namespace Triangulators
{
	class MarchingCubeTriangulator : public BaseTriangulator
	{
		public:
			MarchingCubeTriangulator():BaseTriangulator() {};
			
			void Triangulate(ScalarFieldBuilders::ScalarFieldCreator& inData,const SpatialDiscretization::weight_t& volId, progressOperation& mainProcess);
	};
}

#endif