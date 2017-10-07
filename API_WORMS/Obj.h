#pragma once

#include "Include.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "BitmapManager.h"
#include "ObjList.h"

class CObj
{
protected :
	MathF::VECTOR Pos;
	TAG tag;
	LAYER layer;
	string name;
	float ClipTime;
public :
	CObj(const char * _name = "GameObj",
		TAG _tag = TAG::Tag_Default,
		LAYER _layer = LAYER::Layer_Default,
		MathF::VECTOR _pos = MathF::VECTOR(0, 0));
	~CObj();
public :
	_declspec(property(put = _SetTag_, get = _GetTag_)) TAG Tag;
	_declspec(property(put = _SetLayer_, get = _GetLayer_)) LAYER Layer;
	_declspec(property(put = _SetName_, get = _GetName_)) string Name;
public :
	const TAG& _SetTag_(TAG _tag);
	const LAYER& _SetLayer_(LAYER _layer);
	const string& _SetName_(const char* _name);
	const TAG& _GetTag_() const { return tag; }
	const LAYER& _GetLayer_() const { return layer; }
	const string& _GetName_() const { return name; }
	const MathF::VECTOR getPos() const { return Pos; }
public :
	virtual void Destroy() = 0;
	virtual bool active(CObj& My, CObj& Other) = 0;
	virtual void reactive(CObj& My, CObj& Other) = 0;
public :
	virtual void Update() = 0;
	virtual void Render() = 0;
};

