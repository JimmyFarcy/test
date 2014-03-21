#include "triang_cubic_meshing.hpp"
#include <iostream>
#include <list>


namespace Triangulators
{
	struct weigh_parameters_t
	{
		SpatialDiscretization::weight_t volId;
	};
	inline bool IsOutside( const SpatialDiscretization::weight_t& weightValue,const weigh_parameters_t& weigh_parameters)
	{
		return weightValue!=weigh_parameters.volId;
	}

	void CubicTriangulator::Triangulate(ScalarFieldBuilders::ScalarFieldCreator& inData,const SpatialDiscretization::weight_t& volId, progressOperation& mainProcess)
	{
		/*
		weigh_parameters_t weigh_parameters;
		weigh_parameters.volId=volId;
		BeginFeedingFaces();


		ivec3 coordinates;
		long cellCount(inData.GetDomainSize());
		int nbtri;
		progressOperation thisProcess(&mainProcess,cellCount*cellCount);
		for(coordinates.x=0;coordinates.x<cellCount;coordinates.x++)
		{
			for(coordinates.y=0;coordinates.y<cellCount;coordinates.y++)
			{
				progressOperation thisSubProcess(&thisProcess,1);
				if(inData.ContainsVol(ivec2(coordinates.x,coordinates.y),weigh_parameters.volId))
				{

					for(coordinates.z=0;coordinates.z<cellCount;coordinates.z++)
					{
						//inData.GetCenterCellCoordinates(coordinates+i7)
						//grid.val[2]=WeightEvaluation(inData.GetMatrixValue(coordinates+i2),weigh_parameters);
					}
				}
			}
		}
		FinishFeedingFaces();
		*/
	}
}
