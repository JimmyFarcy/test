#include "e_materiau.h"
#include "data_manager/appconfig.h"
#include "data_manager/e_data_row_materiau.h"
#include "last_cpp_include.hpp"

E_Materiau::E_Materiau(Element* parent,wxString Nom,ELEMENT_TYPE _type,wxXmlNode* nodeElement)
	:Element(parent,"Spectre du matériau",_type,nodeElement)
{
	SetIcon(GRAPH_STATE_ALL,GRAPH_SPECTRUM);
	ignoreModification=false;
	_("Spectre du matériau");
	idMateriau=ApplicationConfiguration::GetFreeMateriauId();

	wxString propVal;
	//Affecte la valeur de l'element

	if(nodeElement!=NULL && nodeElement->GetPropVal("wxid",&propVal))
	{
		//Element initialisé AVEC Xml
		long lval;
		if(nodeElement->GetPropVal("idmateriau",&propVal))
		{
			propVal.ToLong(&lval);
			idMateriau=lval;
		}
		wxXmlNode* currentChild;
		currentChild = nodeElement->GetChildren();
		wxString propValue;
		while(currentChild!=NULL)
		{
			if(currentChild->GetPropVal("eid",&propValue))
			{
				long typeEle;
				propValue.ToLong(&typeEle);
				if(typeEle==Element::ELEMENT_TYPE_ROW_MATERIAU)
				{
					this->AppendFils(new E_Data_Row_Materiau(currentChild,this));
				}			
			}
			currentChild = currentChild->GetNext();
		}
	}else{
		Modified(this); //Ajout de la propriété en cours d'execution
	}
	ApplicationConfiguration::AddMateriau(this);
}
E_Materiau::~E_Materiau()
{
	ApplicationConfiguration::DeleteMateriau(this->elementInfo.xmlIdElement);
}

Element::ELEMENT_TYPE E_Materiau::GetTypeMateriau()
{
	return this->elementInfo.typeElement;
}
void E_Materiau::InitProperties()
{
	const std::vector<ApplicationConfiguration::t_freq> tabfreq=ApplicationConfiguration::GetAllFrequencies();
	//Ajout des bandes
	ignoreModification=true;
	for(int i=0;i<tabfreq.size();i++)
	{
		wxString name;
		wxString label;
		label<<tabfreq[i]<<" Hz";
		name<<tabfreq[i];
		E_Data_Row_Materiau* nouvLigne=new E_Data_Row_Materiau(this,name,label);
		this->AppendFils(nouvLigne);
	}
	ignoreModification=false;
}
void E_Materiau::InitProp()
{

}


wxXmlNode* E_Materiau::SaveXMLDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
	thisNode->SetName("materiau"); // Nom de la balise xml ( pas d'espace autorise )
	//Sauvegarde de l'identifiant du matériau
	thisNode->DeleteProperty("idmateriau");
	thisNode->AddProperty("idmateriau",Convertor::ToString(idMateriau));	
	return thisNode;
}


wxXmlNode* E_Materiau::SaveXMLCoreDoc(wxXmlNode* NoeudParent)
{
	//Recherche si le matériau est utilisé dans le projet courant
	bool isUsedInProject=false;
	t_HashElement::iterator itEnd=ApplicationConfiguration::EndRef(ApplicationConfiguration::ELEMENT_REF_TYPE_FACEGROUP);
	for( 	t_HashElement::iterator it=ApplicationConfiguration::BeginRef(ApplicationConfiguration::ELEMENT_REF_TYPE_FACEGROUP); it!=itEnd && !isUsedInProject;it++)
	{
		if(it->second->GetEntierConfig("idmat")==idMateriau)
		{
			isUsedInProject=true;
			break;
		}
	}
	if(idMateriau==0) //Le matériau par défaut est toujours exporté
		isUsedInProject=true;	

	if(isUsedInProject)
	{
		wxXmlNode* NoeudCourant=new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"type_surface");
		NoeudCourant->AddProperty("id",Convertor::ToString(idMateriau));
		return Element::SaveXMLCoreDoc(NoeudCourant);
	}else{
		return NoeudParent;
	}
}
int E_Materiau::GetIdMateriau()
{
	return idMateriau;
}
void E_Materiau::Modified(Element* eModif)
{
	if(!ignoreModification)
		Element::Modified(eModif); //Element de base modifié
}
