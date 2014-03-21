#ifndef _HSTL
#define _HSTL

/*! \file stl.hpp
    \brief Implémentation de l'interpréteur de fichier modèle STL (*.stl) 
*/
#include "Core/mathlib.h"
#include <vector>

/*! \brief Implémentation de l'interpréteur de fichier modèle STL (*.stl) 
*/
namespace formatSTL
{

	/**
	 * @brief Structure de données d'echange avec la classe
	 */
	struct t_face
	{
		t_face()
		{ }
		t_face(const ivec3& sommets)
			: indicesSommets(sommets)
		{ }
		ivec3 indicesSommets;
	};

	/**
	 * @brief Structure de données du modèle
	 *
	 */
	struct t_model
	{
		std::vector<t_face> modelFaces;
		std::vector<vec3> modelVertices;
	};

/**
 *	\class Cstl
 *	\brief Classe de sauvegarde de fichier STL
 */
class CStl
{
public:

	/**
	 * Constructeur
	 */
	CStl();
	/**
	 * Méthode d'exportation d'un modèle 3D
	 */
	bool ExportSTL(t_model& sceneconst,const char* mfilename);
	/**
	 * Méthode d'importation d'un modèle 3D
	 */
	bool ImportSTL(t_model& sceneconst,const char* mfilename);

};

} //Fin namespace
#endif