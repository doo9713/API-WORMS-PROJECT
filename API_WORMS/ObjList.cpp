#include "ObjList.h"
#include "Obj.h"
#include "Player.h"

CObjList::CObjList()
{
}

CObjList::~CObjList()
{
	for (auto obj : Active)
		delete obj;
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

void CObjList::Remove(CObj * Obj)
{
	if (Obj == nullptr)
		return;

	TagList[Obj->Tag].erase(Obj);

	set<CObj*>::iterator it = LayerList[Obj->Layer].find(Obj);
	(*it)->Layer = Layer_Del;

	auto temp = NameList.find(Obj->Name);
	temp->second.erase(Obj);
}

void CObjList::Dead(CObj * Obj)
{
	if (Obj == nullptr)
		return;

	TagList[Obj->Tag].erase(Obj);

	set<CObj*>::iterator it = LayerList[Obj->Layer].find(Obj);
	(*it)->Layer = Layer_Dead;

	auto temp = NameList.find(Obj->Name);
	temp->second.erase(Obj);
}

void CObjList::Delete()
{
	while (LayerList[Layer_Del].size() > 0)
	{
		CObj * delObj = (*LayerList[Layer_Del].begin());
		LayerList[Layer_Del].begin() = LayerList[Layer_Del].erase(LayerList[Layer_Del].begin());
		delObj->Destroy();
	}
}

void CObjList::Update()
{
	for (set<CObj*>::iterator obj = Active.begin(); obj != Active.end();)
	{
		if (!(*obj)->Update())
			obj = Active.erase(obj);
		else
			++obj;
	}

	if (LayerList[Layer_Del].size() > 0)
		OBJ.Delete();
}

void CObjList::Render()
{
	for (int i = 0; i < Layer_Dead; ++i)
		for (auto obj : LayerList[i])
			obj->Render();
}

void CObjList::ActiveObj(CObj * Obj, TAG Tag)
{
	for (auto object : TagList[Tag])
	{
		if (Obj == object)
			continue;
		if (Obj->active(*Obj, *object))
			(Obj->reactive(*Obj, *object));
	}
}

void CObjList::ActiveObj(CObj * Obj, LAYER layer)
{
	for (auto object : LayerList[layer])
	{
		if (Obj = object)
			continue;
		if (Obj->active(*Obj, *object))
			(Obj->reactive(*Obj, *object));
	}
}

void CObjList::ActiveObj(CObj * Obj, string name)
{
	auto iter = NameList.find(name);
	if (iter == NameList.end())
		return;
	
	for (auto object : iter->second)
	{
		if (Obj == object)
			continue;
		if (Obj->active(*Obj, *object))
			(Obj->reactive(*Obj, *object));
	}
}

void CObjList::ActiveObj(CObj * Obj)
{
	for (auto object : Active)
	{
		if (Obj == object)
			continue;
		if (Obj->active(*Obj, *object))
			(Obj->reactive(*Obj, *object));
	}
}

bool CObjList::CheckAllGround()
{
	for (auto iter : TagList[Tag_Player])
		if (((CPlayer*)iter)->GetState() == "Drop")
			return false;
	return true;
}