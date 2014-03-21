#include "uimenuitem.hpp"

wxUiMenuItem::wxUiMenuItem(wxMenu *parentMenu,
               int id,
               const wxString& name,
               const wxString& help,
               wxItemKind kind,
               wxMenu *subMenu)
			   :wxMenuItem(parentMenu,id,name,help,kind,subMenu)
{


}


	wxString wxUiMenuItem::GetBitmapPath()
	{
		return bitmapPath;
	}
	void wxUiMenuItem::SetBitmapPath(const wxString& _bitmapPath)
	{
		bitmapPath=_bitmapPath;
	}
