#include "first_header_include.hpp"

#ifndef _HMODEL
#define _HMODEL
/**
 * @file Model3D.h
 *
 * @brief Définition de types en rapport avec les modèles 3D
 */
#include <string>
#include <string.h>
#include <vector>
#include "3dengine/Core/Mathlib.h"
/**
 * @brief Indice d'une face
 *
 * Cette classe gère l'indexation d'une face
 */
class t_faceIndex {
public:
	t_faceIndex(void) : f(0), g(0) { }
	t_faceIndex(long _face,long _group) : f(_face), g(_group) { }
	t_faceIndex(const t_faceIndex *_faceIndex) : f(_faceIndex->f), g(_faceIndex->g) { }
	t_faceIndex(const t_faceIndex &_faceIndex) : f(_faceIndex.f), g(_faceIndex.g) { }

	int operator==(const t_faceIndex &_faceIndex) const { return (this->f == _faceIndex.f && this->g == _faceIndex.g ); }
	int operator!=(const t_faceIndex &_faceIndex) const  { return !(*this == _faceIndex); }

	std::size_t GetHashValue() const;
	void Set(long _face,long _group) { f=_face;g=_group; }
	void Set(const t_faceIndex *_faceIndex) { f=_faceIndex->f;g=_faceIndex->g; }
	void Set(const t_faceIndex &_faceIndex) { f=_faceIndex.f;g=_faceIndex.g;}
	bool IsOk() { if(f ==-1 || g==-1) return false; else return true; }
	union {
		struct {long f,g;};
		struct {long face,group;};
	};
};
/**
 * Structure d'un triangle
 */
struct triangleFace {
    float a[3];
	float b[3];
	float c[3];
};

/**
 * @brief Structure d'une face d'un tetrahedre
 */
struct tetraface
{
	ivec3 sommets;
	unsigned int marker;
};

/**
 * @brief Structure d'un tétrahedre du maillage
 *
 */
struct tetrahedre
{
	ivec4 sommets;
	tetraface tetrafaces[4];
	ivec4 tetraNeighboor;		/*!< Si tetraNeighboor[n]==-2 pas de voisin (n pour la face n) */
	int idVolume;				/*!< Indice du volume. 0 Volume général, indice de l'encombrement (xmlId de l'élément) */
};


/**
 * Structure d'un plan de coupe du maillage
 */
struct t_cutPlane{
	  bool actif;	/*!< Activer ou non le plan de coupe */
	  int sign;		/*!< -1 +1 Sens de coupe */
	  float value;	/*!< -1. +1. valeur de coupe (coordonné > ou < non affiché) */
	  int plane;	/*!< x,y,z plan de coupe x:0 y:1 z:2 */
};
/**
 * Structure complète d'une face en 3D
 */
struct SFace3D
{
	SFace3D():idMaterial(-1),selected(false),internalFace(false){memset(Diff,1,sizeof(bool));}
	bool selected;
	ivec3 Vertices;
	ivec3 Normals;
	vec3 FaceNormals;
	ivec3 TexCoords;
	bool Diff[3];			/*!< Affichage ou non des lignes du triangle A B C */
	bool internalFace;
	short idMaterial;		/*!< Identifiant du matériau d'origine du modèle */
};

/**
 * Structure complète d'un groupe de surface
 */
struct SGroup3D
{
	SGroup3D():Material(-1){};
	SGroup3D(const std::string& groupName):Name(groupName),Material(-1){};
	std::string Name;
	std::vector<SFace3D> pFaces;
	long Material;					/*!< Identifiant du matériau d'origine du modèle */
};

#endif
