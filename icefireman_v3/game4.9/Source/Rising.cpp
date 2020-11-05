#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Rising.h"
namespace game_framework
{
	Rising::Rising()
	{
		x = 0,y = 0;
	}
	int Rising::getX()
	{
		return x;
	}
	int Rising::getY()
	{
		return y;
	}
	void Rising::SetXY(int _x,int _y)
	{
		x = _x;
		y = _y-5;
	}
	bool Rising::SetRising(man * player)
	{
		//////////////////////////////////////////////////////////////判斷站在噴射器上///////////////////////////////////////////////////////////////////
		if (((player->GetX1() < x + image.Width() && player->GetX1() > x) || (player->GetX2() < x + image.Width() && player->GetX2() > x)) && (player->GetY2() < y&&player->GetY1()>y-160)) return true;
		else return false;
	}
	void Rising::LoadBitmap()
	{
		image.LoadBitmap(pic_rising, RGB(0, 0, 0));
		smoke.AddBitmap(SMOKE, RGB(0, 0, 0));
		smoke.AddBitmap(SMOKE2, RGB(0, 0, 0));
		smoke.AddBitmap(SMOKE3, RGB(0, 0, 0));
	}
	void Rising::OnShow()
	{
		image.SetTopLeft(x, y);
		smoke.SetTopLeft(x, y - 160);
		image.ShowBitmap();
		smoke.OnShow();
		smoke.OnMove();
	}
}