#include "boost_python_header.h"
#include "UtfConverter.h"
#include "last_cpp_include.hpp"

#ifdef USE_PYTHON
using namespace boost::python;


void translator(elementException const& x) {
    PyErr_SetString(PyExc_UserWarning, x.msg());
}
void ThrowPyException(const std::wstring& _msg)
{
	throw elementException(UtfConverter::ToUtf8(_msg));
}
void ThrowPyException(const char* _msg)
{
	throw elementException(_msg);
}


bool hasattr(const boost::python::object& obj, std::wstring const &attrName) {
     return PyObject_HasAttrString(obj.ptr(), UtfConverter::ToUtf8(attrName).c_str());
}

bool hasattr(const boost::python::object& obj, std::string const &attrName) {
     return PyObject_HasAttrString(obj.ptr(), attrName.c_str());
}
int GetPythonArraySize(const boost::python::object& pyArr)
{
	return extract_or_throw<int>(pyArr.attr("__len__")());
}



void registerexcept()
{
  register_exception_translator<elementException>(translator);
}

void impl_templates()
{
	/*
	extract_or_throw<int>(object());
	extract_or_throw<bool>(object());
	extract_or_throw<object>(object());
	extract_or_throw<list>(object());
	extract_or_throw<float>(object());
	extract_or_throw<std::wstring>(object());
	extract_or_throw<tuple>(object());
*/
	/*
	std::vector<object> impl_vobjects;
	std::vector<std::wstring> impl_vstring;
	const boost::python::list val;
	boost::python::dict parameters;

	extract_array<std::wstring>(parameters.keys(),&impl_vstring);
	extract_array<object>(val,&impl_vobjects);

	printf("%i",impl_vstring.size());
	*/
}
wxString extract_wxstring(const boost::python::object& from)
{
	boost::python::extract<std::string> valtype(boost::python::str(from.attr("__class__")));
	if (valtype.check())
	{
		if(valtype()=="<type 'str'>")
		{
			//standart string
			return extract_or_throw<std::string>(from);
		}else if(valtype()=="<type 'unicode'>")
		{
			//Unicode
			return extract_or_throw<std::wstring>(from);
		}
	}
	//Unknown type format
	return extract_or_throw<std::string>(from);
}

#endif
