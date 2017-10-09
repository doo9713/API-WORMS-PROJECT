#pragma once
#include "MyButton.h"
class CStartButton : public CMyButton
{
public:
	CStartButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey);
	~CStartButton();
public:
	void Destroy();
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void ClickBt();
};

