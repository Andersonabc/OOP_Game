#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include"stone.h"

namespace game_framework 
{
	rockStone::rockStone()
	{
		x = y = x2 = y2 = 0;
	}
	int rockStone::GetX()
	{
		return x;
	}
	int rockStone::GetX2()
	{
		x2 = x + 39;
		return x2;
	}
	int rockStone::GetY()
	{
		return y;
	}
	int rockStone::GetY2()
	{
		y2 = y + 39;
		return y2;
	}
	void rockStone::SetXY(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	void rockStone::LoadBitmap()
	{
		image.LoadBitmap(Stone, RGB(255, 255, 255));
	}
	void rockStone::Down()
	{
		y += 1;//石頭下墜
	}
	bool rockStone::CheckStone(int px1,int px2,int py1,int py2)
	{
		/////////////////////////////////////若是角色碰種到石頭//////////////////////////
		if ((px1 > GetX() && px1 < GetX2() &&py1 > GetY() && py1 < GetY2())) return false;
		if ((px2 > GetX() && px2 < GetX2() &&py2 > GetY() && py2 < GetY2()))return false;
		if ((px1 > GetX() && px1 < GetX2() &&py2 > GetY() && py2 < GetY2()))return false;
		if ((px2 > GetX() && px2 < GetX2() &&py1 > GetY() && py1 < GetY2()))return false;
		return true;
	}
	void rockStone::ShowBitmap()
	{
		image.SetTopLeft(x, y);
		image.ShowBitmap();
	}
}