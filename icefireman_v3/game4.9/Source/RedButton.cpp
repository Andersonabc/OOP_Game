#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedButton.h"

namespace game_framework {
	RedButton::RedButton()
	{
	}
	void RedButton::LoadBitmap()
	{
		image.LoadBitmap(Button, RGB(255, 255, 255));
	}
}