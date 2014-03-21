/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44.hpp"
/**
 * @file octree44_sphereElement.hpp Implémentation de l'élément de type sphérique
 */

#ifndef __OCTREE44_SPHEREELEMENT_H__
#define __OCTREE44_SPHEREELEMENT_H__

namespace octreeTool
{
	/**
	 * @brief Element de type sphere
	 */
	class sphereElement : public spaceElement
	{
		public:
			sphereElement(const coordPrecision position[3],const coordPrecision& _radius);
			sphereElement( );

			coordPrecision GetPositionX( );
			coordPrecision GetPositionY( );
			coordPrecision GetPositionZ( );
			coordPrecision GetRadius( );
			virtual ~sphereElement() {};
			virtual bool IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize);
			virtual void GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3]);
			void Set(const coordPrecision position[3]);
			void SetRadius(const coordPrecision& _radius);
	protected:
			coordPrecision CoordPosition[3];
			coordPrecision radius;
	};
}

#endif
