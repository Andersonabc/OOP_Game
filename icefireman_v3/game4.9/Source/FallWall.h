#pragma once
#ifndef FALLWALL_H
#define FALLWALL_H
#include "man.h"
namespace game_framework
{
	class FallWall
	{
	public:
		FallWall();
		virtual void LoadBitmap();
		int GetX();
		int GetY();
		int Getox();
		int Getoy();
		int GetFall();
		bool Onstand(man player);
		void SetFall(int flag);
		void SetFall(man player);
		void Setoxy(int x, int y);
		void SetTopLeft(int _x, int _y);
		void ShowBitmap();
		void Down();
		void Up();
		void Up(int v);
	protected:
		int x, y;
		int ox, oy;
		int Fall;
		CMovingBitmap image;
	};
}
#endif