#pragma once
#include "Obj.h"

class CCloud : public CObj
{
private:
	int dir;
public:
	CCloud(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int dir);
	~CCloud();
public:
	void Destroy() { this->~CCloud(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void Update();
	void Render();
};

