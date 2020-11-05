#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "StartMovie.h"
namespace game_framework {
	Movie::Movie()
	{
		delaycount = 30;
	}
	void Movie::LoadBitmap()
	{
		////////////////////////////////////讀取圖片/////////////////////////////////////
		iceman.AddBitmap(ICEMAN, RGB(255, 255, 255));
		iceman.AddBitmap(START1, RGB(0, 0, 0));
		iceman.AddBitmap(START2, RGB(0, 0, 0));
		iceman.AddBitmap(START3, RGB(0, 0, 0));
		fireman.AddBitmap(FIRE, RGB(255, 255, 255));
		fireman.AddBitmap(START1, RGB(0, 0, 0));
		fireman.AddBitmap(START2, RGB(0, 0, 0));
		fireman.AddBitmap(START3, RGB(0, 0, 0));
	}
	void Movie::SetIceXY(int _x, int _y)
	{
		iceman.SetTopLeft(_x, _y);
	}
	void Movie::SetFireXY(int _x, int _y)
	{
		fireman.SetTopLeft(_x, _y);
	}
	void Movie::Restart()
	{
		iceman.Reset();
		fireman.Reset();
		delaycount = 30;//開始總時間
	}
	void Movie::OnMove()
	{
		////////////////////////////////////圖片運行/////////////////////////////////////
		if (!iceman.IsFinalBitmap() && !fireman.IsFinalBitmap())
		{
			iceman.OnMove();
			fireman.OnMove();
		}
	}
	void Movie::OnShow()
	{
		iceman.OnShow();
		fireman.OnShow();
	}
	bool Movie::Getend()
	{
		if (iceman.IsFinalBitmap() && fireman.IsFinalBitmap() && delaycount--<=0) return true;//開頭畫面結束
		return false;
	}
}