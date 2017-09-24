#include "Obj.h"

CObj::CObj(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: name(_name), tag(_tag), layer(_layer), Pos(_pos), ClipTime(0)
{
}

CObj::~CObj()
{
}

const TAG& CObj::_SetTag_(TAG _tag)
{
	TAG temp = tag;
	tag = _tag;
	OBJ.ChangeTag(this, temp);
	return tag;
}

const LAYER& CObj::_SetLayer_(LAYER _layer)
{
	LAYER temp = layer;
	layer = _layer;
	OBJ.ChangeLayer(this, temp);
	return layer;
}

const string& CObj::_SetName_(const char * _name)
{
	string temp = name;
	name = _name;
	OBJ.ChangeName(this, temp.data());
	return name;
}