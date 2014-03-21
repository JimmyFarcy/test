#include "first_header_include.hpp"


#include "pythonstdioredirect.hpp"
#include "IHM/pyConsole.hpp"
#include "boost_python_header.h"

#ifndef __PYTHON_SHELL__
#define __PYTHON_SHELL__


#ifdef USE_PYTHON
/**
 * @brief Thread d'execution de python
 *
 * Simule l'execution d'une console python et communique avec le controle de texte associé
 */
class PythonShell
{
public:
    PythonShell(PyConsole* pyCtrl);
	virtual ~PythonShell();
	/**
	 * Donne le bloc d'indentation de la commande passé en paramètre
	 */
	void GetIndentation(const wxString& command,wxString* indentationBlock);
	wxString GetStr(const wxString& strPos);
	bool ShowMsgStack();
	void ExecLineCommand(const wxString& cmd);
	/**
	 * Evaluate the code argument within the python vm. Then return the value of the evaluation
	 * The code will be run as "res=eval(code)"
	 */
	boost::python::object eval(const wxString& code);
	void Init();
	/**
	 * Enregistre un gestionnaire de menu associé au clic droit sur un type d'élément
	 * Ce gestionnaire ira ensuite alimenter ou non le menu
	 */
	void register_menu_manager(const int& element_typeid, boost::python::object& manager);
	/**
	 * Ajoute un événement dans la table des evenements
	 * @return L'indice de l'événement lié
	 * @see call_event
	 */
	int register_event(boost::python::object& func); 
	/**
	 * Appel la méthode python ayant comme indice celui passé en paramètre
	 * @param eventid Indice de l'événement
	 */
	void call_event(const int& eventid,const int& elementid);



	/**
	 * Cette méthode va parcourir les sous dossier à la recherche des fichier se nommant pyfilename
	 * Puis il les executes
	 */
	void run_startupscript(const wxString& scriptPath,const wxString& pyfilename); 
	int GetCountEventTable();
	/**
	 * Modifie le menu au cas où un gestionnaire de menu python est associé à pythonshell
	 * @return vrai si le menu a été modifié
	 */
	bool GetPythonManagedMenu(const int& element_type,const int& elementId,boost::python::list& pymenu);
	
	bool ins_pyelement(boost::python::object& py_el,const wxInt32& wxid, const wxString& module,const wxString& _pyclass);
	
protected:
	boost::python::object main_module;
	boost::python::object main_namespace;
	boost::python::object inspect_module;
	wxString cmd;
	wxString oldcmd;
	wxString promptNewCmd;
	wxString promptMore;
	void RunRawCmd(const wxString& command);
    PyConsole* m_py_ctrl;
	boost::python::list event_lst; /*!< Cette liste contient les événements supplémentaires implémentés sous python */
	boost::python::dict menu_managers; /*!< Ce dictionnaire contient les générateurs de menu, chacun étant associé à un type d'élément du projet */
	PythonStdIoRedirect* outputRedirectOut;
	PythonStdIoRedirect* outputRedirectErr;
	PythonStdIoRedirect* outputRedirectIn;

};

#endif
#endif