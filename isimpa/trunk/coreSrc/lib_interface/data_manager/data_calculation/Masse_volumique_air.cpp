// Cette fonction calcule la masse volumique l'air
//
// Auteur : J. Picaut (LCPC)
// Date de la dernière modification : 19 février 2007
//
// En entrée :	- Pression (Pa)
//				- Température (Kelvin)
// En sortie :	- Masse volumique

#include "calculsPropagation.h"


using namespace std;

namespace CalculsGenerauxThermodynamique
{
	using namespace CGTconst;
	const double M(28.9644);			// Masse volumique de l'air (en kg/kmol)
	const double R(8314.32);			// Constante des gaz parfaits (en J/K.Kmol)

	// Calcul de la masse volumique
	double CCalculsGenerauxThermodynamique::masse_vol(double P, double K)
	{
		double rho = P * M / (R * K);
		return rho;
	}
}
