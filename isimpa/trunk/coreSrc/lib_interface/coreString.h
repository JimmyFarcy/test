#include <string>


#ifndef __CORE_STRING__
#define __CORE_STRING__
/**
 * @file coreString.h
 * Surcharge de la classe std::string
 */

#define entier int						/*!< Type de données pour les entier signé */
#define uentier_court unsigned short	/*!< Type de données pour les entier non signé court ( 65000 maximum )*/
#define entier_court short				/*!< Type de données pour les entier court ( 32000 maximum )*/
#define uentier unsigned int			/*!< Type de données pour les entier non signé */
#define decimal float					/*!< Type de données pour les chiffres à décimal */
#define l_decimal double				/*!< Type de données pour les chiffres à décimal long, a utiliser pour les cumuls d'énergie */
#define t_freq unsigned int				/*!< Type de données pour les fréquences */
#define uentier_long unsigned long		/*!< Type de données entier long */

/**
 * @brief Surcharge de la classe std::string
 *
 * Afin de simplifier l'écriture de certaines opérations, tel que la concaténation cette surcharge a été effectué.
 */

class CoreString : public std::string
{
public:
	/**
	 * Constructeur à partir d'une chaine de caractères complète
	 * @param ch[in] Chaine de caractères
	 */
	CoreString(const char* ch);

	CoreString(std::string outputstr);
	/**
	 * Constructeur à partir d'une fraction d'une chaine de caractères
	 * @param ch[in] Chaine de caractères
	 * @param length[in] Longueur de la chaine de caractères
	 */
	CoreString(const char* ch, unsigned int length);

	/**
	 * Constructeur d'une chaine vide
	 */

	CoreString( );

	static std::string FromInt(const entier& valInt);

	static std::string FromFloat(decimal nombreDecimal,entier digits=3);

	static entier ToInt(const CoreString& strtoconv);
	static decimal ToFloat(const CoreString& strtoconv);

	entier ToInt() const;

	decimal ToFloat() const;
};

#endif
