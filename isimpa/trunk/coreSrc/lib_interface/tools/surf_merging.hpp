#include "../input_output/bin.h"
#include <vector>
#include <list>

/**
 * @file surf_merging.hpp
 * Permet de regrouper les faces selon la même norme et le même matériau
 */
/**
 * Permet de regrouper les faces selon la même norme et le même matériau
 *
 */
namespace surf_merge
{
/**
 * @class SurfaceMerging
 * Regrouper les faces selon la même norme et le même matériau
 *
 * Permet de regrouper les faces selon la même norme et le même matériau
 *
 */
	class SurfaceMerging
	{
	private:
		struct SelfData_t;
		SelfData_t* self;
	public:
		SurfaceMerging();
		virtual ~SurfaceMerging();
		/**
		 * Lectures des structures de données à la recherche des faces coplanaires
		 * @param model Modèle de la scène
		 */
		void LoadGroups(const formatCoreBIN::ioModel& model);
		/**
		 * Retourne le nombre de groupes de surfaces détectés
		 */
		int GetGroups();
		/**
		 * Donne les données pour un groupe
		 * @param[in] idel Indice du groupe [0-GetGroups()[
		 * @param[out] faceIds Faces du groupe
		 * @python Return faceIds vector, use list(SurfaceMerging::GetGroupInformation(idel)) python built-in function to translate into an integer list.
		 */
		void GetGroupInformation(const unsigned int& idel,std::vector<std::size_t>& faceIds);

		/**
		 * Sauvegarde les triangles fusionnés dans le format de fichier .poly
		 * @param strFileName Nom et chemin du fichier de sortie
		 */
		void SavePolyToPolyFile(const char *strFileName);
	};
};
