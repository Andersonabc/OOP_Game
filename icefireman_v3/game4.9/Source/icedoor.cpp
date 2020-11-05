#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "icedoor.h"
namespace game_framework {
	icedoor::icedoor()
	{
	}
	void icedoor::LoadBitmap()
	{
		animation.AddBitmap(ICEDOOR1, RGB(0, 0, 0));
		animation.AddBitmap(ICEDOOR2, RGB(0, 0, 0));
		animation.AddBitmap(ICEDOOR3, RGB(0, 0, 0));
		animation.AddBitmap(ICEDOOR4, RGB(0, 0, 0));
		animation.AddBitmap(ICEDOOR5, RGB(0, 0, 0));
		animation.AddBitmap(ICEDOOR6, RGB(0, 0, 0));
		animation.SetDelayCount(3);
	}
	bool icedoor::Clearance(man player, int icegemnum)
	{
		//////////////////////////////////�Y�O���B�H/////////////////////////////////////
		if (player.Getcharacteristic() == "ice" && player.getgem() == icegemnum)
		{
			if (animation.IsFinalBitmap())//�P�_���O�_���}����
			{
				return true;//�B�H�w�q��
			}
			else
			{
				animation.OnMove();//�N�����}
				return false;
			}
		}
		else
		{
			if (animation.GetCurrentBitmapNumber() != 0)
			{
				animation.Movetonum(animation.GetCurrentBitmapNumber() - 1);//�N�����W
			}
			return false;
		}
	}
};