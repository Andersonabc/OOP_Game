#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "fireman.h"
namespace game_framework {
	fireman::fireman()
	{
		Initialize();
	}
	void fireman::LoadBitmap()
	{
		///////////////////////////////////讀取圖片/////////////////////////////////////////
		animation.AddBitmap(FIRE, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN01, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN02, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN03, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN04, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN05, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN06, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN07, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN08, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN09, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN10, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN11, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN12, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN13, RGB(255, 255, 255));
		animation.AddBitmap(FIREMANRUN14, RGB(255, 255, 255));
		animation.AddBitmap(FIREJUMP00, RGB(255, 255, 255));
		animation.AddBitmap(FIREJUMP01, RGB(255, 255, 255));
		animation.AddBitmap(FIREJUMP02, RGB(255, 255, 255));
		animation.AddBitmap(FIREJUMP03, RGB(255, 255, 255));
		animation.AddBitmap(FIREDOWN00, RGB(255, 255, 255));
		animation.AddBitmap(FIREDOWN01, RGB(255, 255, 255));
		animation.AddBitmap(FIREDOWN02, RGB(255, 255, 255));
		animation.AddBitmap(FIREDOWN03, RGB(255, 255, 255));
		/////////////////////////////////////////////////////////////////////////////////
	}
	void fireman::LoadBitmap(int i)
	{
		/////////////////////////////////////讀取對戰模式圖片/////////////////////////////
		animation.AddBitmap(FIRE_ATTTACK, RGB(0, 0, 0));			//0
		animation.AddBitmap(FIRE_ATTTACK2, RGB(0, 0, 0));			//1
		animation.AddBitmap(FIREATTACKRUN1, RGB(0, 0, 0));			//2
		animation.AddBitmap(FIREATTACKRUN1, RGB(0, 0, 0));			//3
		animation.AddBitmap(FIREATTACKRUN2, RGB(0, 0, 0));			//4
		animation.AddBitmap(FIREATTACKRUN2, RGB(0, 0, 0));			//5
		animation.AddBitmap(FIREATTACKRUN3, RGB(0, 0, 0));			//6
		animation.AddBitmap(FIREATTACKRUN3, RGB(0, 0, 0));			//7
		animation.AddBitmap(FIREATTACKRUN4, RGB(0, 0, 0));			//8
		animation.AddBitmap(FIREATTACKRUN4, RGB(0, 0, 0));			//9
		animation.AddBitmap(FIREATTACKRUN5, RGB(0, 0, 0));			//10
		animation.AddBitmap(FIREATTACKRUN5, RGB(0, 0, 0));			//11
		animation.AddBitmap(FIREATTACKRUN6, RGB(0, 0, 0));			//12
		animation.AddBitmap(FIREATTACKRUN6, RGB(0, 0, 0));			//13
		animation.AddBitmap(FIREATTTACKEDJUMP1, RGB(0, 0, 0));		//14
		animation.AddBitmap(FIREATTTACKEDJUMP2, RGB(0, 0, 0));		//15
		animation.AddBitmap(FIRE_ATTTACKED1, RGB(0, 0, 0));			//16
		animation.AddBitmap(FIRE_ATTTACKED2, RGB(0, 0, 0));			//17
		animation.AddBitmap(FIRE_ATTTACKED3, RGB(0, 0, 0));			//18
		animation.AddBitmap(FIRE_ATTTACKED4, RGB(0, 0, 0));			//19
		animation.AddBitmap(FIRE_ATTTACKED5, RGB(0, 0, 0));			//20
		animation.AddBitmap(FIRE_ATTTACKED6, RGB(0, 0, 0));			//21
		animation.AddBitmap(FIRE_ATTTACKED7, RGB(0, 0, 0));			//22
		animation.AddBitmap(FIRE_ATTTACKED8, RGB(0, 0, 0));			//23
		animation.AddBitmap(FIRE_ATTTACKED9, RGB(0, 0, 0));			//24
		animation.AddBitmap(FIRE_ATTTACKED10, RGB(0, 0, 0));		//25
		animation.AddBitmap(FIRE_ATTTACKED11, RGB(0, 0, 0));		//26
		animation.AddBitmap(FIRE_ATTTACKED12, RGB(0, 0, 0));		//27
		animation.AddBitmap(FIRE_HIT1, RGB(0, 0, 0));				//28
		animation.AddBitmap(FIRE_HIT1, RGB(0, 0, 0));				//29
		animation.AddBitmap(FIRE_HIT2, RGB(0, 0, 0));				//30
		animation.AddBitmap(FIRE_HIT2, RGB(0, 0, 0));				//31
		animation.AddBitmap(FIRE_HIT3, RGB(0, 0, 0));				//32
		animation.AddBitmap(FIRE_HIT3, RGB(0, 0, 0));				//33
		animation.AddBitmap(FIRE_HIT4, RGB(0, 0, 0));				//34
		animation.AddBitmap(FIRE_HIT4, RGB(0, 0, 0));				//35
		animation.AddBitmap(FIRE_DEFENSE1, RGB(0, 0, 0));			//36
		animation.AddBitmap(FIRE_DEFENSE2, RGB(0, 0, 0));			//37
		animation.AddBitmap(FIREATTACKMAGIC, RGB(0, 0, 0));			//38
		animation.AddBitmap(FIREATTACKMAGIC3, RGB(0, 0, 0));		//39
		animation.AddBitmap(FIREATTACKMAGIC2, RGB(0, 0, 0));		//40
		animation.AddBitmap(FIREATTACKMAGIC4, RGB(0, 0, 0));		//41
		//////////////////////////////////////魔力條及魔力擋板//////////////////////////
		MagicBar.LoadBitmap(MAGICBAR);
		Black.LoadBitmap(BLACK);
		///////////////////////////////////////////////////////////////////////////////
	}
	void fireman::Initialize()
	{
		////////////////////////////////////////初始化////////////////////////////////
		floor = 460;
		const int X_POS = 60;
		const int Y_POS = 460 - 39;
		const int INITIAL_VELOCITY = 12;
		const int STEP_SIZE = 7;
		step_size = 7;
		gem = 0;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		characteristic = "fire";
		x = X_POS;
		y = Y_POS;
		times = 0;
		direction = 1;
		isAttacked = 2;
		combodelay = 0;
		damage = 0;
		RushTime = 0;
		magic = 100;
		MagicX = 76;
		MagicY = 30;
		isMagic =isRush=isShooting = isAttack = isTwojump = fly = rising = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		//////////////////////////////////////////////////////////////////////////////////
	}
	void fireman::jumpsound()
	{
		CAudio::Instance()->Play(4,false);//跳躍聲音
	}
}
