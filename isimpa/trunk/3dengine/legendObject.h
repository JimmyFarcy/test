#include "first_header_include.hpp"

/**
 * @file legendObject.h
 * @brief Cette classe représente un élément de légende
 */
#ifndef __LEGEND_OBJECT__
#define __LEGEND_OBJECT__

namespace legendRendering
{


	typedef unsigned char FGL_BYTE;

	enum T_ALIGNEMENT_V
	{
		ALIGNEMENT_V_TOP,
		ALIGNEMENT_V_CENTER,
		ALIGNEMENT_V_BOTTOM
	};
	enum T_ALIGNEMENT_H
	{
		ALIGNEMENT_H_LEFT,
		ALIGNEMENT_H_CENTER,
		ALIGNEMENT_H_RIGHT
	};
	struct legendCfg
	{
		int width;
		int height;
		float u_text;
		float v_text;
		int idTex;
		T_ALIGNEMENT_V alignementV;
		T_ALIGNEMENT_H alignementH;
		int border_top;
		int border_bottom;
		int border_left;
		int border_right;
		bool redim;
		float redim_width_perc;
		float redim_height_perc;
		legendCfg();
	};
	/**
	 * Stocke les données correspondant à un élément de la légende 
	 */
	class legendObject
	{
	public:
		legendObject();
		legendObject(legendObject& cpyFrom);

		virtual ~legendObject();

		/**
		 * Initialisation des données
		 */
		void Init(int _width,int _height);
		void Clear();
		/**
		 * Retourne le premier élément des données de texture de taille width*height*4 (RGBA)
		 * @warning Retourne pointeur NULL(0) si la méthode Init n'a pas été appelé pour cet objet
		 * @return Pointeur vers le premier élément du tableau de pixel, NULL si non initialisé.
		 */
		FGL_BYTE* GetRawData();
		/**
		 * Retourne l'élément de configuration de la légende.
		 * @return Configuration en lecture seule.
		 */
		const legendCfg& GetCfg();
		/**
		 * Remplace l'élément de configuration par celui placé en paramètre.
		 * @param cpyFrom Nouveaux paramètres.
		 */
		void SetCfg(legendCfg& cpyFrom);
		/**
		 * Copie à partir d'une source de données. La méthode Init doit avoir été appelé au préalable sinon cette méthode ne fera rien.
		 * @param[in] RGB_src tableau RVB de taille width*height*3
		 * @param[in] A_src tableau valeur alpha de taille width*height. NULL si pas de couche Alpha
		 */
		void Copy(const FGL_BYTE* RGB_src,const FGL_BYTE* A_src,int _sourcewidth,int _sourceheight); 
		/**
		 * Copie à partir d'une source de données. La méthode Init doit avoir été appelé au préalable sinon cette méthode ne fera rien.
		 * @param[in] RGBA_src tableau RVB de taille width*height*4
		 */
		void Copy(const FGL_BYTE* RGBA_src,int _sourcewidth,int _sourceheight); 

		/**
		 * Redimensionne la texture en conservant les données précédentes
		 */
		void PreserveResize(int _newwidth,int _newheight);
	protected:
		void DoCopy(const FGL_BYTE* RGB_src,const FGL_BYTE* A_src, int srcWidth,int srcHeight, bool overwrite=true,int destCornerX=0,int destCornerY=0);
		legendCfg objConfig;
		FGL_BYTE* foreground_tex;

	};
}

#endif