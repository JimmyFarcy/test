/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44.hpp"


#ifndef __OCTREE44_TRIELEMENT_H__
#define __OCTREE44_TRIELEMENT_H__
/**
 * Indique si un triangle et un cube se superpose
 * @param[in] boxcenter Centre de la boite
 * @param[out] boxhalfsize Dimension de la moitiée de la boite
 * @param[out] triverts Position des sommets des triangles
 * @return 0 si aucun contact, 1 si il y a une superposition
 */
namespace boxtri_test
{
	int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);
}
namespace octreeTool
{
	/**
	 * @brief Element de type triangle
	 */
	class triangleElement : public spaceElement
	{
		public:
			triangleElement(const coordPrecision sommetA[3],const coordPrecision sommetB[3],const coordPrecision sommetC[3]);
			triangleElement( );
			/**
			 * Retourne la position X du sommet
			 * @param indexSommet A:0 B:1 C:2
			 */
			coordPrecision GetSommetX( sommetIndex indexSommet );
			/**
			 * Retourne la position Y du sommet
			 * @param indexSommet A:0 B:1 C:2
			 */
			coordPrecision GetSommetY( sommetIndex indexSommet );
			/**
			 * Retourne la position Z du sommet
			 * @param indexSommet A:0 B:1 C:2
			 */
			coordPrecision GetSommetZ( sommetIndex indexSommet );
			virtual ~triangleElement() {};
			virtual bool IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize);
			virtual void GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3]);
			void Set(const coordPrecision sommetA[3],const coordPrecision sommetB[3],const coordPrecision sommetC[3]);
	protected:
			coordPrecision sommets[3][3];

	};
}

#endif
