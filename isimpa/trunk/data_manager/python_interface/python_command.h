#include "first_header_include.hpp"

/**
 * Cet entête permet d'intéragir avec python sans avoir à inclure le projet ou boost
 * Le code ce trouve dans projet_python.cpp
 */
#include <wx/string>
#ifndef __PYTHON_INTERFACE__
#define __PYTHON_INTERFACE__

void SendPythonCommand(const wxString& cmd);

#endif