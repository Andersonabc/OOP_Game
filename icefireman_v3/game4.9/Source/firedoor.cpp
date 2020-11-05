#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "firedoor.h"
namespace game_framework {
	firedoor::firedoor()
	{
	}
	void firedoor::LoadBitmap()
	{
		animation.AddBitmap(FIREDOOR1, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR2, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR3, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR4, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR5, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR6, RGB(0, 0, 0));
		animation.AddBitmap(FIREDOOR6, RGB(0, 0, 0));
		animation.SetDelayCount(3);
	}
	bool firedoor::Clearance(man player, int firegemnum)
	{
		//////////////////////////////////若是為火人/////////////////////////////////////
		if (player.Getcharacteristic() == "fire" && player.getgem() == firegemnum)
		{
			if (animation.IsFinalBitmap())//判斷門是否打開完成
			{
				return true;//火人已通關
			}
			else
			{
				animation.OnMove();//將門打開
				return false;
			}
		}
		else
		{
			if (animation.GetCurrentBitmapNumber() != 0)
			{
				animation.Movetonum(animation.GetCurrentBitmapNumber() - 1);//將門關上
			}
			return false;
		}
	}
};