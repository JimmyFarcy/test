#include "first_header_include.hpp"


#include <wx/dynarray.h>
#include <wx/hashmap.h>

#ifndef __SIMPLEGRAPH_ARRAYS__
#define __SIMPLEGRAPH_ARRAYS__

namespace sgSpace
{
	class SG_Element;


	WX_DEFINE_ARRAY_DOUBLE(wxDouble, ArrayOfFloats);
	WX_DECLARE_HASH_MAP( wxInt32, SG_Element*, wxIntegerHash, wxIntegerEqual, ArrayOfGraphEl );
}

#endif