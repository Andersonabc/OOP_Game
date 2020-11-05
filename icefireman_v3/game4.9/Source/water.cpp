#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "water.h"
namespace game_framework {
	water::water()
	{
	}
	void water::LoadBitmap()
	{
		animation.AddBitmap(WATER1, RGB(0, 0, 0));
		animation.AddBitmap(WATER2, RGB(0, 0, 0));
		animation.AddBitmap(WATER3, RGB(0, 0, 0));
		animation.AddBitmap(WATER4, RGB(0, 0, 0));
		animation.AddBitmap(WATER5, RGB(0, 0, 0));
		animation.SetDelayCount(3);
	}
	void water::SetDelayTime()
	{
		animation.SetDelayCount(3);
		animation.Reset();
	}
}