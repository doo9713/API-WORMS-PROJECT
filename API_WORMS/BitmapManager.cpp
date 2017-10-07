#include "BitmapManager.h"

CBitmapManager::CBitmapManager()
{
	BackBuffer.Load("BackBuffer.bmp", nullptr);
	Screen = ::GetDC(hWnd);
}

CBitmapManager::~CBitmapManager()
{
	ReleaseDC(hWnd, Screen);
	for (auto bitmap : Image)
		delete bitmap.second;
}

void CBitmapManager::Load(string Name, string Path, initializer_list<RECT> Clip)
{
	auto iter = Image.find(Name);
	if (iter != Image.end())
		return;
	Image.insert(make_pair(Name,
		(new CBitmapLoader)->Load(Path, &Clip)
	));
}

void CBitmapManager::AnimationTransparentBlt(string Name, int Clip, int X, int Y, UINT Color)
{
	auto iter = Anim.find(Name);
	if (iter == Anim.end())
		return;
	TransparentBlt(iter->second.Bitmap, Clip, X, Y, Color);
}

void CBitmapManager::AnimationBitBlt(string Name, int Clip, int X, int Y)
{
	auto iter = Anim.find(Name);
	if (iter == Anim.end())
		return;
	BitBlt(iter->second.Bitmap, Clip, X, Y);
}

void CBitmapManager::BitBlt(string Name, int Clip, int X, int Y)
{
	auto iter = Image.find(Name);
	if (iter == Image.end())
		return;
	RECT rc = iter->second->GetClip(Clip);
	::BitBlt(BackBuffer.DC,
		X - ScrollX, Y - ScrollY,
		rc.right - rc.left, rc.bottom - rc.top,
		iter->second->DC,
		rc.left, rc.top,
		SRCCOPY);
}

void CBitmapManager::TransparentBlt(string Name, int Clip, int X, int Y, UINT Color)
{

	auto iter = Image.find(Name);
	if (iter == Image.end())
		return;
	RECT rc = iter->second->GetClip(Clip);

	::TransparentBlt(BackBuffer.DC,
		X - ScrollX, Y - ScrollY,
		rc.right - rc.left, rc.bottom - rc.top,
		iter->second->DC,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		Color);
}

void CBitmapManager::TransparentUIBlt(string Name, int Clip, int X, int Y, UINT Color)
{

	auto iter = Image.find(Name);
	if (iter == Image.end())
		return;
	RECT rc = iter->second->GetClip(Clip);

	::TransparentBlt(BackBuffer.DC,
		X, Y,
		rc.right - rc.left, rc.bottom - rc.top,
		iter->second->DC,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		Color);
}

void CBitmapManager::LoadBackground(string Path, initializer_list<RECT> Clip)
{
	string Name = "BG";
	auto iter = Image.find(Name);
	if (iter != Image.end())
		return;
	Image.insert(make_pair(Name,
		(new CBitmapLoader)->Load(Path, &Clip)
	));
}

void CBitmapManager::BltBackGround()
{
	auto iter = Image.find("BG");
	if (iter == Image.end())
		return;
	::BitBlt(BackBuffer.DC, 0, 0, WINSIZEX, WINSIZEY, iter->second->DC, 0, 0, SRCCOPY);
}

void CBitmapManager::DrawGage(int startX, int startY, int endX, int endY, COLORREF color)
{
	for (int i = startX - ScrollX; i < endX - ScrollX; ++i)
		for (int j = startY - ScrollY; j < endY - ScrollY; ++j)
			SetPixel(BackBuffer.DC, i, j, color);
}

void CBitmapManager::DrawAngle(int posx, int posy, int angle)
{
	for (int i = posx - ScrollX; i < posx - ScrollX + ANGLESIZE; ++i)
		SetPixel(BackBuffer.DC, i, posy - ScrollY, RGB(255, 100, 0));
	for (int i = posy - ScrollY; i > posy - ScrollY - ANGLESIZE; --i)
		SetPixel(BackBuffer.DC, posx - ScrollX, i, RGB(255, 100, 0));
	(BackBuffer.DC, RGB(255, 100, 0));

	double op = (ANGLESIZE * ANGLESIZE) / 90 * angle;
	MathF::VECTOR dst = { posx - ScrollX + sqrt(ANGLESIZE * ANGLESIZE - op), posy - ScrollY - sqrt(op) };
	for (int i = 0; i < ANGLESIZE; ++i)
	{
		double x = posx - ScrollX + (dst.x - (posx - ScrollX)) / ANGLESIZE * i;
		double y = posy - ScrollY - ((posy - ScrollY) - dst.y) / ANGLESIZE * i;
		SetPixel(BackBuffer.DC, x, y, RGB(255, 100, 0));
	}
}

void CBitmapManager::DrawAngleReverse(int posx, int posy, int angle)
{
	for (int i = posx - ScrollX; i > posx - ScrollX - ANGLESIZE; --i)
		SetPixel(BackBuffer.DC, i, posy - ScrollY, RGB(255, 100, 0));
	for (int i = posy - ScrollY; i > posy - ScrollY - ANGLESIZE; --i)
		SetPixel(BackBuffer.DC, posx - ScrollX, i, RGB(255, 100, 0));

	double op = (ANGLESIZE * ANGLESIZE) / 90 * angle;
	MathF::VECTOR dst = { posx - ScrollX - sqrt(ANGLESIZE * ANGLESIZE - op), posy -ScrollY - sqrt(op) };
	for (int i = 0; i < ANGLESIZE; ++i)
	{
		double x = posx - ScrollX - ((posx - ScrollX) - dst.x) / ANGLESIZE * i;
		double y = posy - ScrollY - ((posy - ScrollY) - dst.y) / ANGLESIZE * i;
		SetPixel(BackBuffer.DC, x, y, RGB(255, 100, 0));
	}
}