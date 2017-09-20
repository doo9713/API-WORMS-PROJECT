#include "App.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"

CApp::CApp()
{
}

CApp::~CApp()
{
}

BOOL CApp::Initialize()
{
	FrameTime = 0;

	// TODO : Initialize Game

	return true;
}

BOOL CApp::Update()
{
	TIME.Set();
	KEY.Set();
	OBJ.Update();
	return true;
}

void CApp::Render()
{
	FrameTime += TIME.RealTime();
	if (FrameTime >= FRAMETIME)
	{
		FrameTime -= FRAMETIME;
		OBJ.Render();
	}
}
