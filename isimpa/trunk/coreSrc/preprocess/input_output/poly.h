#ifndef _HPOLY
#define _HPOLY

/*! \file poly.h
    \brief Impl�mentation de l'interpr�teur de fichier mod�le Poly (*.poly) 
*/
#include "Core/mathlib.h"
#include <vector>

/*! \brief Impl�mentation de l'interpr�teur de fichier mod�le Poly (*.poly) 
*/
namespace formatPOLY
{

	/**
	 * @brief Structure de donn�es de d�finition d'une r�gion
	 */
	struct t_region
	{	
		int regionIndex;					/*!< 0 r�gion par d�faut */
		vec3 dotInRegion;					/*!< Coordonn�es d'un point dans la r�gion */
		float regionRefinement;				/*!< -1 contrainte de volume par d�faut (m3) */
		t_region(){regionRefinement=-1;}
	};	
	/**
	 * @brief Structure de donn�es d'echange avec la classe
	 */
	struct t_face
	{
		ivec3 indicesSommets;
		unsigned int faceIndex;
	};

	/**
	 * @brief Structure de donn�es du mod�le
	 *
	 */
	struct t_model
	{
		bool saveFaceIndex;
		std::vector<t_face> userDefinedFaces; //Faces rajout�s au mod�le
		std::vector<t_face> modelFaces;
		std::vector<vec3> modelVertices;
		std::vector<t_region> modelRegions; /*!< Liste des r�gions du mod�le */
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
	 * M�thode d'exportation d'un mod�le 3D
	 */
	bool ExportPOLY(t_model& sceneconst,const char* mfilename);
	/**
	 * M�thode d'importation d'un mod�le 3D
	 */
	bool ImportPOLY(t_model& sceneconst,const char* mfilename);

};





} //Fin namespace
#endif