#pragma once
#include "Bar.h"
class CHealth : public CBar
{
private:
	double rate;
public:
	CHealth(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super);
	~CHealth();
public:
	void Destroy() { this->~CHealth(); }
public:
	bool Update();
	void Render();
};

