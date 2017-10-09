#include "TitleUI.h"


CTitleUI::CTitleUI(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos)
{
}

CTitleUI::~CTitleUI()
{
}

bool CTitleUI::active(CObj& My, CObj& Other)
{
	return false;
}

void CTitleUI::reactive(CObj& My, CObj& Other)
{

}

void CTitleUI::Update()
{

}

void CTitleUI::Render()
{
	BITMAP.TransparentUIBlt(name, 0, Pos.x, Pos.y, RGB(255, 255, 255));
}