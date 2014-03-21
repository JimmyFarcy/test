// Cette fonction calcule la célérité du son dans l'air
// Norme ISO 9613-1:1993(F)
//
// Auteur : J. Picaut (LCPC)
// Date de la dernière modification : 19 février 2007
//
// En entrée : température en Kelvin
// En sortie : célérité du son en m/s

#include "calculsPropagation.h"
using namespace std;

namespace CalculsGenerauxThermodynamique
{
	using namespace CGTconst;

	double CCalculsGenerauxThermodynamique::c_son(double K)
	{
		double c = 343.2 * sqrt(K/Kref);
		return c;
	}
}
