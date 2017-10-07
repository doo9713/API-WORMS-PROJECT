#pragma once
#include "Obj.h"

class CTimeUI :	public CObj
{
private :

	static double time;
private :
	bool isStart;
	string first;
	string second;
public:
	CTimeUI(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CTimeUI();
public:
	static void SetTimeMax() { time = 30; }
public:
	void Destroy() { this->~CTimeUI(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void Update();
	void Render();
};

