#include <string>


#ifndef __TEMPORARY_ENGLISH_NUMERIC__
#define __TEMPORARY_ENGLISH_NUMERIC__

	/**
	 * Cette classe permet d'utiliser les . comme séparateur de décimale le temps de l'execution du processus
	 */
	class EnglishTemporaryLocale
	{
	protected:
		std::string currentLocale;
	public:
		EnglishTemporaryLocale();
		~EnglishTemporaryLocale();
	};

#endif
