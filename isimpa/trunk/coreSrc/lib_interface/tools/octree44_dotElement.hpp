/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44.hpp"


#ifndef __OCTREE44_DOTELEMENT_H__
#define __OCTREE44_DOTELEMENT_H__

namespace octreeTool
{
	/**
	 * @brief Element de type triangle
	 */
	class dotElement : public spaceElement
	{
		public:
			dotElement(coordPrecision position[3]);
			dotElement( );

			coordPrecision GetPositionX( );
			coordPrecision GetPositionY( );
			coordPrecision GetPositionZ( );
			virtual ~dotElement() {};
			virtual bool IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize);
			virtual void GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3]);
			void Set(coordPrecision position[3]);
	protected:
			coordPrecision CoordPosition[3];

	};
}

#endif
