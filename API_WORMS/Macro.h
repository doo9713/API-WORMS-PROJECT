#pragma once

/* Manager */
#define SINGLE(type) (**type::Inst())
#define OBJ SINGLE(CObjList)
#define TIME SINGLE(CTimeManager)
#define KEY SINGLE(CKeyManager)
#define BITMAP SINGLE(CBitmapManager)
#define TILE SINGLE(CTile)

/* ETC */
#define FRAMETIME 0.016667
#define WINSIZEX 1600
#define WINSIZEY 900

/* Player */
#define HEIGHT 39

/* Ground */
#define SIZEXY 64