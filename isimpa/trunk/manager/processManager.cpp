﻿#include "processManager.h"
#include <wx/txtstrm.h>
#include <wx/log.h>
#include "manager/stringTools.h"
#include <wx/progdlg.h>
#include <wx/frame.h>
#include "last_cpp_include.hpp"

void processManager::OnTerminate(int pid, int status)
{
	run=false;
}
void processManager::AddLogger(smart_ptr<InterfLogger> logger)
{
	this->outlogs.push_back(logger);
}
void processManager::LogOutput(bool &hasOutput, const wxString &label,float *outputProgression)
{
   hasOutput = false;

    if ( IsInputAvailable() )
    {
        wxTextInputStream tis(*GetInputStream());

        // this assumes that the output is always line buffered
        wxString msg;
		wxString output= tis.ReadLine();
		if(!this->outlogs.empty())
		{
			for(std::vector<smart_ptr<InterfLogger> >::iterator itlogs=this->outlogs.begin();itlogs!=this->outlogs.end();itlogs++)
			{
				(*(*itlogs)).LogMessage(output);
			}
		}
		if(outputProgression==NULL || output.Left(1)!="#")
		{
			msg << label << output;
			msg.Replace("%","%%"); //si il y a un seul % alors un bug apparait wxString attend un format du type %s ou %i par exemple
			if(output.Left(1)=="!")
			{
				wxLogWarning(msg);
			}else{
				wxLogMessage(msg);
			}
		}else{
			wxString prog=output.Right(output.Len()-1).Strip();
			*outputProgression=Convertor::ToFloat(prog);
		}

        hasOutput = true;
    }

    while ( IsErrorAvailable() )
    {
        wxTextInputStream tis(*GetErrorStream());
		const wxString& errMsg(tis.ReadLine());
		if(!this->outlogs.empty())
		{
			for(std::vector<smart_ptr<InterfLogger> >::iterator itlogs=this->outlogs.begin();itlogs!=this->outlogs.end();itlogs++)
			{
				(*(*itlogs)).LogError(errMsg);
			}
		}
        // this assumes that the output is always line buffered
        wxString msg;
		msg << _("Erreur exécutable :") << errMsg;
		msg.Replace("%","%%"); //si il y a un seul % alors un bug apparait wxString attend un format du type %s ou %i par exemple
		wxLogError(msg);

        hasOutput = true;
    }
}
bool processManager::IsRunning()
{
	return run;
}


bool uiRunExe(wxFrame* parent,const wxString& path,const wxString& labelOutput, wxWindow* progressDialog,smart_ptr<InterfLogger> extLogger)
{
    _("Elapsed time : ");
	_("Remaining time : ");
	_("Close");
	_("Cancel");
	_("unknown");
	wxProgressDialog * progDialog=wxDynamicCast(progressDialog,wxProgressDialog);
	bool hasOutput=true;
	processManager* process = new processManager(parent,path);
	if(extLogger.get()!=NULL)
		process->AddLogger(extLogger);

	wxLogInfo(_("Execution d'un programme externe :"));
	wxLogInfo(path);

	int processId=wxExecute(path,wxEXEC_ASYNC,process);
	if(!processId)
	{
		wxLogInfo("L'execution du programme a échoué");
		delete process;
		return false;
	}
	float percFinish=0;
	wxDateTime lastProgShow=wxDateTime::UNow();
	while(process->IsRunning())
	{
		hasOutput=true;
		wxMilliSleep(50);
		while(hasOutput) //&& (!progDialog || progDialog->Update(percFinish*100))
		{
			process->LogOutput(hasOutput,labelOutput,&percFinish);
		}
		if(wxDateTime::UNow().GetValue()-lastProgShow.GetValue()>500)
		{
			lastProgShow=wxDateTime::UNow();
			if(parent)
				parent->Update();
			if(percFinish>99.f)
				percFinish=99;
			if(progDialog && !progDialog->Update(percFinish*100))
			{
				wxKillError killerror=wxProcess::Kill(processId,wxSIGKILL);
				wxLogInfo(_("Execution du programme externe annulé."));
				wxLogInfo(_("Réponse du processus :"));
				switch(killerror)
				{
				case wxKILL_OK:              // no error
					wxLogInfo(_("Pas d'erreur."));
					break;
				case wxKILL_BAD_SIGNAL:      // no such signal
					wxLogError(_("Le signal n'existe pas."));
					break;
				case wxKILL_ACCESS_DENIED:   // permission denied
					wxLogError(_("Fermeture du processus non autorisée."));
					break;
				case wxKILL_NO_PROCESS:      // no such process
					wxLogError(_("Ce processus n'existe pas."));
					break;
				case wxKILL_ERROR :           // another, unspecified error
					wxLogError(_("Retour du processus non spécifié"));
					break;
				default:
					wxLogError(_("Retour du processus inconnue"));
					break;
				}
				//Si on supprime le processus maintenant on aura une erreur
				//Si on ne le supprime pas il y a une fuite mémoire
				//delete process;
				return false;
			}
		}
	}
	// On récupère les derniers messages
	wxMilliSleep(150);
	process->LogOutput(hasOutput,labelOutput,&percFinish);
	while(hasOutput)
		process->LogOutput(hasOutput,labelOutput,&percFinish);
	delete process;
	return true;
}
