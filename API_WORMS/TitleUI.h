#pragma once
#include "Obj.h"
class CTitleUI : public CObj
{
public:
	CTitleUI(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos);
	~CTitleUI();
public:
	void Destroy() { this->~CTitleUI(); }
public:
	bool active(CObj& My, CObj& Other);
	void reactive(CObj& My, CObj& Other);
public:
	bool Update();
	void Render();
};

