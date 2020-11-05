#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "door.h"
#include "trap.h"
namespace game_framework {
	trap::trap()
	{
	}
	int trap::GetX1()
	{
		return x;
	}
	int trap::GetY1()
	{
		return y;
	}
	void trap::LoadBitmap()
	{
		return;
	}
	void trap::OnMove()
	{
		animation.OnMove();
	}
	void trap::OnShow(int _x, int _y)
	{
		x = _x; y = _y;
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
};