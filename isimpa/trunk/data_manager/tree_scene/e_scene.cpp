#include "e_scene.h"

#include "e_scene_donnees.h"
#include "e_scene_projet.h"
#include "last_cpp_include.hpp"


E_Scene::E_Scene( wxXmlNode* noeudCourant )
	:Element(NULL,"Scène",Element::ELEMENT_TYPE_SCENE_ROOT,noeudCourant)
{
	_("Scène");
	eventBinded=false;
	this->Init();
	if(noeudCourant!=NULL)
	{
		wxXmlNode* currentChild;
		currentChild = noeudCourant->GetChildren();
		// On va créer les fils de notre noeudCourant
		wxString propValue;
		while(currentChild!=NULL)
		{
			if(currentChild->GetPropVal("eid",&propValue))
			{
				long typeEle;
				propValue.ToLong(&typeEle);
				if(typeEle==Element::ELEMENT_TYPE_SCENE_DONNEES)
				{
					this->AppendFils(new E_Scene_Donnees(currentChild,this));
				}else if(typeEle==Element::ELEMENT_TYPE_SCENE_PROJET)
				{
					this->AppendFils(new E_Scene_Projet(currentChild,this));
				}
			}
			currentChild = currentChild->GetNext();
		}
	}
}

E_Scene::E_Scene( )
	:Element(NULL,"Scène",Element::ELEMENT_TYPE_SCENE_ROOT)
{
	eventBinded=false;
	this->AppendFils(new E_Scene_Donnees(this));
	this->AppendFils(new E_Scene_Projet(this));
	//this->elementInfo.expanded=true;
}

/**
	Initialise le pointeur de méthode vers le gestionnaire de projet
	@param _pointeurFonctionEvent Méthode d'événement de mise à jour
	@see OnElementRootUpdate()
*/
void E_Scene::BindUpdateEvent(void (*_pointeurFonctionEvent)(Element*))
{
	pointeurFonctionEvent=_pointeurFonctionEvent;
	eventBinded=true;
}

void E_Scene::Init()
{


}







wxXmlNode* E_Scene::SaveXMLDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
	thisNode->SetName("Scene"); // Nom de la balise xml ( pas d'espace autorise )

	return thisNode;
}
void E_Scene::Modified(Element* eModif)
{
	Element::Modified(eModif);
	if(eventBinded)
		(*pointeurFonctionEvent)(eModif);
}
