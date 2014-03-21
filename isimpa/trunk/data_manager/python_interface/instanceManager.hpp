#include "first_header_include.hpp"


#include <wx/hashmap.h>


#ifndef __INSTANCE_MANAGER__
#define __INSTANCE_MANAGER__


#define VALHASHEL void*

WX_DECLARE_HASH_MAP( int, VALHASHEL , wxIntegerHash, wxIntegerEqual, t_HashPspsObject );

enum OBJECT_REF_TYPE
{
	OBJECT_REF_TYPE_ELEMENT,	/*!< Tout les élément du projet référencé par t_elementInfo::xmlIdElement */
	OBJECT_REF_TYPE_PROJECT,	/*!< Projet chargé dans le logiciel*/
	OBJECT_REF_TYPE_CAMERA,
	OBJECT_REF_TYPE_SIZE		/*!< Nombre de type d'objet référencé */
};
/**
 * Lors de l'instanciation d'un objet dans le code python cette classe est utilisé afin d'obtenir 
 * la référence de l'objet de PSPS précédement déclaré.
 *
 * Ainsi les modules python ont une source de données communes pour obtenir les références de la variable this désirée
 */

class InstanceManager
{
protected:
	struct t_HashObjectArray
	{
		t_HashPspsObject ptr_hash[OBJECT_REF_TYPE_SIZE];
	};
	static t_HashObjectArray HashObjectArray;
public:

	static void AppendReference(const OBJECT_REF_TYPE& refType, const int& index, VALHASHEL ref);
	static void RemoveReference(const OBJECT_REF_TYPE& refType, const int& index);
	/**
	 * Retourne la référence de l'objet souhaité
	 * @param refType Type de l'élément à extraire
	 * @param index Indice de l'élément
	 * @param[out] Pointeur où placer l'adresse de l'élément
	 * @return Vrai si un élément correspond à cet indice
	 */
	static bool GetReference(const OBJECT_REF_TYPE& refType, const int& index,VALHASHEL* pt_ref);

	static size_t GetElementCount();

};


#endif
