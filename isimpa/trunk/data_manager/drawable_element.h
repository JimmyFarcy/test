﻿#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "3dengine/Core/Model3D.h"

#ifndef __ELEMENT_DRAWABLE__
#define __ELEMENT_DRAWABLE__

/** @file drawable_element.h
 *	@brief Implémentation de E_Drawable
 */

/**
 *  @class E_Drawable
 *  @brief Spécialisation 3D de élément.
 *
 *  La particularité des éléments dérivants de cette classe est qu'elle peuvent être affichée dans la vue 3D.
 *
 *  Si un élément de l'arbre du projet doit être rendu dans la vue 3D alors il faut créer une classe dérivant de E_Drawable. Toutefois cette nouvelle classe ne contiendra aucune instruction openGl.
 *  La nouvelle classe doit utiliser les méthodes de E_Drawable afin de commander le rendu de l'element.
 *  @see CObjet3D::RenderDrawableElement
 *  @example demos/demos_add_element_drawable.h
 */
class E_Drawable: public Element
{
public:
	/**
	 * @brief Structure correspondant à un texte à afficher dans la vue3D
	 */
	struct t_labelInfo
	{
		wxString elementLabel;		/*!< Texte dans la scène 3D associé à cet élément */
		vec3 elementLabelPosition;	/*!< Position x,y,z du texte de cet élément */
		vec3 elementLabelColor;		/*!< Couleur rvb du texte */
	};
	/**
	 * @brief Structure correspondant à un triangle à afficher dans la vue3D
	 */
	struct t_triangle
	{
		vec3 a;		/*!< Coordonnées coté A */
		vec3 b;		/*!< Coordonnées coté B */
		vec3 c;		/*!< Coordonnées coté C */
	};
	/**
	 * @brief Structure correspondant à une couleur à afficher dans la vue3D
	 */
	struct t_el_draw_material
	{
		vec4 colorA;	/*!< Couleur ambiante */
		vec4 colorD;	/*!< Couleur diffuse */
		vec4 colorS;	/*!< Couleur spéculaire */
	};
	/**
	 * @brief Structure correspondant à un ensemble de triangles à afficher dans la vue3D
	 */
	struct t_el_draw_object
	{
		std::vector<t_triangle> triangles;
		std::vector<t_faceIndex> Scenetriangles;
		t_el_draw_material colours;
	};
	/**
	 * @brief Structure correspondant aux données destinnées au mailleur et au code de calcul.
	 * @see E_Drawable::GetConsistentModel()
	 * @see CObjet3D::_SavePOLY()
	 * @see E_Drawable::GetMaillageVolumeInfos()
	 */
	struct t_el_vol_infos
	{
		t_faceIndex firstFace;						/*!< Indice de face de référence afin de déduire dotInsideVol */
		vec3 dotInsideVol;							/*!< Point au sein du volume défini */
		float volumeConstraint;						/*!< Contrainte de volume lors du maillage de l'objet */
		t_el_vol_infos() {volumeConstraint=-1;firstFace.Set(-1,-1); }
	};
	std::vector<t_labelInfo> labelInfo; /*!< Tableau contenant la liste des textes à afficher dans la vue 3D */
	/**
	 * Retourne une liste de triangle qui definissent ce modèle à destination du mailleur et du moteur de calcul sonore
	 * Il sera donc maillé et sera interprété par le moteur de calcul
	 * @param[out] triangleLst Tableau que la méthode va renseigner
	 */
	virtual void GetConsistentModel(std::vector<t_triangle>& triangleLst);
	/**
	 * @param parent Element parent
	 * @param Nom Libellé dans l'arbre du projet
	 * @param _type Type de l'element
	 * @param nodeElement Source XML de l'élément (NULL si nouveau)
	 */
	E_Drawable(Element* parent,wxString Nom,ELEMENT_TYPE _type,wxXmlNode* nodeElement=NULL);

	~E_Drawable();
	/**
	 * @brief Execute les commandes de dessin du modèle
	 *
	 * Surcharger cette méthode afin d'avoir un rendu 3D pour votre élément.
	 * @param unitizeValue Vecteur de redimensionnement du modèle 3D (Coordonnées réél -> coordonnées OpenGl)
	 */
	virtual void DrawItem( vec4 unitizeValue );	//Dessine l'objet immédiatement
	/**
	 *
	 *	Cette méthode renseigne un tableau avec un objet 3D (ensemble de faces) représentant l'Element.
	 *  @param[in] unitizeValue Vecteur de redimensionnement du modèle 3D (Coordonnées réél -> coordonnées OpenGl)
	 *  @param[out] drawObject Tableau de faces
	 *  @see CObjet3D::RenderDrawableElement()
	 */
	virtual void DrawTriangles(vec4 unitizeValue,std::vector<t_el_draw_object> &drawObject); //Dessinera l'objet par la suite (triangles uniquement), permet un dessin correct de la transparence
	/**
	 *	Cette méthode renseigne une structure de données contenant les informations relatives au volume définit par cet objet.
	 *	@param[out] drawableElementInformations Informations relatives au volume
	 *  @return Faux si cet objet ne définit pas de nouveau volume au sein de la scène
	 */
	virtual bool GetMaillageVolumeInfos(t_el_vol_infos& drawableElementInformations);
protected:
	/** Liste de triangle qui definissent ce modèle à destination du mailleur et du moteur de calcul sonore
	 * Il sera donc maillé et sera interprété par le moteur de calcul
	 * @see GetConsistentModel()
	 */
	std::vector<E_Drawable::t_triangle> consistentModel;
	virtual void Modified(Element* elementUpdated);
	/**
	 * Cette méthode execute les instructions OpenGl pour dessiner un ensemble de faces
	 * @param[in] unconsistentModel Ensemble de faces à dessiner
	 * @param[in] colorA Composante de couleur Ambiant
	 * @param[in] colorD Composante de couleur Diffus
	 * @param[in] colorS Composante de couleur Spéculaire
	 */
	void DrawFaces(std::vector<t_triangle>& unconsistentModel,vec4 colorA,vec4 colorD,vec4 colorS);
	/**
	 * Ajouter un texte dans le dessin 3D de cet élément
	 * @param[in] label Libellé du texte
     * @param[in] position Coordonnées du texte dans l'espace (Système de coordonnées OpenGl)
     * @param[in] color Composante Rouge Vert Bleu de dessin du texte [0-255]
	 */
	void AddText(wxString label,vec3 position,vec3 color);
	/**
	 *  Dessine un point dans l'espace
	 *  @param[in] position  Coordonnées du point dans l'espace (Système de coordonnées OpenGl)
     *  @param[in] color Composante Rouge Vert Bleu de dessin du point
	 *  @param[in] size Taille du point (en pixel, hauteur et largeur)
	 */
	void DrawPoint(vec3 position,vec3 color,float size);
	/**
	 *  Dessine une flèche dans l'espace
	 *  @param[in] posOrigine  Coordonnées de la flèche dans l'espace (Système de coordonnées OpenGl)
	 *  @param[in] posDestination  Coordonnées de la flèche dans l'espace (Système de coordonnées OpenGl)
     *  @param[in] color Composante Rouge Vert Bleu de dessin de la flèche
	 *  @param[in] width Largeur de la flèche (en unité OpenGl, hauteur et largeur)
	 */
	void DrawArrow(vec3 posOrigine,vec3 posDestination,vec3 color,float width);
	/**
	 * Début d'instruction du dessin de lignes
	 * @see DrawLine()
	 * @see EndLines()
	 */
	void BeginLines();
	/**
	 * Dessin d'une ligne
	 * @param[in] a Position de début de ligne
	 * @param[in] b Position de fin de ligne
	 * @param[in] color Couleur de la ligne
	 * @see BeginLines()
	 * @see EndLines()
	 */
	void DrawLine(vec3 a,vec3 b,vec4 color);
	/**
	 * Fin d'instruction du dessin de lignes
	 * @see DrawLine()
	 * @see BeginLines()
	 */
	void EndLines();
	/**
	 *	Ajout un triangle dans la liste de consistentModel
	 *  @param A Coordonnées du sommet du triangle
	 *  @param B Coordonnées du sommet du triangle
	 *  @param C Coordonnées du sommet du triangle
	 */
	void PushTriangle(vec3 A,vec3 B,vec3 C);


	private:

		void LookAt(const vec3& a_eye, const vec3& a_at, const vec3& a_up);
};
#endif
