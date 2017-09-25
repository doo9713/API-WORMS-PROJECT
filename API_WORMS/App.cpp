#include "App.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"
#include "Tile.h"
#include "Player.h"
#include "Ground.h"

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

BOOL CApp::Initialize()
{
	FrameTime = 0;

	// TODO : Initialize Game
	BITMAP.LoadBackground("BG.bmp", 
	{
		{ 0, 0, WINSIZEX, WINSIZEY }
	});

	BITMAP.Load("PlayerDrop", "Sheet.bmp",
	{
		{ 1, 259, 57, 326 },
		{ 59, 259, 113, 326 },
		{ 1, 259, 57, 326 },
		{ 115, 259, 169, 326 }
	});
	BITMAP.LoadAnimation("PlayerRDrop", "PlayerDrop", 0, 3);

	BITMAP.Load("PlayerLeft", "Sheet.bmp",
	{
		{ 1, 1, 36, 40 },
		{ 38, 1, 73, 40 },
		{ 112, 1, 147, 40 },
		{ 75, 1, 110, 40 },
		{ 149, 1, 184, 40 },
	
	});
	BITMAP.LoadAnimation("PlayerLIdle", "PlayerLeft", 0, 0);
	BITMAP.LoadAnimation("PlayerLMove", "PlayerLeft", 3, 4);

	BITMAP.Load("PlayerRight", "SheetReverse.bmp", 
	{
		{ 1883, 1, 1918, 40 },
		{ 1846, 1, 1881, 40 },
		{ 1772, 1, 1807, 40 },
		{ 1809, 1, 1844, 40 },
		{ 1735, 1, 1770, 40 }
	});
	BITMAP.LoadAnimation("PlayerRIdle", "PlayerRight", 0, 0);
	BITMAP.LoadAnimation("PlayerRMove", "PlayerRight", 3, 4);

	BITMAP.Load("PlayerJump", "Sheet.bmp", 
	{
		{ 186, 1, 221, 40 },
		{ 186, 1, 221, 40 },
		{ 1152, 1, 1187, 40 },
		{ 1152, 1, 1187, 40 }
	});
	BITMAP.LoadAnimation("PlayerLJump", "PlayerJump", 0, 3);

	BITMAP.Load("TopLeft", "MapTile/1.bmp", 
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("TopCenter", "MapTile/2.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("TopRight", "MapTile/3.bmp",
	{
		{ 0, 0, 64, 64 }
	});

	OBJ.Insert(new CPlayer("Player", Tag_Player, Layer_Object, MathF::VECTOR(100, 100)));

	OBJ.Insert(new CGround("TopLeft", Tag_Ground, Layer_Object, MathF::VECTOR(64, 600)));
	for(int i = 0; i<5; ++i)
		OBJ.Insert(new CGround("TopCenter", Tag_Ground, Layer_Object, MathF::VECTOR(128 + (64 * i), 600)));
	OBJ.Insert(new CGround("TopRight", Tag_Ground, Layer_Object, MathF::VECTOR(64 * 7, 600)));

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
		BITMAP.Clear();
		OBJ.Render();
		BITMAP.Flip();
	}
}
