#ifndef _HPLY
#define _HPLY

/*! \file ply.h
    \brief Implémentation de l'interpréteur de fichier modèle Ply (*.ply) 
	@see 
*/
#include "Mathlib.h"
#include <vector>

/*! \brief Implémentation de l'interpréteur de fichier modèle Poly (*.poly) 
*/
namespace formatPLY
{

	/**
	 * @brief Structure de données d'echange avec la classe
	 */
	struct t_face
	{
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
 *	\class Cply  
 *	\brief Classe de sauvegarde et de chargement de fichier PLY (stanford)
 */
class CPly
{
public:

	/**
	 * Constructeur
	 */
	CPly();
	/**
	 * Méthode d'importation d'un modèle 3D
	 */
	bool ImportPly(t_model& sceneconst,const char* mfilename);
	/**
	 * Méthode d'exportation d'un modèle 3D
	 */
	bool ExportPly(t_model& scene, const char* mfilename);
private:
	enum {FILENAMESIZE = 1024};

};





} //Fin namespace
#endif