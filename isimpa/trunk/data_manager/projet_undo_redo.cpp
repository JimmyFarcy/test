#include "projet.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
#include "last_cpp_include.hpp"
WX_DEFINE_OBJARRAY(ArrayOfXmlTree);


void ProjectManager::OnMenuUndo()
{
	//Si on peut annuler la modification
	if(CanUndo())
	{
		if(currentHistoryNavigation==0)
		{
			PushModificationToHistory(true);
			currentHistoryNavigation++;
		}
		currentHistoryNavigation++;
		projetConfig=configHistory[configHistory.size()-currentHistoryNavigation];
		LoadCurrentProject(false);
		Init();
	}
}
void ProjectManager::OnMenuRedo()
{
	if(CanRedo())
	{
		projetConfig=configHistory[configHistory.size()-currentHistoryNavigation];
		currentHistoryNavigation--;
		LoadCurrentProject(false);
		Init();
	}
}


bool ProjectManager::PushModificationToHistory(bool force)
{
	wxDateTime maintenant=wxDateTime::UNow();
	if(force || (maintenant-lastHistoryUpdate).GetMilliseconds()>UNDO_HISTORY_TIMESTEP)
	{
		lastHistoryUpdate=maintenant;
		if(this->rootUserConfig->GetElementByLibelle("mainpref")->GetElementByLibelle("history")->GetBoolConfig("keep_modification_history"))
		{
			if(!force)
				wxLogDebug("Ajout des modifications dans l'historique des modifications.");
			else
				wxLogDebug("Ajout forcé des modifications dans l'historique des modifications.");
			this->UpdateXmlFile("",false);
			configHistory.Add(new wxXmlDocument(projetConfig));
			//Dû à la modification on perd soit la plus vieille modification soit tout les dernieres modifications ( en fonction de l'etat de navigation dans l'historique)
			if(currentHistoryNavigation==0)
			{
				if(configHistory.size()>UNDO_HISTORY_SIZE)
					configHistory.RemoveAt(0);
			}else{
				//L'utilisateur a fait annuler et il a ensuite modifié le projet, l'utilisateur ne peut donc plus utiliser refaire
				//Supprime de la version courante jusqu'à la dernière version
				configHistory.RemoveAt(configHistory.size()-currentHistoryNavigation,currentHistoryNavigation-1);
				currentHistoryNavigation=0;
			}
			wxCommandEvent eventUpdate( wxEVT_PSPS_MAIN_EVENT, mainFrame->GetId() );
			eventUpdate.SetInt(ApplicationConfiguration::MAIN_EVENT_UNDO_REDO_UPDATE);
			wxPostEvent(mainFrame,eventUpdate);
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
bool ProjectManager::CanUndo()
{
	return currentHistoryNavigation<configHistory.size();
}

bool ProjectManager::CanRedo()
{
	return currentHistoryNavigation>0;
}
void ProjectManager::ClearUndoRedoHistory()
{
	currentHistoryNavigation=0;
	configHistory.Clear();
}