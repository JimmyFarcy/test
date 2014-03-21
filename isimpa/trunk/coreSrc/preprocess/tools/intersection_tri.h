#include <Core/Mathlib.h> //Mathlib de libinterface


#ifndef __INTERSECTIONTRITRI__
#define __INTERSECTIONTRITRI__
namespace CollisionAlgo
{
	bool IntersectionTriTri(const vec3& a, const vec3& b, const vec3& c, const vec3& d, const vec3& e, const vec3& f, vec3* isecA=NULL, vec3* isecB=NULL);
};
#endif