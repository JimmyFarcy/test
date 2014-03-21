#include "data_manager/data_calculation/calculsPropagation.h"
#include <iostream>


#include "input_output/bin.h"
#include "input_output/progressionInfo.h"
#include "data_manager/base_core_configuration.h"
#include "input_output/baseReportManager.h"
/**
 * @file coreInitialisation.h
 * Déclaration
 */
entier GetRecepteurSurfacique(entier xmlIdRs,std::vector<r_Surf*>& recepteur_s_List);

void genprintVec(vec3 inf);


/**
 * Initialise la propriété de tétraèdre courant des sources
 * @param tetraMesh Maillage tétraèdrique de la scène
 * @param lstSources Liste des sources
 */
void InitSourcesTetraLocalisation(t_TetraMesh* tetraMesh,std::vector<t_Source*>* lstSources);


/**
 * Initialisation de la célérité du son dans chaque volume du maillage. La célérité dépend de la hauteur des volumes, de la rugosité Z0, et de C0
 */
void InitTetraCelerite(t_TetraMesh* tetraMesh,Base_Core_Configuration& configManager);
/**
 * Initialise la propriété des tétraèdres lié aux recepteurs ponctuels
 * @param tetraMesh Maillage tétraèdrique de la scène
 * @param lstRecepteurP Liste des recepteurs ponctuels
 */
void InitRecepteurPTetraLocalisation(t_TetraMesh* tetraMesh,std::vector<t_Recepteur_P*>* lstRecepteurP,Base_Core_Configuration& configManager);

/**
 * Réserve l'espace mémoire correspondant à une bande de fréquence.
 */
void InitRecepteurSBfreq(std::vector<r_Surf*>& recepteursSurfaciques,uentier idFreq,uentier nbTimeStep);

/**
 * Initialise les récepteurs surfaciques. Ajoute les faces correspondant aux recepteur composé de plusieurs surfaces du maillage
 * @param tetraMesh Maillage tétraèdrique de la scène
 * @param recepteursSurfaciques Liste des recepteurs surfaciques
 * @param configManager Configuration du projet
 */
void InitRecepteurS(t_TetraMesh* tetraModel,std::vector<r_Surf*>& recepteursSurfaciques,Base_Core_Configuration& configManager);

/**
 * Initialise les récepteurs surfaciques. Réserve l'espace mémoire pour le stockage des résultats
 * @param recepteursSurfaciques Liste des recepteurs surfaciques
 * @param configManager Configuration du projet
 */
void InitRecepteurSCut(std::vector<r_SurfCut*>& recepteursSurfaciques,Base_Core_Configuration& configManager);
/**
 * Initialise les récepteurs surfaciques. Ajoute les faces correspondantes aux recepteurs composés de plusieurs surfaces du modèle
 * @param tetraMesh Maillage tétraèdrique de la scène
 * @param lstRecepteurP Liste des recepteurs ponctuels
 */
void InitRecepteurS(t_Mesh* sceneMesh,std::vector<r_Surf*>& recepteursSurfaciques,Base_Core_Configuration& configManager);

/**
 * Chargement des faces dans les structures appropriées
 */
bool initMesh(t_Mesh &sceneMesh,CoreString workingDir,CoreString sceneMeshPath,Base_Core_Configuration& configManager);
/**
 * Chargement du fichier de maillage et initialisation de l'environnement
 */
bool initTetraMesh(CoreString tetraMeshFilePath,t_Mesh &sceneMesh,int nbFreq,t_TetraMesh& sceneTetraMesh,Base_Core_Configuration& configManager);
/**
 * Enregistrement des données récoltées
 */
void reportCompilation(Base_Core_Configuration& configManager,CoreString workingDir);
