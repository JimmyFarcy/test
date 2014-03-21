#ifndef __PARTICLE_BINARY__
#define __PARTICLE_BINARY__

#define PARTICLE_BINARY_VERSION_INFORMATION 1 /*!< Version du format de fichier de particules incrementer la version en cas de modification des structures */
#define bpLong unsigned long
#define bpFloat float
#define bpUShort unsigned short

/*! 
	\brief Cette structure définit l'entete de fichier de particules
*/
struct binaryFHeader {
	bpLong nbParticles;					/*!< Nombre de particules dans le fichier */
	bpLong formatVersion;				/*!< Version du format */
	bpLong fileInfoLength;				/*!< Taille en octet de l'information du fichier d'entete*/
	bpLong particleInfoLength;			/*!< Taille en octet d'une information de pas de temps */
	bpLong particleHeaderInfoLength;	/*!< Taille en octet d'une information de particule */
	bpLong nbTimeStepMax;				/*!< Nombre de pas de temps maximum */
	bpFloat timeStep;					/*!< Pas de temps de la simulation */
};

/*! 
	\brief Cette structure définit l'entete de fichier de particules
*/
struct binaryPHeader {
	binaryPHeader(){};
	binaryPHeader(const bpLong &_nbTimeStep,const bpUShort& _firstTimeStep) : nbTimeStep(_nbTimeStep),firstTimeStep(_firstTimeStep) {}
	bpLong nbTimeStep;			/*!< Nombre de pas de temps effectif de la particule (nombre de lignes pour cette particule) */
	bpUShort firstTimeStep; /*!< Numero du premier pas de temps */
};


/*! 
	\brief Cette structure définit l'entete de fichier de particules
*/
struct binaryPTimeStep {
	binaryPTimeStep(){}
	binaryPTimeStep(vec3& _pos,bpFloat &_energy) : position(_pos),energy(_energy) {}
	vec3 position;			/*!< Position de la particule */
	bpFloat energy;			/*!< Energie de la particule */
};


/**
 * Charge un fichier de données
 * @param[in] fileName Chemin d'accès au fichier
 * @param[out] nbParticles
 */
bool LoadParticulesFile(const char* fileName,binaryFHeader& fileInfos);
#endif