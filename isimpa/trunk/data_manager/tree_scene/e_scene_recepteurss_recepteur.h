#include "first_header_include.hpp"

#include "e_scene_groupesurfaces_groupe.h"
#include "data_manager/drawable_element.h"
#include "e_scene_recepteurss_recepteur_rendu.h"
#include "e_scene_recepteurss_recepteur_proprietes.h"

/** \file e_scene_recepteurss_recepteur.h
   \brief Element correspondant à un récépteur de surface

   Cet élément hérite de E_Drawable afin d'être représenté dans la vue 3D.
*/

/**
   \brief Element correspondant à un récépteur de surface

   Cet élément hérite de E_Drawable afin d'être représenté dans la vue 3D.
*/
class E_Scene_Recepteurss_Recepteur: public E_Drawable
{
public:
	E_Scene_Recepteurss_Recepteur( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Drawable(parent,"Récepteur scène",Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACE_RECEIVER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACE_RECEIVER_CLOSE);
		this->AllowMultipleSelection();
		this->elementInfo.userDestroyable=true;
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurS++;
		_("Récepteur scène");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_PROPRIETES)
					{
						this->AppendFils(new E_Scene_Recepteurss_Recepteur_Proprietes(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR_RENDU)
					{
						this->AppendFils(new E_Scene_Recepteurss_Recepteur_Rendu(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_GROUPESURFACES_GROUPE)
					{
						this->AppendFils(new E_Scene_Groupesurfaces_Groupe(currentChild,this));
					}
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	/**
	 * Constructeur de création, appelé lors de l'ajout d'un nouveau récepteur.
	 * @param parent Element parent
	 * @param nom Libellé du recepteur
	 */
	E_Scene_Recepteurss_Recepteur( Element* parent,wxString nom="Récepteur")
		:E_Drawable(parent,nom,Element::ELEMENT_TYPE_SCENE_RECEPTEURSS_RECEPTEUR)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_SURFACE_RECEIVER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_SURFACE_RECEIVER_CLOSE);
		this->AllowMultipleSelection();
		this->elementInfo.userDestroyable=true;
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurS++;
		this->AppendFils(new E_Scene_Recepteurss_Recepteur_Proprietes(this));
		//this->AppendFils(new E_Scene_Recepteurss_Recepteur_Rendu(this));
		this->AppendFils(new E_Scene_Groupesurfaces_Groupe(this,"Surface",true));
		_("Surface");
	}
	~E_Scene_Recepteurss_Recepteur()
	{
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurS--;
	}

	void DrawItem( vec4 unitizeValue )
	{

	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"recepteur_surfacique");
		thisNode->AddProperty("id",Convertor::ToString(elementInfo.xmlIdElement));
		
		thisNode->AddProperty("name",elementInfo.libelleElement);
		return thisNode;
	}

	void OnBeginLabelEdit(wxTreeEvent& treeEvent)
	{
		//On autorise l'edition en surchargeant l'événement
	}
	 
	void OnEndLabelEdit(wxTreeEvent& treeEvent)
	{
		if(treeEvent.GetLabel()!="")
		{
			this->elementInfo.libelleElement=treeEvent.GetLabel();
			this->Modified(this); //Indique le l'element a été modifié
		}
	}


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("recepteurs"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};