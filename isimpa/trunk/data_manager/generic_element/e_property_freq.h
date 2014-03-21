#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/appconfig.h"

#ifndef __PROPERTYFREQ__
#define __PROPERTYFREQ__

/** \file e_property_freq.h
   \brief Element représentant la propriété de spectre d'une source sonore (liste déroulante de la source suivi du spectre)
*/

/**
   \brief Element représentant la propriété de spectre d'une source sonore (liste déroulante de la source suivi du spectre)
   @see E_Scene_Sources_Source
*/
class E_Property_Freq: public Element
{
protected:
	int idSpectre;
	ELEMENT_TYPE typeSpectre;
	std::vector<ApplicationConfiguration::t_lstSpec> lastLst;
	bool ignoreUpdate;
	bool askReload;
	static bool orderSpectrums(Element* lEl,Element* rEl);
	void CreateGlobalVal(float valDefault);
	/**
	 * Met à jour la colonne Lw depuis la base de données
	 */
	void LoadLwFromBdd();
	void CreateExtendedBFreq();
	/**
	 * Calcul du niveau global à partir du niveau par bande
	 */
	void CalcNiveauSonoreGlobal(const wxString& typeDb);
	void SetGlobalLevel( const wxString& typeDb, wxFloat32 lvl );
public:
	E_Property_Freq( wxXmlNode* noeudCourant ,  Element* parent);

	/**
	 * Cette méthode a été surchargée afin d'ajouter aux propriétés le spectre correspondant au spectre sélectionné dans la liste déroulante
	 */
	E_Property_Freq( Element* parent, wxString label="Spectre");
	void InitProp(); //Appelé par la grille de propriété avant l'affichage
	void Modified(Element* eModif);
	bool IsAskPropReload();
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent);
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);
	/**
	 * Retourne la valeur courante global
	 */
	float GetGlobaldBVal(const wxString& dbCol);
};
#endif