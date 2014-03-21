#include "first_header_include.hpp"

#include <Core/mathlib.h>

#ifndef __PSPSMATHLIB__
#define __PSPSMATHLIB__

/**
	\brief Conversion Coordonnées Réél->OpenGL OpenGL->Réél

	Cette classe permet de convertir le système de coordonnée OpenGl en système de coordonnée standard et inversement
*/
class coordsOperation
{
public:
	/**
	 Transforme le vecteur du système de coordonnées openGl vers le système de coordonnées commun
	 @param[in] UnitizeVar Vecteur 4 dimensions correspondant au repositionnement des coordonnées standard
	 @param[in] glCoords Vecteur de coordonnées à convertir
	 @see CObjet3D::Unitize()
	 @return Vecteur de coordonnées original
	 */
	static vec3 GlCoordsToCommonCoords(const vec4 &UnitizeVar, const vec3 &glCoords) {
		return vec3((glCoords.x/UnitizeVar.w)+UnitizeVar.x,
-((glCoords.z/UnitizeVar.w)+UnitizeVar.z),
((glCoords.y/UnitizeVar.w)+UnitizeVar.y));
	}
	/**
	 Transforme le vecteur du système de coordonnées standard vers le système de coordonnées openGl
	 @param[in] UnitizeVar Vecteur 4 dimensions correspondant au repositionnement des coordonnées standard
	 @param[in] realCoords Vecteur de coordonnées à convertir
	 @see CObjet3D::Unitize()
	 @return Vecteur de coordonnées openGl
	 */
	static vec3 CommonCoordsToGlCoords(const vec4 &UnitizeVar, const vec3 &realCoords) {

		return vec3((realCoords.x-UnitizeVar.x)*UnitizeVar.w,
			(realCoords.z-UnitizeVar.y)*UnitizeVar.w,
			((-realCoords.y-UnitizeVar.z)*UnitizeVar.w));
	}
};



/**
 * Cette méthode permet le tirage aléatoire d'un nombre décimal
 * @return Decimal de 0 à 1
 */
inline float GetRandValue()
{
	return ((float)rand()) / (float)RAND_MAX;
}

#endif // __HMATHLIB__
