#include "first_header_include.hpp"

#include "element_pywrap.hpp"


#ifdef USE_PYTHON
#ifndef __PYTHON_ELEMENT_FILE_WRAP__
#define __PYTHON_ELEMENT_FILE_WRAP__

namespace uictrl
{
/**
 * \~english Specification of element, representative of a file or a folder
 * \~french Dérive d'un élément, il représente un fichier ou un dossier
 */
class e_file : public element
{
public:
	e_file(const wxInt32& _xmlId);
	e_file(const element& cpyFrom);
	/**
	 * \~english Return the relative path of this file element.
	 * \~french Retourne le chemin relatif de cet élément de fichier.
	 */
	std::wstring buildfullpath();
};
}
#endif
#endif