#include "first_header_include.hpp"

#ifndef __MBIN__
#define __MBIN__

/*! \file data_group_info.h
    \brief Import export d'une liste de face
*/

/**
 * \brief Import export d'une liste de face
 */
namespace formatGRPINFO
{

//Types Import/Export

typedef unsigned short bCourt;
typedef int Intb;
typedef float Floatb;
typedef unsigned long Longb ;
typedef bool Boolb ;
/**
 * @brief Structure d'entete du fichier
 */
struct t_FileHeader
{
	Longb quantFace;
};
/**
 * @brief Structure d'une face
 */
struct binface
{
	Intb group;
	Intb face;
};


/**
 * @brief Structure regroupant les informations du fichier
 */
struct exchangeMainData
{
	t_FileHeader header;
	binface* tabFaces;
	~exchangeMainData(){ delete[] tabFaces;}
	exchangeMainData(){ tabFaces=(binface*)0;}
};

/**
 *	\brief Classe de sauvegarde et de chargement des groupes de faces
 */
class DGIBIN
{
public: 
	/** Constructeur
	 */
	DGIBIN(){}
	/** Destructeur
	 */
	~DGIBIN(){}
	/**
	 * Méthode d'importation d'un fichier binaire
	 * @param strFileName Chemin du fichier
	 * @param exchangeMainData informations du fichier
	 * @return Vrai si l'opération a réussi
	 */
    bool ImportBIN(const char *strFileName,exchangeMainData &mainData);
	/**
	 * Méthode d'exportation d'un modèle 3D
	 * @param strFileName Chemin du fichier
	 * @param exchangeMainData informations du fichier
	 * @return Vrai si l'opération a réussi
	 */
	bool ExportBIN(const char *strFileName,exchangeMainData &mainData);

};


} //namespace
#endif
