#include "MyButton.h"

CMyButton::CMyButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey)
	: CObj(_name, _tag, _layer, _pos), state("Idle"), sizeX(_sizex), sizeY(_sizey)
{
}

CMyButton::~CMyButton()
{
}

void CMyButton::Update()
{
	if (IntoBt() && KEY.Push(VK_LBUTTON))
		ClickBt();
}

void CMyButton::Render()
{
	BITMAP.TransparentUIBlt("bt" + name + state, 0, Pos.x, Pos.y, RGB(255, 255, 255));
}

bool CMyButton::IntoBt()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hWnd, &mouse);

	if ((mouse.x > Pos.x) && (mouse.x < Pos.x + sizeX) && (mouse.y > Pos.y) && (mouse.y < Pos.y + sizeY))
	{
		state = "Into";
		return true;
	}
	state = "Idle";
	return false;
}