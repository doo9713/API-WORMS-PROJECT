#include "ObjList.h"
#include "Obj.h"

CObjList::CObjList()
{
}

CObjList::~CObjList()
{
	for (auto obj : Active)
	{
		delete obj;
	}
}

void CObjList::ChangeTag(CObj * Obj, TAG Tag)
{
	auto iter = TagList[Tag].find(Obj);
	TagList[Tag].erase(iter);
	TagList[Obj->Tag].insert(Obj);
}

void CObjList::ChangeLayer(CObj * Obj, LAYER Layer)
{
	auto iter = LayerList[Layer].find(Obj);
	LayerList[Layer].erase(iter);
	LayerList[Obj->Layer].insert(Obj);
}

void CObjList::ChangeName(CObj * Obj, const char * Name)
{
	auto iter = NameList.find(Name);
	auto second = iter->second.find(Obj);
	iter->second.erase(second);
	if (iter->second.size() < 1)
		NameList.erase(iter);
	iter = NameList.find(Obj->Name);
	if (iter == NameList.end())
	{
		set<CObj*> Temp;
		Temp.insert(Obj);
		NameList.insert(make_pair(Obj->Name, Temp));
	}
	else
		iter->second.insert(Obj);
}

void CObjList::Insert(CObj * Obj)
{
	if (Obj == nullptr)
		return;

	Active.insert(Obj);
	TagList[Obj->Tag].insert(Obj);
	LayerList[Obj->Layer].insert(Obj);

	auto iter = NameList.find(Obj->Name);
	if (iter == NameList.end())
	{
		set<CObj*> Temp;
		Temp.insert(Obj);
		NameList.insert(make_pair(Obj->Name, Temp));
	}
	else
		iter->second.insert(Obj);
}

void CObjList::Update()
{
	for(auto obj : Active)
		obj->Update();
}

void CObjList::Render()
{
	for (int i = 0; i < Layer_End; ++i)
		for (auto obj : LayerList[i])
			obj->Render();
}

void CObjList::ActiveObj(CObj * Obj, TAG Tag)
{}

void CObjList::ActiveObj(CObj * Obj, LAYER layer)
{}

void CObjList::ActiveObj(CObj * Obj, string name)
{}

void CObjList::ActiveObj(CObj * Obj)
{}