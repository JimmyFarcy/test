#include "e_report_unknown_file.h"
#include <wx/mimetype.h> //Permet d'associer un fichier inconnu par psps avec tout les fichiers connu par le système d'exploitation
#include <wx/icon.h>
#include <wx/imaglist.h>
#include "last_cpp_include.hpp"

E_Report_Unknown::E_Report_Unknown(Element* parent,wxString Nom,wxString Path)
		:E_Report_File(parent,Nom,Path,ELEMENT_TYPE_REPORT_UNKNOWN)
{


}

E_Report_Unknown::E_Report_Unknown(Element* parent,wxXmlNode* nodeElement)
	:E_Report_File(parent,"Unnamed file","",ELEMENT_TYPE_REPORT_UNKNOWN,nodeElement)
{


}


wxXmlNode* E_Report_Unknown::SaveXMLDoc(wxXmlNode* NoeudParent)
{
	wxXmlNode* thisNode = E_Report_File::SaveXMLDoc(NoeudParent);
	thisNode->SetName("unk"); // Nom de la balise xml ( pas d'espace autorise )
	return thisNode;
}

bool E_Report_Unknown::ExtKnownByCurrentOs(const wxString& fileName)
{
	wxFileName fileConstr(fileName);
	if(fileConstr.GetExt().empty())
		return false;
	wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension(fileConstr.GetExt());
    if ( !ft )
    {
        return false;
	}else{
		wxString cmd;
		bool ok = ft->GetOpenCommand(&cmd, wxFileType::MessageParameters(fileName));
		delete ft;
		return ok;
	}
}

void E_Report_Unknown::FillWxTree(wxTreeCtrl* treeToFeed,const wxTreeItemId& parentId)
{
	if(!this->elementInfo.idElement.IsOk() && treeToFeed)
	{
		wxFileName fileConstr(this->filePath);
		wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension(fileConstr.GetExt());
		if ( ft )
		{
			wxIconLocation iconLocation;
			if(ft->GetIcon(&iconLocation))
			{
				wxIcon appIcon(iconLocation);
				if(appIcon.Ok())
					this->elementInfo.graphElement=treeToFeed->GetImageList()->Add(appIcon);	
			}
			delete ft;
		}
	}
	E_Report_File::FillWxTree(treeToFeed,parentId);
}
void E_Report_Unknown::OpenFile()
{
	wxFileName fileConstr(this->filePath);
	wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension(fileConstr.GetExt());
	if ( ft )
	{
		wxString fullPath;
		this->BuildFullPath(fullPath);
		wxFileName longPath(fullPath);
		longPath.MakeAbsolute();
		wxString cmd;
		bool ok = ft->GetOpenCommand(&cmd, wxFileType::MessageParameters(longPath.GetFullPath()));
		delete ft;
		wxExecute(cmd);
	}
	
}