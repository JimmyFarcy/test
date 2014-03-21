#include "pythonstdioredirect.hpp"
#include "UtfConverter.h"
#include "last_cpp_include.hpp"

#ifdef USE_PYTHON
using namespace boost::python;


PythonStdIoRedirect::PythonStdIoRedirect()
{
	
}
void PythonStdIoRedirect::Write( std::wstring const& str ) {
    m_outputs.push_back(str);
}
void PythonStdIoRedirect::WriteWx( const wxString& str ) {
    m_outputs.push_back(str);
}

boost::python::str PythonStdIoRedirect::ReadLine( )
{
	wxString retStr;
	GetOutput(retStr);
	return WXSTRINGTOCHARPTR(retStr);
}
bool PythonStdIoRedirect::HasOutput()
{
	return m_outputs.size()>0;
}
bool PythonStdIoRedirect::GetOutput(wxString& strOut)
{
	if(m_outputs.size()>0)
	{
		strOut=m_outputs.front();
		m_outputs.pop_front();
		return true;
	}else{
		return false;
	}
}

#endif