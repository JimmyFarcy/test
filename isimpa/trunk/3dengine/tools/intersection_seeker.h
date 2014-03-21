#include "first_header_include.hpp"


#include "3dengine/Core/Mathlib.h"
#include "3dengine/Core/Model3D.h"
#include <tools/octree44.hpp>
#include <tools/octree44_triangleElement.hpp>
#include <list>

#ifndef __INTERSECTION_TOOL__
#define __INTERSECTION_TOOL__

/*! \file intersection_seeker.h
    \brief  Outil de détection de collision Optimisée
*/
namespace ui_tools
{
	/**
	 * Element stocké dans l'octree
	 */

	class pspsElement : public octreeTool::triangleElement
	{
	public:

		pspsElement()
			:triangleElement()
		{

		}
		pspsElement( const t_faceIndex& faceIndex, std::vector<vec3> &_pVertices, const ivec3& sommets )
			: triangleElement(_pVertices[sommets.a],_pVertices[sommets.b],_pVertices[sommets.c]),
			faceIndices(faceIndex)
		{


		}

		void Init( const t_faceIndex& faceIndex, std::vector<vec3> &_pVertices, const ivec3& sommets )
		{
			faceIndices=faceIndex;
			this->Set(_pVertices[sommets.a],_pVertices[sommets.b],_pVertices[sommets.c]);
		}

		t_faceIndex faceIndices;
	};

	/**
	 * @brief Outil de détection de collision Optimisée
	 *  
	 * Cette classe utilise la carte graphique afin de détecter les collision d'un volume et d'un modèle 3D.
	 * 
	 */
	class IntersectionSeeker
	{
	private:
		std::vector<pspsElement*> modelFaces;
		octreeTool::Octree44* modelOctree;
		struct t_result
		{
			t_result()
			{
			}
			t_result(t_faceIndex _faceCollison,float _dist)
				:faceCollison(_faceCollison),dist(_dist)
			{
			}
			t_faceIndex faceCollison;
			float dist;
		};
		struct t_currentCollisionTest
		{
			t_currentCollisionTest() {clear();}
			void clear()
			{
				testStat=0;
				bestDist=-1.f;
				stopAtFirst=false;
				results.clear();
			}
			int testStat;
			vec3 testCoord;
			bool stopAtFirst;
			float bestDist;
			t_result BestResult;
			std::vector<t_faceIndex> results;
		} currentCollisionTest;
		bool DotTriangleCollisionTest(const octreeTool::elementSize& staticCandidateIndex);
		bool DotTriangleSommetIncludeTest(const octreeTool::elementSize& staticCandidateIndex);
	public:
		/**
		 * Constructeur.
		 *
		 * Les points et faces de la scène doivent être passé en parametre.
		 *
		 */
		IntersectionSeeker(std::vector<vec3> &_pVertices,std::vector<SGroup3D> &_pGroups);
		/**
		 * Destructeur
		 */
		~IntersectionSeeker( );

		/**
		 *  Exécution du test de collision, les premiers tests sont les plus lents car les compilations se font au fur et à mesure des tests. Il y a autant de compilation que de groupes.
		 *  @param debcuboide Debut du volume (coin inférieur d'un cube)
		 *  @param fincuboide Fin du volume (coin supérieur opposé d'un cube)
		 *  @warning Si le volume est incorrect (surface et non volume) toutes les faces sont retournées
		 *  @return Toutes les faces qui comprenent ou traversent le volume cuboïde défini
		 */
		void GetCollisionLst(vec3 debcuboide,vec3 fincuboide,std::vector<t_faceIndex>& vectorToFeed );

		t_faceIndex GetSingleCollision( vec3 position );
		void GetRegionFaceLst( vec3 position,std::vector<t_faceIndex>& results );

		void GetSommetFaceNeighboors( vec3 positionSommet, std::vector<t_faceIndex>& results );
		
		void PushBoxInfos(octreeTool::boxContainer& boxLst);
	};
}

#endif