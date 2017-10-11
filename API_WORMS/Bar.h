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
	void Destroy() { this->~CBar(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	virtual bool Update() = 0;
	virtual void Render() = 0;
};

