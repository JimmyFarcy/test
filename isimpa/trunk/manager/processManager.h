#include "first_header_include.hpp"
#include "manager/smart_ptr.h"
#include "interf_logger.hpp"
#include <wx/process.h>
#include <wx/intl.h>
#include <vector>

#ifndef  __PROCESS_MANAGER__
#define __PROCESS_MANAGER__
/** \file process.h
 *  \brief Gestionnaire d'execution d'un programme externe
 */

class processManager : public wxProcess
{
public:
	/**
	 * Constructeur
	 * @param parent Fenêtre parente
	 * @param cmd Chemin de l'exécutable
	 */
    processManager(wxFrame *parent, const wxString& cmd)
        : wxProcess((wxEvtHandler*)parent), m_cmd(cmd)
    {
        m_parent = parent;
        Redirect();
		run=true;
    }

    // instead of overriding this virtual function we might as well process the
    // event from it in the frame class - this might be more convenient in some
    // cases
	/**
	 * Utilise les messages de la pile de sortie de l'executable externe afin de les afficher vers la sortie wxLog
	 * @param[out] hasOutput Passe à vrai si il reste encore des lignes dans la pile mémoire.
	 * @param[in] label Libellé du message qui précede le texte de sortie
	 * @param[out] Si une des sortie est de la forme "#entier" alors affecte cet entier dans cette variable
	 */
	void LogOutput(bool &hasOutput, const wxString &label=wxString(_("Sortie exécutable :")),float *outputProgression=NULL);
	/**
	 * Permet de connaître l'etat de l'execution
	 * @return Vrai si l'application est en cours d'exécution
	 */
	bool IsRunning();
    /**
	 * Add a logger object
	 * @param logger Instance of log object
	 */
	void AddLogger(smart_ptr<InterfLogger> logger);
private:
	/**
	 * Fin de l'execution de l'application externe
	 */
    virtual void OnTerminate(int pid, int status);
	bool run;
    wxString m_cmd;
	wxFrame* m_parent;
	std::vector<smart_ptr<InterfLogger> > outlogs;
};


bool uiRunExe(wxFrame* parent,const wxString& path,const wxString& labelOutput, wxWindow* progressDialog,smart_ptr<InterfLogger> extLogger=smart_ptr<InterfLogger>(NULL));

#endif