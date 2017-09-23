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

void CGround::Update()
{
	// TODO : Object Update
}

void CGround::Render()
{
	// TODO : Object Render
	BITMAP.TransparentBlt(name, 0, Pos.x, Pos.y, RGB(255,255,255));
}