#include "first_header_include.hpp"

#include "data_manager/element.h"

#ifndef __E_GAMMEABS__
#define __E_GAMMEABS__

/** \file e_gammeabsorption.h
   \brief Classe correspondant au spectre d'un encombrement

   Il calcul automatiquement la valeur du Niveau sonore global moyen à chaque modification d'un de ses membres.
*/

/**
   \brief Classe correspondant au spectre d'un encombrement

   Il calcul automatiquement la valeur du Niveau sonore global moyen à chaque modification d'un de ses membres.	
	@see E_Scene_Encombrements_Encombrement_Model
	@see E_Scene_Encombrements_Encombrement_Cuboide
*/
class E_GammeAbsorption: public Element
{
private:

	void CalcNiveauSonoreGlobalMoyen(wxString typeDb);
	void InitProperties();
	void CopyAverageToEachRow(wxString typeS);
	bool ignoreNextUpdate;
protected:
	void Modified(Element* eModif);
public:
	E_GammeAbsorption(wxXmlNode* nodeElement,Element* parent);
	E_GammeAbsorption(Element* parent);
	virtual wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent);
	virtual wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent);
};

#endif