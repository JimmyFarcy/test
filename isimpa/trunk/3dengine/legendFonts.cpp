#include "legendFonts.h"
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/log.h>
#include "last_cpp_include.hpp"


namespace legendRendering
{

	legendText::legendText()
	{
		textForeground.Set(0,0,0);
		textBackground.Set(0,0,0,0);
	}
	void legendText::SetTextForeground(const wxColour& colour)
	{
		textForeground=colour;
	}
	void legendText::SetTextBackground(const wxColour& colour)
	{	
		textBackground=colour;
	}
	void legendText::SetFont(const wxFont& font)
	{
		textFont=font;
	}
	void legendText::InitText(const wxString& text,int maxLength)
	{
		DoAppendText(text,0,0,true,maxLength);
	}
	/*
	void legendText::DoAppendText(const wxString& text,int x,int y, bool overwrite,int maxLength)
	{
		//Todo utiliser uniquement l'espace nécessaire à la chaine de caractère
		wxMemoryDC textDrawer;
		textDrawer.SetBrush( *wxGREEN_BRUSH );
		textDrawer.SetTextBackground(textBackground);
		textDrawer.SetTextForeground(textForeground);
		textDrawer.SetFont(textFont);

		wxSize sizeText;
		if(maxLength==-1 || maxLength<text.size())
			sizeText=textDrawer.GetTextExtent(text);
		else
			sizeText=textDrawer.GetTextExtent(wxString("0",maxLength));		
		if(!foreground_tex)
		{
			legendObject::Init(sizeText.GetWidth(),sizeText.GetHeight());
		}

		unsigned char* color=new unsigned char[objConfig.width*objConfig.height*3];
		unsigned char* alpha=new unsigned char[objConfig.width*objConfig.height];
		memset(color,0,objConfig.width*objConfig.height*3);
		memset(alpha,255,objConfig.width*objConfig.height);

		wxImage emptyImage(objConfig.width,objConfig.height,color,alpha);

		wxBitmap tmpBitmap(emptyImage);
		textDrawer.SelectObject(tmpBitmap);
		if(textBackground.Alpha()==255)
			textDrawer.SetBackgroundMode(wxSOLID);
		else
			textDrawer.SetBackgroundMode(wxTRANSPARENT);
	
		textDrawer.DrawText(text,x,y);
		textDrawer.SelectObject(wxNullBitmap);
		wxImage imageTxt=tmpBitmap.ConvertToImage();
		CopyFont(imageTxt.GetData(),imageTxt.GetAlpha(),overwrite);	
	}
	*/
	void legendText::DoAppendText(const wxString& text,int x,int y, bool overwrite,int maxLength)
	{
		//Todo utiliser uniquement l'espace nécessaire à la chaine de caractère
		wxMemoryDC textDrawer;
		textDrawer.SetBrush( *wxGREEN_BRUSH );
		textDrawer.SetTextBackground(textBackground);
		textDrawer.SetTextForeground(textForeground);
		textDrawer.SetFont(textFont);

		wxSize sizeText;
		if(maxLength==-1 || maxLength<text.size())
		{
			sizeText=textDrawer.GetTextExtent(text);
		}else{
			sizeText=textDrawer.GetTextExtent(wxString("0").Pad(maxLength));
		}
		if(!foreground_tex)
		{
			legendObject::Init(sizeText.GetWidth(),sizeText.GetHeight());
		}

		unsigned char* color=new unsigned char[sizeText.GetWidth()*sizeText.GetHeight()*3];
		unsigned char* alpha=new unsigned char[sizeText.GetWidth()*sizeText.GetHeight()];
		memset(color,0,sizeText.GetWidth()*sizeText.GetHeight()*3);
		memset(alpha,255,sizeText.GetWidth()*sizeText.GetHeight());

		wxImage emptyImage(sizeText.GetWidth(),sizeText.GetHeight(),color,alpha);

		wxBitmap tmpBitmap(emptyImage);
		textDrawer.SelectObject(tmpBitmap);
		if(textBackground.Alpha()==255)
			textDrawer.SetBackgroundMode(wxSOLID);
		else
			textDrawer.SetBackgroundMode(wxTRANSPARENT);
	
		textDrawer.DrawText(text,0,0);
		textDrawer.SelectObject(wxNullBitmap);
		wxImage imageTxt=tmpBitmap.ConvertToImage();
		DoCopy(imageTxt.GetData(),imageTxt.GetAlpha(),sizeText.GetWidth(),sizeText.GetHeight(),overwrite,x,y);	
	}
	void legendText::AppendText(const wxString& text,int x,int y)
	{
		/*
		wxFont oldfont=textFont;
		//textFont.SetPointSize(textFont.GetPointSize()+2);
		textFont.SetFamily(
		x-=1;
		y-=1;
		wxPen::set
		wxColour oldcolour=textForeground;
		textForeground=*wxBLACK;
		DoAppendText(text,x,y,false);
		textFont=oldfont;
		textForeground=oldcolour;
		*/
		DoAppendText(text,x,y,false);
	}
	
	wxSize legendText::GetTextSize(const wxString& text)
	{
		
		wxMemoryDC textDrawer;
		textDrawer.SetBrush( *wxGREEN_BRUSH );
		textDrawer.SetTextBackground(textBackground);
		textDrawer.SetTextForeground(textForeground);
		textDrawer.SetFont(textFont);
		wxSize sizeText;
		sizeText=textDrawer.GetTextExtent(text);
		return sizeText;
	}
}