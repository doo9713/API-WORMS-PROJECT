#pragma once
#include "Obj.h"

class CExplosion : public CObj
{
private :
	int index;
public:
	CExplosion(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CExplosion();
public:
	void Destroy() { this->~CExplosion(); }
public :
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	bool Update();
	void Render();
};

