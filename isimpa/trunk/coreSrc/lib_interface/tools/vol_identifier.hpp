/**
 * @file vol_identifier.hpp
 * @brief Identifie les volumes à partir de la structure du maillage MBIN
 */
#include "../input_output/importExportMaillage/mbin.h"

namespace volume_identifier
{
/**
 * @class VolumeIdentifier
 * @brief Identifie les volumes à partir de la structure du maillage MBIN
 */
class VolumeIdentifier
{
public:
	/**
	 * Constructor
	 */
	VolumeIdentifier();
	/**
	 * Réinitialise l'indice idVolume de chaque tétraèdre et y affecte de nouveaux indices en fonction de l'agencement des tétraèdres.
	 */
	static void IdentifyVolumes(formatMBIN::trimeshmodel& tetramodel);


};

};
