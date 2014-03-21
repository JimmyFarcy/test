#include "first_header_include.hpp"

#include "uiTreeCtrl.h"
#include "MainPropGrid.h"
#include <wx/frame.h>

#ifndef __FRAME_APPLICATION_PREFERENCE__
#define __FRAME_APPLICATION_PREFERENCE__

enum APP_PREF_CTRLS
{
	APP_PREF_CTRLS_TREECTRL,
	APP_PREF_CTRLS_PROPERTYGRID

};

class applicationPreferences : public wxFrame
{
public:
	applicationPreferences(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
};

#endif