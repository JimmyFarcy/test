#include "Animator.hpp"
#include <wx/intl.h>
#include "last_cpp_include.hpp"

Animator::Animator()
:doRendering(false)
{
	loadingTime=wxDateTime::UNow();
	this->Init();
}
Animator::~Animator()
{

}

void Animator::Init(const bool& resetLoadingTime)
{
	if(resetLoadingTime)
		loadingTime=wxDateTime::UNow();
}

bool Animator::DoLoopFromZero()
{
	return false;
}
int Animator::GetNbTimeStep()
{
	return 0;
}

void Animator::SetTimeStep(const int& timeStep)
{


}
bool Animator::IsNeedUpdate(const wxDateTime& timeToCompare)
{
	return loadingTime>timeToCompare;
}
void Animator::InitLegend(legendRendering::ForeGroundGlBitmap& _legendRenderer)
{


}
wxString Animator::GetRendererLabel()
{
	return _(this->GetRendererName());
}
const wxString& Animator::GetRendererName()
{
	return rendererName;
}
void Animator::SetRendererName(const wxString& renderer)
{	
	rendererName=renderer;
}
void Animator::EnableRendering(bool enable)
{
	doRendering=enable;
	RedrawLegend();
}

bool Animator::IsRenderingEnable()
{
	return doRendering;
}
void Animator::SetTextForegroundColor(const ivec4& foregroundColor)
{
	text_foreground_color.Set(foregroundColor.red,foregroundColor.green,foregroundColor.blue,foregroundColor.alpha);
}
void Animator::SetTextBackgroundColor(const ivec4& backgroundColor)
{
	text_background_color.Set(backgroundColor.red,backgroundColor.green,backgroundColor.blue,backgroundColor.alpha);
}
void Animator::SetTextFont(const wxFont& textFont)
{
	legendFont=textFont;
}