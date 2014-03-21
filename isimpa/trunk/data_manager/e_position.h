#include "first_header_include.hpp"

#include "data_manager/e_data.h"
#include "3dengine/Core/Mathlib.h"

/** \file e_position.h
   \brief Element représentant une position dans l'espace de la scène

   En ajoutant cet élément à votre nouvel élément, vous permettez à l'utilisateur de définir une position x,y,z
   Soit par la saisie des coordonnées, soit par un clic gauche sur la vue 3D
*/

/**
   \brief Element représentant une position dans l'espace de la scène

   En ajoutant cet élément à votre nouvel élément, vous permettez à l'utilisateur de définir une position x,y,z
   Soit par la saisie des coordonnées, soit par un clic gauche sur la vue 3D

   @see Element::AppendPropertyPosition()
*/

#ifndef __ELEMENT_POSITION__
#define __ELEMENT_POSITION__

class E_Position: public E_Data
{
	bool ignoreModification;
public:
	E_Position( wxXmlNode* noeudCourant ,  Element* parent)
		:E_Data(parent,"Position","pos",Element::ELEMENT_TYPE_POSITION,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_POSITION);
		ignoreModification=false;
		//Maj version < 06/11/2008
		wxString propVal;
		if(noeudCourant->GetPropVal("strId",&propVal) && propVal!="")
		{
			propertyLabel=this->elementInfo.libelleElement;
			this->elementInfo.libelleElement=propVal;
			noeudCourant->DeleteProperty("strId");
		}
		if(noeudCourant->GetPropVal("expcore",&propVal) && propVal!="")
		{
			this->exportToCore=true;
			noeudCourant->DeleteProperty("expcore");
		}
		//Fin Maj version < 06/11/2008
	}

	/**
	 * Constructeur de E_Position
	 *
	 * @param parent Element parent
	 * @param _name Nom de l'élément ( Lors de l'appel GetPositionValue( _name ) )
	 * @param libel Libellé de la propriété ( visible dans l'arbre )
	 * @param defaultvalue Position x,y,z par défaut
	 * @param _exportToCore A vrai cette propriété sera visible par les coeurs de calcul lors de l'exportation
	 * @see Element::GetPositionValue()
	 */
	E_Position( Element* parent,wxString _name,wxString libel,vec3 defaultvalue,bool _exportToCore=false)
		:E_Data(parent,_name,libel,Element::ELEMENT_TYPE_POSITION,NULL,false,1,_exportToCore)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_EL_POSITION);
		ignoreModification=false;
		initProps(defaultvalue,_exportToCore);
	}
	void FillWxTree(wxTreeCtrl* treeToFeed,const wxTreeItemId& parentId)
	{
		Element::FillWxTree(treeToFeed,parentId);
	}
	virtual wxString GetTreeLabel() const
	{
		return propertyLabel;
	}
	void OnRightClic(wxMenu* leMenu)
	{
		leMenu->Append(GetMenuItem(leMenu,Element::IDEVENT_SELECT_POSITION, _("Définir via la vue 3D")));
		E_Data::OnRightClic(leMenu);
	}
	wxString GetColTitle(int col)
	{
		return _("Valeur (m)");
	}
	/**
	 * Affecte la valeur de la position
	 * @param newPos Nouvelle valeur de l'élément
	 */
	void SetPosValue(vec3 newPos)
	{
		ignoreModification=true;
		this->UpdateDecimalConfig("x",newPos.x);
		this->UpdateDecimalConfig("y",newPos.y);
		this->UpdateDecimalConfig("z",newPos.z);
		ignoreModification=false;
		this->Modified(this);
	}
	/**
	 * Retourne la valeur du vecteur
	 * @return Vecteur de position
	 **/
	vec3 GetPosValue()
	{
		return vec3(this->GetDecimalConfig("x"),this->GetDecimalConfig("y"),this->GetDecimalConfig("z"));
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		if(exportToCore)
		{
			return E_Data::SaveXMLCoreDoc(NoeudParent);
		}else{
			return NoeudParent;
		}
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = E_Data::SaveXMLDoc(NoeudParent);
		thisNode->SetName("position"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
	void Modified(Element* eModif)
	{
		if(!ignoreModification)
		{
			if(eModif!=this)
			{
				this->Modified(this);
			}
			E_Data::Modified(eModif);
		}
	}
private:

	void initProps(vec3 defaultval,bool exportToCore)
	{
		this->AppendPropertyDecimal("x","x",defaultval.x,false,6,false,false,0,0,exportToCore);
		this->AppendPropertyDecimal("y","y",defaultval.y,false,6,false,false,0,0,exportToCore);
		this->AppendPropertyDecimal("z","z",defaultval.z,false,6,false,false,0,0,exportToCore);
	}
};

#endif
