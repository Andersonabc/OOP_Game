#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "FallWall.h"

namespace game_framework
{
	FallWall::FallWall()
	{
	}
	void FallWall::LoadBitmap()
	{
		image.LoadBitmap(elevator, RGB(255, 255, 255));
	}
	int FallWall::GetX()
	{
		return x;
	}
	int FallWall::GetY()
	{
		return y;
	}
	int FallWall::Getox()
	{
		return ox;
	}
	int FallWall::Getoy()
	{
		return oy;
	}

	int FallWall::GetFall()
	{
		return Fall;
	}

	bool FallWall::Onstand(man player)
	{
		////////////////////////////////////////////////判斷角色站在下落地板上//////////////////////////////////////
		if (x < (player.GetX1() + player.GetX2()) / 2 && (player.GetX1() + player.GetX2()) / 2 < x + 60 && (y + 44 > player.GetY2() && y - 5 < player.GetY2())) return true;
		else return false;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	void FallWall::SetFall(int flag)
	{
		Fall = flag;
	}

	void FallWall::SetFall(man player)
	{
		if (x < (player.GetX1() + player.GetX2()) / 2 && (player.GetX1() + player.GetX2()) / 2 < x + 60 && (y+40 > player.GetY2() && y-3 < player.GetY2()))  Fall+=1;
	}
	void FallWall::Setoxy(int x, int y)
	{
		ox = x;
		oy = y;
	}
	void FallWall::SetTopLeft(int _x, int _y)
	{
		x = _x; y = _y;
	}
	void FallWall::ShowBitmap()
	{
		image.SetTopLeft(x, y);
		image.ShowBitmap();
	}
	void FallWall::Down()
	{
		y+=4;
	}
	void FallWall::Up()
	{
		y--;
	}
	void FallWall::Up(int v)
	{
		y-=v;
	}
}