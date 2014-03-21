#include "first_header_include.hpp"

/**
 * @file recepteursurf_difference.hpp
 * @brief Méthode de calcul de calcul d'attenuation entre deux fichiers de récepteur de surface
 *
 * Cet ensemble de méthode permet de calculer l'attenuation à partir de plusieurs enregistrements.
 */
#include <vector>
#include <wx/string.h>
#include <Core/mathlib.h>
#include <input_output/exportRecepteurSurf/rsbin.h>

#ifndef __RSURF_ATTENUATION_COMPUTATION__
#define __RSURF_ATTENUATION_COMPUTATION__
/**
 * @brief Méthode de calcul de calcul d'attenuation entre deux fichiers de récepteur de surface
 *
 * Cet ensemble de méthode permet de calculer l'attenuation à partir de plusieurs enregistrements.
 */
class RecepteurSurfAttenuationComputation
{
public:

	RecepteurSurfAttenuationComputation(wxString rsurfReferenceFile);

	bool SaveAttenuationRecepteurSurfFile(wxString rsurfSecondFile, wxString destinationResultFile );
private:
	struct t_rs_face
	{
		std::vector<wxInt32> timeStepToIndex; //-1 indique que ce pas de temps correspond a une énérgie nulle
	};
	struct t_r_surfprocess
	{
		std::vector<t_rs_face> faces;
	};
	struct t_process_data
	{
		formatRSBIN::t_ExchangeData rawData;
		std::vector<t_r_surfprocess> recepteurSurf;
	};
	t_process_data referenceRS;
	bool LoadRs(wxString pathRsFile,t_process_data* dataDestination);
	bool SaveRs(wxString pathRsFile,t_process_data& dataSource);

};

#endif