#ifdef _DEBUG
#ifdef _WIN32
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#endif
#ifdef WXINTL_NO_GETTEXT_MACRO
#ifdef _UNIX
#define _(s) wxGetTranslation((s))
#endif
#endif
