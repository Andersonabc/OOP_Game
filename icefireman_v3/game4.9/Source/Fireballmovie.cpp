#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Fireballmovie.h"
namespace game_framework {
	FireBallMovie::FireBallMovie()
	{
		Init();
		Start = false;
	}
	void FireBallMovie::Init()
	{
		x = 640;
		y = 100;
		Start = true;
		Stop = true;
	}
	/////////////////////////////////////////Ū���Ϥ�///////////////////////////////////////////
	void FireBallMovie::LoadBitmap()
	{
		image.LoadBitmap(FIREBALLMOVIE);
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////��ܧޯ�Ϥ�///////////////////////////////////////
	void FireBallMovie::OnShow()
	{
		image.SetTopLeft(x, y);
		image.ShowBitmap();
		isEnd();
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////���ʧޯ�Ϥ�///////////////////////////////////////
	void FireBallMovie::OnMove()
	{
		if (x > 0) x -= 40;
		else if (x == 0 && Stop)
		{
			delaycount = 30;
			Stop = false;
			CAudio::Instance()->Play(7, false);
		}
		else if (delaycount-- <= 0) x -=40;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////�P�_�O�_�����Ϥ����ʮĪG/////////////////////////////
	void FireBallMovie::isEnd()
	{
		if (x == -640) Start = false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	bool FireBallMovie::isStart()
	{
		return Start;
	}
}