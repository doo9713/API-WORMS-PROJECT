#pragma once
#include "Bar.h"
class CFireGage : public CBar
{
private :
	double rate;
public:
	CFireGage(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super);
	~CFireGage();
public:
	void Update();
	void Render();
};

