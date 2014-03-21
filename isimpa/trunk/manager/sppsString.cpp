#include "stringTools.h"
#include <wx/tokenzr.h>
#include "last_cpp_include.hpp"

wxString Convertor::fromConvDecimal=' ';
wxString Convertor::toConvDecimal=' ';

float Convertor::ToFloat( const wxString& sval )
{
		double rval(0.);
		if(sval.ToDouble(&rval))
			return rval;
		else
		{
			if(toConvDecimal==' ')
				updateDecimalChar(); //Conversion decimal si necessaire
			wxString convDecimal(sval);
			convDecimal.Replace( fromConvDecimal,toConvDecimal,false);
			convDecimal.ToDouble(&rval);
			return rval;
		}
}
char Convertor::getConvFrom()
{
	if(fromConvDecimal==' ')
		updateDecimalChar();
	return fromConvDecimal.GetChar(0);
}


void SplitString(wxString src,wxString delimiter,wxArrayString& dst)
{
	wxStringTokenizer tkz(src, delimiter);
	while ( tkz.HasMoreTokens() )
	{
		dst.Add(tkz.GetNextToken());
	}
}
void SplitString(wxString src,wxString delimiter,std::vector<wxFloat32>& dst)
{
	wxStringTokenizer tkz(src, delimiter);
	while ( tkz.HasMoreTokens() )
	{
		dst.push_back(Convertor::ToFloat(tkz.GetNextToken()));
	}
}
char Convertor::getConvTo()
{
	if(toConvDecimal==' ')
		updateDecimalChar();
	return toConvDecimal.GetChar(0);
}
float Convertor::ToFloat(char* String)
{
	double val;
	val=atof( String );
	return val;

}
wxString Convertor::ToString( float fval ,wxString decimal, int nbdecimal)
{
		wxString toD=toConvDecimal;
		if(toConvDecimal==' ')
			updateDecimalChar();
		if(decimal!=' ')
		{
			decimal=fromConvDecimal;
			if(decimal==".")
				toD=",";
			else
				toD=".";
		}
		wxString sval;
		sval.Printf("%."+ToString(nbdecimal)+"f",fval); //<<fval;
		if(decimal!=' ')
			sval.Replace(toD, decimal,false);
		return sval;
}

wxString Convertor::ToString( int ival)
{
		if(toConvDecimal==' ')
			updateDecimalChar();
		wxString sval;
		sval<<ival;
		return sval;
}
int Convertor::ToInt( const wxString& sval )
{
		long rval;
		sval.ToLong(&rval);
		return rval;
}

long long Convertor::ToLong( wxString sval )
{
		long long rval;
		sval.ToLongLong(&rval);
		return rval;
}

void Convertor::updateDecimalChar()
{
	struct lconv locale_structure;
	struct lconv *locale_ptr=&locale_structure;
	locale_ptr=localeconv();
	locale_ptr->decimal_point;

	if(*locale_ptr->decimal_point=='.')
	{
		fromConvDecimal=',';
		toConvDecimal='.';
	}else{
		fromConvDecimal='.';
		toConvDecimal=',';
	}
}
