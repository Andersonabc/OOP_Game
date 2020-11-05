#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "iceman.h"

namespace game_framework {
	iceman::iceman()
	{
		Initialize();
	}
	void iceman::LoadBitmap()
	{
		/////////////////////////////////讀取圖片//////////////////////////////////////
		animation.AddBitmap(ICEMAN, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN01, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN02, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN03, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN04, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN05, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN06, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN07, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN08, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN09, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN10, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN11, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN12, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN13, RGB(255, 255, 255));
		animation.AddBitmap(ICERUN14, RGB(255, 255, 255));
		animation.AddBitmap(ICEJUMP00, RGB(255, 255, 255));
		animation.AddBitmap(ICEJUMP01, RGB(255, 255, 255));
		animation.AddBitmap(ICEJUMP02, RGB(255, 255, 255));
		animation.AddBitmap(ICEJUMP03, RGB(255, 255, 255));
		animation.AddBitmap(ICEDOWN00, RGB(255, 255, 255));
		animation.AddBitmap(ICEDOWN01, RGB(255, 255, 255));
		animation.AddBitmap(ICEDOWN02, RGB(255, 255, 255));
		animation.AddBitmap(ICEDOWN03, RGB(255, 255, 255));
		/////////////////////////////////////////////////////////////////
	}
	void iceman::LoadBitmap(int i)
	{
		////////////////////////////////////讀取對戰冰人圖片/////////////////////
		animation.AddBitmap(IceAttack, RGB(0, 0, 0));				//0
		animation.AddBitmap(ICEATTACK2, RGB(0, 0, 0));				//1
		animation.AddBitmap(ICEATTACKRUN1, RGB(0, 0, 0));			//2
		animation.AddBitmap(ICEATTACKRUN1, RGB(0, 0, 0));			//3
		animation.AddBitmap(ICEATTACKRUN2, RGB(0, 0, 0));			//4
		animation.AddBitmap(ICEATTACKRUN2, RGB(0, 0, 0));			//5
		animation.AddBitmap(ICEATTACKRUN3, RGB(0, 0, 0));			//6
		animation.AddBitmap(ICEATTACKRUN3, RGB(0, 0, 0));			//7
		animation.AddBitmap(ICEATTACKRUN4, RGB(0, 0, 0));			//8
		animation.AddBitmap(ICEATTACKRUN4, RGB(0, 0, 0));			//9
		animation.AddBitmap(ICEATTACKRUN5, RGB(0, 0, 0));			//10
		animation.AddBitmap(ICEATTACKRUN5, RGB(0, 0, 0));			//11
		animation.AddBitmap(ICEATTACKRUN6, RGB(0, 0, 0));			//12
		animation.AddBitmap(ICEATTACKRUN6, RGB(0, 0, 0));			//13
		animation.AddBitmap(ICEATTACKJUMP1, RGB(0, 0, 0));			//14
		animation.AddBitmap(ICEATTACKJUMP2, RGB(0, 0, 0));			//15
		animation.AddBitmap(ICEATTACKED1, RGB(0, 0, 0));			//16
		animation.AddBitmap(ICEATTACKED2, RGB(0, 0, 0));			//17
		animation.AddBitmap(ICEATTACKED3, RGB(0, 0, 0));			//18
		animation.AddBitmap(ICEATTACKED4, RGB(0, 0, 0));			//19
		animation.AddBitmap(ICEATTACKED5, RGB(0, 0, 0));			//20
		animation.AddBitmap(ICEATTACKED6, RGB(0, 0, 0));			//21
		animation.AddBitmap(ICEATTACKED7, RGB(0, 0, 0));			//22
		animation.AddBitmap(ICEATTACKED8, RGB(0, 0, 0));			//23
		animation.AddBitmap(ICEATTACKED9, RGB(0, 0, 0));			//24
		animation.AddBitmap(ICEATTACKED10, RGB(0, 0, 0));			//25
		animation.AddBitmap(ICEATTACKED11, RGB(0, 0, 0));			//26
		animation.AddBitmap(ICEATTACKED12, RGB(0, 0, 0));			//27
		animation.AddBitmap(ICE_HIT1, RGB(0, 0, 0));				//28
		animation.AddBitmap(ICE_HIT1, RGB(0, 0, 0));				//29
		animation.AddBitmap(ICE_HIT2, RGB(0, 0, 0));				//30
		animation.AddBitmap(ICE_HIT2, RGB(0, 0, 0));				//31
		animation.AddBitmap(ICE_HIT3, RGB(0, 0, 0));				//32
		animation.AddBitmap(ICE_HIT3, RGB(0, 0, 0));				//33
		animation.AddBitmap(ICE_HIT4, RGB(0, 0, 0));				//34
		animation.AddBitmap(ICE_HIT4, RGB(0, 0, 0));				//35
		animation.AddBitmap(ICE_DEFENSE1, RGB(0, 0, 0));			//36
		animation.AddBitmap(ICE_DEFENSE2, RGB(0, 0, 0));			//37
		animation.AddBitmap(ICEATTACKMAGIC, RGB(0, 0, 0));			//38
		animation.AddBitmap(ICEATTACKMAGIC3, RGB(0, 0, 0));			//39
		animation.AddBitmap(ICEATTACKMAGIC2, RGB(0, 0, 0));			//40
		animation.AddBitmap(ICEATTACKMAGIC4, RGB(0, 0, 0));			//41
		//////////////////////////////////////魔力條及魔力擋板//////////////////////////
		MagicBar.LoadBitmap(MAGICBAR);
		Black.LoadBitmap(BLACK);
		////////////////////////////////////////////////////////////////////////////////
		animation.OnMove();
	}
	void iceman::Initialize()
	{
		////////////////////////////////////////初始化////////////////////////////////
		floor = 460;
		const int X_POS = 60;
		const int Y_POS = 400 - 39;
		const int INITIAL_VELOCITY = 12;
		const int STEP_SIZE = 7;
		step_size = 7;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		characteristic = "ice";
		gem = 0;
		x = X_POS;
		y = Y_POS;
		times = 0;
		direction = 0;
		isAttacked = 2;
		combodelay = 0;
		damage = 0;
		RushTime = 0;
		magic = 100;
		MagicX = 364;
		MagicY = 30;
		isMagic=isRush=isShooting = isAttack = isTwojump = fly = rising = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		/////////////////////////////////////////////////////////////////////////////////////////
	}

	void iceman::jumpsound()
	{
		CAudio::Instance()->Play(3,false);//跳躍聲音
	}

}
