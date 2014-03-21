#include "first_header_include.hpp"

#include "e_userprefitem.hpp"
#include <wx/hashmap.h>
#include <wx/dir.h>
#include <wx/filename.h>

#ifndef __E_USERPREFITEMISO__
#define __E_USERPREFITEMISO__


/*! \file e_userprefitemisotemplate.hpp
    \brief Correspond à l'élément porteur de propriétés iso
*/
/**
	\brief Correspond à l'élément porteur de propriétés iso
	Cette classe permet de placer des propriétés
*/
class E_UserPreferenceItemIsoTemplate: public E_UserPreferenceItem
{
protected:
	bool folder_parsed;
	std::list<wxString> fullPathIso;
public:
	E_UserPreferenceItemIsoTemplate(Element* parent,wxString Nom, wxXmlNode* nodeElement=NULL)
		:E_UserPreferenceItem(parent,Nom,ELEMENT_TYPE_USER_PREFERENCE_ITEM_ISOTEMPLATE,nodeElement)
		,folder_parsed(false)
	{
		if(!nodeElement)
			this->AppendPropertyText("path_isofile","path_isofile",ApplicationConfiguration::CONST_RESOURCE_DATA_FOLDER+ApplicationConfiguration::CONST_RESOURCE_ISO_FOLDER+"jet.gpl")->Hide();
		
	}

	virtual bool IsContainsProperties()
	{
		return true;
	}
	virtual void InitProp()
	{
		if(!folder_parsed)
		{
			wxArrayString files_found;
			wxString folderiso(ApplicationConfiguration::CONST_RESOURCE_FOLDER+ApplicationConfiguration::CONST_RESOURCE_DATA_FOLDER+ApplicationConfiguration::CONST_RESOURCE_ISO_FOLDER);
			int defaultIso(0);
			Element* isoprop(NULL);
			wxStringHash strHash;
			if(this->IsPropertyExist("isofilename",&isoprop))
			{
				defaultIso=this->GetListConfig("isofilename");
				this->DeleteElementByXmlId(isoprop->GetXmlId());
			}else{
				defaultIso=strHash("jet");
			}

			std::vector<wxString> gplFileName;
			std::vector<int> gplFileId;
			if(wxDirExists(folderiso))
			{
				if(wxDir::GetAllFiles(folderiso,&files_found,"*.gpl"))
				{
					gplFileName.reserve(files_found.size());
					gplFileId.reserve(files_found.size());
					for(wxArrayString::iterator itfile=files_found.begin();itfile!=files_found.end();itfile++)
					{
						fullPathIso.push_back((*itfile));
						wxFileName fichGPL((*itfile));
						int idFichier=(int)strHash(fichGPL.GetName());
						gplFileId.push_back(idFichier);
						gplFileName.push_back(fichGPL.GetName());
					}
				}
			}
			this->AppendPropertyList("isofilename","Palette des niveaux",gplFileName,defaultIso,false,1,gplFileId,false);
			_("Palette des niveaux");
			folder_parsed=true;
		}
	}
	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("prefitemiso"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
	virtual void Modified(Element* eModif)
	{
		if(eModif->GetElementInfos().libelleElement=="isofilename")
		{
			int selectedEl=this->GetListConfig("isofilename");
			wxStringHash strHash;
			for(std::list<wxString>::iterator itpal=this->fullPathIso.begin();itpal!=this->fullPathIso.end();itpal++)
			{
				wxFileName fileiso(*itpal);
				if((int)strHash(fileiso.GetName())==selectedEl)
				{
					this->UpdateStringConfig("path_isofile",(*itpal));
					break;
				}
			}
		}
		E_UserPreferenceItem::Modified(eModif);
	}
};

#endif