#include "first_header_include.hpp"

#ifndef _HMESH
#define _HMESH

/*! \file mesh.h
    \brief Implémentation de l'interpréteur de fichier modèle Mesh (*.mesh) 
*/
#include "Mathlib.h"
#include <vector>
#include "manager/smart_ptr.h"
#include "Model3D.h"

/*! \brief Implémentation de l'interpréteur de fichier modèle Mesh (*.mesh) 
*/
namespace formatMESH
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
 *	\class CMesh 
 *	\brief Classe de sauvegarde de fichier MESH
 */
class CMesh
{
public:


	/**
	 * Constructeur
	 */
	CMesh();
	/**
	 * Méthode d'exportation d'un modèle 3D
	 * @param mfilename Chemin du fichier
	 * @param UnitizeValue Vecteur 4d redimensionnement et de translation du modèle
	 * @param Vertices Tableau de points
	 * @param pModel Tableau de groupes
	 * @param nbVertices Nombre de points
	 * @param nbFaces Nombre de faces
	 */
	void ExportMESH(vec4 UnitizeValue,std::vector<SGroup3D> &pModel, std::vector<vec3> &Vertices, const char *mfilename,long nbVertices, long nbFaces);


private:
	enum {FILENAMESIZE = 1024};

};





} //Fin namespace
#endif