#pragma once

#include "Obj.h"

class CBar : public CObj
{
public:
	CBar(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CBar();
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void Update();
	void Render();
};

