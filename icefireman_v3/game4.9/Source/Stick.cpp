#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Stick.h"

namespace game_framework 
{
	int Stick::GetX()
	{
		return x;
	}
	int Stick::GetY()
	{
		return y;
	}
	void Stick::LoadBitmap()
	{
		stickImage.LoadBitmap(Button, RGB(255, 255, 255));
	}
	void Stick::SetTopLeft(int _x, int _y)
	{
		x = _x;
		y = _y;
		stickImage.SetTopLeft(x, y);
	}
	void Stick::ShowBitmap()
	{
		stickImage.ShowBitmap();
	}
	void Stick::Move()
	{
	
	}
}