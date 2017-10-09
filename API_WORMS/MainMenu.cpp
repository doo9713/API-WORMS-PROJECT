#include "MainMenu.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"
#include "TitleUI.h"
#include "StartButton.h"
#include "ExitButton.h"

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
	OBJ.Destroy();
	TIME.Destroy();
	KEY.Destroy();
	BITMAP.Destroy();
}

BOOL CMainMenu::Initialize()
{
	FrameTime = 0;

	// TODO : Initialize Game
	/* BackGround */
	BITMAP.LoadBackground("BG.bmp",
	{
		{ 0, 0, WINSIZEX, WINSIZEY }
	});

	/* UI */
	BITMAP.Load("Title1", "title1.bmp",
	{
		{ 0, 0, 730, 290 }
	});
	BITMAP.Load("Title2", "title2.bmp",
	{
		{ 0, 0, 700, 140 }
	});
	BITMAP.Load("btStartIdle", "menu1.bmp",
	{
		{ 65, 60, 385, 160 }
	});
	BITMAP.Load("btStartInto", "menu2.bmp",
	{
		{ 65, 60, 385, 160 }
	});
	BITMAP.Load("btExitIdle", "menu1.bmp",
	{
		{ 100, 200, 355, 295 }
	});
	BITMAP.Load("btExitInto", "menu2.bmp",
	{
		{ 100, 200, 355, 295 }
	});

	OBJ.Insert(new CTitleUI("Title1", Tag_UI, Layer_UI, MathF::VECTOR(400, 110)));
	OBJ.Insert(new CTitleUI("Title2", Tag_UI, Layer_UI, MathF::VECTOR(430, 400)));
	OBJ.Insert(new CStartButton("Start", Tag_UI, Layer_UI, MathF::VECTOR(640, 550), 320, 100));
	OBJ.Insert(new CExitButton("Exit", Tag_UI, Layer_UI, MathF::VECTOR(675, 650), 255, 95));
	return true;
}

BOOL CMainMenu::Update()
{
	TIME.Set();
	KEY.Set();
	OBJ.Update();
	return true;
}

void CMainMenu::Render()
{
	FrameTime += TIME.RealTime();
	if (FrameTime >= FRAMETIME)
	{
		FrameTime -= FRAMETIME;
		BITMAP.Clear();
		OBJ.Render();
		BITMAP.Flip();
	}
}

void CMainMenu::Destroy()
{
	this->~CMainMenu();
}