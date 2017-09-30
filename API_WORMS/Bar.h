#pragma once

#include "Obj.h"
#include "Player.h"

class CBar : public CObj
{
protected:
	CPlayer * const super;
public:
	CBar(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, CPlayer * const _super);
	~CBar();
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void Update();
	void Render();
};

