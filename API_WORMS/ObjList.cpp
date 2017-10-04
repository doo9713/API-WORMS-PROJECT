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

	for (auto iter : Active) 
	{
		if (iter == Obj)
		{
			Active.erase(iter);
			break;
		}
	}
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
			LayerList[Obj->Layer].erase(iter);
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

void CObjList::Update()
{
	CObj * del = nullptr;
	for (auto obj : Active)
	{
		if (!obj->Update())
		{
			del = obj;
			Remove(obj);
			break;
		}
	}

	if(del != nullptr)
		del->Destroy();
}

void CObjList::Render()
{
	for (int i = 0; i < Layer_End; ++i)
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