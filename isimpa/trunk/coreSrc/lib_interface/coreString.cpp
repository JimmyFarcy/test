#include "coreString.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

CoreString::CoreString(const char* ch):std::string( ch )
{

}

CoreString::CoreString(std::string outputstr):std::string( outputstr )
{

}

CoreString::CoreString(const char* ch, unsigned int length):std::string( ch, length )
{

}

CoreString::CoreString( ):std::string( )
{

}

entier CoreString::ToInt(const CoreString& strtoconv)
{
	return strtoconv.ToInt();
}
decimal CoreString::ToFloat(const CoreString& strtoconv)
{
	return strtoconv.ToFloat();
}
std::string CoreString::FromInt(const entier& valInt)
{
	char buffer[255];
	//itoa(entierLong,buffer,10);
	sprintf(buffer,"%i",valInt);
	std::string fromStr=buffer;
	return fromStr;
}

std::string CoreString::FromFloat(decimal nombreDecimal,entier digits)
{
	char buffer[256];
	//gcvt(nombreDecimal,digits,buffer);
	//std::string fromStr=buffer;
    std::string form;
    std::stringstream form_stream;
    form_stream<<"%"<<digits<<"f";
    form_stream>>form;
    sprintf(buffer,form.c_str(),nombreDecimal);
    std::string fromStr=buffer;
	return fromStr;
}

entier CoreString::ToInt() const
{
	return atoi(this->c_str());
}

decimal CoreString::ToFloat() const
{
	if(this)
	{
		size_type sepPos=this->find(',');
		if(sepPos<this->size())
		{
			CoreString dotnb=*this;
			dotnb.replace(sepPos,1,".");
			return (decimal)atof(dotnb.c_str());
		}else{
			return (decimal)atof(this->c_str());
		}
	}else{
		return 0.f;
	}
}
