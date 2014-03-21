
#include "simpleGraphEnumerators.h"
#include <wx/arrimpl.cpp> 
#include "simpleGraph.h"
#include "last_cpp_include.hpp"

namespace sgSpace
{
	WX_DEFINE_OBJARRAY(StyleArray);

	void SG_EnumeratorFiller::FillStyleEnumeration(StyleArray& arrayToFeed)
	{
		//Chargement des styles de tracés
		arrayToFeed.Add(t_LstEnums(_("Courbe"),DRAWING_METHOD_LINE));
		arrayToFeed.Add(t_LstEnums(_("Histogramme"),DRAWING_METHOD_COLS));
		arrayToFeed.Add(t_LstEnums(_("Echogramme"),DRAWING_METHOD_ECHOGRAM));
		arrayToFeed.Add(t_LstEnums(_("Nuage d'images"),DRAWING_METHOD_STIPPLE));
		arrayToFeed.Add(t_LstEnums(_("Nuage de marqueurs"),DRAWING_METHOD_DOT_CLOUD));
		arrayToFeed.Add(t_LstEnums(_("Courbe arrondi (méthode des splines)"),DRAWING_METHOD_SPLINE));
	}

	const wxString& SG_EnumeratorFiller::FindStringWithIndex( StyleArray* dataSrc , wxInt32 enumIndex)
	{
		for(wxInt32 idligne=0;idligne<dataSrc->GetCount();idligne++)
		{
			if(dataSrc->Item(idligne).enumId==enumIndex)
				return dataSrc->Item(idligne).lblEnum;
		}
		return dataSrc->Item(0).lblEnum;
	}
	void SG_EnumeratorFiller::FillPenStyleEnumeration(StyleArray& arrayToFeed)
	{
		arrayToFeed.Add(t_LstEnums(_("Transparent"),wxTRANSPARENT));
		arrayToFeed.Add(t_LstEnums(_("Trait continu"),wxSOLID));
		arrayToFeed.Add(t_LstEnums(_("Point"),wxDOT));
		arrayToFeed.Add(t_LstEnums(_("Tiret diagonale (gauche)"),wxBDIAGONAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Croix"),wxCROSS_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Trait horizontal"),wxHORIZONTAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Trait vertical"),wxVERTICAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Trait long et point"),wxDOT_DASH));
		arrayToFeed.Add(t_LstEnums(_("Tirets court"),wxSHORT_DASH));
		arrayToFeed.Add(t_LstEnums(_("Tirets longs"),wxLONG_DASH));
	}
	void SG_EnumeratorFiller::FillBrushStyleEnumeration(StyleArray& arrayToFeed)
	{
		arrayToFeed.Add(t_LstEnums(_("Transparent"),wxTRANSPARENT));
		arrayToFeed.Add(t_LstEnums(_("Plein"),wxSOLID));
		arrayToFeed.Add(t_LstEnums(_("Tiret diagonale (gauche)"),wxBDIAGONAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Croix"),wxCROSSDIAG_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Tiret diagonale (droite)"),wxFDIAGONAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Croix 2"),wxCROSS_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Trait horizontal"),wxHORIZONTAL_HATCH));
		arrayToFeed.Add(t_LstEnums(_("Trait vertical"),wxVERTICAL_HATCH));
	}
	void SG_EnumeratorFiller::FillMarkersStyleEnumeration(StyleArray& arrayToFeed)
	{
		arrayToFeed.Add(t_LstEnums(_("Aucun"),DRAWING_MARKER_NONE));
		arrayToFeed.Add(t_LstEnums(_("Rond"),DRAWING_MARKER_DOT));
		arrayToFeed.Add(t_LstEnums(_("Carré"),DRAWING_MARKER_SQUARE));
		arrayToFeed.Add(t_LstEnums(_("Croix diagonale"),DRAWING_MARKER_CROSS_D));
	}
}