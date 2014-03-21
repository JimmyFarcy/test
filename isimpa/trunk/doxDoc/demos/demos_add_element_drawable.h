#include "data_manager/drawable_element.h"

/**  \file e_scene_projet_demo.h
 *   \brief Description courte de la classe
 * 
 *   Informations détaillées de la classe
 */

/**
 *   \brief Description courte de la classe
 * 
 *   Informations détaillées de la classe
 */
class E_Scene_Projet_Demo: public E_Drawable 
{
public:
	E_Scene_Projet_Demo( wxXmlNode* noeudCourant ,  Element* parent) 
		:E_Drawable(parent,"Demo",Element::ELEMENT_TYPE_SCENE_PROJET_DEMO,Element::GRAPH_ITEM,noeudCourant)
	{
		_("Demo");
	}

	E_Scene_Projet_Demo( Element* parent)
		:E_Drawable(parent,"Demo",Element::ELEMENT_TYPE_SCENE_PROJET_DEMO,Element::GRAPH_ITEM)
	{
		this->AppendPropertyText("demoname","Nom de la démo","Sans nom !");
		_("Nom de la démo");
		this->AppendPropertyColor("democolor","Couleur de démonstration",0,120,0);
		_("Couleur de démonstration");
	}

	void DrawItem( vec4 unitizeValue )
	{
		vec3 couleurTexteDemo=this->GetColorConfig("democolor")/255;	// Lecture de la couleur
		wxString texteDemo=this->GetStringConfig("demoname");			// Lecture du libellé
		vec3 PositionDemo(0,0,0);										// Position du texte à l'origine
		labelInfo.clear();
		AddText(texteDemo,PositionDemo,couleurTexteDemo);
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("demo"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};