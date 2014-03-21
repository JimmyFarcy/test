/**
 * Cette classe permet de connaitre de facon rapide le point le plus proche des surfaces à partir d'un point de référence
 * Ainsi la classe BaseTriangulator est capable de modifier sa grille afin de coller au plus proche du modèle d'origine. Tout en garantissant la réussite d'un maillage tétraèdrique
 */
#include "smart_macro.h"
#include <Core/mathlib.h> //Mathlib de libinterface
#include <list>
#include <utility>

#ifndef __ADAPTATIVE_MESH_GUIDE__
#define __ADAPTATIVE_MESH_GUIDE__


namespace Triangulators
{
	typedef std::pair<decimal,vec3> Candidate_t;
	typedef std::list<Candidate_t> ClosestCandidates_t;
	class AdaptativeMeshGuide
	{
	private:
		struct AdaptativeMeshGuideData_t;
		typedef PTR<AdaptativeMeshGuideData_t> shared_ptr_data;
		shared_ptr_data AdaptativeMeshGuideData;
	public:
		/**
		 * Constructeur
		 * @param minBox Position x,y,z minimum de la boite englobante
		 * @param maxBox Position x,y,z maximum de la boite englobante
		 */
		AdaptativeMeshGuide();
		/**
		 * Ajoute un triangle dans l'espace de l'instance de AdaptativeMeshGuide
		 */
		void AddTri(const vec3& A,const vec3& B,const vec3& C);
		/**
		 * @param maxDepth Discretisation, maxDepth=log(cellCount)/log(2)
		 */
		void EndTriangleFeeding(const unsigned short maxDepth=5);
		/**
		 *  Recherche le point planaire par rapport aux surfaces du domaine le plus proche du point d'origine en paramètre.
		 *  @param OriginPoint Point à partir duquel ce fait le test
		 *  @param PointNormal Normal du point. Cette normale permet de rendre en priorité le point le plus proche dans la direction de la normale
		 *  @param maxDist Contrainte de test des surfaces autour du point
		 */
		bool GetClosestPoint(const vec3& OriginPoint,const decimal& maxDist,ClosestCandidates_t& foundPositions);

		void SortByDistance(ClosestCandidates_t& foundPositions);
	};
};

#endif
