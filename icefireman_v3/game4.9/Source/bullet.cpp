#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "bullet.h"

namespace game_framework{
	bullet::bullet(int _x, int _y,int _direction,string _characteristic)
	{
		///////////////////////初始化////////////////////////////////
		if (_direction == 1) _x -= 15;
		else _x += 15;
		SetXY(_x, _y);
		direction = _direction;
		characteristic = _characteristic;
		AddPic();
		////////////////////////////////////////////////////////////
	}
	int bullet::GetX1()
	{
		return x;
	}
	int bullet::GetY1()
	{
		return y;
	}
	int bullet::GetX2()
	{
		return x+bulletPic.Width();
	}
	int bullet::GetY2()
	{
		return y+bulletPic.Height();
	}
	int bullet::Getdirection()
	{
		return direction;
	}
	void bullet::AddPic()
	{
		/////////////////////////////讀取圖片////////////////////////////
		bulletPic.AddBitmap(BLACK, RGB(0, 0, 0));				//0
		bulletPic.AddBitmap(FIREBULLET1, RGB(8, 96, 0));		//0
		bulletPic.AddBitmap(FIREBULLET2, RGB(8, 96, 0));		//1
		bulletPic.AddBitmap(FIREBULLET3, RGB(8, 96, 0));		//2
		bulletPic.AddBitmap(FIREBULLET4, RGB(8, 96, 0));		//3
		bulletPic.AddBitmap(FIREBULLET5, RGB(8, 96, 0));		//4
		bulletPic.AddBitmap(FIREBULLET6, RGB(8, 96, 0));		//5
		bulletPic.AddBitmap(FIREBULLET7, RGB(8, 96, 0));		//6
		bulletPic.AddBitmap(FIREBULLET8, RGB(8, 96, 0));		//7
		bulletPic.AddBitmap(FIREBULLET9, RGB(8, 96, 0));		//8
		bulletPic.AddBitmap(FIREBULLET10, RGB(8, 96, 0));		//9
		bulletPic.AddBitmap(FIREBULLET11, RGB(8, 96, 0));		//10
		bulletPic.AddBitmap(FIREBULLET12, RGB(8, 96, 0));		//11
		bulletPic.AddBitmap(FIREBULLET13, RGB(8, 96, 0));		//12
		bulletPic.AddBitmap(FIREBULLET14, RGB(8, 96, 0));		//13
		bulletPic.AddBitmap(FIREBULLET15, RGB(8, 96, 0));		//14
		bulletPic.AddBitmap(FIREBULLET16, RGB(8, 96, 0));		//15
		bulletPic.AddBitmap(FIREBULLET17, RGB(8, 96, 0));		//16
		bulletPic.AddBitmap(FIREBULLET18, RGB(8, 96, 0));		//17
		bulletPic.AddBitmap(FIREBULLET19, RGB(8, 96, 0));		//18
		bulletPic.AddBitmap(FIREBULLET20, RGB(8, 96, 0));		//19
		bulletPic.AddBitmap(FIREBULLET21, RGB(8, 96, 0));		//20
		bulletPic.AddBitmap(FIREBULLET22, RGB(8, 96, 0));		//21
		bulletPic.AddBitmap(FIREBULLET23, RGB(8, 96, 0));		//22
		bulletPic.AddBitmap(ICEBULLET1, RGB(0, 160, 160));		//23
		bulletPic.AddBitmap(ICEBULLET2, RGB(0, 160, 160));		//24
		bulletPic.AddBitmap(ICEBULLET3, RGB(0, 160, 160));		//25
		bulletPic.AddBitmap(ICEBULLET4, RGB(0, 160, 160));		//26
		bulletPic.AddBitmap(ICEBULLET5, RGB(0, 160, 160));		//27
		bulletPic.AddBitmap(ICEBULLET2, RGB(0, 160, 160));		//28
		bulletPic.AddBitmap(ICEBULLET3, RGB(0, 160, 160));		//29
		bulletPic.AddBitmap(ICEBULLET4, RGB(0, 160, 160));		//30
		bulletPic.AddBitmap(ICEBULLET5, RGB(0, 160, 160));		//31
		bulletPic.AddBitmap(ICEBULLET6, RGB(255, 251, 255));	//32
		bulletPic.AddBitmap(ICEBULLET7, RGB(255, 251, 255));	//33
		bulletPic.AddBitmap(ICEBULLET8, RGB(255, 251, 255));	//34
		bulletPic.AddBitmap(ICEBULLET9, RGB(0, 160, 160));		//35
		bulletPic.AddBitmap(ICEBULLET10, RGB(0, 160, 160));		//36
		bulletPic.AddBitmap(ICEBULLET11, RGB(0, 160, 160));		//37
		bulletPic.AddBitmap(ICEBULLET12, RGB(0, 160, 160));		//38
		bulletPic.AddBitmap(ICEBULLET13, RGB(0, 160, 160));		//39
		bulletPic.AddBitmap(ICEBULLET10, RGB(0, 160, 160));		//40
		bulletPic.AddBitmap(ICEBULLET11, RGB(0, 160, 160));		//41
		bulletPic.AddBitmap(ICEBULLET12, RGB(0, 160, 160));		//42
		bulletPic.AddBitmap(ICEBULLET13, RGB(0, 160, 160));		//43
		bulletPic.AddBitmap(ICEBULLET14, RGB(255, 251, 255));	//44
		bulletPic.AddBitmap(ICEBULLET15, RGB(255, 251, 255));	//45
		bulletPic.AddBitmap(ICEBULLET16, RGB(255, 251, 255));	//46
		bulletPic.SetDelayCount(3);
		bulletPic.Reset();
		///////////////////////////////////////////////////////////////////////
	}
	void bullet::SetXY(int _x, int _y) {
		x = _x;
		y = _y;
	}
	CAnimation bullet::Getbullet()
	{
		return bulletPic;
	}
	void bullet::Move()
	{
		///////////////////////////////////子彈移動////////////////////////////////////////////
		if (direction==1)x += 15;
		else x -= 15;
		///////////////////////////////////根據屬性及方向決定圖片//////////////////////////////
		if (direction == 1 && characteristic=="fire")
		{
			if (!(bulletPic.GetCurrentBitmapNumber() >= 1 && bulletPic.GetCurrentBitmapNumber() < 12))
				bulletPic.Movetonum(1);
			else bulletPic.OnMove();
		}
		if (direction == 0 && characteristic == "fire")
		{
			if (!(bulletPic.GetCurrentBitmapNumber() >= 13 && bulletPic.GetCurrentBitmapNumber() < 23))
				bulletPic.Movetonum(13);
			else bulletPic.OnMove();
		}
		if (direction == 1 && characteristic == "ice")
		{
			if (!(bulletPic.GetCurrentBitmapNumber() >= 24 && bulletPic.GetCurrentBitmapNumber() < 35))
				bulletPic.Movetonum(24);
			else bulletPic.OnMove();
		}
		if (direction == 0 && characteristic == "ice")
		{
			if (!(bulletPic.GetCurrentBitmapNumber() >= 36 && bulletPic.GetCurrentBitmapNumber() < 47))
				bulletPic.Movetonum(36);
			else bulletPic.OnMove();
		}
		////////////////////////////////////////////////////////////////////////////////////////////
	}
	void bullet::OnShow()
	{
		bulletPic.SetTopLeft(x, y);
		bulletPic.OnShow();
	}

}