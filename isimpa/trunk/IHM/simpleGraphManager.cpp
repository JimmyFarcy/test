#include "simpleGraphManager.h"
#include "simpleGraphDialogs.h"
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/clipbrd.h>
#include "base64.h"
#include "UtfConverter.h"
#include "last_cpp_include.hpp"

namespace sgSpace
{


	BEGIN_EVENT_TABLE(MainSimpleGraphWindow, simpleGraph)
		EVT_RIGHT_UP( MainSimpleGraphWindow::OnRightUp)
		EVT_MENU(ID_MSGW_ZOOMFIT, MainSimpleGraphWindow::OnZoomFitMenu)
		EVT_MENU(ID_MSGW_CONFIGURATION, MainSimpleGraphWindow::OnShowGraphParameters)
		EVT_MENU(ID_MSGW_EXPORT_SAVE_AS, MainSimpleGraphWindow::OnExportToImageFile)
		EVT_MENU(ID_MSGW_EXPORT_TO_CLIPBOARD, MainSimpleGraphWindow::OnExportToImageToClipboard)
		EVT_MENU_RANGE(ID_MSGW_FILTER_CHECK_FIRST,ID_MSGW_FILTER_CHECK_LAST, MainSimpleGraphWindow::OnSwitchCurveVisibility)
		EVT_MENU(ID_MSGW_FILTER_UNSELECT_ALL, MainSimpleGraphWindow::OnHideAllCurves)
		EVT_MENU(ID_MSGW_FILTER_SELECT_ALL, MainSimpleGraphWindow::OnShowAllCurves)
	END_EVENT_TABLE()


	MainSimpleGraphWindow::MainSimpleGraphWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos,
			const wxSize& size, long style, const wxString& name)
			: simpleGraph(parent,id, pos, size, style, name ),
				updateConfigOnChange(false),
				cfgManagerToUpdate(NULL)
	{


		parameters.DisableCfg(B_PARAM_RIGHT_CLICK_ZOOM_FIT);


	}

	void MainSimpleGraphWindow::OnZoomFitMenu(wxCommandEvent& event)
	{
		OnZoomOut();
	}

	void MainSimpleGraphWindow::OnShowGraphParameters(wxCommandEvent& event)
	{
		//Ouverture de l'interface de personalisation du rendu graphique
		SG_PropertySheetDialog* propertyDialog=new SG_PropertySheetDialog(this,-1,_("Configuration du rendu"));
		propertyDialog->ShowModal();
		if(cfgManagerToUpdate && updateConfigOnChange)
		{
			SaveConfig(cfgManagerToUpdate,cfgPathToUpdate);
		}
	}

	void MainSimpleGraphWindow::OnExportToImageToClipboard(wxCommandEvent& event)
	{
		if (wxTheClipboard->Open())
		{
			wxBitmapDataObject* bmpData= new wxBitmapDataObject(GetAreaBitmap());
			// This data objects are held by the clipboard,
			// so do not delete them in the app.
			wxTheClipboard->SetData( bmpData );
			wxTheClipboard->Close();
			wxTheClipboard->Flush(); //même si l'application est fermé, les données resteront dans le presse papier
		}
	}

	wxBitmap MainSimpleGraphWindow::GetAreaBitmap()
	{
		wxSize windowSize = GetClientSize();
		wxBitmap bitmap(windowSize.x, windowSize.y);
		wxClientDC dc(this);
		wxMemoryDC memDC;
		memDC.SelectObject(bitmap);
		memDC.Blit(0, 0, windowSize.x, windowSize.y, & dc, 0, 0);
		memDC.SelectObject(wxNullBitmap);
		return bitmap;
	}
	void MainSimpleGraphWindow::OnExportToImageFile(wxCommandEvent& event)
	{
		wxBitmap bitmap=GetAreaBitmap();
		wxInitAllImageHandlers();
		wxFileDialog saveFileDialog( this, _("Exporter le graphique"), defaultGraphSavePath, "", _("Image PNG (*.png)|*.png|Image Jpg (*.jpg)|*.jpg|Image Bitmap (*.bmp)|*.bmp"),wxFD_SAVE);
		if (saveFileDialog.ShowModal() == wxID_OK)
		{
			wxString FileName(saveFileDialog.GetPath());
			wxImage imageToSave=bitmap.ConvertToImage();
			imageToSave.SaveFile(FileName);
		}
	}

	void MainSimpleGraphWindow::OnSwitchCurveVisibility(wxCommandEvent& event)
	{
		SG_Element* drawingEl=this->GetDrawingElement(event.GetId()-ID_MSGW_FILTER_CHECK_FIRST);
		if(drawingEl)
		{
			drawingEl->Hide(!drawingEl->IsVisible());
			Refresh();
		}
	}
	void MainSimpleGraphWindow::OnHideAllCurves(wxCommandEvent& event)
	{
		ArrayOfGraphEl::iterator it;
		for( it = elements.begin(); it != elements.end(); ++it )
		{
			if(it->second->drawingArea==AREA_TYPE_MAINGRAPH)
				it->second->Hide();
		}
		Refresh();
	}
	void MainSimpleGraphWindow::OnShowAllCurves(wxCommandEvent& event)
	{
		ArrayOfGraphEl::iterator it;
		for( it = elements.begin(); it != elements.end(); ++it )
		{
			if(it->second->drawingArea==AREA_TYPE_MAINGRAPH)
				it->second->Hide(true);
		}
		Refresh();
	}
	void MainSimpleGraphWindow::OnRightUp( wxMouseEvent &event )
	{

		//Creation du menu popup

		wxMenu popup_menu;
		popup_menu.Append(ID_MSGW_ZOOMFIT, _("Zoom d'origine"));
		popup_menu.AppendSeparator();

		wxMenu* popup_menu_export= new wxMenu();
		popup_menu_export->Append(ID_MSGW_EXPORT_SAVE_AS, _("Vers un fichier image"));
		//popup_menu_export->Append(ID_MSGW_EXPORT_SAVE_AS_POSTSCRIPT_FILE, _("Vers un fichier PostScript"));
		popup_menu_export->Append(ID_MSGW_EXPORT_TO_CLIPBOARD, _("Vers le presse-papier"));

		popup_menu.Append(ID_MSGW_EXPORT, _("Exporter"),popup_menu_export);


		wxMenu* popup_menu_checkCurveVisibility= new wxMenu();
		//Ajout du sous-menu de séléction d'affichage
		popup_menu_checkCurveVisibility->Append(ID_MSGW_FILTER_SELECT_ALL, _("Tout afficher"));
		popup_menu_checkCurveVisibility->Append(ID_MSGW_FILTER_UNSELECT_ALL, _("Tout cacher"));
		popup_menu_checkCurveVisibility->AppendSeparator();
		ArrayOfGraphEl::iterator it;
		for( it = elements.begin(); it != elements.end(); ++it )
		{
			SG_Element* drawingEl=it->second;
			if(drawingEl->drawingArea==AREA_TYPE_MAINGRAPH)
			{
				wxMenuItem* newCheck=popup_menu_checkCurveVisibility->AppendCheckItem(ID_MSGW_FILTER_CHECK_FIRST+it->first,drawingEl->GetLabel());
				newCheck->Check(drawingEl->IsVisible());
			}
		}
		popup_menu.Append(ID_MSGW_FILTER, _("Afficher/Cacher courbes"),popup_menu_checkCurveVisibility);

		popup_menu.AppendSeparator();
		popup_menu.Append(ID_MSGW_CONFIGURATION, _("Modifier les parametres d'affichage"));

		wxWindow* associatedWindow=wxDynamicCast(event.GetEventObject(),wxWindow);
		if(associatedWindow)
			associatedWindow->PopupMenu(&popup_menu,event.GetPosition());
		else
			this->PopupMenu(&popup_menu,event.GetPosition());
	}


		bool MainSimpleGraphWindow::LoadConfig( wxConfigBase* configManager, const wxString& cfgPathName, bool saveModifications )
		{
			if(saveModifications)
			{
				updateConfigOnChange=true;
				cfgPathToUpdate=cfgPathName;
				cfgManagerToUpdate=configManager;
			}
			ArrayOfGraphEl::iterator it;
			for( it = elements.begin(); it != elements.end(); ++it ) //Pour chaque élément de dessin
			{
				SG_Element* drawingEl=it->second;
				//Il y a un enregistrement de style par libellé d'élément et par style de tracé, ainsi chaque tracé dispose de son propre style
				wxString grpName;
				grpName<<cfgPathName<<"/"<<drawingEl->el_style.GetDrawingMethod()<<"/"<<wxBase64::Encode((const wxUint8 *)WXSTRINGTOCHARPTR(drawingEl->GetLabel()), drawingEl->GetLabel().size());
				wxString cfgValue;
				if(configManager->Read(grpName,&cfgValue))
				{ //Une configuration existe pour cet élément
					drawingEl->el_style.FromSerialization(cfgValue);
				}
			}
			return true;
		}
		bool MainSimpleGraphWindow::SaveConfig( wxConfigBase* configManager, const wxString& cfgPathName )
		{
			ArrayOfGraphEl::iterator it;
			for( it = elements.begin(); it != elements.end(); ++it ) //Pour chaque élément de dessin
			{
				SG_Element* drawingEl=it->second;
				wxString grpName;
				grpName<<cfgPathName<<"/"<<drawingEl->el_style.GetDrawingMethod()<<"/"<<wxBase64::Encode((const wxUint8 *)WXSTRINGTOCHARPTR(drawingEl->GetLabel()), drawingEl->GetLabel().size());
				// Ecriture de la chaine dans le support de configuration
				configManager->Write(grpName,drawingEl->el_style.Serialize());
			}
			return true;
		}
}
