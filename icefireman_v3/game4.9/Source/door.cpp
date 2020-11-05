#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "door.h"
namespace game_framework {
	door::door()
	{
	}
	int door::GetX1()
	{
		return x;
	}
	int door::GetY1()
	{
		return y;
	}
	CAnimation* door::GetDoor()
	{
		return &animation;
	}
	void door::LoadBitmap()
	{
		return ;
	}
	void door::OnShow(int _x,int _y)
	{
		x = _x; y = _y;
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
	bool door::Clearance(man player,int gemnum)
	{
		return false;
	}
}