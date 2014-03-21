#include "stdgabe.h"


namespace gabe_io
{
	using namespace std;
	using namespace formatGABE;

#define CHECK_GABE_COL_INDICE (int)indicecol<cols && colsContainer[indicecol]!=NULL

	Gabe_rw::Gabe_rw(const size_t& sizeHint)
		:GABE(sizeHint)
	{
		filledcols=0;
	}

	Gabe_rw::Gabe_rw()
		:GABE()
	{
		filledcols=0;
	}
	bool Gabe_rw::Load(const string& fileName)
	{
		bool res=GABE::Load(fileName.c_str());
		filledcols=GABE::GetCols();
		return res;
	}
	bool Gabe_rw::Save(const string& fileName)
	{
		return GABE::Save(fileName.c_str());
	}

	void Gabe_rw::AppendStrCol( const stringarray& coldata, const string& coltitle )
	{
		GABE_Data_ShortString* cdata=new GABE_Data_ShortString(coldata.size());
		for(size_t idrow=0;idrow<cdata->GetSize();idrow++)
			cdata->SetString(idrow,coldata[idrow].c_str());
		cdata->SetLabel(coltitle.c_str());
		this->AppendCol(cdata);
	}
	void Gabe_rw::AppendIntCol( const intarray& coldata, const string& coltitle )
	{
		GABE_Data_Integer* cdata=new GABE_Data_Integer(coldata.size());
		for(size_t idrow=0;idrow<cdata->GetSize();idrow++)
			cdata->Set(idrow,coldata[idrow]);
		cdata->SetLabel(coltitle.c_str());
		this->AppendCol(cdata);
	}
	void Gabe_rw::AppendFloatCol( const floatarray& coldata, const string& coltitle, const int& precision )
	{
		GABE_Data_Float* cdata=new GABE_Data_Float(coldata.size());
		for(size_t idrow=0;idrow<cdata->GetSize();idrow++)
			cdata->Set(idrow,coldata[idrow]);
		cdata->SetLabel(coltitle.c_str());
		cdata->headerData.numOfDigits=precision;
		this->AppendCol(cdata);
	}
	bool Gabe_rw::IsReadOnly()
	{
		return GABE::IsReadOnly();
	}
	void Gabe_rw::SetReadOnly(const bool& ReadOnly)
	{
		if(ReadOnly)
			GABE::LockData();
		else
			GABE::UnlockData();

	}

	int Gabe_rw::GetFirstEmptyCol()
	{
		Longb colsiz(this->GetCols());
		for(Intb idcol=0;idcol<colsiz;idcol++)
		{
			if(colsContainer[idcol]==NULL)
				return idcol;
		}
		return -1;
	}
	void Gabe_rw::AppendCol(GABE_Object* objtoappend)
	{
		Longb insertcol=this->GetFirstEmptyCol();
		if(insertcol==-1)
		{
			insertcol=GABE::GetCols();
			GABE::Redim(GABE::GetCols()+1);
		}
		GABE::SetCol(insertcol,objtoappend);
		filledcols=insertcol+1;
	}

	size_t Gabe_rw::size() const
	{
		return filledcols;
	}
	stringarray Gabe_rw::operator[](size_t indicecol)
	{
		if(CHECK_GABE_COL_INDICE)
		{
			size_t nbrows=colsContainer[indicecol]->GetSize();
			stringarray retval(nbrows);
			for(size_t idrow=0;idrow<nbrows;idrow++)
				retval[idrow]=colsContainer[indicecol]->GetStringEquiv(idrow);
			return retval;
		}else{
			return stringarray();
		}
	}
	string Gabe_rw::GetColTitle(const size_t& indicecol)
	{
		if(CHECK_GABE_COL_INDICE)
		{
			return colsContainer[indicecol]->GetLabel();
		}else{
			return string();
		}
	}
	typearray Gabe_rw::GetTabTypes()
	{
		typearray tabtypes;
		Longb colsiz(this->GetCols());
		tabtypes.reserve(colsiz);
		for(Intb idcol=0;idcol<colsiz;idcol++)
		{
			if(colsContainer[idcol]!=NULL)
			{
				tabtypes.push_back(colsContainer[idcol]->GetObjectType());
			}
		}
		return tabtypes;
	}
	void Gabe_rw::ReadColStr(const size_t& indicecol,stringarray& coldata)
	{
		if(CHECK_GABE_COL_INDICE)
		{
			size_t nbrows=colsContainer[indicecol]->GetSize();
			coldata.reserve(nbrows);
			for(size_t idrow=0;idrow<nbrows;idrow++)
				coldata.push_back(colsContainer[indicecol]->GetStringEquiv(idrow));
		}
	}

	void Gabe_rw::ReadColInt(const size_t& indicecol,intarray& coldata)
	{
		if(CHECK_GABE_COL_INDICE)
		{
			GABE_Data_Integer* colobj;
			if(GABE::GetCol(indicecol,&colobj))
			{
				size_t nbrows=colobj->GetSize();
				coldata.reserve(nbrows);
				for(size_t idrow=0;idrow<nbrows;idrow++)
					coldata.push_back(colobj->GetValue(idrow));
			}
		}
	}
	void Gabe_rw::ReadColFloat(const size_t& indicecol,floatarray& coldata)
	{

		if(CHECK_GABE_COL_INDICE)
		{
			GABE_Data_Float* colobj;
			if(GABE::GetCol(indicecol,&colobj))
			{
				size_t nbrows=colobj->GetSize();
				coldata.reserve(nbrows);
				for(size_t idrow=0;idrow<nbrows;idrow++)
					coldata.push_back(colobj->GetValue(idrow));
			}
		}
	}


};
