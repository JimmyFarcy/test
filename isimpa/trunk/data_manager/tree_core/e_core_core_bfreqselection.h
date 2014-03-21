#include "first_header_include.hpp"

#include "data_manager/element.h"
#include "data_manager/e_data_bool_bfreqchoice.h"
#include "data_manager/appconfig.h"

#ifndef _BFREQ_SELECTION_
#define _BFREQ_SELECTION_

/*! \file e_core_core_bfreqselection.h
    \brief Element permettant de limiter le spectre de fréquence à calculer.
*/

/**
 \brief Element permettant de limiter le spectre de fréquence à calculer.
*/
class E_Core_Core_Bfreqselection: public Element
{
public:
	E_Core_Core_Bfreqselection( wxXmlNode* nodeElement ,  Element* parent)
		:Element(parent,"Limitation bande de fréquence",Element::ELEMENT_TYPE_CORE_CORE_BFREQSELECTION,nodeElement)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_SPECTRUM);
		_("Limitation bande de fréquence");
		wxString propVal;
		//Affecte la valeur de l'element

		if(nodeElement!=NULL && nodeElement->GetPropVal("wxid",&propVal))
		{
			wxString propValue;

			//Element initialisé AVEC Xml
			wxXmlNode* currentChild;
			currentChild = nodeElement->GetChildren();
			while(currentChild!=NULL)
			{
				if(currentChild->GetPropVal("eid",&propValue))
				{
					long typeEle;
					propValue.ToLong(&typeEle);
					if(typeEle==Element::ELEMENT_TYPE_BOOL_BFREQ)
					{
						this->AppendFils(new E_Data_Bool_Bfreq(currentChild,this));
					}			
				}
				currentChild = currentChild->GetNext();
			}
		}
	}

	E_Core_Core_Bfreqselection( Element* parent)
		:Element(parent,"Limitation bande de fréquence",Element::ELEMENT_TYPE_CORE_CORE_BFREQSELECTION)
	{
		SetIcon(GRAPH_STATE_ALL,GRAPH_SPECTRUM);
		InitProperties();
	}

	wxXmlNode* SaveXMLCoreDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* NoeudCourant=new wxXmlNode(NoeudParent,wxXML_ELEMENT_NODE,"freq_enum");
		return Element::SaveXMLCoreDoc(NoeudCourant);
	}

	void SetPreselection( Element::IDEVENT preselectionMode)
	{
		short cur_count=0;
		for(std::list<Element*>::iterator itfils=this->fils.begin();itfils!=this->fils.end();itfils++)
		{
			E_Data_Bool* elData=dynamic_cast<E_Data_Bool*>((*itfils));
			if(elData)
			{
				ApplicationConfiguration::t_freq freq=Convertor::ToInt(elData->GetElementInfos().libelleElement);
				bool checkItem=false;
				bool isOctave=(cur_count==1);
				switch(preselectionMode)
				{
					case Element::IDEVENT_BFREQ_PRESELECTION_ALL:
					case Element::IDEVENT_BFREQ_PRESELECTION_THIRD_BAND:
						checkItem=true;
						break;
					case Element::IDEVENT_BFREQ_PRESELECTION_BUILDING_THIRD_BAND:
						if(freq>=100 && freq<=5000)
							checkItem=true;
						break;
					case Element::IDEVENT_BFREQ_PRESELECTION_BAND:
						checkItem=isOctave;
						break;
					case Element::IDEVENT_BFREQ_PRESELECTION_BUILDING_BAND:
						if(isOctave && freq>=125 && freq<=4000)
							checkItem=true;
						break;					
				};
				elData->SetValue(checkItem);
				cur_count++;
				if(cur_count==3)
					cur_count=0;
			};
		}
	}
	void OnRightClic(wxMenu* leMenu)
	{
		wxMenu* submenupreselect=new wxMenu();
		submenupreselect->Append(Element::GetMenuItem(submenupreselect,Element::IDEVENT_BFREQ_PRESELECTION_NONE, _("Tout désélectionner")));
		submenupreselect->Append(Element::GetMenuItem(submenupreselect,Element::IDEVENT_BFREQ_PRESELECTION_ALL, _("Tout sélectionner")));
		wxMenu* submenupreselect_octave=new wxMenu();
		submenupreselect_octave->Append(Element::GetMenuItem(submenupreselect_octave,Element::IDEVENT_BFREQ_PRESELECTION_BAND, _("Tout [63-16000] Hz")));
		submenupreselect_octave->Append(Element::GetMenuItem(submenupreselect_octave,Element::IDEVENT_BFREQ_PRESELECTION_BUILDING_BAND, _("Batiment/Routier [125-4000] Hz")));
		wxMenu* submenupreselect_thirdoctave=new wxMenu();
		submenupreselect_thirdoctave->Append(Element::GetMenuItem(submenupreselect_thirdoctave,Element::IDEVENT_BFREQ_PRESELECTION_THIRD_BAND, _("Tout [50-20000] Hz")));
		submenupreselect_thirdoctave->Append(Element::GetMenuItem(submenupreselect_thirdoctave,Element::IDEVENT_BFREQ_PRESELECTION_BUILDING_THIRD_BAND, _("Batiment/Routier [100-5000] Hz")));
		submenupreselect->AppendSubMenu(submenupreselect_octave,_("Octave"));
		submenupreselect->AppendSubMenu(submenupreselect_thirdoctave,_("Tiers d'octave"));
		leMenu->AppendSubMenu(submenupreselect,_("Séléction automatique"));
		Element::OnRightClic(leMenu);
	}

	wxXmlNode* SaveXMLDoc(wxXmlNode* NoeudParent)
	{
		wxXmlNode* thisNode = Element::SaveXMLDoc(NoeudParent);
		thisNode->SetName("core_conf_bfreq"); // Nom de la balise xml ( pas d'espace autorise )
		return thisNode;
	}
protected:
	/**
	 Initialisation des propriétés
	*/
	void InitProperties()
	{
		std::vector<ApplicationConfiguration::t_freq> freqTab(ApplicationConfiguration::GetAllFrequencies());

		for(int i=0;i<freqTab.size();i++)
		{
			this->AppendFils(new E_Data_Bool_Bfreq(this,Convertor::ToString(freqTab[i]),Convertor::ToString(freqTab[i])+" Hz",true));
		}
	}
	
};

#endif