// Cette fonction calcule la c�l�rit� du son dans l'air
// Norme ISO 9613-1:1993(F)
//
// Auteur : J. Picaut (LCPC)
// Date de la derni�re modification : 19 f�vrier 2007
//
// En entr�e : temp�rature en Kelvin
// En sortie : c�l�rit� du son en m/s

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
