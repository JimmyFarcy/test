#include "first_header_include.hpp"

#include <wx/window.h>
#include <wx/imaglist.h>
#include <wx/artprov.h>
#include <vector>
#include <wx/treectrl.h>
#include <wx/timer.h>
#include "../data_manager/element.h"

#ifndef __uiTreeCtrl_H__
#define __uiTreeCtrl_H__


/** 
 * @file uiTreeCtrl.h
 * @brief Déclaration de la classe uiTreeCtrl
 */

/**
 * @class uiTreeCtrl
 * @brief Classe de gestion de l'affichage des éléments sous forme hiérarchique
 *
 * Surcharge de wxTreeCtrl afin d'intéragir avec les instances de la classe Element 
 */
class uiTreeCtrl : public wxTreeCtrl
{
	private : 
		void (*pointeurElementEvent)(wxCommandEvent&);
		bool selectionEventState; //A faux les évenements générés par les éléments sont désactivés
		std::vector<Element*> DragLst;
		wxTimer m_Timer;
		struct t_highlightEl
		{
			wxTreeItemId el;
			float compteurHl;
			int scrollPos;
		};
		t_highlightEl highlightEl;
		void OnTimer( wxTimerEvent& event );
		void OnMouseMove(wxMouseEvent& event);
		wxPoint mousePos;
		void InitTree();
		smart_ptr<bool> alive;
	protected :
		DECLARE_EVENT_TABLE()

		Element* rootItem;
		void BeginDrag(wxTreeEvent&);
		void OnDoubleClic(wxTreeEvent&);
		void OnRightClic(wxTreeEvent&);
		void OnLeftClic(wxMouseEvent&); 
		void OnSelectTreeItem(wxTreeEvent&);
		void EndDrag(wxTreeEvent&);
		void OnBeginLabelEdit(wxTreeEvent&);
		void OnEndLabelEdit(wxTreeEvent&);
		void OnExpanding(wxTreeEvent& treeEvent);
		void OnCollapsing(wxTreeEvent& treeEvent);
		void OnKeyUp(wxKeyEvent&); 
	public :
		/**
		 * Constructeur de la fenêtre
		 * @param parent Fenêtre parente
		 * @param id Indice de la fenêtre
		 * @param pos Position de la fenêtre
		 * @param size Taille de la fenêtre
		 * @param style Style de la fenêtre
		 */
		uiTreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS);
		uiTreeCtrl();
		/**
		 * Destructeur
		 */
		~uiTreeCtrl();
		/**
		 * Lie l'événement validation de menu d'un Element à une méthode externe
		 * @param fevent Méthode externe
		 */
		void BindElementEvent(void (*fevent)(wxCommandEvent&));
		/**
		 * Evenement de clic sur un menu popup
		 * @param eventElement Objet lié à l'événement
		 */
		void OnElementEvent(wxCommandEvent&);
		/**
		 * Initialise le controle avec le premier élément
		 */
		void Init(Element* rootElement);
		/**
		 * Charge un nouvel élément au sein de l'arbre ( appelé par une instance de Element)
		 */
		void AddElement(Element* newElement);
		/**
		 * Cette surcharge désactive l'événement de sélection le temps de la suppression d'un élément dans l'arbre
		 * @param item Indice de l'objet supprimé
		 */
		virtual void Delete(const wxTreeItemId &item);
		/**
		 * Cette surcharge permet de recupérer l'élément sélectionné ou bien le dernier élément sélectionné par ceux sélectionnée
		 */
		virtual wxTreeItemId GetSelection() const;
		wxInt32 GetXmlId(const wxTreeItemId& itemId);
		Element* GetElement(const wxTreeItemId& itemId);
		/**
		 * Empêche les éléments de l'arbre de générer des évenements
		 */
		void LockElementEvent(bool lock=true) { selectionEventState=!lock; }
};

#endif