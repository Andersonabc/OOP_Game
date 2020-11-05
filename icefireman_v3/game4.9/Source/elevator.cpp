#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "elevator.h"
namespace game_framework 
{
	buttonelevator::buttonelevator()
	{
		velocity = 5;
	}
	int buttonelevator::GetX()
	{
		return x;
	}
	int buttonelevator::GetY()
	{
		return y;
	}
	int buttonelevator::getox()
	{
		return ox;
	}
	int buttonelevator::getoy()
	{
		return oy;
	}
	void buttonelevator::setoxy(int x, int y)
	{
		ox = x;
		oy = y;
	}
	void buttonelevator::LoadBitmap()
	{
		image.LoadBitmap(elevator,RGB(255,255,255));
	}
	void buttonelevator::SetTopLeft(int _x, int _y)
	{
		x = _x;
		y = _y;
		image.SetTopLeft(x, y);
	}
	void buttonelevator::ShowBitmap()
	{
		image.ShowBitmap();
	}
	int buttonelevator::Getvelocity()
	{
		return velocity;
	}
	int buttonelevator::down()
	{
		y += velocity;
		return y;
	}
	int buttonelevator::up()
	{
		y -= velocity;
		return y;
	}
}