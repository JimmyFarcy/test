#include "triangulator.hpp"

#ifndef __TRIANGULATOR__CUBIC_MESHING__
#define __TRIANGULATOR__CUBIC_MESHING__

namespace Triangulators
{
	class CubicTriangulator : public BaseTriangulator
	{
		public:
			CubicTriangulator():BaseTriangulator() {};
			
			void Triangulate(ScalarFieldBuilders::ScalarFieldCreator& inData,const SpatialDiscretization::weight_t& volId, progressOperation& mainProcess);
	};
}

#endif