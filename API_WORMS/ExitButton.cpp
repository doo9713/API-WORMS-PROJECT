#include "ExitButton.h"

CExitButton::CExitButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey)
	: CMyButton(_name, _tag, _layer, _pos, _sizex, _sizey)
{
}

CExitButton::~CExitButton()
{
}

void CExitButton::Destroy()
{
	this->~CExitButton();
}

bool CExitButton::active(CObj& My, CObj& Other)
{
	return false;
}

void CExitButton::reactive(CObj& My, CObj& Other)
{

}

void CExitButton::ClickBt()
{
	gSceneController = EXITGAME;
}
