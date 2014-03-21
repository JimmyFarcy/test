#include "intersection_tri.h"
#include <tools/collision.h>

namespace CollisionAlgo
{
	bool IntersectionVecTri(const vec3& origin, const vec3& dest,const vec3& a, const vec3& b, const vec3& c,float* t,float* u,float* v, vec3* posIntersect)
	{
		using namespace collision_manager;
		if(intersect_triangle(origin,dest-origin,a,b,c,t,u,v)==0)
		{
			return false;
		}else{
			if(*t>=0 && *t<=1)
			{
				vec3 i=origin+((origin-dest)*(*t));
				if(posIntersect!=NULL)
				{
					*posIntersect=i;
				}
				if(i.barelyEqual(a) || i.barelyEqual(b)  || i.barelyEqual(c))
					return false;
				return true;
			}else{
				return false;
			}
		}
	}
	//TODO Output two intersection
	bool IntersectionTriTri(const vec3& a, const vec3& b, const vec3& c, const vec3& d, const vec3& e, const vec3& f, vec3* isect, vec3* isecB)
	{
		float t,u,v;
		bool hasIntersection=false;
		vec3 tempInt;
		if(IntersectionVecTri(b,a,d,e,f,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}
		}
		if(IntersectionVecTri(c,a,d,e,f,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}
			
		}
		if(IntersectionVecTri(b,c,d,e,f,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}

		}
		if(IntersectionVecTri(d,e,a,b,c,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}
		}
		if(IntersectionVecTri(d,f,a,b,c,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}

		}
		if(IntersectionVecTri(f,e,a,b,c,&t,&u,&v,&tempInt))
		{
			if(!hasIntersection)
			{
				hasIntersection=true;
				*isect=tempInt;
			}else{
				*isecB=tempInt;
				return true;
			}
		}
		*isecB=*isect;
		return hasIntersection;
	}

}