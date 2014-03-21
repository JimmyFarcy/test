#include "first_header_include.hpp"

#include "data_manager/element.h"

/** \file e_scene_volumes.h
   \brief Dans ce dossier se trouve tout les volumes détéctés par l'interface.
*/

/**
   \brief Dans ce dossier se trouve tout les volumes détéctés par l'interface.
*/
class E_Scene_Volumes: public Element
{
public:
	E_Scene_Volumes( wxXmlNode* noeudCourant ,  Element* parent);

	E_Scene_Volumes( Element* parent);
	
	// Sauvegarde des informations à destination des moteurs de calculs
	virtual Element* AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle="");
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent);

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);
	
	void OnRightClic(wxMenu* leMenu);
};