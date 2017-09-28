#include "Bar.h"
#include "BitmapManager.h"

CBar::CBar(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos)
{
}

CBar::~CBar()
{
}

bool CBar::active(CObj& My, CObj& Other)
{
	return false;
}

void CBar::reactive(CObj& My, CObj& Other)
{

}

void CBar::Update()
{

}

void CBar::Render()
{
	BITMAP.BitBlt("Bar", 0, Pos.x, Pos.y);
}