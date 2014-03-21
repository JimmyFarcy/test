#include "first_header_include.hpp"

#include "legendObject.h"
#include <vector>
/**
 * @file GlBitmapSurface.h
 * @brief Gestion d'affichage de bitmap au premier plan d'une vue en 3D
 */

#ifndef __LEGEND_RENDERER__
#define __LEGEND_RENDERER__


/**
 * @class ForeGroundGlBitmap
 * @brief Gestion d'affichage de bitmap au premier plan d'une vue en 3D
 */

namespace legendRendering
{

	class ForeGroundGlBitmap
	{
	public:

		ForeGroundGlBitmap();
		ForeGroundGlBitmap(ForeGroundGlBitmap& cpyFrom);
		~ForeGroundGlBitmap();

		/**
		 * Rendu OpenGl de la liste des objets chargée
		 * @param view_width Largeur de la fenêtre
		 * @param view_height Hauteur de la fenêtre
		 * @param renewTex Si vrai la méthode redéclare les textures associées aux légendes, ralentit le processus mais permet de dessiner sur un autre contexte de rendu sans avoir à recopier toutes les légendes.
		 */
		void Draw(int view_width,int view_height);

		/**
		 * Ajoute un élément de légende. Il sera supprimé par cet objet lors de sa destruction.
		 */
		void Push(legendObject* newLegend);
		void Delete(legendObject* oldLegend);

		/**
		 * Recupere la liste des objets de légendes.
		 */
		const std::vector<legendObject*>* GetLegendObjects();

		/**
		 * Efface les objets de légendes.
		 */
		void Clear();
	private:
		std::vector<legendObject*> legendsList;
	};

}

#endif