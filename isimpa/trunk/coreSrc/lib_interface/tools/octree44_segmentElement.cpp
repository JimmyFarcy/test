/*
 * Code source écrit dans le cadre du projet OPALHA contrat ADEME n°06.04.C.0070 (2007)
 */
#include "octree44_segmentElement.hpp"

#include <math.h>


#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])


#define SUB(dest,v1,v2) \
		  dest[0]=v1[0]-v2[0]; \
		  dest[1]=v1[1]-v2[1]; \
		  dest[2]=v1[2]-v2[2];
#define ADD(dest,v1,v2) \
		  dest[0]=v1[0]+v2[0]; \
		  dest[1]=v1[1]+v2[1]; \
		  dest[2]=v1[2]+v2[2];

#define MULTBYVEC(dest,v1,v2) \
		  dest[0]=v1[0]*v2[0]; \
		  dest[1]=v1[1]*v2[1]; \
		  dest[2]=v1[2]*v2[2];
#define MULTBYFLOAT(dest,v1,f2) \
		  dest[0]=v1[0]*f2; \
		  dest[1]=v1[1]*f2; \
		  dest[2]=v1[2]*f2;


/*
	float projectionOnLine(const vec3 &vA, const vec3 &vB) {
		vec3 v(vB - vA);
		return v.dot(*this - vA) / v.dot(v);
	}
	*/

/*
vec3 closestPointOnSegment(const vec3 &vA, const vec3 &vB) {
		float factor = this->projectionOnLine(vA, vB);
		if (factor <= 0.0f) return vA;
		if (factor >= 1.0f) return vB;
		return (((vB-vA) * factor) + vA);
	}

*/


namespace octreeTool
{
	segmentElement::segmentElement(const coordPrecision positionA[3],const coordPrecision positionB[3])
	{
		Set(positionA,positionB);
	}
	segmentElement::segmentElement( )
	{
		SETVEC(0,CoordPositionA);
		SETVEC(0,CoordPositionB);
	}
	bool segmentElement::IsOverlap(coordPrecision boxcenter[3],const coordPrecision& boxhalfsize)
	{

		//Todo trouver l'origine du probleme
		float res[3];
		closestPointOnSegment(boxcenter,CoordPositionA,CoordPositionB,res);

		if(fabs(boxcenter[0]-res[0])>boxhalfsize)
			return false;
		if(fabs(boxcenter[1]-res[1])>boxhalfsize)
			return false;
		if(fabs(boxcenter[2]-res[2])>boxhalfsize)
			return false;
		return true;

                /*
		coordPrecision PosMilieu[3];
		ADD(PosMilieu,CoordPositionA,CoordPositionB);
		MULTBYFLOAT(PosMilieu,PosMilieu,.5);
		coordPrecision Longueur[3];
		SUB(Longueur,CoordPositionA,CoordPositionB);
		coordPrecision lengthhalf=sqrtf(DOT(Longueur,Longueur))/1.1;

		if(fabs(boxcenter[0]-PosMilieu[0])>boxhalfsize+lengthhalf)
			return false;
		if(fabs(boxcenter[1]-PosMilieu[1])>boxhalfsize+lengthhalf)
			return false;
		if(fabs(boxcenter[2]-PosMilieu[2])>boxhalfsize+lengthhalf)
			return false;
		return true;
                */
	}

	void segmentElement::GetMinMax(coordPrecision xyzMin[3],coordPrecision xyzMax[3])
	{
		xyzMin[0]=MIN(CoordPositionA[0],CoordPositionB[0]);
		xyzMin[1]=MIN(CoordPositionA[1],CoordPositionB[1]);
		xyzMin[2]=MIN(CoordPositionA[2],CoordPositionB[2]);
		xyzMax[0]=MAX(CoordPositionA[0],CoordPositionB[0]);
		xyzMax[1]=MAX(CoordPositionA[1],CoordPositionB[1]);
		xyzMax[2]=MAX(CoordPositionA[2],CoordPositionB[2]);
	}
	void segmentElement::Set(const coordPrecision positionA[3],const coordPrecision positionB[3])
	{
		COPYVEC(positionA,CoordPositionA);
		COPYVEC(positionB,CoordPositionB);
	}

	void segmentElement::projectionOnLine( float point[3],float VA[3],float VB[3], float* res)
	{
		float V[3];
		float subValue[3];
		float denumerateur;
		SUB(V,VB,VA);
		denumerateur=DOT(V,V);
		SUB(subValue,point,VA);
		*res=DOT(V,subValue)/denumerateur;
	}
	void segmentElement::closestPointOnSegment(float point[3],float VA[3],float VB[3],float res[3])
	{
		float factor;
		projectionOnLine(point,VA,VB,&factor);
		if (factor <= 0.0f)
		{
			COPYVEC(VA,res);
		}else if (factor >= 1.0f)
		{
			COPYVEC(VB,res);
		}else{
			float subValue[3];
			SUB(subValue,VB,VA);
			MULTBYFLOAT(subValue,subValue,factor);
			ADD(res,subValue,VA);
		}
	}
}
