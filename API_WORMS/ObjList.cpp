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

	for (auto iter : TagList[Obj->Tag]) 
	{
		if (iter == Obj)
		{
			TagList[Obj->Tag].erase(iter);
			break;
		}
	}
	for (auto iter : LayerList[Obj->Layer])
	{
		if (iter == Obj)
		{
			iter->Layer = Layer_Del;
			break;
		}
	}

	auto temp = NameList.find(Obj->Name);
	for (auto iter : temp->second)
	{
		if (iter == Obj)
		{
			temp->second.erase(iter);
			break;
		}
	}
}

void CObjList::Delete(CObj * Obj)
{
	if (Obj == nullptr)
		return;

	for (auto iter : Active)
	{
		if (iter == Obj)
		{
			Active.erase(iter);
			break;
		}
	}
}

void CObjList::Update()
{
	for (auto obj : Active)
		obj->Update();

	for (auto obj : LayerList[Layer_Del])
		OBJ.Delete(obj);

	LayerList[Layer_Del].clear();
}

void CObjList::Render()
{
	for (int i = 0; i < Layer_Del; ++i)
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