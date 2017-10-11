#pragma once
#include "Obj.h"

class CMyButton : public CObj
{
protected:
	string state;
	int sizeX;
	int sizeY;
	bool FirstInto;
public:
	CMyButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey);
	~CMyButton();
public:
	virtual void Destroy() = 0;
	virtual bool active(CObj& My, CObj& Other) = 0;
	virtual void reactive(CObj& My, CObj& Other) = 0;
public:
	void Update();
	void Render();
public:
	bool IntoBt();
	virtual void ClickBt() = 0;
};

