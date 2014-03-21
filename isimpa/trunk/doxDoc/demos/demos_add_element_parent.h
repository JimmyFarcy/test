...
#include "e_scene_projet_demo.h"
...

class E_Scene_Projet: public Element
{
public:
	E_Scene_Projet( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Projet",Element::ELEMENT_TYPE_SCENE_PROJET,Element::GRAPH_FOLDER,noeudCourant)
	{
		_("Projet");
		
		if(noeudCourant!=NULL)
		{
			wxXmlNode* currentChild;
			currentChild = noeudCourant->GetChildren();
			// Lecture des fils noeud courant et création des éléments correspondants
			wxString propValue;
			while(currentChild!=NULL)
			{
				if(currentChild->GetPropVal("element_type",&propValue))
				{
					long typeEle;
					propValue.ToLong(&typeEle);
					if(typeEle==Element::ELEMENT_TYPE_SCENE_PROJET_DEMO)
						this->AppendFils(new E_Scene_Projet_Demo(currentChild,this));
					else if(...)
						...
					...
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Scene_Projet( Element* parent)
		:Element(parent,"Projet",Element::ELEMENT_TYPE_SCENE_PROJET,Element::GRAPH_FOLDER)
	{
		this->AppendFils(new E_Scene_Projet_Demo(this));
	}
	...
};