#ifndef _HCBIN
#define _HCBIN

/*! \file bin.h
    \brief Implémentation de la classe CformatBIN
*/
#include <fstream>
#include <vector>
#include <math.h>
#ifdef _MSC_VER
#include "../vc_stdint.h"
#else
#include <stdint.h>
#endif
/**
 * \brief Implémentation de l'interpréteur de fichier modèle Bin (*.bin)
 */
namespace formatCoreBIN
{
// Types généraux
#define indiceV unsigned int
#define indiceMat unsigned int
#define indiceRS int
#define indiceEN int

//Types Import/Export
#ifndef EPSILON
#define EPSILON				0.000001f
#endif
class t_pos
{
public:
	t_pos(float _x,float _y,float _z) : x(_x), y(_y), z(_z) { }
	operator float*() { return this->v; }
	int operator==(const t_pos &_v) {
		return (fabs(this->x - _v.x) < EPSILON && fabs(this->y - _v.y) < 0 && fabs(this->z - _v.z) < 0);
	}


	const float &operator[](int _i) const { return this->v[_i]; }
	union {
		struct {float x,y,z;};
		float v[3];
	};

};
/**
 * @brief Structure d'une face, déstiné à l'echange fichier<->CObjet3D
 */
struct ioFace {
	int operator==(const ioFace &_f) {
		return a==_f.a && b==_f.b && c==_f.c && idMat==_f.idMat && idRs==_f.idRs && idEn==_f.idEn;
	}
	indiceV a;/*!<  Indice du sommet */
	indiceV b;/*!<  Indice du sommet */
	indiceV c; /*!<  Indice du sommet */
	indiceMat idMat;  /*!< Identifiant du matériau associé à la face (aucun 0) */
	indiceRS idRs; /*!< Identifiant du récepteur surfacique (aucun -1) */
	indiceEN idEn; /*!< Identifiant de l'encombrement (aucun -1)*/
};

/**
 * @brief Structure du modèle, déstiné à l'echange fichier<->CObjet3D
 */
struct ioModel {
	std::vector<ioFace> faces; /*!< Faces de la scène */
	std::vector<t_pos> vertices; /*!< Sommets des triangles */
};




/**
 *	\brief Classe de sauvegarde et de chargement de fichier de modèle entre l'interface et le mode de calcul SPPS
 *	@see CObjet3D::Save()
 *	@see CObjet3D::Load()
 */
class CformatBIN
{
public:
	/** Constructeur
	 */
    CformatBIN();
	/** Destructeur
	 */
	~CformatBIN();
	/**
	 * Méthode d'importation d'un fichier binaire
	 * @param modelImport Structure de données où stocker le modèle à charger
	 * @param strFileName Chemin du fichier
	 * @return Vrai si l'opération a réussi
	 */
    bool ImportBIN(ioModel &modelImport, const char *strFileName);
	/**
	 * Méthode d'exportation d'un modèle 3D
	 * @param strFileName Chemin du fichier
	 * @param modelExport Modèle à exporter, déjà converti par coordsOperation::GlCoordsToCommonCoords() .
	 * @param matFacesAssociations Lien entre les faces et les materiaux.
	 * @return Vrai si l'opération a réussi
	 */
	bool ExportBIN(const char *strFileName,ioModel &modelExport);

	/**
	 * Retourne l'aire de la surface
	 */
	float GetSurfAire( const ioModel& model, const int& indiceface );
private:
	enum NODE_TYPE {
		NODE_TYPE_VERTICES,
		NODE_TYPE_GROUP
	};

	bool ProcessNode(std::fstream &binFile,ioModel &modelImport);
	bool ProcessNodeVertices(std::fstream &binFile,ioModel &modelImport);
	bool ProcessNodeGroup(std::fstream &binFile,ioModel &modelImport);

	void writeNode(std::fstream &binFile,CformatBIN::NODE_TYPE nodeType,std::size_t nodeHeadSize,std::size_t nodeSize);

};


} //namespace
#endif
