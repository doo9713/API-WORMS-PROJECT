#include "TimeUI.h"
#include "ObjList.h"
#include "BitmapManager.h"
#include "Player.h"

double CTimeUI::time = 30.0;
CTimeUI::CTimeUI(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos), isStart(false)
{
}

CTimeUI::~CTimeUI()
{
}

bool CTimeUI::active(CObj& My, CObj& Other)
{
	return false;
}

void CTimeUI::reactive(CObj& My, CObj& Other)
{

}

void CTimeUI::Update()
{
	if (!isStart && OBJ.CheckAllGround())
		isStart = true;

	if (time < 1)
	{
		CPlayer::TurnChange();
		isStart = false;
	}

	if (isStart)
	{
		time = MathF::ClampCycle(time - TIME.RealTime(), 0.0, 30.0);
		first = to_string((int)(time / 10));
		second = to_string((int)time % 10);
	}
}

void CTimeUI::Render()
{
	if (isStart)
	{
		BITMAP.TransparentUIBlt(first, 0, 0, 0, RGB(255, 255, 255));
		BITMAP.TransparentUIBlt(second, 0, 15, 0, RGB(255, 255, 255));
	}
}