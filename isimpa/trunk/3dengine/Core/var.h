#include "first_header_include.hpp"

#ifndef _HVAR
#define _HVAR

/*! \file var.h
 *  \brief Exportation du fichier de contrainte tetgen
 */
#include "Mathlib.h"
#include <vector>

/*!
 *    \brief Exportation du fichier de contrainte tetgen
 */
namespace formatVAR
{

	/**
	 * @brief Structure de données de contrainte du maillage
	 */
	struct t_facet_constraint
	{
		unsigned int boundaryMarker;
		float areaConstraint;
		t_facet_constraint(){};
		t_facet_constraint(unsigned int _boundaryMarker , float _areaConstraint ):boundaryMarker(_boundaryMarker),areaConstraint(_areaConstraint){}

	};

	/**
	 * @brief Structure de données englobant toutes les contraintes
	 *
	 */
	struct t_file
	{
		std::vector<t_facet_constraint> facetsConstraints;
	};

/**
 *	\class Cvar  
 *	\brief Exportation du fichier de contrainte tetgen
 */
class CVar
{
public:

	/**
	 * Constructeur
	 */
	CVar();
	/**
	 * Méthode d'exportation d'un modèle 3D
	 */
	bool BuildVar(t_file& sceneconst,const char* mfilename);
private:
	enum {FILENAMESIZE = 1024};

};





} //Fin namespace
#endif