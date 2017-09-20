#pragma once

#include "Manager.h"

class CObj;
class CObjList : public CManager<CObjList>
{
private :
	set<CObj*> TagList[TAG::Tag_End];
	set<CObj*> LayerList[LAYER::Layer_End];
	map<string, set<CObj*>> NameList;
	set<CObj*> Active;
public :
	CObjList();
	~CObjList();
public :
	void ChangeTag(CObj * Obj, TAG Tag);
	void ChangeLayer(CObj * Obj, LAYER Layer);
	void ChangeName(CObj * Obj, const char * Name);
	void Insert(CObj * Obj);
	void Update();
	void Render();
public:
	void ActiveObj(CObj * Obj, TAG Tag);
	void ActiveObj(CObj * Obj, LAYER Layer);
	void ActiveObj(CObj * Obj, string Name);
	void ActiveObj(CObj * Obj);
};

