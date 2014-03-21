#include "first_header_include.hpp"

#ifndef _HMaterial
#define _HMaterial

/*! \file Material.h
    \brief Gestion des matériaux OpenGl
    
    Les informations de rendu des faces du modèle(scène) dans la vue 3D au niveau couleur et reflexion lumineuse sont stockées ici
*/

#include <string.h>
#include "Mathlib.h"
#include "Texture.h"
 
/*!
    \brief Structure de données d'un matériau
*/

struct SMaterial
{
	std::string Name;		/*!< Nom de la texture (Nom du fichier)*/
	vec4 ColorA;	/*!< Couleur ambiante */
	vec4 ColorD;	/*!< Couleur diffuse */
	vec4 ColorS;	/*!< Couleur spéculaire */
	float Transparency;	/*!< Transparence [0;1] */
	float Shininess;	/*!< Brillance [0;1] */
	long idTex;			/*!< Indice de la texture */
};

/**
 *\class CMaterial 
 *	\brief Classe de gestion des matériaux OpenGl (de la scène)
 *
 *	Cette classe stocke et execute les commandes OpenGl de rendu de matériaux OpenGL
 *	@see CObjet3D::_RenderGroupTexture()
 *	
 */

class CMaterial 
{
public:

	/**
	 * Constructeur
	 */
	CMaterial() 
	{
	}

	/**
	 * Destructeur
	 */
	~CMaterial() 
	{	
		//for(long i=0;i<this->_pMaterial.size();i++)
	    //delete this->_pMaterial[i].Name;
		this->_pMaterial.empty();
	}
	/**
	 * Cette méthode permet d'acceder à la liste des matériaux utilisés. Utile pour sauvegarder celles-ci.
	 * @see CformatBIN::ExportBIN
	 * @return Un tableau de matériaux
	 */
	const std::vector<SMaterial>& GetMaterials(){ return _pMaterial; }
	/**
	 * Créer un matériau à partir d'informations de base (stockage dans la classe de gestion de matériau)
	 * @param name		Libellé du matériau
	 * @param colorA	Valeur RGB de la couche Ambiante
	 * @param colorD	Valeur RGB de la couche Diffuse	
	 * @param colorS	Valeur RGB de la couche Spéculaire
	 * @return L'identifiant du matériau créé
	 */
	unsigned long Create(char *name,const vec4 &colorA, vec4 &colorD, vec4 &colorS);	
	/**
	 * Créer un matériau à partir de l'objet matériau (stockage dans la classe de gestion de matériau)
	 * @param strm	Matériau
	 * @return L'identifiant du matériau inseré
	 */
	unsigned long Create(const SMaterial *strm);
	/**
	 * A partir du libellé du matériau retourne son identifiant
	 * @param name	Libellé du matériau
	 * @return L'identifiant du matériau (0-Nb matériau), si introuvable 0 (matériau par défaut)
	 */
	unsigned long GetId(const std::string& name);
	/**
	 * Cette méthode execute les commandes OpenGl correspondant au matériau
	 * @param m	Identifiant du matériau
	 * @param forcetransparency	Force la transparence du matériau, -1 par défaut
	 * @return L'identifiant du matériau si existant, 0 si inexistant
	 */
	unsigned long SetColor(unsigned long m,float forcetransparency=-1);
	/**
	 * Cette méthode execute les commandes OpenGl correspondant au matériau avec la gestion des textures
	 * @param m	Identifiant du matériau
	 * @return L'identifiant du matériau si existant, 0 si inexistant
	 */
	unsigned long SetMat(unsigned long m);
	/**
	 * Vrai si ce matériau a une texture
	 */
	bool HasTexture(unsigned long m);
	/**
	 * Retourne idTex
	 */
	long GetTextureId(unsigned long m);
private:
	std::vector<SMaterial> _pMaterial;
};

#endif  //_HMaterial
