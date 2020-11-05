#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SkillStart.h"
namespace game_framework {
	skillstart::skillstart()
	{
		Init();
		Start = false;
	}
	void skillstart::Init()
	{
		x = 640;
		y = 100;
		Start = true;
		Stop = true;
	}
	/////////////////////////////////////////讀取圖片///////////////////////////////////////////
	void skillstart::LoadBitmap(int IDB_BITMAP, COLORREF colorkey)
	{
		image.LoadBitmap(IDB_BITMAP, colorkey);
	}
	/////////////////////////////////////////顯示技能圖片///////////////////////////////////////
	void skillstart::OnShow()
	{
		image.SetTopLeft(x, y);
		image.ShowBitmap();
		isEnd();
	}
	/////////////////////////////////////////移動技能圖片///////////////////////////////////////
	void skillstart::OnMove()
	{
		if (x > 0) x -= 40;
		else if (x == 0 && Stop)
		{
			delaycount = 40;
			Stop = false;
		}
		else if (delaycount-- <= 0) x -= 40;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	void skillstart::isEnd()
	{
		if (x <= -640) 
			Start = false;
	}
	bool skillstart::isStart()
	{
		return Start;
	}
}