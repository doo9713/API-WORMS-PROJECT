#pragma once

#include "Obj.h"
#include "TimeUI.h"

class CPlayer : public CObj
{
private :
	static bool isOver;
	static int playerTurn;
	static string playerList[2];
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
public :
	static void TurnChange() 
	{ 
		playerTurn = MathF::ClampCycle(playerTurn + 1, 0, 1); 
		isOver = false; 
		CTimeUI::SetTimeMax();
	}
public:
	void Destroy() { this->~CPlayer(); }
	void GetDamage(double _damage) { health = MathF::Clamp(health - _damage, 0.0, 100.0); }
	double GetHealth() { return health; }
	double GetGage() { return powergage; }
	string GetState() { return State; }
	MathF::VECTOR GetCenter() { return Pos + 18; }
public :
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	void Update();
	void Render();
};

