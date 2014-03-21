#include "first_header_include.hpp"

#ifndef _HNFF
#define _HNFF

/*! \file Nff.h
    \brief Implémentation de l'interpréteur de fichier modèle Nff (*.nff)
 */
#include "Mathlib.h"
#include <vector>
#include "manager/smart_ptr.h"
#include "Model3D.h"

/*! \brief Implémentation de l'interpréteur de fichier modèle Nff (*.nff)
 */
namespace formatNFF
{

/**
 *	\class CNff 
 *	\brief Classe de chargement de fichier modèle Nff (*.nff)
 */
class CNff
{
public:

	/**
	 * Constructeur
	 */
	CNff();
	/**
	 * Méthode d'exportation d'un modèle 3D
	 * @param mfilename Chemin du fichier
	 * @param UnitizeValue Vecteur 4d redimensionnement et de translation du modèle
	 * @param Vertices Tableau de points
	 * @param pModel Tableau de groupes
	 * @param nbVertices Nombre de points
	 * @param nbFaces Nombre de faces
	 */
	void ExportNFF(vec4 UnitizeValue,std::vector<SGroup3D> &pModel, std::vector<vec3> &Vertices, const char *mfilename,long nbVertices, long nbFaces);
	/**
	 * Méthode d'exportation du maillage 3D
	 * @param mfilename Chemin du fichier
	 * @param UnitizeValue Vecteur 4d redimensionnement et de translation du modèle
	 * @param tabVertexMaillage Tableau de triangles
	 * @param nbFaces Nombre de faces
	 */
	void ExportTetraNFF(vec4 UnitizeValue,triangleFace *tabVertexMaillage, const char *mfilename, long nbFaces);
private:
	enum {FILENAMESIZE = 1024};

};





} //Fin namespace
#endif