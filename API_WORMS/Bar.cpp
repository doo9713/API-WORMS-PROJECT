#include "Bar.h"
#include "BitmapManager.h"

CBar::CBar(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super)
	: CObj(_name, _tag, _layer, _pos), super(_super)
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