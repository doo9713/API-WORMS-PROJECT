#include "Tile.h"
#include "BitmapManager.h"

CTile::CTile()
{
}

CTile::~CTile()
{
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
			// 맵 오브젝트 생성
		}
	}
}

void CTile::TileLoad(const char* Path)
{
	TileName = Path;
	RECT rc = BITMAP.GetClip(Path, 0);
	HDC dc = BITMAP.GetDC(Path);
	for (int i = 0; i < rc.right; ++i)
	{
		for (int j = 0; j < rc.bottom; ++j)
		{
			if (GetPixel(dc, i, j) != RGB(0, 0, 0))
			{
				Tile[i + j * rc.right].X = i * 64;
				Tile[i + j * rc.right].Y = j * 64;
				// 픽셀의 색깔값에 따른 타일 지정
			}
		}
	}
}