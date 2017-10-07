#pragma once

#include "Manager.h"

class CBitmapManager : public CManager<CBitmapManager>
{
private :
	class CBitmapLoader
	{
	private :
		HBITMAP Bitmap;
		HBITMAP Before;
		vector<RECT> ClipSize;
	public :
		HDC DC;
		RECT GetClip(int index)
		{
			if (ClipSize.size() > index)
				return ClipSize[index];
			RECT rc = { 0, 0, 0, 0 };
			return rc;
		}
		CBitmapLoader * Load(string Name, initializer_list<RECT> * PTR)
		{
			if (PTR != nullptr)
			{
				if (PTR->size() > 0)
				{
					ClipSize.resize(PTR->size());
					for (int i = 0; i < PTR->size(); ++i)
						ClipSize[i] = (*PTR).begin()[i];
				}
			}
			Name = "./Resource/Texture/" + Name;
			HDC dc = ::GetDC(hWnd);
			DC = CreateCompatibleDC(dc);
			ReleaseDC(hWnd, dc);
			Bitmap = (HBITMAP)LoadImageA(nullptr, Name.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			Before = (HBITMAP)SelectObject(DC, Bitmap);
			return this;
		}
		~CBitmapLoader()
		{
			SelectObject(DC, Before);
			DeleteObject(Bitmap);
			DeleteDC(DC);
		}
	};
	class AnimClip
	{
	public:
		string Bitmap;
		int Begin;
		int End;
		AnimClip(string _bitmap, int _begin = 0, int _end = 0)
			: Begin(_begin), End(_end), Bitmap(_bitmap)
		{}
	};
	map<string, CBitmapLoader*> Image;
	map<string, AnimClip> Anim;
	CBitmapLoader BackBuffer;
	HDC Screen;
	INT ScrollX = 0;
	INT ScrollY = 0;
public :
	CBitmapManager();
	~CBitmapManager();
public :
	POINT GetScroll() const
	{
		return { ScrollX, ScrollY };
	}
	HDC GetDC(string Name)
	{
		auto iter = Image.find(Name);
		return iter->second->DC;
	}
	RECT GetClip(string Name, int Index)
	{
		auto iter = Image.find(Name);
		return iter->second->GetClip(Index);
	}
	void SetScroll(int _X, int _Y)
	{
		ScrollX = MathF::Clamp(_X, 0, WINSIZEX);
		ScrollY = MathF::Clamp(_Y, 0, WINSIZEY - 900);
	}
	int AnimationChange(string Name, int Index)
	{
		auto iter = Anim.find(Name);
		if (iter == Anim.end())
			return Index;
		if (iter->second.Begin <= Index && Index <= iter->second.End)
			return Index;
		return iter->second.Begin;
	}
	void Clear()
	{
		Rectangle(BackBuffer.DC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);
		BltBackGround();
	}
	void Flip()
	{
		::BitBlt(Screen, 0, 0, WINSIZEX, WINSIZEY, BackBuffer.DC, 0, 0, SRCCOPY);
	}
	void LoadAnimation(string Name, const char * Bitmap, int Begin, int End)
	{
		auto iter = Anim.find(Name);
		if (iter != Anim.end())
			return;
		Anim.insert(make_pair(Name, AnimClip(Bitmap, Begin, End)));
	}
	int AnimationUpdate(string Name, int Clip)
	{
		auto iter = Anim.find(Name);
		if (iter == Anim.end())
			return -1;
		if (iter->second.End >= Clip + 1)
			return Clip + 1;
		return iter->second.Begin;
	}
public :
	void Load(string Name, string Path, initializer_list<RECT> Clip);
	void AnimationBitBlt(string Name, int Clip, int X, int Y);
	void AnimationTransparentBlt(string Name, int Clip, int X, int Y, UINT Color = RGB(0, 0, 0));
	void BitBlt(string Name, int Clip, int X, int Y);
	void TransparentBlt(string Name, int Clip, int X, int Y, UINT Color = RGB(0, 0, 0));
	void TransparentUIBlt(string Name, int Clip, int X, int Y, UINT Color);
	void LoadBackground(string Path, initializer_list<RECT> Clip);
	void BltBackGround();
	void DrawGage(int startX, int startY, int endX, int endY, COLORREF color);
	void DrawAngle(int posx, int posy, int angle);
	void DrawAngleReverse(int posx, int posy, int angle);
};

