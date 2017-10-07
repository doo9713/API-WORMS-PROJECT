#pragma once

#include "App.h"

class CGamePlay : public CApp
{
private:
	double FrameTime;
public:
	CGamePlay();
	~CGamePlay();
public:
	BOOL Initialize();
	BOOL Update();
	void Render();
};

