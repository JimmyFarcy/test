#ifndef _HPOLY
#define _HPOLY

/*! \file poly.h
    \brief Implémentation de l'interpréteur de fichier modèle Poly (*.poly) 
*/
#include "Core/mathlib.h"
#include <vector>

/*! \brief Implémentation de l'interpréteur de fichier modèle Poly (*.poly) 
*/
namespace formatPOLY
{

	/**
	 * @brief Structure de données de définition d'une région
	 */
	struct t_region
	{	
		int regionIndex;					/*!< 0 région par défaut */
		vec3 dotInRegion;					/*!< Coordonnées d'un point dans la région */
		float regionRefinement;				/*!< -1 contrainte de volume par défaut (m3) */
		t_region(){regionRefinement=-1;}
	};	
	/**
	 * @brief Structure de données d'echange avec la classe
	 */
	struct t_face
	{
		ivec3 indicesSommets;
		unsigned int faceIndex;
	};

	/**
	 * @brief Structure de données du modèle
	 *
	 */
	struct t_model
	{
		bool saveFaceIndex;
		std::vector<t_face> userDefinedFaces; //Faces rajoutés au modèle
		std::vector<t_face> modelFaces;
		std::vector<vec3> modelVertices;
		std::vector<t_region> modelRegions; /*!< Liste des régions du modèle */
	};

/**
 *	\class Cpoly  
 *	\brief Classe de sauvegarde de fichier POLY
 */
class CPoly
{
public:

	/**
	 * Constructeur
	 */
	CPoly();
	/**
	 * Méthode d'exportation d'un modèle 3D
	 */
	bool ExportPOLY(t_model& sceneconst,const char* mfilename);
	/**
	 * Méthode d'importation d'un modèle 3D
	 */
	bool ImportPOLY(t_model& sceneconst,const char* mfilename);

};





} //Fin namespace
#endif