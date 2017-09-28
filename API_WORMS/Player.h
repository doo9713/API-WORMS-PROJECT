#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
private :
	bool isGround;
	int index;
	double health;
	string Dir;
	string State;
public :
	CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CPlayer();
public :
	void SetHealth(double _Health) { health = _Health; }
	double GetHealth() { return health; }
public :
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	void Update();
	void Render();
};

