#include "Explosion.h"
#include "Player.h"

CExplosion::CExplosion(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos), index(0)
{
	gSndController->Play("Explo");
}

CExplosion::~CExplosion()
{
}

bool CExplosion::active(CObj& My, CObj& Other)
{
	return false;
}

void CExplosion::reactive(CObj& My, CObj& Other)
{

}

bool CExplosion::Update()
{
	if (index == 13)
	{
		CPlayer::TurnChange();
		OBJ.Remove(this);
		return false;
	}

	BITMAP.SetScroll(Pos.x - 800, Pos.y - 650);

	ClipTime += TIME.Delta();
	if (ClipTime >= 0.04)
	{
		ClipTime -= 0.04;
		index = BITMAP.AnimationUpdate("Explosion", index);
	}
	return true;
}

void CExplosion::Render()
{
	BITMAP.AnimationTransparentBlt("Explosion", index, Pos.x, Pos.y, RGB(255, 255, 255));
}