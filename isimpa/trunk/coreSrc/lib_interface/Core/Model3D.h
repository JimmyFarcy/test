#ifndef _HMODEL
#define _HMODEL

/**
 * @file Model3D.h
 * 
 * @brief Définition de types en rapport avec les modèles 3D
 */
#include <vector>

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

	int operator==(const t_faceIndex &_faceIndex) { return (this->f == _faceIndex.f && this->g == _faceIndex.g ); }
	int operator!=(const t_faceIndex &_faceIndex) { return !(*this == _faceIndex); }
	
	void Set(long _face,long _group) { f=_face;g=_group; }
	void Set(const t_faceIndex *_faceIndex) { f=_faceIndex->f;g=_faceIndex->g; }
	void Set(const t_faceIndex &_faceIndex) { f=_faceIndex.f;g=_faceIndex.g;}

	union {
		struct {long f,g;};
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
 * Structure complète d'une face en 3D
 */
struct SFace3D 
{
	ivec3 Vertices;   
	vec3 FaceNormals; 
};

/**
 * Structure complète d'un groupe de surface
 */
struct SGroup3D 
{
	std::vector<SFace3D> pFaces; 
	long numOfVerts;
};

#endif