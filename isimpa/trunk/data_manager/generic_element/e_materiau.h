#include "first_header_include.hpp"

#include "data_manager/element.h"

#ifndef __E_MATERIAU__
#define __E_MATERIAU__

/** \file e_materiau.h
   \brief Classe correspondant au spectre d'un type de surface
*/

/**
   \brief Classe correspondant au spectre d'un type de surface

    Les calculs entre chaque ligne et la valeur global est spécifié ici
	@see E_Data_Row_BandeFreq
	@see E_Scene_Bdd_Materiaux_User_Materiau
	@see E_Scene_Bdd_Materiaux_App_Materiau
*/
class E_Materiau: public Element
{
protected:
	bool ignoreModification; /*!< A vrai, bloque la mis à jour du champ dB global et la propagation vers les éléments superieur*/
	int idMateriau; /*!< Identifiant du matériau (voir ApplicationConfiguration) */
	/** 
     * @brief Structure champ lecture seule
	 *
	 *    Lors de la construction des sous-élément, se tableau indique lequel de ses sous-éléments seront en lecture seule.
	 */
	struct t_idChamp
	{
		int row; /*!< Ligne */
		int col; /*!< Colonne */
	};
	/**
	 * Calcul du niveau Sonore Global
	 * @param[in] typeDb Nom de la colonne a calculer
	 */
	void CalcNiveauSonoreGlobal(wxString typeDb);
	void Modified(Element* eModif);
	void InitProperties();
public:
	E_Materiau(Element* parent,wxString Nom,ELEMENT_TYPE _type,wxXmlNode* nodeElement=NULL);
	virtual ~E_Materiau();
	/**
	 * Retourne l'identifiant du matériau
	 * @return Entier correspondant à l'identifiant
	 * @see ApplicationConfiguration
	 */
	int GetIdMateriau();
	/**
	 * Retourne l'identifiant du matériau
	 * @return Type du type du matériau (Utilisateur ou Application)
	 * @see ApplicationConfiguration
	 */
	Element::ELEMENT_TYPE GetTypeMateriau();
	virtual void InitProp();
	virtual wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);
	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent);
};

#endif