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

BOOL CApp::Initialize()
{
	FrameTime = 0;

	// TODO : Initialize Game
	/* BackGround */
	BITMAP.LoadBackground("BG.bmp",
	{
		{ 0, 0, WINSIZEX, WINSIZEY }
	});

	/* UI */
	BITMAP.Load("Bar", "bar.bmp",
	{
		{ 0, 0, 96, 16 }
	});

	/* Player */
	BITMAP.Load("PlayerDrop", "Sheet.bmp",
	{
		{ 1, 259, 57, 326 },
		{ 59, 259, 113, 326 },
		{ 1, 259, 57, 326 },
		{ 115, 259, 169, 326 }
	});
	BITMAP.LoadAnimation("PlayerLDrop", "PlayerDrop", 0, 3);

	BITMAP.Load("PlayerLeft", "Sheet.bmp",
	{
		{ 75, 1, 110, 40 },
		{ 1, 1, 36, 40 },
		{ 149, 1, 184, 40 },
		{ 223, 42, 258, 81 },
		{ 186, 42, 221, 81 },
		{ 260, 42, 295, 81 }
	});
	BITMAP.LoadAnimation("PlayerLIdle1", "PlayerLeft", 3, 3);
	BITMAP.LoadAnimation("PlayerLIdle2", "PlayerLeft", 4, 4);
	BITMAP.LoadAnimation("PlayerLIdle3", "PlayerLeft", 5, 5);
	BITMAP.LoadAnimation("PlayerLMove", "PlayerLeft", 0, 2);

	BITMAP.Load("PlayerRight", "SheetReverse.bmp", 
	{
		{ 1809, 1, 1844, 40 },
		{ 1883, 1, 1918, 40 },
		{ 1735, 1, 1770, 40 },
		{ 1661, 42, 1696, 81 },
		{ 1698, 42, 1733, 81 },
		{ 1624, 42, 1659, 81 }
	});
	BITMAP.LoadAnimation("PlayerRIdle1", "PlayerRight", 3, 3);
	BITMAP.LoadAnimation("PlayerRIdle2", "PlayerRight", 4, 4);
	BITMAP.LoadAnimation("PlayerRIdle3", "PlayerRight", 5, 5);
	BITMAP.LoadAnimation("PlayerRMove", "PlayerRight", 0, 2);

	//BITMAP.Load("PlayerJump", "Sheet.bmp", 
	//{
	//	{ 186, 1, 221, 40 },
	//	{ 186, 1, 221, 40 },
	//	{ 1152, 1, 1187, 40 },
	//	{ 1152, 1, 1187, 40 }
	//});
	//BITMAP.LoadAnimation("PlayerLJump", "PlayerJump", 0, 3);

	/* Bomb */
	BITMAP.Load("Bomb", "Bomb.bmp",
	{
		{ 0, 0, 16, 16 }
	});

	/* Explosion */
	BITMAP.Load("Explosion", "Explo.bmp",
	{
		{ 0, 1, 36, 38 },
		{ 37, 1, 72, 38 },
		{ 73 ,1, 108, 38 },
		{ 109, 1, 144, 38 },
		{ 145 ,1, 180, 38 },
		{ 181, 1, 216, 38 },
		{ 0, 39, 36, 75 },
		{ 37, 39, 72, 75 },
		{ 73 ,39, 108, 75 },
		{ 109, 39, 144, 75 },
		{ 145 ,39, 180, 75 },
		{ 181, 39, 216, 75 },
		{ 0, 76, 36, 112 },
		{ 37, 76, 72, 112 }
	});
	BITMAP.LoadAnimation("Explosion", "Explosion", 0, 13);

	/* Map Test */
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

	/* MAKE TEMP MAP */
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
