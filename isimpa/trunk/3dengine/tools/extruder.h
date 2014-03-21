/*! \file extruder.h
    \brief Implémentation de la classe Extruder
*/


#include "intersection_seeker.h"

#ifndef __EXTRUDER_TOOL__
#define __EXTRUDER_TOOL__
/**
 * Panel de classes permettant la manipulation de modèle en 3D
 */
namespace ui_tools
{
	/**
	 * @brief Outil d'extrusion de volumes
	 * Retourne la nouvelle base d'une surface en collision avec un modèle défini par une liste de triangles
	 *
	 */
	class Extruder
	{
		private:
		typedef int t_point;
		struct ligne
		{
			t_point	a;
			t_point b;
		};
		static bool isEqual(ligne lLigne,ligne rLigne);
		void GetFaceToDelete(	std::vector<t_faceIndex> retFaces,std::vector<vec3> &_pVertices,std::vector<SGroup3D> &_pGroups,IntersectionSeeker& intersectionTool,std::vector<t_faceIndex> &volumeExtrusion);
		bool CreateWay(std::vector<ivec3> baseFaces,std::vector<ligne>& chemin);

		public:
			/**
			 * Constructeur
			 */
			Extruder();
			/**
			 * Destructeur
			 */
			~Extruder( );

		/**
		 * Effectuer l'extrusion d'un objet à partir d'un modèle
		 * @param[in] intersectionTool Classe permettant de détecter trés rapidement la collision de faces avec un volume
		 * @param _pVertices Tableau de points du modèle
		 * @param _pGroups Tableau de points du modèle
		 * @param[in] volumeExtrusion Indice des triangles contenues dans _pGroups correspondant au volume à créer
		 * @return En cas d'extrusion impossible alors qu'il y a des collisions alors retourne false, true si il n'y a rien a faire (volume flottant) ou si l'extrusion a été fait.
		 */
		bool DoExtrusion(IntersectionSeeker& intersectionTool,
			std::vector<vec3> &_pVertices,
			std::vector<SGroup3D> &_pGroups,
			std::vector<t_faceIndex> &volumeExtrusion
			);
	};

}

#endif
