/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44_sphereElement.hpp"

#include <math.h>

namespace octreeTool
{

	#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
	#define SUB(dest,v1,v2) \
			  dest[0]=v1[0]-v2[0]; \
			  dest[1]=v1[1]-v2[1]; \
			  dest[2]=v1[2]-v2[2];
	#define ADD(dest,v1,v2) \
			  dest[0]=v1[0]+v2[0]; \
			  dest[1]=v1[1]+v2[1]; \
			  dest[2]=v1[2]+v2[2];

	////////////////////////////////////////////////////////////////////////////////////////////////
	//// Implémentation de triangleElement
	////////////////////////////////////////////////////////////////////////////////////////////////

	sphereElement::sphereElement(const coordPrecision position[3],const coordPrecision& _radius)

	{
		Set(position);
		SetRadius(_radius);
	}
	sphereElement::sphereElement()
	{
		SETVEC(0,CoordPosition);
		radius=1.;
	}
	void sphereElement::Set(const coordPrecision position[3])
	{
		COPYVEC(position,CoordPosition);
	}

	void sphereElement::SetRadius(const coordPrecision& _radius)
	{
		radius=_radius;
	}

	coordPrecision sphereElement::GetPositionX( )
	{
		return CoordPosition[0];
	}
	coordPrecision sphereElement::GetPositionY( )
	{
		return CoordPosition[1];
	}
	coordPrecision sphereElement::GetPositionZ( )
	{
		return CoordPosition[2];
	}
	coordPrecision sphereElement::GetRadius( )
	{
		return radius;
	}
	bool sphereElement::IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize)
	{

		//Test X Y Z
		if(fabs(boxcenter[0]-CoordPosition[0])>boxhalfsize+radius)
			return false;
		if(fabs(boxcenter[1]-CoordPosition[1])>boxhalfsize+radius)
			return false;
		if(fabs(boxcenter[2]-CoordPosition[2])>boxhalfsize+radius)
			return false;
		return true;

		/*
		//Calcul de la longueur entre boxcenter et CoordPosition
		coordPrecision BS[3];
		SUB(BS,boxcenter,CoordPosition);
		coordPrecision length=sqrtf(DOT(BS,BS));

		if(length>boxhalfsize+radius)
			return false;
		return true;
		*/
	}
	void sphereElement::GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3])
	{
		coordPrecision tmp[3];
		SETVEC(radius,tmp)
		SUB(xyzMin,CoordPosition,tmp);
		ADD(xyzMax,CoordPosition,tmp);
	}

}
