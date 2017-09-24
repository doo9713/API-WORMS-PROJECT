#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
private :
	bool isGround;
	int index;
	string Dir;
	string State;
public :
	CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CPlayer();
public :
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	void Update();
	void Render();
};

