#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "yellowbutton.h"

namespace game_framework 
{
	yellowbutton::yellowbutton()
	{

	}
	int yellowbutton::GetX()
	{
		return x;
	}
	int yellowbutton::GetY()
	{
		return y;
	}
	bool yellowbutton::Onpress(int _x, int _y)
	{
		////////////////////////////角色站在按鈕上///////////////////////
		if (x < _x && _x < x + 20 && y < _y && _y < y + 20) return true;
		else return false;
	}
	void yellowbutton::LoadBitmap()
	{
		image.LoadBitmap(Button,RGB(255, 255, 255));
	}
	void yellowbutton::SetTopLeft(int _x, int _y)
	{
		x = _x;
		y = _y;
		image.SetTopLeft(x, y+13);
	}
	void yellowbutton::ShowBitmap()
	{
		image.ShowBitmap();
	}
}
