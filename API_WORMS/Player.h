#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
private :
	bool isGround;
	int index;
	double health;
	double angle;
	double powergage;
	string Dir;
	string State;
public :
	CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CPlayer();
public:
	void Destroy() { this->~CPlayer(); }
public :
	void SetHealth(double _Health) { health = _Health; }
	double GetHealth() { return health; }
	double GetGage() { return powergage; }
	string GetState() { return State; }
public :
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	bool Update();
	void Render();
};

