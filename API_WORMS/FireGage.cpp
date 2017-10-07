#include "FireGage.h"
#include "KeyManager.h"


CFireGage::CFireGage(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super)
	: CBar(_name, _tag, _layer, _pos, _super), rate(0)
{
}

CFireGage::~CFireGage()
{
}

void CFireGage::Update()
{ 
	if (super->Layer == Layer_Del)
	{
		OBJ.Remove(this);
		return;
	}

	Pos.x = super->getPos().x - 25;
	Pos.y = super->getPos().y + 56;

	rate = (double)94 / 100 * super->GetGage();
}

void CFireGage::Render()
{
	if (super->GetState() != "Drop")
	{
		BITMAP.BitBlt("Bar", 0, Pos.x, Pos.y);
		BITMAP.DrawGage(Pos.x + 1, Pos.y + 1, Pos.x + rate, Pos.y + 15, RGB(255, 255, 0));
	}
}