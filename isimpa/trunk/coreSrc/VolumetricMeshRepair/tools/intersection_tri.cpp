#include "intersection_tri.h"
#include <tools/collision.h>

namespace CollisionAlgo
{
	bool IntersectionVecTri(const vec3& origin, const vec3& dest,const vec3& a, const vec3& b, const vec3& c,float* t,float* u,float* v)
	{
		using namespace collision_manager;
		if(intersect_triangle(origin,dest-origin,a,b,c,t,u,v)==0)
		{
			return false;
		}else{
			if(*t>=0 && *t<=1)
			{
				if(origin.barelyEqual(a) || origin.barelyEqual(b)  || origin.barelyEqual(c)
					|| dest.barelyEqual(a) || dest.barelyEqual(b)  || dest.barelyEqual(c))
					return false;
				//vec3 posIntersect=a+(b-a)*(*u)+(c-a)*(*v);
				return true;
			}else{
				return false;
			}
		}
	}
	bool IntersectionTriTri(const vec3& a, const vec3& b, const vec3& c, const vec3& d, const vec3& e, const vec3& f)
	{
		float t,u,v;
		if(IntersectionVecTri(b,a,d,e,f,&t,&u,&v))
			return true;
		if(IntersectionVecTri(c,a,d,e,f,&t,&u,&v))
			return true;
		if(IntersectionVecTri(b,c,d,e,f,&t,&u,&v))
			return true;
		if(IntersectionVecTri(d,e,a,b,c,&t,&u,&v))
			return true;
		if(IntersectionVecTri(d,f,a,b,c,&t,&u,&v))
			return true;
		if(IntersectionVecTri(f,e,a,b,c,&t,&u,&v))
			return true;

		return false;
	}

}