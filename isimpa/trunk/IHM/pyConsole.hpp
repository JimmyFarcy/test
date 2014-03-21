#include "first_header_include.hpp"

#include <wx/textctrl.h>

#ifndef __PY_CONSOLE_CTRL_
#define __PY_CONSOLE_CTRL_
/**
 * @brief Console Python
 *
 * C'est le contrôle texte qui permet d'emuler python si il est utilisé avec PythonShellThread
 */
class PyConsole : public wxTextCtrl
{
protected:
	void OnTextEnter(wxCommandEvent& txtEvent);
	void OnKeyDown(wxKeyEvent& txtEvent);
	int promptSize; /*!< Nombre de caractère de la ligne de commande */
	long lastpromptpos;
	bool waitingForNextPrompt; /*!< L'utilisateur ne peut taper de command si python ne nous a pas laissé la main */
public:

	PyConsole(wxWindow* parent);
	/**
	 * Ajoute le resulat interpreté par python  dans la console
	 */
	void AddPythonMsg(const wxString& pyMsg);
	/**
	 * Ajoute le message d'erreur dans la console
	 */
	void AddPythonError(const wxString& pyErr);
	/**
	 * Ajoute les caractère de ligne de commande (>>> , ... ou autre)
	 */
	void AddPrompt(const wxString& pyPrompt);
	
    virtual void Clear();
	/**
	 * Ajoute des caractère de la même couleur que le texte tapé par l'utilisateur
	 */
	void AddCmd(const wxString& pyCmd,bool atInsertionPoint=false);
	/**
	 * C'est le nombre de caractère minimal dans une ligne.
	 */
	void SetPromptSize(const wxInt32& lengthPrompt)
	{
		promptSize=lengthPrompt;
	}
	DECLARE_EVENT_TABLE();
};

#endif