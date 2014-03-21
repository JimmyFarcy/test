#include "scalar_field_creator.hpp"
#include <string>

#ifndef __TRIANGLE_SCALARFIELDBUILDERS__
#define __TRIANGLE_SCALARFIELDBUILDERS__

namespace ScalarFieldBuilders
{


class TriangleScalarFieldCreator : public ScalarFieldCreator
{
#ifdef _DEBUG
	ivec2 inoutbox;
#endif
public:
 TriangleScalarFieldCreator(const decimal& _resolution); 

 void SecondStep_PushTri(const vec3& A,const vec3& B,const vec3& C);

};

}

#endif