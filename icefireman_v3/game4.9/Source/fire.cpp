#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "fire.h"
namespace game_framework {
	fire::fire()
	{
	}
	void fire::LoadBitmap()
	{
		animation.AddBitmap(FIRE1, RGB(0, 0, 0));
		animation.AddBitmap(FIRE2, RGB(0, 0, 0));
		animation.AddBitmap(FIRE3, RGB(0, 0, 0));
		animation.AddBitmap(FIRE4, RGB(0, 0, 0));
		animation.AddBitmap(FIRE5, RGB(0, 0, 0));
		animation.SetDelayCount(5);
	}
	void fire::SetDelayTime()
	{
		animation.SetDelayCount(5);
		animation.Reset();
	}
}
