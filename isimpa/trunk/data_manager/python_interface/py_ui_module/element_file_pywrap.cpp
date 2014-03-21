#include "element_file_pywrap.hpp"
#include "data_manager/tree_rapport/e_report_file.h"
#include "data_manager/python_interface/instanceManager.hpp"
#include "UtfConverter.h"
#include "last_cpp_include.hpp"

#ifdef USE_PYTHON
using namespace boost::python;
using namespace uictrl;

#ifndef REMTR
#define REMTR
#endif

void export_project_class_pyfilelement()
{
	class_<e_file, bases<element> >("e_file",init<int>())
		.def(init<e_file>())
		.def("buildfullpath", &e_file::buildfullpath, REMTR("Retourne le chemin vers ce dossier ou fichier."));
}

E_Report_File* GetFileElement(const wxInt32& xmlId)
{
	void *obj;
	if(InstanceManager::GetReference(OBJECT_REF_TYPE_ELEMENT,xmlId,&obj))
	{
		E_Report_File* el=dynamic_cast<E_Report_File*>( (Element*)obj);
		if(el)
		{
			return el;
		}else{
			ThrowPyException(_("Cet élément ne représente pas un fichier ou un dossier."));
			return NULL;
		}
	}else{
		ThrowPyException(_("Cet élément n'existe pas ou plus."));
		return NULL;
	}
}


namespace uictrl
{
e_file::e_file(const wxInt32& _xmlId)
:element(_xmlId)
{
	GetFileElement(xmlId);
}
e_file::e_file(const element& cpyFrom)
:element((const element&)cpyFrom)
{
	GetFileElement(xmlId);
}

std::wstring e_file::buildfullpath()
{
	E_Report_File* self=GetFileElement(xmlId);
	wxString path;
	self->BuildFullPath(path);
	return WXSTRINGTOSTDWSTRING(path);
}
}
#endif
