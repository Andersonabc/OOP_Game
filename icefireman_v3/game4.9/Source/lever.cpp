#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "lever.h"
namespace game_framework
{
	lever::lever()
	{
	}
	void lever::SetXY(int _x, int _y)
	{
		x = _x, y = _y;
	}
	int lever::GetX()
	{
		return x;
	}
	int lever::GetY()
	{
		return y;
	}
	CAnimation lever::Getimage()
	{
		return image;
	}
	void lever::OnMove()
	{
		image.OnMove();
	}
	void lever::OnShow()
	{
		image.SetTopLeft(x, y);
		image.OnShow();
	}
	void lever::LoadBitmap()
	{
		image.AddBitmap(LEVER, RGB(255, 255, 255));
		image.AddBitmap(LEVER2, RGB(255, 255, 255));
	}
}