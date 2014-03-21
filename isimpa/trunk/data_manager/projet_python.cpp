/**
 * @file projet_python.cpp
 * @brief Specification des méthodes de ProjectManager ayant un rapport avec le module python
 */
#include "python_interface/pythonshell.hpp"
#include "projet.h"
#include <wx/arrstr.h>
#include "last_cpp_include.hpp"


#ifdef USE_PYTHON

extern ProjectManager *projetCourant;

using namespace boost::python;

void SendPythonCommand(const wxString& cmd)
{
	projetCourant->RunPythonCmd(cmd);
}
bool ins_pyelement(boost::python::object& py_el,const wxInt32& wxid, const wxString& module,const wxString& _pyclass)
{
  PythonShell* pyshell=projetCourant->GetPythonShell();
  if(pyshell)
  {
	return pyshell->ins_pyelement(py_el,wxid,module,_pyclass);
  }
  return false;
}
bool RunPyManagedMenu(const int& elementType,const int& elementId, wxMenu& menu)
{
	return projetCourant->GetPythonManagedMenu(elementType,elementId,menu);
}
bool GetFormulaEvaluation(const wxString& formula,double& evalResult)
{
  PythonShell* pyshell=projetCourant->GetPythonShell();
  if(pyshell)
  {
    try
	{
      	evalResult=extract_or_throw<double>(pyshell->eval(formula),WXSTRINGTOSTDWSTRING(_("The formula result must be a number.")));
	}catch( error_already_set ) {
		wxLogError(_("Unable to solve the user's defined formula !"));
		return false;
    }
	catch( elementException elexc)
	{

		wxLogError(_("Unable to solve the user's defined formula :\n")+elexc.msg());
		return false;
	}
	//return pyshell->ins_pyelement(py_el,wxid,module,_pyclass);
	return true;
  }
  return false;
}
void ProjectManager::InitPythonEngine()
{
	if(pyShell==NULL)
	{
		Py_Initialize();
		
		pyShell=new PythonShell(shellControl);

		pyShell->Init();
		
	}
}

void GetListItems(boost::python::list& pymenu, wxMenu& menu);
boost::python::list GetMenuItems(wxMenu* menuToFill);

void ProjectManager::PyProjectLoadingEvt()
{
	if(pyShell)
	{
		pyShell->run_startupscript(L"UserScript/",L"__project_loading__.py");
	}

}

bool ProjectManager::GetPythonManagedMenu(const int& elementType,const int& elementId, wxMenu& menu)
{
	try
	{
		//1ere étape transformer le menu en objet python
		boost::python::list pymenu=GetMenuItems(&menu);
		//2eme étape fournir à pyshell les éléments
		if(pyShell)
		{
			if(pyShell->GetPythonManagedMenu(elementType,elementId,pymenu))
			{
				//Supprime l'ancien menu
				wxMenuItemList menuitems=menu.GetMenuItems();
				wxMenuItemList::iterator iter;
				for (iter = menuitems.begin(); iter != menuitems.end(); ++iter)
				{
					wxMenuItem *current = *iter;
					menu.Destroy(current);
				}
				//Ajoute les anciens et les nouveaux éléments de menu
				GetListItems(pymenu,menu);
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	} catch( error_already_set ) {
		if (PyErr_Occurred())
		{
			PyErr_Print();
		}
	}
	return false;
}
void ProjectManager::OnClearShell()
{
	shellControl->Clear();
}
void ProjectManager::UnloadPyShell()
{
	delete pyShell;
	pyShell=NULL;
	Py_Finalize();
}
void ProjectManager::OnPushPythonCommand(wxCommandEvent& eventCmdPython)
{
	RunPythonCmd(eventCmdPython.GetString());
}
void ProjectManager::RunPythonCmd(const wxString& cmd)
{
	//wxCriticalSectionLocker locker(m_critsectWork);
	if(pyShell)
		pyShell->ExecLineCommand(cmd);
}
void ProjectManager::AppendBatchParameters(const wxString& name,const wxString& value)
{
	this->pyenventparams[name]=value;
}
void ProjectManager::ClearBatchParameters()
{
	this->pyenventparams.clear();
}
bool ProjectManager::GetParameter(const wxString& name,wxString& value)
{
	StringHash_wxImplementation_HashTable::iterator it=this->pyenventparams.find(name);
	if(it != this->pyenventparams.end())
	{
		value=it->second;
		return true;
	}else{
		wxLogError(_("Python parameter %s not found"),name);
		return false;
	}
}

PythonShell* ProjectManager::GetPythonShell()
{
	return pyShell;
}


void ProjectManager::SendPythonEvent(const int& eventid,const int& elementid)
{
	pyShell->call_event(eventid,elementid);
}

#else
bool GetFormulaEvaluation(const wxString& formula,double& evalResult)
{
	return false;
}
void SendPythonCommand(const wxString& cmd)
{
}

bool RunPyManagedMenu(const int& elementType,const int& elementId, wxMenu& menu)
{
	return false;
}

void ProjectManager::InitPythonEngine()
{
}

void ProjectManager::PyProjectLoadingEvt()
{
}

bool ProjectManager::GetPythonManagedMenu(const int& elementType,const int& elementId, wxMenu& menu)
{
	return false;
}
void ProjectManager::OnClearShell()
{
	
}
void ProjectManager::UnloadPyShell()
{
	
}
void ProjectManager::OnPushPythonCommand(wxCommandEvent& eventCmdPython)
{

}
void ProjectManager::RunPythonCmd(const wxString& cmd)
{

}
void ProjectManager::AppendBatchParameters(const wxString& name,const wxString& value)
{
	
}
void ProjectManager::ClearBatchParameters()
{
	
}
bool ProjectManager::GetParameter(const wxString& name,wxString& value)
{
	return false;
}

PythonShell* ProjectManager::GetPythonShell()
{
	return NULL;
}


void ProjectManager::SendPythonEvent(const int& eventid,const int& elementid)
{
	
}
#endif