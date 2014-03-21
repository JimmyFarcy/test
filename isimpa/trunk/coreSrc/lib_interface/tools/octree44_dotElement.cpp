/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44_dotElement.hpp"

#include <math.h>

namespace octreeTool
{


	////////////////////////////////////////////////////////////////////////////////////////////////
	//// Implémentation de triangleElement
	////////////////////////////////////////////////////////////////////////////////////////////////

	dotElement::dotElement(coordPrecision position[3])

	{
		Set(position);
	}
	void dotElement::Set(coordPrecision position[3])
	{
		COPYVEC(position,CoordPosition);
	}

	coordPrecision dotElement::GetPositionX( )
	{
		return CoordPosition[0];
	}
	coordPrecision dotElement::GetPositionY( )
	{
		return CoordPosition[1];
	}
	coordPrecision dotElement::GetPositionZ( )
	{
		return CoordPosition[2];
	}
	bool dotElement::IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize)
	{
		//Test X Y Z
		if(fabs(boxcenter[0]-CoordPosition[0])>boxhalfsize)
			return false;
		if(fabs(boxcenter[1]-CoordPosition[1])>boxhalfsize)
			return false;
		if(fabs(boxcenter[2]-CoordPosition[2])>boxhalfsize)
			return false;
		return true;
	}
	void dotElement::GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3])
	{
		COPYVEC(CoordPosition,xyzMin);
		COPYVEC(CoordPosition,xyzMax);
	}
}
