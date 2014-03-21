#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/appconfig.h"
/** \file e_scene_projet_informations.h
 *  \brief Element représentant les informations du projet
 */

/**
 *  \brief Element représentant les informations du projet
 */
class E_Scene_Projet_Information: public Element
{
public:
	E_Scene_Projet_Information( wxXmlNode* noeudCourant ,  Element* parent)
		:Element(parent,"Informations",Element::ELEMENT_TYPE_SCENE_PROJET_INFORMATION,noeudCourant)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_INFORMATION);
		_("Informations");
		if(!this->IsPropertyExist("nbencombrementenable"))
		{
			AppendNewProperties();
			this->SetReadOnlyAllConfig();
		}
	}

	E_Scene_Projet_Information( Element* parent)
		:Element(parent,"Informations",Element::ELEMENT_TYPE_SCENE_PROJET_INFORMATION)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_INFORMATION);
		InitProperties();
	}
	/**
	 * Nouveaux champs à la version 1.02 du logiciel
	 */
	void AppendNewProperties()
	{

		this->AppendPropertyEntier("nbencombrementenable","Nombre d'encombrements actifs",0);
		this->AppendPropertyEntier("nbsourcesenable","Nombre de sources sonores actives",0);
		_("Nombre d'encombrements actifs");
		_("Nombre de sources sonores actives");
	}
	/*
	 * Ajoute les éléments de configuration tel que l'emplacement du fichier de modèle et le chemin de sauvegarde par défaut du projet
	 */
	void InitProperties() 
	{
		this->AppendPropertyEntier("nbfacemodel","Nombre de faces de la scène",0);
		this->AppendPropertyEntier("nbencombrement","Nombre d'encombrements",0);
		this->AppendPropertyEntier("nbrecepteurp","Nombre de récepteurs ponctuels",0);
		this->AppendPropertyEntier("nbrecepteurs","Nombre de récepteurs surfaciques",0);
		this->AppendPropertyEntier("nbsources","Nombre de sources sonores",0);
		this->AppendPropertyEntier("nbsurfacegroup","Nombre de groupes de surfaces",0);
		this->AppendPropertyDecimal("volmodel","Volume total de la scène (m3)",0.f,true,1);
		this->AppendPropertyDecimal("surfscene","Surface totale de la scène (m2)",0.f,true,1);
		AppendNewProperties();
		this->SetReadOnlyAllConfig();
		_("Nombre de faces de la scène");
		_("Nombre d'encombrements");
		_("Nombre de récepteurs ponctuels");
		_("Nombre de récepteurs surfaciques");
		_("Nombre de sources sonores");
		_("Nombre de groupes de surfaces");
		_("Volume total de la scène (m3)");
		_("Surface totale de la scène (m2)");
	}
		
	void InitProp()
	{
		this->UpdateEntierConfig("nbfacemodel",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Faces);
		this->UpdateEntierConfig("nbencombrement",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement);
		this->UpdateEntierConfig("nbencombrementenable",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Encombrement_Actifs);
		this->UpdateEntierConfig("nbrecepteurp",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurP);
		this->UpdateEntierConfig("nbrecepteurs",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_RecepteurS);
		this->UpdateEntierConfig("nbsources",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources);
		this->UpdateEntierConfig("nbsourcesenable",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_Sources_Actives);
		this->UpdateEntierConfig("nbsurfacegroup",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.quant_SurfGroup);
		if(ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.volScene!=-1)
			this->UpdateDecimalConfig("volmodel",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.volScene);
		if(ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.surfScene!=-1)
			this->UpdateDecimalConfig("surfscene",ApplicationConfiguration::GLOBAL_CURRENT_APPLICATION_INFORMATIONS.surfScene);
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("info"); // Nom de la balise xml ( pas d'espace autorise )

		return thisNode;
	}
};