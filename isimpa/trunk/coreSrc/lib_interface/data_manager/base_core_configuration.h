#include "coreTypes.h"
#include "input_output/cxml.h"
/**
 * @file base_core_configuration.h
 * @brief Gestion des données de configuration
 *
 * Cette classe permet d'acceder aux informations de la scène de facon optimisé et simple
 */
class CXml;

#ifndef __BASE_CORE_CONFIGURATION__
#define __BASE_CORE_CONFIGURATION__

/**
 * @brief Gestion des données de configuration
 *
 * Cette classe permet d'acceder aux informations de la scène de facon optimisé et simple
 */
class Base_Core_Configuration
{
public:
	/**
	 * Enumeration des propriétés de type chaine
	 */
	enum BASE_SPROP
	{
		SPROP_MODEL_FILE_PATH=100,												/*!< Chemin d'accès au fichier de modèle */
		SPROP_CORE_WORKING_DIRECTORY,									/*!< Chemin d'accès au dossier de travail de l'application */
		SPROP_TETRAHEDRALIZATION_FILE_PATH,						/*!< Chemin d'accès au fichier de maillage */
		SPROP_RECEPTEUR_SURFACIQUE_FILE_PATH,				/*!< Nom du fichier de sortie des recepteurs surfaciques (par bande) */
		SPROP_RECEPTEUR_SURFACIQUE_FILE_CUT_PATH,				/*!< Nom du fichier de sortie des recepteurs surfaciques (par bande) */
		SPROP_RECEPTEUR_SURFACIQUE_FOLDER_PATH,			/*!< Nom de dossier de sortie des recepteurs surfaciques (toute bande)*/
		SPROP_PONCTUAL_RECEIVER_FOLDER_PATH,			/*!< Nom du dossier contenant les récepteurs ponctuel */
		SPROP_PONCTUAL_RECEIVER_FILE_PATH,				/*!< Nom du fichier de récepteur ponctuel */
		SPROP_ADV_PONCTUAL_RECEIVER_FILE_PATH,			/*!< Nom du fichier avancé de récepteur ponctuel */
		SPROP_CUMUL_FILE_PATH,							/*!< Nom du ficher contenant le niveau global du domaine */
		SPROP_LAST										/*!< Dernière énumération (Insérer les nouveaux éléments avant celui-ci) */
	};
	/**
	 * Enumeration des propriétés de type float
	 */
	enum BASE_FPROP
	{
		FPROP_SIMULATION_TIME=100,								/*!< Durée de la simulation en seconde */
		FPROP_TIME_STEP,														/*!< Pas de temps de la simulation en seconde */
		FPROP_TEMPERATURE,												/*!< Temperature °C */
		FPROP_PRESSION_ATMOSPHERIQUE,					/*!< Pression atmosphérique (Pa) */
		FPROP_HUMIDITE,															/*!< Humidité 0 à 100 % */
		FPROP_CELERITE,															/*!< C0 Celerite du son dans l'air en dessous de Z0 (m/s)  */ //\f$\343.2\sqrt{\frac{K}{K_0}}\f$
		FPROP_RHO,																		/*!< Masse volumique de la scène kg/m3 */
		FPROP_Z0,																			/*!< Paramètre de rugosité */
		FPROP_ALOG,																	/*!< Paramètre de gradient de célérité */
		FPROP_BLIN,																		/*!< Paramètre de gradient de célérité */
		FPROP_LAST																		/*!< Dernière énumération (Insérer les nouveaux éléments avant celui-ci) */
	};
	/**
	 * Enumeration des propriétés de type entier
	 */
	enum BASE_IPROP
	{
		IPROP_QUANT_BFREQ_TO_CALCULATE=100,		/*!< Nombre de bande de frequence qui vont etre calculées*/
		IPROP_QUANT_TIMESTEP,			     	/*!< Nombre de pas de temps*/
		IPROP_CUTTING_PLANE_USAGE,				/*!< Utilisation d'un ou plusieurs récepteur plan */
		IPROP_LAST								/*!< Dernière énumération (Insérer les nouveaux éléments avant celui-ci) */
	};
	/**
	 * Initialisation des paramètres du coeur de calcul à partir d'un fichier XML
	 * @param xmlFilePath Chemin du fichier XML
	 */
	Base_Core_Configuration( );


	/**
	 * Destructeur
	 */
	virtual ~Base_Core_Configuration( );

	std::vector<t_Source*> srcList;							/*!< Tableau de sources */
	std::vector<t_Material*> materialList;					/*!< Tableau de matériaux */
	std::vector<t_FreqUsage*> freqList;						/*!< Tableau contenant les informations propres aux fréquences */
	std::vector<t_Recepteur_P*> recepteur_p_List;			/*!< Tableau contenant les recepteurs ponctuels */
	std::vector<r_Surf*> recepteur_s_List;					/*!< Tableau contenant les recepteurs surfaciques */
	std::vector<r_SurfCut*> recepteur_scut_List;			/*!< Tableau contenant les recepteurs surfaciques plan */
	std::vector<t_Encombrement*> encombrement_List;			/*!< Tableau contenant les encombrements */

	/////////////////////////////////////////////////////////
	//	Trés rapide
	/////////////////////////////////////////////////////////
	inline decimal* FastGetConfigValue(BASE_FPROP propertyIndex){return (tabFloatProp+propertyIndex); }
	inline CoreString* FastGetConfigValue(BASE_SPROP propertyIndex){return (tabStringProp+propertyIndex); }
	inline entier* FastGetConfigValue(BASE_IPROP propertyIndex){return (tabIntProp+propertyIndex); }


	/**
	 * Retourne l'adresse du matériau correspondant à l'indice Xml du matériau
	 * @param outsideIndex Indice Xml
	 * @return Pointeur vers un matériau si existant. NULL si inéxistant.
	 */
	t_Material* GetMaterialByOutsideIndex( uentier outsideIndex );

	/**
	 * Retourne l'adresse de l'encombrement correspondant à l'indice Xml de l'encombrement provenant de l'interface
	 * @param outsideIndex Indice Xml
	 * @return Pointeur vers un encombrement si existant. Pointeur NULL si inéxistant.
	 */
	t_Encombrement* GetEncombrementByOutsideIndex( uentier outsideIndex );
protected:

	/**
	 * Chargement des paramètres à partir d'un fichier XML
	 * @param fichierXml Objet contenant les données
	 */
	bool LoadCfgFile( CXml& fichierXml );

	decimal *tabFloatProp;
	entier *tabIntProp;
	CoreString *tabStringProp;


	void SetConfigInformation(BASE_FPROP propertyIndex,decimal valeur);
	void SetConfigInformation(BASE_SPROP propertyIndex,CoreString valeur);
	void SetConfigInformation(BASE_IPROP propertyIndex,entier valeur);

};

#endif
