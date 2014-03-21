#include <string>
#include <fstream>

#ifndef __PARTICLE_IO__
#define __PARTICLE_IO__
/**
 * @brief Lecture, ecriture des fichiers de particules
 */
namespace particleio
{
	/**
	 * Cette classe permet la gestion du fichier d'enregistrement de la propagation des particules
	 * Les données sont consérvés uniquement sur le disque durant toute la procédure d'écriture et de lecture car ce type de fichier pouvant être trés volumineux.
	 */
	class ParticuleIO
	{
	public:
		ParticuleIO();
		/**
		 * Fermeture du fichier
		 * Cette méthode est automatiquement appelé lors de la destruction de l'instance de ParticuleIO
		 */
		void Close();
		~ParticuleIO();
		/** @defgroup methodwritepart Ecriture d'un fichier de particule
		 *
		 *	Ces méthodes permettent de créer un nouveau fichier de particule
		 *  @{
		 */
		bool OpenForWrite(const std::string& fileName);
		/**
		 * Met à jour les données de l'entete du fichier
		 * @param timeStep Pas de temps en seconde
		 */
		void SetHeaderData(const float& timeStep);
		/**
		 * Enregistre une nouvelle particule
		 */
		void NewParticle(const unsigned long& firsttimestep);
		/**
		 * Enregistre une nouvelle position pour la particule courante
		 * @param x Position
		 * @param y Position
		 * @param z Position
		 * @param energy Energie w
		 */
		void NewPositionParticle(const float& x,const float& y,const float& z,const float& energy);
		/** @} */

		/** @defgroup methodreadpart Lecture d'un fichier de particule
		 *
		 *	Ces méthodes permettent de lire un fichier de particule
		 *  @{
		 */
		/**
		 * Lecture d'un fichier de particule
		 * @param fileName Chemin d'accès au fichier de particule
		 */
		bool OpenForRead(const std::string& fileName);
		/**
		 * Permet d'accéder aux données d'entête du fichier de particule
		 * @param[out] timeStep Pas de temps en seconde
		 * @param[out] nbParticles Nombre de particules
		 * @param[out] nbTimeStep Nombre de particules
		 * @python Return a tuple containing (timeStep,nbParticles,nbStepMax)
		 */
		void GetHeaderData(float& timeStep,unsigned long& nbParticles,unsigned long& nbStepMax);
		/**
		 * Passe à la prochaine particule
		 * @param[out] firstTimeStep Premier pas de temps
		 * @param[out] nbTimeStep Nombre de pas de temps
		 * @python Return a tuple containing (firstTimeStep,nbTimeStep)
		 */
		void NextParticle(unsigned long& firstTimeStep,unsigned long& nbTimeStep);
		/**
		 * Lis une nouvelle position pour la particule courante
		 * @param[out] x Position
		 * @param[out] y Position
		 * @param[out] z Position
		 * @param[out] energy Energie w
		 * @python Return a tuple containing (x,y,z,energy)
		 */
		void NextTimeStep(float& x,float& y,float& z,float& energy);
		/** @} */

	private:
		std::fstream* particleFile;
		unsigned long lastParticuleFileHeaderInfo;
		unsigned long lastParticuleHeaderInfo;
		bool readonly;
		bool IsOpenAndReadyForWrite();
		bool IsOpenAndReadyForRead();
		void WriteHeader(bool returntopos);
		void CloseAndClear();
		void CloseLastParticleHeader();

		struct fileInfo_t
		{
			unsigned long fileInfoLength;				/*!< Taille en octet de l'information du fichier d'entete*/
			unsigned long particleInfoLength;			/*!< Taille en octet d'une information de pas de temps */
			unsigned long particleHeaderInfoLength;		/*!< Taille en octet d'une information de particule */
			bool isoldversionfile;
			unsigned long nbparticles;
			float timeStep;
			unsigned long maxstepcount;
		}fileInfo;
		struct currentPartInfo_t
		{
			bool opened;
			unsigned long idpart;
			unsigned long currentstep;
			unsigned long firsttimestep;
			unsigned long nbtimestep;
		}currentPartInfo;
	};
};

#endif
