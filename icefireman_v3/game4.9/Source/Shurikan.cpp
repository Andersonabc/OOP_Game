#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Shurikan.h"

namespace game_framework {
	Shurikan::Shurikan(int _x, int _y, int _direction)
	{
		Init(_x, _y, _direction);
	}
	void Shurikan::Init(int _x, int _y, int _direction)
	{
		x = _x;
		y = _y;
		direction = _direction;
		AddPic();
	}
	int Shurikan::GetX1()
	{
		return x;
	}
	int Shurikan::GetY1()
	{
		return y;
	}
	int Shurikan::GetX2()
	{
		return x+ Shurikanpic.Width()*2;
	}
	int Shurikan::GetY2()
	{
		return y+ Shurikanpic.Height()*2;
	}
	int Shurikan::Getdirection()
	{
		return direction;
	}
	void Shurikan::AddPic()
	{
		Shurikanpic.AddBitmap(SHURIKAN, RGB(73, 176, 255));
		Shurikanpic.AddBitmap(SHURIKAN2, RGB(73, 176, 255));
		Shurikanpic.AddBitmap(SHURIKAN3, RGB(73, 176, 255));
		Shurikanpic.SetDelayCount(3);
		Shurikanpic.Reset();
	}
	void Shurikan::OnShow()
	{
		Shurikanpic.SetTopLeft(x, y);
		Shurikanpic.OnShow(2);
	}
	void Shurikan::Move()
	{
		if (direction == 1)x += 15;
		else x -= 15;
		Shurikanpic.OnMove();
	}
	void Shurikan::SetXY(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}