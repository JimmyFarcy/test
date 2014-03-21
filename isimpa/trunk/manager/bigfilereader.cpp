﻿#include "bigfilereader.h"
#include "last_cpp_include.hpp"
#define CHAR_TAB 9
#define CHAR_RETURN_WIN 13
#define CHAR_RETURN_UNIX 10
#define CHAR_FINCHAINE 0

BigFileReader::BigFileReader(wxString file,unsigned long _cacheSize)
{
	cacheSize=_cacheSize;
	fBuffer=new char[_cacheSize];
	bufferPos=0;
	if(wxFileExists(file))
	{
		if(oFile.Open(file))
		{
			FillBuffer();
		}
	}
}
BigFileReader::~BigFileReader()
{
	delete[] fBuffer;
	oFile.Close();
}
bool BigFileReader::FillBuffer()
{
	long remind=oFile.Length()-oFile.Tell();
	if(remind<cacheSize)
		cacheSize=remind;
	if(cacheSize==0)
		return false;
	bufferPos=0;
	oFile.Read(fBuffer,cacheSize);
	return true;
}

float BigFileReader::getPercentRead()
{
	long currentsize=oFile.Tell()-cacheSize+bufferPos;
	return (float)currentsize/oFile.Length();
}

bool BigFileReader::IsOk()
{
	return oFile.IsOpened() && cacheSize>0;
}

bool BigFileReader::GetDecimal(double *fl)
{
	char pBuffer[35] = {0};
    int index = 0;
	this->GetNext(pBuffer + index);
    while (*(pBuffer + index) != CHAR_TAB && *(pBuffer + index) != CHAR_RETURN_WIN && *(pBuffer + index) != CHAR_RETURN_UNIX && *(pBuffer + index) != CHAR_FINCHAINE)
	{
		index++;
		this->GetNext(pBuffer + index);
    }
	pBuffer[index]=0;
	if(index==0)
	{
		return false;
	}else{
		*fl = atof( pBuffer );
		return true;
	}
}

//Retourne le prochain caractère
bool BigFileReader::GetNext(char* outputChar)
{
	if(bufferPos>=cacheSize)
		if(!FillBuffer())
			return false;
	*outputChar=fBuffer[bufferPos];
	bufferPos++;
	return true;
}


wxString BigFileReader::GetLine()
{
	std::string valRet;
	char pBuffer;

	this->GetNext(&pBuffer);

	while (!(pBuffer != CHAR_RETURN_WIN && pBuffer != CHAR_RETURN_UNIX && pBuffer != CHAR_FINCHAINE))
	{
		if(!this->GetNext(&pBuffer))
			break;
	}

	while (pBuffer != CHAR_RETURN_WIN && pBuffer != CHAR_RETURN_UNIX && pBuffer != CHAR_FINCHAINE)
	{
		valRet.append(&pBuffer,1);
		if(!this->GetNext(&pBuffer))
			break;
	}
	return valRet;
}