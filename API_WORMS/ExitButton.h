#pragma once
#include "MyButton.h"

class CExitButton : public CMyButton
{
public:
	CExitButton(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, int _sizex, int _sizey);
	~CExitButton();
public:
	void Destroy();
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	void ClickBt();
};

