#pragma once

#include "Obj.h"

class CGround : public CObj
{
private:
	MathF::VECTOR CollisionPos[TILESIZEXY];
public:
	CGround(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CGround();
public:
	void Destroy() { this->~CGround(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void Update();
	void Render();
public:
	bool IsGroundCheck(MathF::VECTOR check, int data);
};

