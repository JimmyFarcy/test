#include "e_scene_volumes.h"
#include "e_scene_volumes_volume.h"
#include "last_cpp_include.hpp"

E_Scene_Volumes::E_Scene_Volumes( wxXmlNode* noeudCourant ,  Element* parent)
:Element(parent,"Volumes",Element::ELEMENT_TYPE_SCENE_VOLUMES,noeudCourant)
{
	
	SetIcon(GRAPH_STATE_EXPANDED,GRAPH_VOLUMES_OPEN);
	SetIcon(GRAPH_STATE_NORMAL,GRAPH_VOLUMES_CLOSE);
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
				
				if(typeEle==Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME )
				{
					this->AppendFils(new E_Scene_Volumes_Volume(currentChild,this));
				}
			}
			currentChild = currentChild->GetNext();
		}
	}
}

E_Scene_Volumes::E_Scene_Volumes( Element* parent)
:Element(parent,"Volumes",Element::ELEMENT_TYPE_SCENE_VOLUMES)
{
	SetIcon(GRAPH_STATE_EXPANDED,GRAPH_VOLUMES_OPEN);
	SetIcon(GRAPH_STATE_NORMAL,GRAPH_VOLUMES_CLOSE);
	_("Volumes");
}


Element* E_Scene_Volumes::AppendFilsByType(ELEMENT_TYPE etypefils,const wxString& libelle)
{
	if(etypefils==Element::ELEMENT_TYPE_SCENE_VOLUMES_VOLUME )
	{
		return this->AppendFils(new E_Scene_Volumes_Volume(this));
	}
	return Element::AppendFilsByType(etypefils,libelle);
}

wxXmlNode* E_Scene_Volumes::SaveXMLCoreDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"subdomains");
	Element::SaveXMLCoreDoc(thisNode);
	return thisNode;
}

wxXmlNode* E_Scene_Volumes::SaveXMLDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
	thisNode->SetName("volumes"); // Nom de la balise xml ( pas d'espace autorise )

	return thisNode;
}
void E_Scene_Volumes::OnRightClic(wxMenu* leMenu)
{
	leMenu->Append(GetMenuItem(leMenu,IDEVENT_NEW_VOLUME, _("Déclarer un volume"),"./Bitmaps/popup_new.png"));
	leMenu->Append(GetMenuItem(leMenu,IDEVENT_BUILD_VOLUMES_FROM_TRIMESH, _("Auto-détection des volumes"),"./Bitmaps/popup_new.png"));
	Element::OnRightClic(leMenu);
}