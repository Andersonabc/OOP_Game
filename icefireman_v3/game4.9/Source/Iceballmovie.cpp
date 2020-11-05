#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Iceballmovie.h"
namespace game_framework {
	IceBallMovie::IceBallMovie()
	{
		Init();
		Start = false;
	}
	void IceBallMovie::Init()
	{
		x = 640;
		y = 100;
		Start = true;
		Stop = true;
	}
	/////////////////////////////////////////讀取圖片///////////////////////////////////////////
	void IceBallMovie::LoadBitmap()
	{
		image.LoadBitmap(ICEBALLMOVIE);
	}
	/////////////////////////////////////////顯示技能圖片///////////////////////////////////////
	void IceBallMovie::OnShow()
	{
		image.SetTopLeft(x, y);
		image.ShowBitmap();
		isEnd();
	}
	/////////////////////////////////////////移動技能圖片///////////////////////////////////////
	void IceBallMovie::OnMove()
	{
		if (x > 0) x -= 40;
		else if (x == 0 && Stop)
		{
			delaycount = 40;
			Stop = false;
			CAudio::Instance()->Play(8, false);
		}
		else if (delaycount-- <= 0) x -= 40;
	}
	//////////////////////////////////////判斷是否完成圖片移動效果/////////////////////////////
	void IceBallMovie::isEnd()
	{
		if (x == -640) Start = false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	bool IceBallMovie::isStart()
	{
		return Start;
	}
}