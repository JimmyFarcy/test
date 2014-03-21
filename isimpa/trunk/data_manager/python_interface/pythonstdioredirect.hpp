#include "first_header_include.hpp"

#include "boost_python_header.h"
#include <wx/string.h>
#include <list>
/**
 * Cette classe va rediriger la sortie de python vers la zone qui lui est réservé dans l'interface
 */

#ifdef USE_PYTHON
#ifndef __PYTHON_STDIO_REDIRECT__
#define __PYTHON_STDIO_REDIRECT__

class PythonStdIoRedirect {
public:
	PythonStdIoRedirect();
    typedef std::list<wxString> ContainerType;
    void Write( std::wstring const& str );
    void WriteWx( const wxString& str );
	boost::python::str ReadLine(  );
	//Lit une ligne de code
	//Si il n'y a aucun code il faut faire attendre
	bool HasOutput();
    bool GetOutput(wxString& strOut);
protected:
    ContainerType m_outputs;
};

#endif
#endif