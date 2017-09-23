#pragma once

#define SINGLE(type) (**type::Inst())
#define OBJ SINGLE(CObjList)
#define TIME SINGLE(CTimeManager)
#define KEY SINGLE(CKeyManager)
#define BITMAP SINGLE(CBitmapManager)
#define TILE SINGLE(CTile)

#define FRAMETIME 0.016667
#define WINSIZEX 1600
#define WINSIZEY 900