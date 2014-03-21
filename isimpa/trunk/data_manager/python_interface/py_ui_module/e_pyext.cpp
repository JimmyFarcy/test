#include "e_pyext.hpp"
#include <wx/log.h>
#include "data_manager/tree_core/e_core_core.h"
#include "data_manager/drawable_element.h"
#include "data_manager/tree_userpref/e_userprefnode.hpp"
#include "last_cpp_include.hpp"

#define MAKE_ELEMENT_PYTHON_DECLARATION(TYPE_EL) newel=(E_Python_Extension<Element>*)new E_Python_Extension<TYPE_EL>(parent,baseType,module,pyclass,noeudCourant);
												

#ifdef USE_PYTHON

/**
 * C'est ici qu'il faut ajouter les déclaration pour les éléments pouvant être surchargé par python.
 *
 **/

Element* SwitchNewElement(const Element::ELEMENT_TYPE& baseType,Element* parent,const wxString& module,const wxString& pyclass="pyel",bp::object* pyobj=NULL,wxXmlNode* noeudCourant=NULL)
{
	E_Python_Extension<Element>* newel;
	switch(baseType)
	{
		case Element::ELEMENT_TYPE_CORE_CORE:
			MAKE_ELEMENT_PYTHON_DECLARATION(E_Core_Core);	
			break;
		case Element::ELEMENT_TYPE_DRAWABLE:
			MAKE_ELEMENT_PYTHON_DECLARATION(E_Drawable);	
			break;
		case Element::ELEMENT_TYPE_USER_PREFERENCE_ITEM:
			MAKE_ELEMENT_PYTHON_DECLARATION(E_UserPreferenceItem);	
		case Element::ELEMENT_TYPE_USER_PREFERENCE_NODE:
			MAKE_ELEMENT_PYTHON_DECLARATION(E_UserPreferenceNode);
		default:
			MAKE_ELEMENT_PYTHON_DECLARATION(Element);	
	}
	if(pyobj)
		*pyobj=newel->GetPyObj();
	return newel;
}




Element* New_E_Python_Extension( const Element::ELEMENT_TYPE& baseType,Element* parent,const wxString& module,const wxString& pyclass)
{
	return SwitchNewElement(baseType,parent,module,pyclass);
}


Element* New_E_Python_Extension( const Element::ELEMENT_TYPE& baseType,Element* parent,const wxString& module,const wxString& pyclass,bp::object& pyobj)
{
	return SwitchNewElement(baseType,parent,module,pyclass,&pyobj);
}
Element* New_E_Python_Extension( Element* parent,wxXmlNode* noeudCourant)
{
	wxString propValue;
	noeudCourant->GetPropVal("beid",&propValue);
	
	Element::ELEMENT_TYPE baseType=(Element::ELEMENT_TYPE)Convertor::ToInt(propValue);
	return SwitchNewElement(baseType,parent,"","",NULL,noeudCourant);
}

Element::ELEMENT_TYPE GetPythonExtBaseType( Element* pythonEl)
{
	E_Python_Extension<Element>* castedEl=static_cast<E_Python_Extension<Element>*>(pythonEl);
	if(castedEl)
	{
		return castedEl->GetBaseElementId();
	}else{
		return Element::ELEMENT_TYPE_ELEMENT;
	}
}

#endif