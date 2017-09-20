#pragma once

#include "Include.h"

class CApp
{
private :
	double FrameTime;
public :
	CApp();
	~CApp();
public :
	BOOL Initialize();
	BOOL Update();
	void Render();
};

