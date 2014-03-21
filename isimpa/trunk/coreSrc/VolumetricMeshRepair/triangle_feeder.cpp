#include "triangle_feeder.hpp"
#include <tools/octree44_triangleElement.hpp>

#ifdef __USE_MULTITHREAD__
	#include <boost/thread/thread.hpp>
	#include <boost/bind.hpp>
#endif

#ifndef MIN
	#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
	#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/**
 * Calcul la liste des coordonn�es de cubes en intersection avec ce triangle
 * @param[in] boxCellCount Nombre de cellules dans les axes x,y,z
 * @param[in] boxCenter Position x,y,z de la boite englobante
 * @param[in] cellSize Taille d'une cellule
 * @param[in] triA Position du sommet A du triangle
 * @param[in] triB Position du sommet B du triangle
 * @param[in] triC Position du sommet C du triangle
 * @param[out] minRange Indice de d�but de l'intervalle
 * @param[out] maxRange Indice de fin de l'intervalle
 */
void GetRangeIntersectedBoundingCubeByTri(const SpatialDiscretization::cell_id_t& boxCellCount,const vec3& boxCenter,const decimal& cellSize,const vec3& triA,const vec3& triB,const vec3& triC, ivec3& minRange,ivec3& maxRange)
{
	//Ancienne m�thode
	vec3 bmin(MIN(MIN(triA.x,triB.x),triC.x),MIN(MIN(triA.y,triB.y),triC.y),MIN(MIN(triA.z,triB.z),triC.z));
	vec3 bmax(MAX(MAX(triA.x,triB.x),triC.x),MAX(MAX(triA.y,triB.y),triC.y),MAX(MAX(triA.z,triB.z),triC.z));
	vec3 tmpvec=((bmin-boxCenter)/cellSize);
	ivec3 halfCellCount(boxCellCount/2,boxCellCount/2,boxCellCount/2);
	minRange=ivec3((long)floor(tmpvec.x),(long)floor(tmpvec.y),(long)floor(tmpvec.z))+halfCellCount;
	tmpvec=((bmax-boxCenter)/cellSize);
	maxRange=ivec3((long)ceil(tmpvec.x),(long)ceil(tmpvec.y),(long)ceil(tmpvec.z))+halfCellCount;
}

namespace ScalarFieldBuilders
{

	TriangleScalarFieldCreator::TriangleScalarFieldCreator(const decimal& _resolution)
	:ScalarFieldCreator(_resolution)
	{


	}

	void TriangleScalarFieldCreator::SecondStep_PushTri(const vec3& A,const vec3& B,const vec3& C)
	{
		#ifdef _DEBUG
		bool insideABox(false);
		#endif
		using namespace SpatialDiscretization;
		ivec3 minRange,maxRange;
		GetRangeIntersectedBoundingCubeByTri(this->volumeInfo.cellCount,this->volumeInfo.mainVolumeCenter,this->volumeInfo.cellSize,A,B,C,minRange,maxRange);
		decimal boxhalfsize[3],triverts[3][3];

		memcpy(boxhalfsize,&this->volumeInfo.cellHalfSize,sizeof(vec3));
		memcpy(triverts[0],&A,sizeof(vec3));
		memcpy(triverts[1],&B,sizeof(vec3));
		memcpy(triverts[2],&C,sizeof(vec3));

		//Todo multi-thread sur X ou X,Y
		vec3 boxcenter;
		for(cell_id_t cell_x=minRange.x;cell_x<=(cell_id_t)maxRange.x;cell_x++)
		{
			for(cell_id_t cell_y=minRange.y;cell_y<=(cell_id_t)maxRange.y;cell_y++)
			{
				for(cell_id_t cell_z=minRange.z;cell_z<=(cell_id_t)maxRange.z;cell_z++)
				{
					boxcenter=CellIdToCenterCoordinate(ivec3(cell_x,cell_y,cell_z),this->volumeInfo.cellSize,this->volumeInfo.zeroCellCenter);
					if(boxtri_test::triBoxOverlap(boxcenter,boxhalfsize,triverts)==1)
					{
						//currentCell->SetData(cell_z_offset,this->domainInformation,weight_t(1));
						(*this->fieldData)[cell_x][cell_y].SetData(cell_z,this->domainInformation,weight_t(1));
						
						#ifdef _DEBUG
						insideABox=true;
						#endif
					}
				}
			}
		}
		#ifdef _DEBUG
		if(!insideABox)
			inoutbox.b++;
		else
			inoutbox.a++;
		#endif
	}
}