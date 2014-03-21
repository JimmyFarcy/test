#ifndef SMART_MACRO_INCLUDED
#define SMART_MACRO_INCLUDED

#define USE_LOCAL_SMART_PTR
#ifndef USE_LOCAL_SMART_PTR
#include <boost/smart_ptr.hpp>
#define PTR boost::shared_ptr
#define PTR_ARR boost::shared_array
#else
#include "manager/smart_ptr.h"
#define PTR smart_ptr
#define PTR_ARR smart_ptr_ar
#endif

#endif // SMART_MACRO_INCLUDED
