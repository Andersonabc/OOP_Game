#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SasukeFireball.h"
namespace game_framework {
	SasukeFireball::SasukeFireball(int _x, int _y, int _direction)
	{
		Init(_x, _y, _direction);
		CAudio::Instance()->Play(25);
	}
	void SasukeFireball::Init(int _x, int _y, int _direction)
	{
		SetXY(_x, _y);
		direction = _direction;
		AddPic();
	}
	int SasukeFireball::GetX1()
	{
		return x;
	}
	int SasukeFireball::GetY1()
	{
		return y;
	}
	int SasukeFireball::GetX2()
	{
		return x + Fireballpic.Width() * 2;
	}
	int SasukeFireball::GetY2()
	{
		return y+ Fireballpic.Height()*2;
	}
	int SasukeFireball::Getdirection()
	{
		return direction;
	}
	void SasukeFireball::AddPic()
	{
		//////////////////////////////////////設定火球各方向圖片////////////////////////////////////////////////////
		if (direction == 0)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL1, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL2, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL3, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL4, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL5, RGB(73, 176, 255));
		}
		if (direction == 1)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL6, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL7, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL8, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL9, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL10, RGB(73, 176, 255));
		}
		if (direction == 2)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL11, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL12, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL13, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL14, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL15, RGB(73, 176, 255));
		}
		if (direction == 3)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL16, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL17, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL18, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL19, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL20, RGB(73, 176, 255));
		}
		if (direction == 4)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL21, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL22, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL23, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL24, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL25, RGB(73, 176, 255));
		}
		if (direction == 5)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL26, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL27, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL28, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL29, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL30, RGB(73, 176, 255));
		}
		if (direction == 6)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL31, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL32, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL33, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL34, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL35, RGB(73, 176, 255));
		}
		if (direction == 7)
		{
			Fireballpic.AddBitmap(SASUKEFIREBALL36, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL37, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL38, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL39, RGB(73, 176, 255));
			Fireballpic.AddBitmap(SASUKEFIREBALL40, RGB(73, 176, 255));
		}
		//////////////////////////////////////////////////////////////////////////////////////
		Fireballpic.SetDelayCount(3);
		Fireballpic.Reset();
	}
	void SasukeFireball::OnShow()
	{
		Fireballpic.SetTopLeft(x, y);
		Fireballpic.OnShow(2);
	}
	void SasukeFireball::Move()
	{
		/////////////////////////////////////////////往各方向移動/////////////////////////////////
		if (direction == 0)	x += 15;					//往右
		else if (direction == 1) { x += 15; y += 15;}	//往右下
		else if (direction == 2) { y += 15; }			//下
		else if (direction == 3) { x -= 15; y += 15;}	//往左下
		else if (direction==4) x -= 15;					//往左
		else if (direction==5) { x -= 15; y -= 15; }	//往左上
		else if (direction==6) {y -= 15; }				//往上
		else if (direction==7) { x += 15; y -= 15; }	//往右下
		Fireballpic.OnMove();
	}
	void SasukeFireball::SetXY(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}