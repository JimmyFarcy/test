#ifndef _HSTL
#define _HSTL

/*! \file stl.hpp
    \brief Impl�mentation de l'interpr�teur de fichier mod�le STL (*.stl) 
*/
#include "Core/mathlib.h"
#include <vector>

/*! \brief Impl�mentation de l'interpr�teur de fichier mod�le STL (*.stl) 
*/
namespace formatSTL
{

	/**
	 * @brief Structure de donn�es d'echange avec la classe
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
	 * @brief Structure de donn�es du mod�le
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
	 * M�thode d'exportation d'un mod�le 3D
	 */
	bool ExportSTL(t_model& sceneconst,const char* mfilename);
	/**
	 * M�thode d'importation d'un mod�le 3D
	 */
	bool ImportSTL(t_model& sceneconst,const char* mfilename);

};

} //Fin namespace
#endif