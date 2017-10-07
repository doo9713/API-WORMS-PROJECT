#pragma once
#include "Obj.h"
class CBomb : public CObj
{
private :
	bool isOver;
	double speed;
	MathF::VECTOR startPos;
	MathF::VECTOR dstPos;
	MathF::VECTOR midPos;
	string Dir;
	string State;
	string Angle;
public:
	CBomb(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, double _power, double _angle, int _dir);
	~CBomb();
public :
	void Destroy() { this->~CBomb(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public :
	void Update();
	void Render();
};

