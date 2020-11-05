#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "poison.h"

namespace game_framework {
	poison::poison()
	{
	}
	void poison::LoadBitmap()
	{
		animation.AddBitmap(POISON1, RGB(30, 30, 30));
		animation.AddBitmap(POISON2, RGB(30, 30, 30));
		animation.AddBitmap(POISON3, RGB(30, 30, 30));
		animation.AddBitmap(POISON4, RGB(30, 30, 30));
		animation.AddBitmap(POISON5, RGB(30, 30, 30));
		animation.SetDelayCount(5);
	}
	void poison::SetDelayTime()
	{
		animation.SetDelayCount(5);
		animation.Reset();
	}
}