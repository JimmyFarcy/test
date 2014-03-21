/**
 * @file inter_logger.hpp
 * This file define the interface methods to retrieve processManager messages.
 */
#include "first_header_include.hpp"
#include <wx/string.h>

#ifndef __INTERFACE_LOGGER__
#define __INTERFACE_LOGGER__
class InterfLogger
{
public:
	virtual void LogMessage(const wxString& mess)=0;
	virtual void LogError(const wxString& mess)=0;
	virtual void LogWarning(const wxString& mess)=0;
};
#endif