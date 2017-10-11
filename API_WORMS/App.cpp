#include "App.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"
#include "Tile.h"
#include "Player.h"
#include "Ground.h"
#include "Bar.h"

CApp::CApp()
{
}

CApp::~CApp()
{
	OBJ.Destroy();
	TIME.Destroy();
	KEY.Destroy();
	BITMAP.Destroy();
	TILE.Destroy();
}
