#ifndef __M_REPORT_BIN__
#define __M_REPORT_BIN__

/*! \file m_report_bin.h
    \brief Import export du rendu energetique du maillage tétrahedrique
*/

/**
 *   \brief Import export du rendu energetique du maillage tétrahedrique
 */
namespace formatMRENDERBIN
{

//Types Import/Export

typedef unsigned short bCourt;
typedef int Intb;
typedef float Floatb;
typedef unsigned long Longb ;
typedef bool Boolb ;

/**
 * @brief Structure d'entete du fichier
 */
struct t_FileHeader
{
	Longb quantTetra;
	Longb quantNodes;
};
/**
 * @brief Structure d'un noeud
 */
struct t_binNode
{
	Floatb node[3];
	Floatb energy;
};

/**
 * @brief Structure d'un tétrahedre du maillage
 *
 */
struct bintetrahedre
{
	Intb sommets[4];
};

struct t_reportbinexchange
{
	t_binNode* nodes;
	bintetrahedre* tetras;
	t_FileHeader data_infos;
	t_reportbinexchange() { nodes=0; tetras=0;}
	~t_reportbinexchange() { delete[] nodes; delete[] tetras;}
};


/**
 *	\brief Classe de sauvegarde et de chargement du rendu énergétique du maillage tétrahedrique
 */
class REPORT_MBIN
{
public: 
	/** Constructeur
	 */
	REPORT_MBIN(){}
	/** Destructeur
	 */
	~REPORT_MBIN(){}
	/**
	 * Méthode d'importation d'un fichier binaire
	 * @param strFileName Chemin du fichier
	 * @param t_reportbinexchange Modèle de tetrahèdre
	 * @return Vrai si l'opération a réussi
	 */
    bool ImportBIN(const char *strFileName,t_reportbinexchange& reportData);
	/**
	 * Méthode d'exportation d'un modèle 3D
	 * @param strFileName Chemin du fichier
	 * @param t_reportbinexchange Modèle de tetrahèdre
	 * @return Vrai si l'opération a réussi
	 */
	bool ExportBIN(const char *strFileName,t_reportbinexchange& reportData);

};


} //namespace
#endif
