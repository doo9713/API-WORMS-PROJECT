#include "Player.h"
#include "Ground.h"

CPlayer::CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos), index(0), isGround(false)
{
	Dir = "R";
	State = "Idle";
}

CPlayer::~CPlayer()
{
}

bool CPlayer::active(CObj& My, CObj& Other)
{
	MathF::VECTOR checkPos = My.getPos();
	checkPos.x += 17;
	checkPos.y += 19;
	return ((CGround&)Other).IsGroundCheck(checkPos);
}

void CPlayer::reactive(CObj& My, CObj& Other)
{
	isGround = true;
}

void CPlayer::Update()
{
	// TODO : Object Update
	isGround = false;
	OBJ.ActiveObj(this, Tag_Ground);
	if(!isGround)
		Pos.y += 150 * TIME.Delta();

	State = "Idle";
	if (KEY.Down(VK_LEFT))
	{
		State = "Move";
		Dir = "L";
		Pos.x -= 70 * TIME.Delta();
	}
	else if (KEY.Down(VK_RIGHT))
	{
		State = "Move";
		Dir = "R";
		Pos.x += 70 * TIME.Delta();
	}

	int change = BITMAP.AnimationChange(name + Dir + State, index);
	if (change != index)
	{
		ClipTime = 0;
		index = change;
	}

	ClipTime += TIME.Delta();
	if (ClipTime >= 0.14)
	{
		ClipTime -= 0.14;
		index = BITMAP.AnimationUpdate(name + Dir + State, index);
	}
}

void CPlayer::Render()
{
	// TODO : Object Render
	BITMAP.AnimationTransparentBlt(name + Dir + State, index, Pos.x, Pos.y);
}