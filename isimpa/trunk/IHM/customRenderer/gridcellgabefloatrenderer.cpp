#include "gridcellgabefloatrenderer.hpp"
#include <wx/log.h>
#include <float.h>
#include <std_tools.hpp>
#include "last_cpp_include.hpp"

// ----------------------------------------------------------------------------
// wxGridCellGabeFloatRenderer
// ----------------------------------------------------------------------------

wxGridCellGabeFloatRenderer::wxGridCellGabeFloatRenderer(int precision)
{
    SetPrecision(precision);
}

wxGridCellRenderer *wxGridCellGabeFloatRenderer::Clone() const
{
    wxGridCellGabeFloatRenderer *renderer = new wxGridCellGabeFloatRenderer;
    renderer->m_precision = m_precision;
    return renderer;
}

wxString wxGridCellGabeFloatRenderer::GetString(const wxGrid& grid, int row, int col)
{
    wxGridTableBase *table = grid.GetTable();

    bool hasDouble;
    double val;
    wxString text;
    if ( table->CanGetValueAs(row, col, wxGRID_VALUE_FLOAT) )
    {
        val = table->GetValueAsDouble(row, col);
        hasDouble = true;
    }
    else
    {
        text = table->GetValue(row, col);
        hasDouble = text.ToDouble(&val);
    }

    if ( hasDouble )
    {
		if(st_isfinite(val))
		{
			text=wxString::Format("%."+wxString::Format("%i",m_precision)+"f",val);
		}else{
			if(val>0)
				text="+Inf";
			else
				text="-Inf";
		}
    }
    //else: text already contains the string

    return text;
}

void wxGridCellGabeFloatRenderer::Draw(wxGrid& grid,
                                   wxGridCellAttr& attr,
                                   wxDC& dc,
                                   const wxRect& rectCell,
                                   int row, int col,
                                   bool isSelected)
{
    wxGridCellRenderer::Draw(grid, attr, dc, rectCell, row, col, isSelected);

    SetTextColoursAndFont(grid, attr, dc, isSelected);

    // draw the text right aligned by default
    int hAlign, vAlign;
    attr.GetAlignment(&hAlign, &vAlign);
    hAlign = wxALIGN_RIGHT;

    wxRect rect = rectCell;
    rect.Inflate(-1);

    grid.DrawTextRectangle(dc, GetString(grid, row, col), rect, hAlign, vAlign);
}

wxSize wxGridCellGabeFloatRenderer::GetBestSize(wxGrid& grid,
                                            wxGridCellAttr& attr,
                                            wxDC& dc,
                                            int row, int col)
{
    return DoGetBestSize(attr, dc, GetString(grid, row, col));
}

void wxGridCellGabeFloatRenderer::SetParameters(const wxString& params)
{
    if ( !params )
    {
        // reset to defaults
        SetPrecision(-1);
    }
    else
    {
		long precision;
        if ( params.ToLong(&precision) )
        {
            SetPrecision((int)precision);
        }
        else
        {
            wxLogDebug(_T("Invalid wxGridCellGabeFloatRenderer precision parameter string '%s ignored"), params.c_str());
        }
    }
}
