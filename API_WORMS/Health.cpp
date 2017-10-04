#include "Health.h"



CHealth::CHealth(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super)
	: CBar(_name, _tag, _layer, _pos, _super)
{
}

CHealth::~CHealth()
{
}

bool CHealth::Update()
{
	Pos.x = super->getPos().x - 25;
	Pos.y = super->getPos().y + 40;
	return true;
}

void CHealth::Render()
{
	if (super->GetState() != "Drop")
	{
		BITMAP.BitBlt("Bar", 0, Pos.x, Pos.y);
		BITMAP.DrawGage(Pos.x + 1, Pos.y + 1, Pos.x + 94, Pos.y + 15, RGB(255, 0, 0));
	}
}