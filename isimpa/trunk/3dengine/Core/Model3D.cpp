#include "Model3D.h"
#include <boost/functional/hash.hpp>
#include "last_cpp_include.hpp"



std::size_t t_faceIndex::GetHashValue() const
{
	std::size_t seed = 0;
    boost::hash_combine(seed, f);
    boost::hash_combine(seed, g);
    return seed;
}