/**
 * @file calculsPropagation.h
 *  Définition des classes pour les fonctions nécessaires au calcul de la propagation au dessus d'un sol
 *
 * Auteur : J. Picaut (LCPC)
 * Date de la dernière modification : 19 février 2009 (ajout de l'espace de nom)
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
/**
 * @brief Calculs de theromodynamique
 */
namespace CalculsGenerauxThermodynamique
{
	using namespace std;
	/// @cond INCLUDE_PYTHON_HIDDEN_MEMBERS
	namespace CGTconst
	{

		// Définition de constantes thermodynamiques
		const double K_0(273.15);	// Temperature en K correspondant à 0°C
		const double Pref(101325);	// Pression atmospherique ambiante de reference (Pa)
		const double Kref(293.15);	// Temperature atmospherique ambiante de reference (K)
		const double FmolO(0.209);	// Fraction molaire de l'oxygene
		const double FmolN(0.781);	// Fraction molaire de l'azote
		const double KvibO(2239.1);	// Temperature vibratoire de l'oxygene (K)
		const double KvibN(3352.0);	// Temperature vibratoire de l'azote (K)
		const double K01(273.16);   // Temperature istotherme au point triple (K)

		// Définition du nombre imaginaire complexe I
		const complex<double> I(0.,1.);
	}
	/// @endcond
	class CCalculsGenerauxThermodynamique
	{
	public:
		static double c_son(double x);
		static double masse_vol(double P, double K);
		static double Coef_Att_Atmos(double F, double H, double P, double K);
	};
};
