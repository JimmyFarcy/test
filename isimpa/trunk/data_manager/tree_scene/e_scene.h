#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene.h
   \brief Element représentant la racine des élément de scène du projet
*/

/**
   \brief Element représentant la racine des élément de scène du projet
*/

class E_Scene: public Element
{
private:
void (*pointeurFonctionEvent)(Element*);
bool eventBinded;
public:
	E_Scene( wxXmlNode* noeudCourant );

	E_Scene( );

	/**
		Initialise le pointeur de méthode vers le gestionnaire de projet
		@param _pointeurFonctionEvent Méthode d'événement de mise à jour
		@see OnElementRootUpdate()
	*/
	void BindUpdateEvent(void (*_pointeurFonctionEvent)(Element*));

	void Init();

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);

protected:

	void Modified(Element* eModif);

};
