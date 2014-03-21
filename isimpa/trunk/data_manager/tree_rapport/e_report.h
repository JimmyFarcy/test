#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/tree_rapport/e_report_folder.h"

/** \file e_report.h
   \brief Element représentant la racine des rapports de calcul d'un projet
*/

/**
   \brief Element représentant la racine des rapports de calcul d'un projet
*/

class E_Report: public Element
{
private:
void (*pointeurFonctionEvent)(Element*);
bool eventBinded;
public:
	E_Report( wxXmlNode* noeudCourant )
		:Element(NULL,"Résultats",Element::ELEMENT_TYPE_RESULT_ROOT ,noeudCourant)
	{
		eventBinded=false;
		_("Résultats");
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
					if(typeEle==ELEMENT_TYPE_REPORT_FOLDER)
					{

						//maj version 1.0.3
						if(currentChild->GetPropVal("filepath",&propValue) && propValue==wxString("current")+wxFileName::GetPathSeparator()+wxString("report")+wxFileName::GetPathSeparator())
						{
							currentChild->DeleteProperty("filepath");
							currentChild->AddProperty("filepath",ApplicationConfiguration::CONST_REPORT_FOLDER_PATH);
						}
						//fin maj version < 1.0.3
						this->AppendFils(new E_Report_Folder(this,currentChild));
					}
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Report( )
		:Element(NULL,"Résultats",Element::ELEMENT_TYPE_RESULT_ROOT)
	{
		eventBinded=false;
		wxString ReportFolder=ApplicationConfiguration::GLOBAL_VAR.cacheFolderPath+ApplicationConfiguration::CONST_REPORT_FOLDER_PATH;
		if(!wxFileExists(ReportFolder))
			wxMkdir(ReportFolder);
		this->AppendFils(new E_Report_Folder(this,"Résultats",ApplicationConfiguration::CONST_REPORT_FOLDER_PATH));
	}
	/**
		Initialise le pointeur de méthode vers le gestionnaire de projet
		@param _pointeurFonctionEvent Méthode d'événement de mise à jour
		@see OnElementRootUpdate()
	*/
	void BindUpdateEvent(void (*_pointeurFonctionEvent)(Element*))
	{
		pointeurFonctionEvent=_pointeurFonctionEvent;
		eventBinded=true;
	}
	/**
	 * Actualise la liste des rapports de résultat
	 */
	void RefreshReportFolder()
	{
		if(!this->fils.empty())
		{
			Element* eleBase=this->GetElementByType(Element::ELEMENT_TYPE_REPORT_FOLDER);
			if(eleBase)
			{
				E_Report_Folder* reportEle=dynamic_cast<E_Report_Folder*>(eleBase);
				if(reportEle)
				{
					reportEle->RefreshFolderContents();
					reportEle->FillWxTree(treeCtrl,this->elementInfo.idElement);
				}
			}
		}
	}


	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("Report"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
protected:

	void Modified(Element* eModif)
	{
		Element::Modified(eModif);
		if(eventBinded)
			(*pointeurFonctionEvent)(eModif);
	}
};
