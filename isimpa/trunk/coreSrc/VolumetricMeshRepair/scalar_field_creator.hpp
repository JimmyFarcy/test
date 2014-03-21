#include "spatial_discretization.hpp"
#include <vector>
#include <string>

#ifndef __SCALARFIELDBUILDERS__
#define __SCALARFIELDBUILDERS__

namespace ScalarFieldBuilders
{
	/**
	 * Retourne les coordonnées du centre du cube correspondant à l'indice en paramètre
	 */
	vec3 CellIdToCenterCoordinate( const ivec3& cell_id, const decimal& cellSize, const vec3& zeroCellCenter);
	/**
	 * Cette classe permet de générer un espace discrétisé en plusieurs volumes. C'est la première étape de la reconstruction du modèle.
	 */
	class ScalarFieldCreator
	{
	protected:
		PTR<SpatialDiscretization::weight_matrix> fieldData; //Données de la matrice X,Y,Z


		struct mainVolumeConstruction_t
		{
			decimal cellSize;
			unsigned int cellCount;
			vec3 mainVolumeCenter;
			vec3 cellHalfSize;
			vec3 zeroCellCenter;
			SpatialDiscretization::weight_t volumeCount;
			std::vector<decimal> volumeValue;
			vec3 boxMin;
			vec3 boxMax;
		} volumeInfo;
		SpatialDiscretization::domainInformation_t domainInformation;
		decimal resolution;
		static void ComputeMatrixParams(const vec3& boxMin,const vec3& boxMax, const decimal& minResolution, mainVolumeConstruction_t& computedVolumeInfo);
		/**
		 * Initialise les données pour le volume extérieur
		 */
		void InitExteriorVolumeId();
		/**
		 * Propage les valeurs des identifiants de volume d'une cellule à l'autre
		 * Si la cellule cible est modifié cette méthode retourne vrai
		 */
		bool CellToCellVolumePropagation(const ivec2& destinationPropa,const ivec2& sourcePropa,const SpatialDiscretization::weight_t& volumeId);
		/**
		 * Propage un indice de volume dans toute la matrice
		 */
		void ExtandVolume(const SpatialDiscretization::weight_t& volumeId);
		/**
		 * Retourne la position de la première cellule avec la valeur en paramètre
		 */
		ivec3 GetFirstCellByWeight(const SpatialDiscretization::weight_t& weight,SpatialDiscretization::zcell** foundCell);

		/**
		 * Calcul pour chaque volume sa valeur en m^3
		 * @param[out] volumeValue Un tableau de dimension égale au nombre de volume dans le domaine. Dont la valeur est en m^3.
		 */
		void ComputeVolumesValue(std::vector<decimal>& volumeValue);

		/**
		 * Retourne l'indice de la cellule contenant le point passé en paramètre
		 */
		ivec3 GetCellIdByCoord(const vec3& position);
	public:
		/**
		 * Constructeur
		 * @param _resolution Dimension d'une cellule qui composera la matrice. Plus la résolution est élevée plus le model généré sera proche du modèle en entrée et plus de triangles seront générés.
		 */
		ScalarFieldCreator(const decimal& _resolution);
		/**
		 * Initialisation de la matrice selon la résolution et la boite englobante passé en paramètre.
		 * @param boxMin Coordonnées minimale des objets qui alimenteront la matrice
		 * @param boxMax Coordonnées maximale des objets qui alimenteront la matrice
		 */
		void FirstStep_Params(const vec3& boxMin,const vec3& boxMax);
		virtual ~ScalarFieldCreator();

		/**
		 * Une fois toutes les primitives renseignées. Cette méthode doit être appelée afin de détecter les volumes délimité par les limites.
		 */
		void ThirdStep_VolumesCreator();

		/**
		 * Retourne la valeur de la matrice selon les indices des cellules
		 * @param index Entier positif désignant le n° de cellule.
		 * @see GetDomainSize()
		 */
		SpatialDiscretization::weight_t GetMatrixValue(const ivec3& index);


		vec3 GetCenterCellCoordinates( const ivec3& cell_id) const;


		/**
		 * Pour toutes les valeurs de Z pour un x,y donné. Retourne la valeur min,max.
		 */
		void GetMinMaxOnZ( const ivec2& xyCell, SpatialDiscretization::weight_t& minVolId,SpatialDiscretization::weight_t& maxVolId);
		bool IsContainsVol( const ivec2& xyCell, SpatialDiscretization::weight_t& volId);

		SpatialDiscretization::weight_t GetVolumeCount();
		decimal GetVolumeValue(const SpatialDiscretization::weight_t& volId);

		void GetMinMax(vec3& minBox,vec3& maxBox);

		/**
		 * Exporte les indices et volumes des domaines
		 * @param fileName Nom et chemin du fichier de sortie
		 * @param volsLabelsFileName Nom et chemin du fichier d'entrée des noms utilisateur de volume (fichier texte avec "x y z NomDuVolume" à chaque ligne)
		 */
		void ExportVolsStats(const std::string& fileName, const std::string& volsLabelsFileName=std::string());
		///////////////////////////////
		// Debug Functions
		unsigned int count();
		void MakeXYZ(const std::string& filename,const SpatialDiscretization::weight_t& idVol);
		void MakeXYZ(const std::string& filename,const decimal& minVol);
		std::size_t GetDomainSize();


	};

}

#endif
