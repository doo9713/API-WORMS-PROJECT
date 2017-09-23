#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
private :
	int index;
	string Dir;
	string State;
public:
	CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CPlayer();
public:
	void Update();
	void Render();
};

