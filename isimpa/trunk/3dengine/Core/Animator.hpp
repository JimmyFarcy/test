﻿#include "first_header_include.hpp"
#include <wx/log.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/colour.h>
#include <wx/font.h>
#include "Mathlib.h"
#include "3dengine/GlBitmapSurface.h"

#ifndef __UI_3D_ANIMATOR__
#define __UI_3D_ANIMATOR__
/**
 * @file Animator.hpp
 * @brief Classe modèle pour les rendu d'animations tels que la propagation des particules
 *
 */


/**
 * @brief Classe modèle pour les rendu d'animations tels que la propagation des particules
 *
 * Cette classe déclare les méthodes communes à tout les contrôles d'animations. Ce contrôleur sera commandé par OpenGLApp
 */

class Animator
{
private:
	bool doRendering;
	wxString rendererName;
protected:
	wxDateTime loadingTime; /*!> Moment où le fichier de données a été (re)chargé */
	void SetRendererName(const wxString& renderer);
	wxColour text_foreground_color;
	wxColour text_background_color;
	wxFont legendFont;
public:
	/**
	  * Constructeur
	  */
	Animator();
	 /**
	  * Destructeur
	  */
	virtual ~Animator();
	/**
	 * Initialisation. Efface les données de l'animation en mémoire
	 * @param resetLoadingTime Remet à zero la date de chargement de l'animation
	 */
	virtual void Init(const bool& resetLoadingTime=true);

	/**
	 * @return A vrai les pas de temps sont rendu de pas de temps = 0 à pas de temps = pas de temps courant
	 */
	virtual bool DoLoopFromZero();
	/**
	 * Rendu de l'animation.
	 * @param timeStep Pas de temps de rendu
	 */
	virtual void Render(const int& timeStep=-1)=0;

	/**
	 * @return Nombre de pas de temps de la simulation
	 */
	virtual int GetNbTimeStep();
	/**
	 * A chaque passage d'un pas de temps à l'autre cette méthode est appelée
	 * @param timeStep Pas de temps courant
	 */
	virtual void SetTimeStep(const int& timeStep);
	/**
	 * OpenGLApp Rechargera l'animation si cette méthode retourne vrai
	 */
	virtual bool IsNeedUpdate(const wxDateTime& timeToCompare);
	/**
	 * Initialise la légende
	 */
	virtual void InitLegend(legendRendering::ForeGroundGlBitmap& _legendRenderer);
	/**
	 * Redessine l'élément de légende de l'animateur
	 */
	virtual void RedrawLegend() = 0;
	/**
	 * @return Le nom de l'animation
	 */
	const wxString& GetRendererName();
	/**
	 * @return Le libellé de l'animation
	 */
	virtual wxString GetRendererLabel();
	/**
	 * Active le rendu
	 */
	virtual void EnableRendering(bool enable=true);
	/**
	 * Active le rendu
	 */
	virtual bool IsRenderingEnable();

	/**
	 * Met à jour la couleur du texte de la légende
	 * @param foregroundColor Nouvelle couleur [r,g,b]
	 */
	virtual void SetTextForegroundColor(const ivec4& foregroundColor);
	/**
	 * Met à jour la couleur de fond du texte de la légende
	 * @param backgroundColor Nouvelle couleur [r,g,b]
	 */
	virtual void SetTextBackgroundColor(const ivec4& backgroundColor);
	/**
	 * Met à jour la police du texte de la légende
	 * @param textFont Nouvelle police
	 */
	virtual void SetTextFont(const wxFont& textFont);
};

#endif
