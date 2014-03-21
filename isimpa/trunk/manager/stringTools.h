#include "first_header_include.hpp"


#include <iostream>
#include <string>
#include <sstream>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>

#ifndef __M_STR_H__
#define __M_STR_H__



/*! \file stringTools.h
    \brief Gestion des chaînes de caractère au sein de l'interface
*/

/**
	Convertir n'importe quel valeur vers une chaîne de caractere ( soumis à la définition du séparateur de decimal)
*/
template <class T>
std::wstring toString( T value )
{
   std::ostringstream oss;

   oss << value;

   return oss.str();
}

/**
 Concatenation de deux données et convertion en chaîne de caractères.
*/
template <class T,class U>
std::wstring Concatenate( T valuel, U valuer )
{
   std::ostringstream oss;

   oss << valuel << valuer;

   return oss.str();
}
/**
	Divise une chaîne de caractere et place ces fragment dans un tableau de chaînes
	@param[in] src Chaîne à séparer
	@param[in] delimiter Délimiteur de la chaîne de caractère
	@param[out] dst	Tableau à renseigner avec les fragments de chaîne. ( Le tableau n'est pas vidé)
*/
void SplitString(wxString src,wxString delimiter,wxArrayString& dst);


/**
	Divise une chaîne de caractere et place ces fragment dans un tableau de flottants
	@param[in] src Chaîne à séparer
	@param[in] delimiter Délimiteur de la chaîne de caractère
	@param[out] dst	Tableau à renseigner avec les fragments de chaîne. ( Le tableau n'est pas vidé)
*/
void SplitString(wxString src,wxString delimiter,std::vector<wxFloat32>& dst);
/**
 @brief Cette classe n'a pas besoin d'être initialisée, gestion de conversion des types de données

 Afin de ne pas être sensible à la localité ( pays) des chiffres à décimal cette classe peut être utilisée pour les conversions de données
*/
class Convertor{
private:
  static wxString fromConvDecimal;
  static wxString toConvDecimal;
  static void updateDecimalChar();
public:
	/**
	  Correspond au caractère de séparateur de décimale qui n'est pas compatible avec la localisation du logiciel.
	  @see getConvTo()
	  @return Caractère séparateur de décimal
	*/
	static char getConvFrom();
	/**
	  Correspond au caractère de séparateur de décimale qui est compatible avec la localisation du logiciel.
	  @see getConvFrom()
	  @return Caractère séparateur de décimal
	*/
	static char getConvTo();
	/**
		Convertir une chaîne en flottant
	*/
	static float ToFloat( const wxString& sval );
	/**
		Convertir une chaîne en flottant
	*/
	static float ToFloat(char* String);
	/**
		Convertir un flottant en chaîne
		@param fval Nombre à décimale à convertir
		@param decimal Renseigne le caractère à utiliser comme séparateur de décimal, si non renseigné la décimale du language sera utilisé
	*/
	static wxString ToString( float fval ,wxString decimal=' ', int nbdecimal=3 );
	/**
		Convertir un entier en chaîne de caractères
	*/
	static wxString ToString( int ival);
	/**
		Convertir une chaîne de caractère en entier	
	*/
	static int ToInt( const wxString& sval );
	/**
		Convertir une chaîne de caractère en entier long
	*/
	static long long ToLong( wxString sval );
};


#endif