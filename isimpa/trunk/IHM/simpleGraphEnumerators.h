#include "first_header_include.hpp"

#include <wx/dynarray.h>
#include <wx/string.h>

#ifndef __SIMPLEGRAPH_ENUMERATORS__
#define __SIMPLEGRAPH_ENUMERATORS__

namespace sgSpace
{
	/**
	 * @brief Permet d'associer un nombre à une chaine de caractère
	 *
	 */
	struct t_LstEnums
	{
		t_LstEnums(const wxString& _lblEnum,wxInt32 _enumId):lblEnum(_lblEnum),enumId(_enumId){}
		wxString lblEnum;
		wxInt32 enumId;
	};
	WX_DECLARE_OBJARRAY(t_LstEnums, StyleArray);

	class SG_EnumeratorFiller
	{
	public:
		static void FillStyleEnumeration(StyleArray& arrayToFeed);
		static void FillPenStyleEnumeration(StyleArray& arrayToFeed);
		static void FillBrushStyleEnumeration(StyleArray& arrayToFeed);
		static void FillMarkersStyleEnumeration(StyleArray& arrayToFeed);
		static const wxString& FindStringWithIndex( sgSpace::StyleArray* dataSrc , wxInt32 enumIndex);
	};
}
#endif