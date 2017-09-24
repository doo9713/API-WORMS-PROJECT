#include "Ground.h"

CGround::CGround(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos)
{
	for (int i = 0; i < 64; ++i)
		CollisionPos[i] = MathF::VECTOR(Pos.x + i, Pos.y);
}

CGround::~CGround()
{
}

bool CGround::active(CObj& My, CObj& Other)
{
	return false;
}

void CGround::reactive(CObj& My, CObj& Other)
{
}

void CGround::Update()
{
	// TODO : Object Update
}

void CGround::Render()
{
	// TODO : Object Render
	BITMAP.TransparentBlt(name, 0, Pos.x, Pos.y, RGB(255,255,255));
}

bool CGround::IsGroundCheck(MathF::VECTOR check)
{
	for (int i = 0; i < SIZEXY; ++i)
		if (MathF::Distance(CollisionPos[i], check) <= HEIGHT / 2 - 4)
			return true;
	return false;
}