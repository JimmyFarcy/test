#include "en_numeric.hpp"
#include <locale.h>


EnglishTemporaryLocale::EnglishTemporaryLocale()
{
	currentLocale=setlocale( LC_NUMERIC, NULL );
	setlocale(  LC_NUMERIC, "English" );
}
EnglishTemporaryLocale::~EnglishTemporaryLocale()
{
	setlocale(  LC_NUMERIC, currentLocale.c_str() );
}
