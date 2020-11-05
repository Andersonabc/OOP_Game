#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Chainelevator.h"
#include "math.h"
namespace game_framework
{
	ChainElevator::ChainElevator()
	{
	}
	void ChainElevator::SetX2Y2(int X2, int Y2)
	{
		x2 = X2, y2 = Y2;
	}
	void ChainElevator::Setaimy1(int _y)
	{
		aimy1 = _y+10;
		rangey1 = aimy1-y;
	}
	void ChainElevator::Setaimy2(int y)
	{
		aimy2 = y;
		rangey2 = y-y2;
	}
	bool ChainElevator::Onstand2(man player)
	{
		///////////////////////////若是站在電梯2上/////////////////////////////////////
		if (x2 < (player.GetX1() + player.GetX2()) / 2 && (player.GetX1() + player.GetX2()) / 2 < x2 + 60 && (y2 + 44 +(int)Getcount() > player.GetY2() && y2 - 5 + (int)Getcount() < player.GetY2()))
			return true;
		else return false;
	}
	bool ChainElevator::OnStand(int _x, int _y)
	{
		//////////////////////////站在電梯1上////////////////////////////////
		if (x < _x && _x < x + 60 && y + 50  > _y && y - 20  < _y)
			return true;
		else return false;
	}
	bool ChainElevator::OnStand2(int x, int y)
	{
		////////////////////////////站在電梯2上///////////////////////////
		if (x2 < x && x < x2 + 60 && (y2 + 44 + (int)Getcount() > y && y2 - 5 + (int)Getcount() < y))
			return true;
		else return false;
	}
	int ChainElevator::GetFall2()
	{
		return Fall2;
	}
	void ChainElevator::SetFall2(int flag)
	{
		Fall2 = flag;
	}
	void ChainElevator::SetFall2(man player)
	{
		if (x2 < (player.GetX1() + player.GetX2()) / 2 && (player.GetX1() + player.GetX2()) / 2 < x2 + 60 && (y2 + 44 + (int)Getcount() > player.GetY2() && y2 - 5 + (int)Getcount() < player.GetY2()))
			Fall2+=1;
	}
	double ChainElevator::Getcount()
	{
		////////////////////取得兩電梯移動得比值/////////////////////////
		double scale = ((double)rangey2 / (double)rangey1);
		count = (rangey1 - abs(y - aimy1)) * scale;
		return count;
	}
	int ChainElevator::GetaimY1()
	{
		return aimy1;
	}
	int ChainElevator::GetX2()
	{
		return x2;
	}
	int ChainElevator::GetY2()
	{
		return y2;
	}
	void ChainElevator::LoadBitmap()
	{
		///////////////////////讀檔/////////////////////////////
		image.LoadBitmap(elevator, RGB(255, 255, 255));
		Elevator2.LoadBitmap(elevator, RGB(255, 255, 255));
	}
	void ChainElevator::onShow()
	{
		//////////////////////顯示//////////////////////////////
		FallWall::ShowBitmap();
		Elevator2.SetTopLeft(x2, y2+(int)Getcount());
		Elevator2.ShowBitmap();
	}
}
