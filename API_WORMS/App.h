#pragma once

#include "Include.h"

class CApp
{
protected:
	double FrameTime;
public :
	CApp();
	~CApp();
public :
	virtual BOOL Initialize() = 0;
	virtual BOOL Update() = 0;
	virtual void Render() = 0;
};

