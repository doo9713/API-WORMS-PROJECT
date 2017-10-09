#include "Tile.h"
#include "BitmapManager.h"
#include "ObjList.h"
#include "Ground.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

bool CTile::TileInit()
{
	BITMAP.Load("GroundLeft", "MapTile/13.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("GroundMid", "MapTile/14.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("GroundRight", "MapTile/15.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("WaterUp", "MapTile/17.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	BITMAP.Load("WaterDown", "MapTile/18.bmp",
	{
		{ 0, 0, 64, 64 }
	});
	return true;
}

void CTile::TileLoad(const char* Path)
{
	TileName = Path;
	RECT rc = BITMAP.GetClip(Path, 0);
	HDC dc = BITMAP.GetDC(Path);
	Tile.resize(rc.right * rc.bottom);
	for (int i = 0; i < rc.right; ++i)
	{
		for (int j = 0; j < rc.bottom; ++j)
		{
			if (GetPixel(dc, i, j) != RGB(0, 0, 0))
			{
				Tile[i + j * rc.right].X = i * 64;
				Tile[i + j * rc.right].Y = j * 64;
				Tile[i + j * rc.right].Number = -1;

				if(GetPixel(dc, i, j) == RGB(0, 0, 200))
					Tile[i + j * rc.right].Number =	17;
				if(GetPixel(dc, i, j) == RGB(0, 0, 255))
					Tile[i + j * rc.right].Number = 18;

				/* Make Ground Object */
				if (GetPixel(dc, i, j) == RGB(0, 100, 0))
					OBJ.Insert(new CGround("GroundLeft", Tag_Ground, Layer_Object, MathF::VECTOR(Tile[i + j * rc.right].X, Tile[i + j * rc.right].Y)));
				if (GetPixel(dc, i, j) == RGB(0, 150, 0))
					OBJ.Insert(new CGround("GroundMid", Tag_Ground, Layer_Object, MathF::VECTOR(Tile[i + j * rc.right].X, Tile[i + j * rc.right].Y)));
				if (GetPixel(dc, i, j) == RGB(0, 200, 0))
					OBJ.Insert(new CGround("GroundRight", Tag_Ground, Layer_Object, MathF::VECTOR(Tile[i + j * rc.right].X, Tile[i + j * rc.right].Y)));
			}
			else
				Tile[i + j * rc.right].Number = -1;
		}
	}
}

void CTile::MakeMap()
{
	POINT scroll = BITMAP.GetScroll();
	RECT rc = BITMAP.GetClip(TileName, 0);
	for (int i = 0; i < WINSIZEX / 64 + 3; ++i)
	{
		for (int j = 0; j < WINSIZEY / 64 + 3; ++j)
		{
			int index = (scroll.x / 64 - 1 + i) +
				(scroll.y / 64 - 1 + j) * rc.right;
			if (index < 0 || index >= Tile.size())
				continue;
			switch (Tile[index].Number)
			{
			case 17 :
				BITMAP.TransparentBlt("WaterUp", 0, Tile[index].X, Tile[index].Y, RGB(255, 255, 255));
				break;
			case 18 :
				BITMAP.BitBlt("WaterDown", 0, Tile[index].X, Tile[index].Y);
				break;
			}
		}
	}
}