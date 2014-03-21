#include "first_header_include.hpp"

#include "data_manager/drawable_element.h"
#include "e_scene_recepteursp_recepteur_rendu.h"
#include "e_scene_recepteursp_recepteur_proprietes.h"
#include "data_manager/generic_element/e_property_freq.h"


/** \file e_scene_recepteursp_recepteur.h
   \brief Element correspondant à un récépteur ponctuel

   Cet élément hérite de E_Drawable afin d'être représenté dans la vue 3D.
*/

/**
   \brief Element correspondant à un récépteur ponctuel

   Cet élément hérite de E_Drawable afin d'être représenté dans la vue 3D.
*/

class E_Scene_Recepteursp_Recepteur: public E_Drawable
{
private:
	bool lockdirectioncomputation;
public:
	void AddDirectionProperty()
	{
		this->AppendPropertyPosition("direction_dot","Direction",vec3());
		_("Direction");
	}
	E_Scene_Recepteursp_Recepteur( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Drawable(parent,"Récepteur",Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR,noeudCourant)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_PUNCTUAL_RECEIVER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_PUNCTUAL_RECEIVER_CLOSE);
		this->AllowMultipleSelection();
		lockdirectioncomputation=true;
		bool noiseSet=false;
		this->elementInfo.userDestroyable=true;
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurP++;
		this->elementInfo.exportLblToCore=true;
		_("Récepteur");
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
					
					if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_PROPRIETES)
					{
						this->AppendFils(new E_Scene_Recepteursp_Recepteur_Proprietes(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_RENDU)
					{
						this->AppendFils(new E_Scene_Recepteursp_Recepteur_Rendu(currentChild,this));
					}else if(typeEle==Element::ELEMENT_TYPE_PROPERTY_FREQ)
					{
						this->AppendFils(new E_Property_Freq(currentChild,this));
						noiseSet=true;
					}
				}
				currentChild = currentChild->GetNext();
			}
		}
		if(!noiseSet) //maj version < 4/11/2008
		{
			this->AppendFils(new E_Property_Freq(this,"Bruit de fond"));
		}
		if(!IsPropertyExist("direction_dot")) //maj version < 6/11/2008
		{
			AddDirectionProperty();
		}
		lockdirectioncomputation=false;
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"recepteur_ponctuel");
		thisNode->AddProperty("id",Convertor::ToString(elementInfo.xmlIdElement));
		thisNode->AddProperty("name",elementInfo.libelleElement);
		AddDirectionProperty();
		return Element::SaveXMLCoreDoc(thisNode);
	}
	/**
	 * Constructeur de création, appelé lors de l'ajout d'un nouveau récepteur.
	 * @param parent Element parent
	 * @param nom Libellé du recepteur
	 */
	E_Scene_Recepteursp_Recepteur( Element* parent,wxString nom=wxString::Format(_("Récepteur %i"),ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurP+1))
		:E_Drawable(parent,nom,Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR)
	{
		SetIcon(GRAPH_STATE_EXPANDED,GRAPH_PUNCTUAL_RECEIVER_OPEN);
		SetIcon(GRAPH_STATE_NORMAL,GRAPH_PUNCTUAL_RECEIVER_CLOSE);
		this->AllowMultipleSelection();
		lockdirectioncomputation=true;
		this->elementInfo.exportLblToCore=true;
		this->elementInfo.userDestroyable=true;
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurP++;
		this->AppendFils(new E_Scene_Recepteursp_Recepteur_Proprietes(this));
		this->AppendFils(new E_Scene_Recepteursp_Recepteur_Rendu(this));
		this->AppendFils(new E_Property_Freq(this,"Bruit de fond"));
		_("Bruit de fond");
		_("Position");
		AddDirectionProperty();
		this->AppendPropertyPosition("pos_recepteur","Position",vec3(0,0,0),true);
		lockdirectioncomputation=false;
	}

	~E_Scene_Recepteursp_Recepteur()
	{
		ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurP--;
	}

	void DrawItem( vec4 unitizeValue )
	{
		vec3 position=this->GetPositionConfig("pos_recepteur");
		vec3 couleurElement;
		vec3 destinationFleche;
		Element* elFils=this->GetElementByType(Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_RENDU);
		if(elFils!=NULL)
			couleurElement=elFils->GetColorConfig("couleur");
		Element* elFilsProperty=this->GetElementByType(Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_PROPRIETES);
		if(elFilsProperty)
		{
			destinationFleche.set(elFilsProperty->GetDecimalConfig("u"),elFilsProperty->GetDecimalConfig("v"),elFilsProperty->GetDecimalConfig("w"));
			destinationFleche=position+(((destinationFleche/destinationFleche.length())/unitizeValue.w)*.1f);
		}
		destinationFleche=coordsOperation::CommonCoordsToGlCoords(unitizeValue,destinationFleche);
		position=coordsOperation::CommonCoordsToGlCoords(unitizeValue,position);
		labelInfo.clear();
		bool drawText=false;
		if(elFils!=NULL)
			drawText=elFils->GetBoolConfig("showlabel");
		if(drawText)
		{
			AddText(" "+this->elementInfo.libelleElement,position,couleurElement);
		}

		this->DrawPoint( position,couleurElement,5);
		//this->DrawArrow( position,destinationFleche,couleurElement/255,.008f);
		this->BeginLines();
		this->DrawLine( position,destinationFleche,couleurElement/255);
		this->EndLines();
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


	void Modified(Element* eModif)
	{
		t_elementInfo filsInfo=eModif->GetElementInfos();
		if(!lockdirectioncomputation && filsInfo.typeElement==ELEMENT_TYPE_POSITION)
		{
			
			//L'utilisateur a peut être désigné un élément dans le décor vers lequel ce récepteur ponctuel doit s'orienter
			vec3 directionTo=this->GetPositionConfig("direction_dot");
			vec3 position=this->GetPositionConfig("pos_recepteur");
			if(!directionTo.barelyEqual(position)) //si l'objet pointé n'est pas trop proche du recepteur ponctuel
			{
				vec3 nvDirection=directionTo-position;
				nvDirection/=nvDirection.length();	//Normalisation
				Element* elFilsProperty=this->GetElementByType(Element::ELEMENT_TYPE_SCENE_RECEPTEURSP_RECEPTEUR_PROPRIETES);
				if(elFilsProperty)
				{
					elFilsProperty->UpdateDecimalConfig("u",nvDirection.x);
					elFilsProperty->UpdateDecimalConfig("v",nvDirection.y);
					elFilsProperty->UpdateDecimalConfig("w",nvDirection.z);
					this->Modified(this);
				}
			}
		}
		E_Drawable::Modified(eModif);
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("recepteurp"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
	void BeginDrag(wxTreeEvent& treeEvent,wxTreeCtrl* tree)
	{
		treeEvent.Allow();
	}
};