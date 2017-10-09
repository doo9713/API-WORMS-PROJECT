#pragma once

/* Manager */
#define SINGLE(type) (**type::Inst())
#define OBJ SINGLE(CObjList)
#define TIME SINGLE(CTimeManager)
#define KEY SINGLE(CKeyManager)
#define BITMAP SINGLE(CBitmapManager)
#define TILE SINGLE(CTile)

/* Scene */
#define MAINSCENE 0
#define GAMELOAD 1
#define GAMESCENE 2
#define EXITGAME 3

/* ETC */
#define FRAMETIME 0.016667
#define WINSIZEX 1600
#define WINSIZEY 900

/* Player */
#define PLAYERHEIGHT 39
#define ANGLESIZE 40

/* Ground */
#define TILESIZEXY 64