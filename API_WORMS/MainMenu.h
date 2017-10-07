#pragma once
#include "App.h"
class CMainMenu : public CApp
{
public:
	CMainMenu();
	~CMainMenu();
public:
	BOOL Initialize();
	BOOL Update();
	void Render();
};

