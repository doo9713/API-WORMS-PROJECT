#include "Player.h"

CPlayer::CPlayer(const char * _name, TAG _tag, LAYER _layer, MathF::VECTOR _pos)
	: CObj(_name, _tag, _layer, _pos), index(0)
{
	Dir = "R";
	State = "Idle";
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	// TODO : Object Update
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

	//if (KEY.Push(VK_SPACE))
	//{
	//	State = "Jump";
	//}

	int change = BITMAP.AnimationChange(Name + Dir + State, index);
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