#include "first_header_include.hpp"
#include <wx/grid.h>

#ifndef __GRID_CELL_GABE_RENDERER__
#define __GRID_CELL_GABE_RENDERER__

class WXDLLIMPEXP_ADV wxGridCellGabeFloatRenderer : public wxGridCellStringRenderer
{
public:
    wxGridCellGabeFloatRenderer(int precision = -1);

    // get/change formatting parameters
    int GetPrecision() const { return m_precision; }
    void SetPrecision(int precision) 
	 {
		 if(m_precision != precision)
		 {
			 m_precision = precision;
		 }	
	}

    // draw the string right aligned with given width/precision
    virtual void Draw(wxGrid& grid,
                      wxGridCellAttr& attr,
                      wxDC& dc,
                      const wxRect& rect,
                      int row, int col,
                      bool isSelected);

    virtual wxSize GetBestSize(wxGrid& grid,
                               wxGridCellAttr& attr,
                               wxDC& dc,
                               int row, int col);

    // parameters string format is "precision"
    virtual void SetParameters(const wxString& params);

    virtual wxGridCellRenderer *Clone() const;

protected:
    virtual wxString GetString(const wxGrid& grid, int row, int col);

private:
    // formatting parameters
    short m_precision;
};

#endif