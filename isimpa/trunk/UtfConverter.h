#include "first_header_include.hpp"

#include <string>

#ifndef UTFCONVERTER__H__
#define UTFCONVERTER__H__

//#define WXSTRINGTOCHARPTR(wxstr) UtfConverter::ToUtf8(wxstr.t_str()).c_str()
//#define WXSTRINGTOSTDSTRING(wxstr) UtfConverter::ToUtf8(wxstr.t_str())
#define WXSTRINGTOCHARPTR(wxstr) ((const char*)wxstr.mb_str())
#define WXSTRINGTOSTDSTRING(wxstr) std::string((const char*)wxstr.mb_str())
#define WXSTRINGTOSTDWSTRING(wxstr) std::wstring(wxstr.wc_str())
#define STDWSTRINGTOCONSTCHAR(stdwstr) UtfConverter::ToUtf8(stdwstr).c_str()

namespace UtfConverter
{
    std::wstring FromUtf8(const std::string& utf8string);
    std::string ToUtf8(const std::wstring& widestring);
}

#endif
