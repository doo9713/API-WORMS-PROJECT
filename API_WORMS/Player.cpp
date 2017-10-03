#include "Player.h"
#include "Ground.h"
#include "Health.h"
#include "FireGage.h"

CPlayer::CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos), index(0), health(100), angle(45), powergage(0), isGround(false)
{
	Dir = "L";
	State = "Drop";
	OBJ.Insert(new CHealth("Bar", Tag_UI, Layer_UI, MathF::VECTOR(_pos.x - 25, _pos.y + 40), this));
	OBJ.Insert(new CFireGage("Bar", Tag_UI, Layer_UI, MathF::VECTOR(_pos.x - 25, _pos.y + 56), this));
}

CPlayer::~CPlayer()
{
}

bool CPlayer::active(CObj& My, CObj& Other)
{
	MathF::VECTOR checkPos = My.getPos();
	// Make Value Center
	if (State == "Drop")
	{
		checkPos.x += 26;
		checkPos.y += 31;
	}
	else 
	{
		checkPos.x += 17;
		checkPos.y += 19;
	}
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
	if (!isGround) 
	{
		if (State != "Drop")
			State = "Idle";
		Pos.y += 150 * TIME.Delta();
	}
	else
	{
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

		if (KEY.Down(VK_UP))
		{
			angle += 100 * TIME.Delta();
			if (angle > 90)
				angle = 90;
		}
		else if (KEY.Down(VK_DOWN))
		{
			angle -= 100 * TIME.Delta();
			if (angle < 1)
				angle = 1;
		}

		if (KEY.Down(VK_SPACE))
		{
			powergage += 100 * TIME.Delta();
			if (powergage > 100)
				powergage = 100;
		}
		else
			powergage = 0;
	}

	int change = BITMAP.AnimationChange(name + Dir + State, index);
	if (change != index)
	{
		ClipTime = 0;
		index = change;
	}

	// Animation Time
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
	if (State != "Drop")
	{
		if (Dir == "R")
			BITMAP.DrawAngle(Pos.x + 36, Pos.y + 18, angle);
		else
			BITMAP.DrawAngleReverse(Pos.x, Pos.y + 18, angle);
	}
}