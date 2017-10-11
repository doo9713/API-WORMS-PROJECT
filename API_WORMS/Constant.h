#pragma once

extern HWND hWnd;
extern GameSound gSndController;
extern INT gSceneController;

enum LAYER
{
	Layer_Default,
	Layer_Object,
	Layer_Player,
	Layer_Particle,
	Layer_UI,
	Layer_Del,
	Layer_End
};

enum TAG
{
	Tag_Default,
	Tag_Ground,
	Tag_Player,
	Tag_Bullet,
	Tag_Particle,
	Tag_UI,
	Tag_End
};
