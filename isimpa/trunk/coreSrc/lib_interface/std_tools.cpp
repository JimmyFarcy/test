#include "std_tools.hpp"
#include <math.h>
#include <float.h>
#ifdef _WIN32
	#include <direct.h>
#endif
#ifdef _UNIX
	#include <sys/stat.h>
    #include <sys/types.h>
#endif

int st_mkdir(const char* pathname, int perm)
{
	#ifdef _WIN32
		return mkdir(pathname);
	#endif
	#ifdef _UNIX
		return mkdir(pathname,perm);
	#endif
}


bool st_isfinite(const float& value)
{
	#ifdef _MSC_VER
		return _finite(value);
	#else
		return isfinite(value);
	#endif
}
