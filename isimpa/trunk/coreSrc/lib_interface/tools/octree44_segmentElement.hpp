/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44.hpp"
/**
 * @file octree44_segmentElement.hpp
 *
 * @brief Implémentation de l'élément segment de droite
 */

#ifndef __OCTREE44_SEGMENTELEMENT_H__
#define __OCTREE44_SEGMENTELEMENT_H__

namespace octreeTool
{
	/**
	 * @brief Element de type segment de droite
	 *
	 * Surtout utile pour les tests au sein de l'octree. Il est possible de le dériver afin de définir un rayon et non un segment seul
	 */
	class segmentElement : public spaceElement
	{
		public:
			segmentElement(const coordPrecision positionA[3],const coordPrecision positionB[3]);
			segmentElement( );
			virtual bool IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize);
			virtual void GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3]);
			void Set(const coordPrecision positionA[3],const coordPrecision positionB[3]);
	protected:
			/**
			 * Projection du point vers un segment de droite définit par deux coordonnées VA et VB, res correspond alors au point de la projection
			 *
			 * @param[in] point Point dans l'espace a projeter sur la droite
			 * @param[in] VA Position du point A appartenant à la droite AB
			 * @param[in] VB Position du point B appartenant à la droite AB
			 * @param[out] res Position du point I appartenant au segment de droite AB où AI (ou BI) forme un angle droit avec IP. Cette position est limitée entre VA et VB.
			 * @warning
			 */
			static void closestPointOnSegment(float point[3],float VA[3],float VB[3],float res[3]);

			/**
			 * Projection du point vers la droite définit par deux coordonnées VA et VB.
			 *
			 * @param[in] point Point dans l'espace a projeter sur la droite
			 * @param[in] VA Position du point A appartenant à la droite AB
			 * @param[in] VB Position du point B appartenant à la droite AB
			 * @param[out] res Correspond à un facteur ( 0 correspond à VA et 1 correspond à VB )
			 * @warning Res appartient au domaine ]-Inf;+Inf[ car il s'agit d'une projection sur un droite et non sur un segment.
			 */
			static void projectionOnLine( float point[3],float VA[3],float VB[3], float* res);

			coordPrecision CoordPositionA[3];
			coordPrecision CoordPositionB[3];

	};
}

#endif
