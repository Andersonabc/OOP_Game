#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "bloodcount.h"

namespace game_framework {
	bloodcount::bloodcount()
	{

	}
	void bloodcount::Init(int _x, int _y, string _characteristic, int _numOfBlood, int IDB_BITMAP, COLORREF colorkey)
	{
		////////////////////////////////////初始化//////////////////////////////////////
		characterUI.LoadBitmap(IDB_BITMAP, colorkey);
		MagicBar.LoadBitmap(SasukeMagicBar, RGB(0, 0, 0));
		bloodbackground.LoadBitmap(blood_background);
		Blood.LoadBitmap(blood);
		Blood2.LoadBitmap(blood_2);
		Magic.LoadBitmap(Magic1);
		Chakura.LoadBitmap(chakura_black);
		SkillText.AddBitmap(SasukeSkillText1, RGB(255, 255, 255));
		SkillText.AddBitmap(SasukeSkillText2, RGB(255, 255, 255));
		SkillText.AddBitmap(SasukeSkillText3, RGB(255, 255, 255));
		SkillText.AddBitmap(SasukeSkillText4, RGB(255, 255, 255));
		SkillText.SetDelayCount(1);
		SkillText.Reset();
		SetXY(_x, _y);
		numOfMagic = 0;
		numOfChakura = 64;
		numOfBlood = _numOfBlood;
		characteristic = _characteristic;
		characterUI.SetTopLeft(_x, 10);
		MagicBar.SetTopLeft(84, 74);
		if(_characteristic == "AI") bloodbackground.SetTopLeft(_x+3, 29);
		else bloodbackground.SetTopLeft(84, 29);
		//////////////////////////////////////////////////////////////////////////////////////////////
	}
	int bloodcount::GetX1()
	{
		return x;
	}
	int bloodcount::GetY1()
	{
		return y;
	}

	void bloodcount::SetXY(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}
	void bloodcount::ChangeBlood(int _numOfBlood) 
	{
		numOfBlood = _numOfBlood;
	}
	void bloodcount::SetisMolding(bool flag,int _numOfMagic)
	{
		isMolding = flag;
		numOfMagic = _numOfMagic;
	}
	void bloodcount::ChangeChakura(int _chakura) 
	{
		numOfChakura = _chakura;
	}
	int bloodcount::GetChakura() 
	{
		return numOfChakura;
	}
	void bloodcount::OnShow()
	{
		characterUI.ShowBitmap(2);
		bloodbackground.ShowBitmap();
		/////////////////////消耗越多查克拉越少//////////////////////////
		for (int i = 0; i < 64 - numOfChakura; i++)
		{
			Chakura.SetTopLeft(84 + (64 - i)*2, 48);
			Chakura.ShowBitmap();
		}
		/////////////////////血量減少///////////////////////////////////
		if (characteristic == "player")
		{
			for (int i = 0; i < numOfBlood && i < 65; i++)
			{
				Blood2.SetTopLeft(84 + (i * 2), 29);
				Blood2.ShowBitmap();
			}
			if (numOfBlood >= 64)
			{
				for (int i = 0; i < numOfBlood - 63; i++)
				{
					Blood.SetTopLeft(84 + (i * 2), 29);
					Blood.ShowBitmap();
				}
			}
			//////////////////////集氣增加////////////////////////////
			if (isMolding && numOfMagic>0)
			{
				MagicBar.ShowBitmap(2);
				int num = numOfMagic;
				if (numOfMagic > 128 && numOfMagic < 512) num -= (numOfMagic / 128) * 128;
				for (int i = 0; i < 128-num; i++)
				{
					Magic.SetTopLeft(84 + (127-i), 77);
					Magic.ShowBitmap();
				}
				SkillText.SetTopLeft(84, 97);
				SkillText.Movetonum((numOfMagic / 128));
				SkillText.OnShow();
			}
		}
		else
		{
			///////////////////////////血量減少/////////////////////////////
			for (int i = 0; i < numOfBlood && i < 65; i++)
			{
				Blood2.SetTopLeft(x + 3 + ((64-i) * 2), 29);
				Blood2.ShowBitmap();
			}
			if (numOfBlood >= 64)
			{
				for (int i = 0; i < numOfBlood - 63; i++)
				{
					Blood.SetTopLeft(x + 3 + ((64-i) * 2), 29);
					Blood.ShowBitmap();
				}
			}
			////////////////////////////////////////////////////////////////
		}
	}

	int bloodcount::GetBlood() 
	{
		return numOfBlood;
	}

	 
}