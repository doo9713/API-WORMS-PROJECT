#pragma once
#include "Bar.h"
class CHealth : public CBar
{
public:
	CHealth(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super);
	~CHealth();
public:
	void Update();
	void Render();
};

