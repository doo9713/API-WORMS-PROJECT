#include "Bomb.h"
#include "Explosion.h"
#include "Player.h"
#include "Ground.h"

CBomb::CBomb(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos, double _power, double _angle, int _dir)
	: CObj(_name, _tag, _layer, _pos), isOver(false)
{
	speed = 0;
	startPos = { _pos.x, _pos.y };
	dstPos = { _pos.x + _power * 20 * abs(cos(_angle * 3.1416 / 180)) * _dir, WINSIZEY };
	midPos = { _pos.x + abs(dstPos.x - _pos.x) / 2 * _dir, _pos.y - _power * 20 * abs(sin(_angle * 3.1416 / 180)) };
}

CBomb::~CBomb()
{
}

bool CBomb::active(CObj& My, CObj& Other)
{
	MathF::VECTOR center = Pos + 18;
	if (Other.Tag == Tag_Ground)
		return ((CGround&)Other).IsGroundCheck(center, 120);
	if (Other.Tag == Tag_Player)
		if (MathF::Distance(((CPlayer&)Other).GetCenter(), center) < sqrt(18 * 18 * 2) / 2)
			return true;
	return false;
}

void CBomb::reactive(CObj& My, CObj& Other)
{
	if(Other.Tag == Tag_Player)
		((CPlayer&)Other).GetDamage(Func::Random(10, 30));
	if(!isOver)
		OBJ.Insert(new CExplosion("Explo", Tag_Particle, Layer_Particle, Pos));
	isOver = true;
}

void CBomb::Update()
{
	if (isOver)
	{
		OBJ.Remove(this);
		return;
	}

	if (Pos.y >= WINSIZEY)
	{
		CPlayer::TurnChange();
		OBJ.Remove(this);
		return;
	}

	BITMAP.SetScroll(Pos.x - 800, Pos.y - 650);

	OBJ.ActiveObj(this, Tag_Player);
	OBJ.ActiveObj(this, Tag_Ground);

	speed += TIME.Delta() / 2.5;
	Pos = MathF::Slerp(speed, { startPos, midPos, dstPos });
}

void CBomb::Render()
{
	BITMAP.TransparentBlt("Bomb", 0, Pos.x, Pos.y, RGB(255, 255, 255));
}
