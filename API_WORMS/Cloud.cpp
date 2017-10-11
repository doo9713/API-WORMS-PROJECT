#include "Cloud.h"



CCloud::CCloud(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _dir)
	: CObj(_name, _tag, _layer, _pos), dir(_dir)
{
}


CCloud::~CCloud()
{
}

bool CCloud::active(CObj& My, CObj& Other)
{
	return false;
}

void CCloud::reactive(CObj& My, CObj& Other)
{

}

void CCloud::Update()
{
	// Pos.x += TIME.Delta() * 100;
	Pos.x = MathF::ClampCycle(Pos.x + TIME.Delta() * dir * 100, -200, 2000);
}

void CCloud::Render()
{
	BITMAP.TransparentBlt(name, 0, Pos.x, Pos.y, RGB(200, 200, 200));
}