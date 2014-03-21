#include "first_header_include.hpp"

#include <wx/file.h>
#ifndef __BIG_FILE_READER__
#define __BIG_FILE_READER__

/*! \file bigfilereader.h
    \brief Implémentation de la classe BigFileReader
*/

/**
 *\class BigFileReader 
 *	\brief Classe de lecture de fichiers volumineux
 *	
 *	Cette classe permet de specifier la taille du cache utilisé pour lire le fichier
 *	L'evolution sera d'implementer des algorithme d'optimisation dédié aux fichier ASCII
 *	@see stringParser()
 *	
 */
class BigFileReader
{
private:
	wxFile oFile;		/**< Contient l'instance de la classe de lecture de fichier de wxWidgets */ 
	long bufferPos;		/**< Entier indiquant la position du curseur de lecture dans le buffer mémoire */ 
	char* fBuffer;		/**< Buffer mémoire de taille variable (défini dans le constructeur) */ 
	long cacheSize;		/**< Taille du buffer mémoire fBuffer */ 
	/**
	 * Lit le fichier et place les données dans le buffer mémoire
	 * @return Vrai si il reste des données à lire dans le fichier
	 */
	bool FillBuffer();
public :
	/**
	 * Constructeur de la classe BigFileReader
	 * @param file Chemin et nom du fichier à lire
	 * @param cacheSize Taille en octets à placer en mémoire
	 * @see ~BigFileReader()
	 */
	BigFileReader(wxString file,unsigned long cacheSize);
	/**
	 * Destructeur de la classe BigFileReader
	 * @see BigFileReader()
	 */
	~BigFileReader();
	/**
	 * Rapport octets lu sur la taille du fichier
	 * @return Pourcentage lu du fichier de 0 à 1
	 */
	float getPercentRead();
	/**
	 * Permet de connaître l'etat du fichier
	 * @return Vrai si le fichier est ouvert et pret a etre lu, faux si fin de fichier ou fichier impossible a ouvrir
	 */
	bool IsOk();
	/**
	 * Lit le prochain octets du fichier
	 * @param outputChar Adresse où écrire la valeur du prochain octet
	 * @return Vrai si l'octet a été lu correctement
	 */
	bool GetNext(char* outputChar);
	/**
	 * Lit le prochain octets du fichier
	 * @param fl Adresse où écrire la valeur de la prochaine valeur décimale dans le fichier
	 * @return Vrai si l'octet a été lu correctement
	 */
	bool GetDecimal(double *fl);
	/**
	 * Lit les octets jusqu'au prochain retour chariot
	 * @return La chaîne de caractère correspondant à la ligne
	 */
	wxString GetLine();
};

#endif