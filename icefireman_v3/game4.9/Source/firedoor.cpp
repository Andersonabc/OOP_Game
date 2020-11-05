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
		//////////////////////////////////�Y�O�����H/////////////////////////////////////
		if (player.Getcharacteristic() == "fire" && player.getgem() == firegemnum)
		{
			if (animation.IsFinalBitmap())//�P�_���O�_���}����
			{
				return true;//���H�w�q��
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