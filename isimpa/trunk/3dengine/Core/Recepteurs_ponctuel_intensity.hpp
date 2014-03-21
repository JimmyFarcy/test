#include "first_header_include.hpp"

#include "Animator.hpp"
#include "Mathlib.h"
#include "../GlBitmapSurface.h" //rendu des légendes
#include "../legendFonts.h"
/**
 * @file Recepteurs_ponctuel_intensity.hpp
 * @brief Animation des vecteurs d'intensité des récepteurs ponctuels
 *
 * La classe implémentée gère le rendu de l'animation contenu dans les fichiers .rpi
 */

/**
 * @brief Gère le rendu de l'animation contenu dans les fichiers .rpi
 * 
 * Cette classe charge le fichier .rpi puis affiche dans la vue 3D la légende et les vecteurs d'intensitée par pas de temps
 */
#ifndef __RECEPTEUR_P_ANIMATION__
#define __RECEPTEUR_P_ANIMATION__

class RecepteursPControler : public Animator
{
private:
	wxString pathLoadedFile;
	struct t_p_legends
	{
		legendRendering::legendText* currentFile;
		legendRendering::legendText* currentTimeStep;
		t_p_legends()
		{
			currentFile=NULL;
			currentTimeStep=NULL;
		}
	} p_legends;
	struct RecepteurPData_t
	{
		RecepteurPData_t(){ this->min=0;this->max=0;}
		vec3 position;
		float min;
		float max;
		std::vector<vec3> vecDir;
	};
	std::vector<RecepteurPData_t> recepteurs;
	int nbtimestep;
	float timestep;
	legendRendering::ForeGroundGlBitmap* legendRenderer;
public:
	 /**
	  * Constructeur
	  */
	RecepteursPControler();
	 /**
	  * Destructeur
	  */
	~RecepteursPControler();
	/**
	 * Initialisation. Vide les informations en mémoire
	 */
	virtual void Init(const bool& resetLoadingTime=true);
	/**
	 * Passe au pas de temps passé en paramètre (met à jour la légende)
	 */
	void SetTimeStep(const int& timeStp);
	/**
	 * Passe au prochain pas de temps de rendu (reviens au premier pas de temps si c'était le dernier)
	 */
	void NextTimeStep();
	/**
	 * Charge le fichier RPI
	 * @param mfilename Chemin et nom du fichier
	 * @param UnitizeVal Vecteur de transformation du modèle (@see coordsOperation)
	 * @param 
	 */
	bool LoadRecepteursPFile(const wxString& path, const vec4& UnitizeVal);

	/**
	 * Execute les commandes OpenGL de rendu des recepteurs ponctuel
	 * @param timeStp Pas de temps de rendu
	 */
	void Render(const int& timeStp=-1);

	/**
	 * Informations sur le fichier de recepteurs ponctuel chargé
	 * @return Nombre de pas de temps
	 */
	int GetNbTimeStep();

	/**
	 * Initialise l'objet de rendu de légendes
	 * @param drawingContext Contexte de rendu 
	 */

	void InitLegend(legendRendering::ForeGroundGlBitmap& legendRenderer);

	virtual wxString GetRendererLabel();

	virtual void RedrawLegend();
	
};

#endif