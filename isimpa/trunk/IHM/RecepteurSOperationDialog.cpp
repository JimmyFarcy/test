﻿#include "RecepteurSOperationDialog.h"

#include <wx/frame.h>
#include <wx/sizer.h>
#include "ComboTreeCtrl.h"
#include <wx/stattext.h>
#include <wx/log.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include "last_cpp_include.hpp"

RecepteurSelectionWizard::RecepteurSelectionWizard(wxFrame *frame, E_Report_File* _rootFolder)
        : wxWizard(frame,wxID_ANY,_("Opération de soustraction de récepteur de surfaces"),wxBitmap("./Bitmaps/wiz3.png", wxBITMAP_TYPE_PNG)),
		rootFolder(_rootFolder)
{ 
	_("&Cancel");
	_("< &Back");
    m_page1 = new PageReferenceSelection(this);
	PageOtherRecepeurSurfSelection* otherPage=new PageOtherRecepeurSurfSelection(this);
	PageReferenceSelection::Chain(m_page1,otherPage);


    GetPageAreaSizer()->Add(m_page1);
    GetPageAreaSizer()->Add(otherPage);
 
}


RecepteurSelectionWizard::t_UserSelection RecepteurSelectionWizard::GetUserPreferences()
{
	return userSelection;
}

void RecepteurSelectionWizard::RefreshNextButtonState()
{
	wxButton* btNext=wxDynamicCast(wxWindow::FindWindowById(wxID_FORWARD,this),wxButton);
	btNext->SetLabel( HasNextPage(this->GetCurrentPage()) ? _("&Next >") : _("&Finish"));
}
BEGIN_EVENT_TABLE(PanelReferenceSelection, wxPanel)
	EVT_COMBOBOX(WIZARDCTRL_REFERENCE_SELECTION,  PanelReferenceSelection::OnRecepteurSurfSelected)
END_EVENT_TABLE()

PanelReferenceSelection::PanelReferenceSelection(wxWindow* parent,RecepteurSelectionWizard *wizManager, wxWindowID id)
		: wxPanel(parent, id)
	{

        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

		wxGenericComboCtrl* NewControl = new wxGenericComboCtrl(this, WIZARDCTRL_REFERENCE_SELECTION, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxCB_READONLY);

		ComboTreeCtrl* popupCtrlTree=new ComboTreeCtrl();
		popupCtrlTree->AddActiveFilter(Element::ELEMENT_TYPE_REPORT_RECEPTEURSSVISUALISATION_STANDART);
		popupCtrlTree->AddActiveFilter(Element::ELEMENT_TYPE_REPORT_FOLDER);
		NewControl->SetPopupControl(popupCtrlTree);

		wizManager->GetRootFolder()->FillWxTree(popupCtrlTree,popupCtrlTree->AddRoot("root"));

        wxBoxSizer *hboxSizer = new wxBoxSizer(wxHORIZONTAL);
		
        hboxSizer->Add(
            NewControl,
            1, //Stretching
            wxALL,
            5 // Border
        );

		 mainSizer->Add(
		hboxSizer,
            0,
           wxGROW| wxALL,
            5
        );
        SetSizer(mainSizer);
        mainSizer->Fit(this);

	}

void PanelReferenceSelection::OnRecepteurSurfSelected(wxCommandEvent& event)
{
	wxGenericComboCtrl* TreeBox = wxDynamicCast(wxWindow::FindWindowById(WIZARDCTRL_REFERENCE_SELECTION,this),wxGenericComboCtrl);
	if(TreeBox)
	{
		//On vérifie si l'élément séléctionné est bien du type recherché
		ComboTreeCtrl* popupCtrlTree= wxDynamicCast(TreeBox->GetPopupControl(),ComboTreeCtrl);
		if(popupCtrlTree)
		{
			Element* comboElement=popupCtrlTree->GetElementSelection();
			if(comboElement && !comboElement->IsFittingWithThisType(Element::ELEMENT_TYPE_REPORT_RECEPTEURSSVISUALISATION))
			{
				wxLogError(_("Ce fichier ou dossier ne correspond pas à un récepteur de surface compatible."));
			}
			
		}
	}
}

E_Report_File* PanelReferenceSelection::GetSelectedReportFile()
{
	wxGenericComboCtrl* TreeBox = wxDynamicCast(wxWindow::FindWindowById(WIZARDCTRL_REFERENCE_SELECTION,this),wxGenericComboCtrl);
	if(TreeBox)
	{
		//On vérifie si l'élément séléctionné est bien du type recherché
		ComboTreeCtrl* popupCtrlTree= wxDynamicCast(TreeBox->GetPopupControl(),ComboTreeCtrl);
		if(popupCtrlTree)
		{
			Element* selectedElement=popupCtrlTree->GetElementSelection();
			if(selectedElement)
			{
					return dynamic_cast<E_Report_File*>(selectedElement);
			}
		}
	}
	return NULL;
}

BEGIN_EVENT_TABLE(PageReferenceSelection, wxWizardPageSimple)
	EVT_WIZARD_PAGE_CHANGING(wxID_ANY,  PageReferenceSelection::OnPageChanging)
END_EVENT_TABLE()
PageReferenceSelection::PageReferenceSelection(RecepteurSelectionWizard *parent)
: wxWizardPageSimple(parent) ,
  wiz_parent(parent)
    { 
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(
			new wxStaticText(this, wxID_ANY,_("Veuillez sélectionner le récepteur surfacique de référence :")),
            0,
            wxALL,
            5
        );

		panelCtrl=new PanelReferenceSelection(this,parent);
		
		mainSizer->Add(
            panelCtrl,
            0,
            wxGROW| wxALL,
            0 
			  );

        SetSizer(mainSizer);
        mainSizer->Fit(this);
    }

void PageReferenceSelection::OnPageChanging(wxWizardEvent& wizEvent)
{
		E_Report_File* selectedFile=panelCtrl->GetSelectedReportFile();
		if(!selectedFile || selectedFile->GetElementInfos().typeElement!=Element::ELEMENT_TYPE_REPORT_RECEPTEURSSVISUALISATION)
		{
			wxLogError(_("Vous devez sélectionner un fichier de résultat du type récepteur de surface pour pouvoir continuer."));
			wizEvent.Veto();
			return;
		}
		selectedFile->BuildFullPath(wiz_parent->userSelection.referenceFilePath);
}


BEGIN_EVENT_TABLE(PageOtherRecepeurSurfSelection, wxWizardPageSimple)
	EVT_WIZARD_PAGE_CHANGING(wxID_ANY,  PageOtherRecepeurSurfSelection::OnPageChanging)
	EVT_WIZARD_PAGE_CHANGED(wxID_ANY,  PageOtherRecepeurSurfSelection::OnPageChanged)
	EVT_CHECKBOX(WIZARDRSCTRL_CHECKBOX_ANOTHER_RS_ENTRY, PageOtherRecepeurSurfSelection::OnCheck )
END_EVENT_TABLE()
PageOtherRecepeurSurfSelection::PageOtherRecepeurSurfSelection(RecepteurSelectionWizard *parent)
: wxWizardPageSimple(parent) ,
  wiz_parent(parent),
  id_rsarray_entry(-1)
    { 
		nextRSchooser=NULL;
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(
			new wxStaticText(this, wxID_ANY,_("Récepteur surfacique à comparer avec les données de référence :")),
            0,
            wxALL,
            5
        );

		panelCtrl=new PanelReferenceSelection(this,parent);
		
		mainSizer->Add(
            panelCtrl,
            0,
			wxGROW| wxALL,
            0 
			  );

        mainSizer->Add(
			new wxStaticText(this, wxID_ANY,_("Nom du fichier de résultat de la comparaison :")),
            0,
            wxALL,
            5
        );
        mainSizer->Add(
			new wxTextCtrl(this,WIZARDRSCTRL_TEXTBOX_RESULT_FILENAME,_("Gain")),
            0,
            wxALL,
            5
        );

		wxCheckBox* checkAdd=new wxCheckBox(this,WIZARDRSCTRL_CHECKBOX_ANOTHER_RS_ENTRY,_("Ajouter d'autres fichiers."));
		checkAdd->SetToolTip(_("Continuer à ajouter d'autres fichiers à comparer avec le fichier de référence."));
        mainSizer->Add(
			checkAdd,
            0,
            wxALL,
            5
        );
        SetSizer(mainSizer);
        mainSizer->Fit(this);
    }

void PageOtherRecepeurSurfSelection::OnPageChanging(wxWizardEvent& wizEvent)
{
		if(wizEvent.GetDirection()) //Si on va en avant
		{
			wxTextCtrl* libelCtrl=wxDynamicCast(wxWindow::FindWindowById(WIZARDRSCTRL_TEXTBOX_RESULT_FILENAME,this),wxTextCtrl);
			E_Report_File* selectedFile=panelCtrl->GetSelectedReportFile();
			//On test si l'utilisateur a bien choisi un fichier compatible
			if(!selectedFile || selectedFile->GetElementInfos().typeElement!=Element::ELEMENT_TYPE_REPORT_RECEPTEURSSVISUALISATION)
			{
				wxLogError(_("Vous devez sélectionner un fichier de résultat du type récepteur de surface pour pouvoir continuer."));
				wizEvent.Veto();
				return;
			}
			//Chargement du nom et chemin du fichier
			wxString selectedFileName;
			wxString outputFileName=libelCtrl->GetValue();
			selectedFile->BuildFullPath(selectedFileName);
			//On test si l'utilisateur n'a pas déjà choisi ce fichier dans le traitement, de même pour nom du fichier de sortie
			if(outputFileName.IsEmpty())
			{
				wxLogError(_("Veuillez saisir un libellé valide pour le fichier de sortie qui sera créé."));
				wizEvent.Veto();
				return;
			}
			if(selectedFileName==wiz_parent->userSelection.referenceFilePath)
			{
				wxLogError(_("Vous venez de séléctionner le même fichier que le fichier de référence. Veuillez séléctionner un fichier différend pour effectuer le traitement."));
				wizEvent.Veto();
				return;
			}
			for(wxInt32 identry=0;identry<wiz_parent->userSelection.comparaisonFilesPath.size();identry++)
			{
				if(identry!=id_rsarray_entry)
				{
					if(wiz_parent->userSelection.comparaisonFilesPath[identry]==selectedFileName)
					{
						wxLogError(_("Vous avez déjà séléctionné ce fichier dans le lot de traitement. Veuillez séléctionner un fichier différend pour effectuer le traitement."));
						wizEvent.Veto();
						return;
					}
					if(outputFileName==wiz_parent->userSelection.comparaisonFilesOutputFileNames[identry])
					{
						wxLogError(_("Vous avez déjà utilisé ce libellé comme fichier de sortie. Veuillez séléctionner un libellé différend."));
						wizEvent.Veto();
						return;
					}
				}
			}
			if(id_rsarray_entry==-1)
			{
				wiz_parent->userSelection.comparaisonFilesPath.push_back(selectedFileName);
				wiz_parent->userSelection.comparaisonFilesOutputFileNames.push_back(outputFileName);
				id_rsarray_entry=wiz_parent->userSelection.comparaisonFilesPath.size()-1;
			}else{
				wiz_parent->userSelection.comparaisonFilesPath[id_rsarray_entry]=selectedFileName;
				wiz_parent->userSelection.comparaisonFilesOutputFileNames[id_rsarray_entry]=outputFileName;
				if(!this->GetNext())
				{
					//Si l'utilisateur est revenu en arrière et a déchoché le choix de poursuivre l'insertion de fichier supplémentaire, il faut supprimer les enregistrements qui suivent l'enregistrement courant
					this->wiz_parent->userSelection.comparaisonFilesOutputFileNames.erase(this->wiz_parent->userSelection.comparaisonFilesOutputFileNames.begin()+id_rsarray_entry+1,this->wiz_parent->userSelection.comparaisonFilesOutputFileNames.end());
					this->wiz_parent->userSelection.comparaisonFilesPath.erase(this->wiz_parent->userSelection.comparaisonFilesPath.begin()+id_rsarray_entry+1,this->wiz_parent->userSelection.comparaisonFilesPath.end());
				}
			}
		}
}
		
void PageOtherRecepeurSurfSelection::OnCheck(wxCommandEvent& ctrlEvent)
{
	wiz_parent->RefreshNextButtonState();
}

void PageOtherRecepeurSurfSelection::OnPageChanged(wxWizardEvent& wizEvent)
{
		if(wizEvent.GetDirection() && !nextRSchooser) //Si on arrive de la page précédente pour la première fois 
		{
			nextRSchooser=new PageOtherRecepeurSurfSelection(wiz_parent);
			nextRSchooser->SetPrev(this);
		}
}


wxWizardPage* PageOtherRecepeurSurfSelection::GetNext() const
{
	wxCheckBox* checkBoxCtrl=wxDynamicCast(wxWindow::FindWindowById(WIZARDRSCTRL_CHECKBOX_ANOTHER_RS_ENTRY,this),wxCheckBox);
	if(checkBoxCtrl)
	{
		if(checkBoxCtrl->GetValue())
		{
			return nextRSchooser;
		}else{
			return NULL;
		}
	}
	return NULL;
}
