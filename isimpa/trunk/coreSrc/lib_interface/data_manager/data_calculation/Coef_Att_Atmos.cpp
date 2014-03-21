// Cette fonction calcule le coefficient d'atténuation
// atmosphérique du son dans l'air
// Norme ISO 9613-1:1993(F)
//
// Auteur : J. Picaut (LCPC)
// Date de la dernière modification : 23 juillet 2007
//
// En entrée :
// - fréquence acoustique (Hz)
// - humidité relative (en %)
// - pression atmosphérique (en Pa)
// - température en Kelvin (en K)
// En sortie : Absorption totale en dB/m

#include "calculsPropagation.h"


namespace CalculsGenerauxThermodynamique
{
	using namespace CGTconst;
	double CCalculsGenerauxThermodynamique::Coef_Att_Atmos(double F, double H, double P, double K)
	{
		// Célérité du son
		double cson = CCalculsGenerauxThermodynamique::c_son(K);

		// Calcul de la fraction molaire de vapeur d'eau
		double C = -6.8346 * pow( K01 / K , 1.261) + 4.6151;
		double Ps = Pref * pow( 10. ,C);
		double hmol = H * Ps / Pref;

		// Absorption classique et rotationnelle
		double Acr = (Pref/P) * (1.60E-10) * sqrt( K / Kref) * pow(F,2);

		// Absorption vibratoire de l'oxygène
		double Fr = (P/Pref) * (24. + 4.04E4 * hmol * (0.02 + hmol) / (0.391 + hmol) );
		double Am = 1.559 * FmolO * exp(-KvibO/K) * pow(KvibO/K,2);
		double AvibO = Am * (F/cson) * 2. *(F/Fr) / (1 + pow(F/Fr,2));

		// Absorption vibratoire de l'azote
		Fr = (P/Pref) * sqrt(Kref/K) * (9. + 280. * hmol * exp( -4.170 * (pow(K/Kref,-1./3.)-1)));
		Am = 1.559 * FmolN * exp(-KvibN/K) * pow(KvibN/K,2);
		double AvibN = Am * (F/cson) * 2. * (F/Fr) / (1+pow(F/Fr,2));

		// Absorption totale en dB/m
		double alpha = Acr + AvibO + AvibN;

		return alpha;
	}

};
