#include "GamePlay.h"
#include "Obj.h"
#include "ObjList.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"
#include "Tile.h"
#include "Player.h"
#include "Ground.h"
#include "Bar.h"
#include "TimeUI.h"
#include "Cloud.h"

CGamePlay::CGamePlay()
{
}

CGamePlay::~CGamePlay()
{
	OBJ.Destroy();
	TIME.Destroy();
	KEY.Destroy();
	BITMAP.Destroy();
	TILE.Destroy();
}

BOOL CGamePlay::Initialize()
{
	FrameTime = 0;

	// TODO : Initialize Game
	/* Sound Initialize */
	gSndController->LoadSound("PlaySong", "./Resource/Sound/Play.mp3", true);
	gSndController->LoadSound("Fire", "./Resource/Sound/Cannon.mp3");
	gSndController->LoadSound("Explo", "./Resource/Sound/Explosion.mp3");
	gSndController->Stop("MainSong");
	gSndController->Play("PlaySong");

	/* BackGround */
	BITMAP.LoadBackground("BG.bmp",
	{
		{ 0, 0, WINSIZEX, WINSIZEY }
	});

	/* Map */
	BITMAP.Load("Map", "MapTile/Map.bmp",
	{
		{ 0, 0, 30, 15 }
	});
	if (TILE.TileInit())
		TILE.TileLoad("Map");

	/* UI */
	BITMAP.Load("Bar", "bar.bmp",
	{
		{ 0, 0, 96, 16 }
	});
	BITMAP.Load("Arrow", "arrow.bmp",
	{
		{ 0, 0, 15, 20 }
	});
	for (int i = 0; i < 10; ++i)
	{
		string temp = to_string(i);
		BITMAP.Load(temp, "number.bmp",
		{
			{ 50 * i, 0, 50 * (i + 1), 52 }
		});
	}
	BITMAP.Load("GameOver", "gameover.bmp",
	{
		{ 0, 0, 1200, 180 }
	});
	BITMAP.Load("Player1Win", "wintitle.bmp",
	{
		{ 0, 0, 679, 130 }
	});
	BITMAP.Load("Player2Win", "wintitle.bmp",
	{
		{ 0, 131, 679, 260 }
	});
	BITMAP.Load("Player3Win", "wintitle.bmp",
	{
		{ 0, 261, 679, 390 }
	});
	BITMAP.Load("Player4Win", "wintitle.bmp",
	{
		{ 0, 391, 679, 520 }
	});
	BITMAP.Load("btExitIdle", "menu1.bmp",
	{
		{ 100, 200, 355, 295 }
	});
	BITMAP.Load("btExitInto", "menu2.bmp",
	{
		{ 100, 200, 355, 295 }
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

	/* Bomb */
	BITMAP.Load("Bomb", "Bomb.bmp",
	{
		{ 0, 0, 16, 16 }
	});

	/* Cloud */
	BITMAP.Load("Cloud", "Cloud.bmp",
	{
		{ 0, 0, 200, 82 }
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

	OBJ.Insert(new CPlayer("Player1", Tag_Player, Layer_Player, MathF::VECTOR(100, 100)));
	OBJ.Insert(new CPlayer("Player2", Tag_Player, Layer_Player, MathF::VECTOR(1500, 130)));
	OBJ.Insert(new CPlayer("Player3", Tag_Player, Layer_Player, MathF::VECTOR(300, 70)));
	OBJ.Insert(new CPlayer("Player4", Tag_Player, Layer_Player, MathF::VECTOR(900, 160)));

	OBJ.Insert(new CTimeUI("TimeUI", Tag_UI, Layer_UI, MathF::VECTOR(760, 10)));

	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(10, 50), 1));
	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(1400, 100), -1));
	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(450, 170), 1));
	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(1800, 70), -1));
	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(900, 120), 1));
	OBJ.Insert(new CCloud("Cloud", Tag_Particle, Layer_Particle, MathF::VECTOR(400, 90), -1));

	return true;
}

BOOL CGamePlay::Update()
{
	gSndController->Update();
	TIME.Set();
	KEY.Set();
	OBJ.Update();
	return true;
}

void CGamePlay::Render()
{
	FrameTime += TIME.RealTime();
	if (FrameTime >= FRAMETIME)
	{
		FrameTime -= FRAMETIME;
		BITMAP.Clear();
		TILE.MakeMap();
		OBJ.Render();
		BITMAP.Flip();
	}
}
