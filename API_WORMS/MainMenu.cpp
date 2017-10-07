#include "MainMenu.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"

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