/**
 * @file inter_logger.hpp
 * This file define the interface methods to retrieve processManager messages.
 */
#include "first_header_include.hpp"
#include "manager/interf_logger.hpp"
#include <wx/string.h>
#include <vector>
#include <wx/regex.h>

#ifndef __TETGEINTERFACE_LOGGER__
#define __TETGEINTERFACE_LOGGER__
class TetgenDebugLogger : public InterfLogger
{
private:
	std::vector<int> faceIntersect;
	wxRegEx invalidPolyHeader;
	wxRegEx intersectTriHeader;
public:
	TetgenDebugLogger()
		:  invalidPolyHeader(wxT("  Facet \\(([0-9]*), ([0-9]*), ([0-9]*)\\) \\(([0-9]*)\\) is not a valid polygon.")),
		 intersectTriHeader(wxT(" Facet #([0-9]*) intersects facet #([0-9]*) at triangles:"))
	{

	}
	virtual void LogMessage(const wxString& mess)
	{
		if(invalidPolyHeader.Matches(mess))
		{
			const wxString& sfaceInd(invalidPolyHeader.GetMatch(mess,4));
			long faceInd(0);
			if(sfaceInd.ToLong(&faceInd))
				faceIntersect.push_back(faceInd);
		}else if(intersectTriHeader.Matches(mess))
		{
			const wxString& sfaceInd(intersectTriHeader.GetMatch(mess,1));
			long faceInd(0);
			if(sfaceInd.ToLong(&faceInd))
				faceIntersect.push_back(faceInd);
			const wxString& sface2Ind(intersectTriHeader.GetMatch(mess,2));
			if(sface2Ind.ToLong(&faceInd))
				faceIntersect.push_back(faceInd);
		}
	}
	virtual void LogError(const wxString& mess)
	{

	}
	virtual void LogWarning(const wxString& mess)
	{

	}
	std::vector<int>& GetFaces()
	{
		return faceIntersect;
	}
};
#endif
