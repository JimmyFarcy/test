#include "first_header_include.hpp"

#include "data_manager/element.h"

/**  \file e_scene_sources_source_rendu.h
 *   \brief Propriétés de rendu 3D d'une source sonore ponctuelle de la scène
 */

/**
 *   \brief Propriétés de rendu 3D d'une source sonore ponctuelle de la scène
 * 
 */
class E_Scene_Sources_Source_Rendu: public Element
{
private:

	void InitProperties()
	{
		this->AppendPropertyColor("couleur","Couleur",255,0,0);
		_("Couleur"); //Pour generer le fichier de langues automatiquement
		this->AppendPropertyBool("showlabel","Afficher le libellé",true);
		_("Afficher le libellé");
	}
public:
	E_Scene_Sources_Source_Rendu( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_SOURCES_SOURCE_RENDU,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		_("Rendu");
		InitProperties();
	}

	E_Scene_Sources_Source_Rendu( Element* parent)
		:Element(parent,"Rendu",Element::ELEMENT_TYPE_SCENE_SOURCES_SOURCE_RENDU)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_3D_DISPLAY);
		InitProperties();
	}

	
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("rendu"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
};