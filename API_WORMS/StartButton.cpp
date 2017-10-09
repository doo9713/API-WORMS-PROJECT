#include "StartButton.h"

CStartButton::CStartButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey)
	:CMyButton(_name, _tag, _layer, _pos, _sizex, _sizey)
{
}

CStartButton::~CStartButton()
{
}

void CStartButton::Destroy()
{
	this->~CStartButton();
}

bool CStartButton::active(CObj& My, CObj& Other)
{
	return false;
}

void CStartButton::reactive(CObj& My, CObj& Other)
{

}

void CStartButton::ClickBt()
{
	gSceneController = GAMELOAD;
}
