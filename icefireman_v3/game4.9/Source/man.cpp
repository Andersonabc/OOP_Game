#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "man.h"

namespace game_framework {
	man::man()
	{
		Initialize();
	}
	int man::GetX1()
	{
		return x;
	}

	int man::GetY1()
	{
		return y;
	}

	int man::GetX2()
	{
		return x + 31 ;
	}

	int man::GetY2()
	{
		return y + 39;
	}

	int man::Getvelocity()
	{
		return velocity;
	}
	int man::Getfloor()
	{
		return floor;
	}
	bool man::Onfloor()
	{
		if (animation.GetCurrentBitmapNumber() < 14 ||animation.GetCurrentBitmapNumber()>22) return true;
		else return false;
	}
	string man::Getcharacteristic()
	{
		return characteristic;
	}
	bool man::GetRising()
	{
		return rising;
	}
	bool man::Getfly()
	{
		return fly;
	}
	void man::Addgem()
	{
		gem++;
	}
	int man::getgem()
	{
		return gem;
	}
	int man::Getstep()
	{
		return step_size;
	}

	void man::Initialize()
	{
	}
	void man::LoadBitmap()
	{
	}
	void man::LoadBitmap(int i)
	{
	}
	void man::OnMove()
	{
		animation.SetDelayCount(1);
		////////////////////////////////////////////////////判斷是否移動////////////////////////////////////////////////
		if (isMovingLeft || isMovingRight || isMovingUp)
		{
			////////////////////////////////////////////////////左移////////////////////////////////////////////////
			if (isMovingLeft)
			{
				if (left == 1)
					x -= step_size;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 14))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
			}
			////////////////////////////////////////////////////右移////////////////////////////////////////////////
			else if (isMovingRight)
			{
				if (right == 1)
					x += step_size;
				if (!(animation.GetCurrentBitmapNumber() > 0 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(1);
				}
				else
				{
					animation.OnMove();
				}
			}
			////////////////////////////////////////////////////跳躍////////////////////////////////////////////////
			if ((isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39))
			{
				rising = true;
				velocity = initial_velocity;
				if (!(animation.GetCurrentBitmapNumber() > 14 && animation.GetCurrentBitmapNumber() < 18))
				{
					animation.Movetonum(15);
				}
			}
		}
		///////////////////////////////////////////////////////站在原地//////////////////////////////////////
		else
			animation.Reset();
		jump();
	}

	void man::OnMove(man *player)
	{
		//--------子彈---------
		if (isShooting && isAttacked == 2)
		{
			shoot.push_back(new bullet(this->GetX1(), this->GetY1(),direction,characteristic));
			isShooting = false;
		}
		if (shoot.size() != 0) {
			for (int count = 0; count < this->GetBullet(); count++) {
				shoot[count]->Move();
				if (shoot[count]->Getbullet().GetCurrentBitmapNumber()==12 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 23 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 35 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 47) {
					delete shoot[count];
					shoot.erase(shoot.begin()+count);
				}
				else if (((shoot[count]->GetX2()>player->GetX1()&&shoot[count]->Getdirection()==1 && shoot[count]->GetX1() < player->GetX2()) ||  (shoot[count]->GetX1() < player->GetX2()&&shoot[count]->Getdirection() == 0&& shoot[count]->GetX2() > player->GetX1()))&&((player->GetY1()<shoot[count]->GetY2() && player->GetY1()>shoot[count]->GetY1())||(player->GetY2()>shoot[count]->GetY1()&&player->GetY2()<shoot[count]->GetY2()))) {
					player->SetAttacked(shoot[count]->Getdirection());
					delete shoot[count];
					shoot.erase(shoot.begin() + count);
				}
			}
		}
		///////////////////////////////////////
		animation.SetDelayCount(1);
		///////////////////判斷使用衝鋒技能////////////////////////
		if (isRush)
		{
			////////////////////////////若是衝鋒還有時間///////////////////////
			if (direction == 0 && RushTime>0)
			{
				///////////////////////////////向左衝刺///////////////////////
				if (left == 1)
					x -= step_size*2;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 13))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
				direction = 0;
				////////////////////////////////////////////////////////////////
			}
			else if (direction == 1 && RushTime > 0)
			{
				///////////////////////////////向右衝刺///////////////////////
				if (right == 1)
					x += step_size * 2;
				if (!(animation.GetCurrentBitmapNumber() > 1 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(2);
				}
				else
				{
					animation.OnMove();
				}
				direction = 1;
				////////////////////////////////////////////////////////////////
			}
			if (RushTime-- <= 0)
				isRush = false;//結束衝刺
		}
		///////////////////集氣////////////////////////
		else if (isMagic && isAttacked == 2)
		{
			animation.SetDelayCount(5);
			if(magic<100) magic++;//增加魔力
			//////////////////////////切換圖片/////////////////////////////////////////////
			if (direction == 0)
			{
				if(animation.GetCurrentBitmapNumber()!=40) animation.Movetonum(40);
				else animation.Movetonum(41);
			}
			else if (direction == 1)
			{
				if (animation.GetCurrentBitmapNumber() != 38) animation.Movetonum(38);
				else animation.Movetonum(39);
			}
			//////////////////////////////////////////////////////////////////////////
		}
		///////////////////防禦////////////////////////
		else if (isMovingDown && isAttacked == 2)
		{
			if (direction == 0) animation.Movetonum(37);
			else if (direction == 1) animation.Movetonum(36);
		}
		///////////////////移動//////////////////////
		else if ((isMovingLeft || isMovingRight || isMovingUp) && isAttacked ==2)
		{
			/////////////////////////////////左移//////////////////////////////////
			if (isMovingLeft)
			{
				if (left == 1)
					x -= step_size;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 13))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
				direction = 0;
			}
			////////////////////////////////////////////////////右移////////////////////////////////////////////////
			else if (isMovingRight)
			{
				if (right == 1)
					x += step_size;
				if (!(animation.GetCurrentBitmapNumber() > 1 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(2);
				}
				else
				{
					animation.OnMove();
				}
				direction = 1;
			}
			////////////////////////////////////////////////////跳躍////////////////////////////////////////////////
			if ((isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39) || (isMovingUp && isTwojump))
			{
				if (!(isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39))
					isTwojump = false;
				rising = true;
				isMovingUp = false;
				velocity = initial_velocity;

			}
			//////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else if (isAttack && isAttacked==2)
		{
		//////////////////////////////////////////////////////攻擊命中且對手未防禦或破防///////////////////////////////////////////////
			if (x + 59 > player->GetX1() && player->GetX1() > x && direction ==1 && player->GetY1() < y + 10 && player->GetY1() > y - 10 &&(player->GetAnimation().GetCurrentBitmapNumber()!=37 || player->GetDamage() > 5))
			{
				if (!(animation.GetCurrentBitmapNumber() > 27 && animation.GetCurrentBitmapNumber() <= 31)) animation.Movetonum(28);
				else if (animation.GetCurrentBitmapNumber() == 31)
				{
					player->SetAttacked(1);//將對手設定為被擊中
					isAttack = false;
					CAudio::Instance()->Play(9, false);
				}
				else animation.OnMove();
				
			}
			else if (x-20 < player->GetX2() && player->GetX2() < GetX2() && direction == 0 && player->GetY1() < y + 10 && player->GetY1() > y - 10 && direction == 0 && (player->GetAnimation().GetCurrentBitmapNumber() != 36 || player->GetDamage()>5))
			{
				if (!(animation.GetCurrentBitmapNumber() > 31 && animation.GetCurrentBitmapNumber() <= 35)) animation.Movetonum(32);
				else if (animation.GetCurrentBitmapNumber() == 35)
				{
					player->SetAttacked(0);
					isAttack = false;
					CAudio::Instance()->Play(9, false);
				}
				else animation.OnMove();
			}
			///////////////////////////////////////////////攻擊未命中//////////////////////////////////////////////////
			else if (direction == 1)
			{
				if (animation.GetCurrentBitmapNumber() < 28)animation.Movetonum(28);
				else if (animation.GetCurrentBitmapNumber() == 31) isAttack = false;
				else animation.OnMove();
			}
			else if (direction == 0)
			{
				if (animation.GetCurrentBitmapNumber() < 32)animation.Movetonum(32);
				else if (animation.GetCurrentBitmapNumber() == 35) isAttack = false;
				else animation.OnMove();
			}
			/////////////////////////////////////////////////擊中防禦狀態增加破防值/////////////////////////////////////////
			if (((x + 59 > player->GetX1() && player->GetX1() > x && direction == 1 && player->GetY1() < y + 10 && player->GetY1() > y - 10 )||(x - 20 < player->GetX2() && player->GetX2() < GetX2() && player->GetY1() < y + 10 && player->GetY1() > y - 10)) && player->GetAnimation().GetCurrentBitmapNumber() - 36 == direction &&(animation.GetCurrentBitmapNumber() == 31|| animation.GetCurrentBitmapNumber() == 35))
				player->AddDamage();
		}
		/////////////////////////////////////////被擊中////////////////////////////////////////////////////////
		else if (isAttacked!=2)
		{
		/////////////////////////////向後移動////////////////////////////////
			if (isAttacked == 0 && left == 1)
				x -= step_size/2;
			else if (isAttacked == 1 && right == 1)
				x += step_size/2;
			if (times == 24)
			{
				times = 0;
				isAttacked = 2;
			}
			else
			{
				if (times % 4 == 0 && player->GetX1() >= x && left == 1)
				{
					if (animation.GetCurrentBitmapNumber() >= 16 && animation.GetCurrentBitmapNumber() < 21)
						animation.OnMove();
					else
						animation.Movetonum(16);
				}
				else if (times % 4 == 0 && player->GetX1() < x && left == 1)
				{
					if (animation.GetCurrentBitmapNumber() >= 21 && animation.GetCurrentBitmapNumber() < 27)
						animation.OnMove();
					else
						animation.Movetonum(21);
				}
				times++;
			}
			//////////////////////////////////////////////////////////////////
		}
		else
		/////////////////////////////////站在原地////////////////////////////////////////////
			if(direction ==1 ) animation.Reset();
			else if(direction == 0) animation.Movetonum(1);
		//////////////////////////////////////////////////////////////////
		jump(1);
	}

	void man::setfloor(int _floor)
	{
		floor = _floor;
	}

	void man::sethead(bool flag)
	{
		head = flag;
	}

	void man::setleft(int flag)
	{
		left = flag;
	}

	void man::setright(int flag)
	{
		right = flag;
	}

	void man::jump()
	{
		if (rising)  			// 上升狀態
		{
			if(velocity == initial_velocity) 	jumpsound();
			if (velocity > 0)
			{
				if (head)
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				if (fly && velocity < initial_velocity) velocity++;
				else velocity--;		// 受重力影響，下次的上升速度降低
			}
			else
			{
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
			if (animation.GetCurrentBitmapNumber() > 14 && animation.GetCurrentBitmapNumber() < 18)
				animation.OnMove();
			else
			{
				animation.Movetonum(15);
			}
		}
		else  				// 下降狀態
		{
			if (y < floor - 39)  // 當y座標還沒碰到地板
			{
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (fly) velocity-=2;
				else velocity++;		// 受重力影響，下次的下降速度增加

				if (animation.GetCurrentBitmapNumber() > 18 && animation.GetCurrentBitmapNumber() < 22)
					animation.OnMove();
				else
					animation.Movetonum(19);
			}
			else
			{
				y = floor - 39;  // 當y座標低於地板，更正為地板上
				velocity = initial_velocity; // 重設上升初始速度
			}
		}
	}
	void man::jump(int i)
	{
		if (rising)  			// 上升狀態
		{
			if (velocity == initial_velocity) 	jumpsound();
			if (velocity > 0)
			{
				if (head)
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				if (fly && velocity < initial_velocity) velocity++;
				else velocity--;		// 受重力影響，下次的上升速度降低
			}
			else
			{
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
			if (direction == 1)
				animation.Movetonum(14);
			if (direction == 0)
				animation.Movetonum(15);
		}
		else  				// 下降狀態
		{
			if (y < floor - 39)  // 當y座標還沒碰到地板
			{
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (fly) velocity -= 2;
				else velocity++;		// 受重力影響，下次的下降速度增加0
				if (direction == 1)
					animation.Movetonum(14);
				if (direction == 0)
					animation.Movetonum(15);
			}
			else
			{
				y = floor - 39;  // 當y座標低於地板，更正為地板上
				velocity = initial_velocity; // 重設上升初始速度
			}

		}
	}
	void man::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag) combo.push_back('D');//將COMBO指令丟進COMBO表
		if (flag) damage = 0;
	}

	void man::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) combo.push_back('L');//將COMBO指令丟進COMBO表
	}

	void man::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) combo.push_back('R');//將COMBO指令丟進COMBO表
	}

	void man::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if(flag) combo.push_back('U');//將COMBO指令丟進COMBO表
	}
	bool man::SetShooting()
	{
		if((int)combo.size() ==3 && combo[2]=='A' && (combo[1] == 'R' || combo[1] == 'L') && combo[0] == 'D' &&magic>=20)//若是按下防前攻的指令
		{
			isShooting = true;//射出子彈
			magic -= 20;
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//清除COMBO表
			return true;
		}
		return false;
	}

	void man::SetRush()
	{
		if ((int)combo.size() > 3) combo.erase(combo.begin());//清除COMBO表
		if ((int)combo.size() == 3 && combo[2] == 'A' && ((combo[1] == 'R' && combo[0] == 'R') || (combo[1] == 'L'&& combo[0] == 'L'))&&magic>=20)//若是按下前前攻的指令
		{
			isRush = true;//向前衝刺
			RushTime = 10;
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//清除COMBO表
			magic -= 20;
		}
		if (combodelay-- <= 0)
		{
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//清除COMBO表
		}
		
	}

	void man::SetisMagic(bool flag)
	{
		isMagic = flag;
	}

	CAnimation man::GetAnimation()
	{
		return animation;
	}

	void man::SetTwojump(bool flag)
	{
		isTwojump = flag;
	}

	void man::SetAttack(bool flag)
	{
		isAttack = flag;
		if (flag) combo.push_back('A');//將COMBO指令丟進COMBO表
	}

	void man::SetAttacked(int flag)
	{
		isAttacked = flag;
	}
	bool man::Getshooting()
	{
		return isShooting;
	}
	bool man::GetRush()
	{
		return isRush;
	}
	bool man::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool man::GetMovingRight()
	{
		return isMovingRight;
	}

	bool man::Getleft()
	{
		return left;
	}

	bool man::Getright()
	{
		return right;
	}

	void man::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void man::Setfly(bool flag)
	{
		fly = flag;
		if (fly && velocity <= 1) rising = true;
	}

	void man::jumpsound()
	{
		CAudio::Instance()->Play(3,false);
	}

	void man::DeleteBullet()
	{
		///////////////////////////////////////刪除子彈//////////////////////////////
		int shootnum = (int)shoot.size();
		for (int i=0; i < shootnum; i++)
		{
			delete shoot[0];
			shoot.erase(shoot.begin());
		}
		////////////////////////////////////////////////////////////////////////////
	}

	int man::GetBullet()
	{
		return shoot.size();
	}

	int man::GetDamage()
	{
		return damage;
	}

	void man::AddDamage()
	{
		damage +=1;
	}

	void man::SetCombodelay()
	{
		combodelay = 5;
	}

	void man::OnShow()
	{
		///////////////////////////////////////////////////////////////////顯示角色/////////////////////////////////////////////////
		if   (animation.GetCurrentBitmapNumber() > 0 && animation.GetCurrentBitmapNumber() < 8) animation.SetTopLeft(x-19, y);//修正座標
		else if (animation.GetCurrentBitmapNumber() > 18 && animation.GetCurrentBitmapNumber() < 23) animation.SetTopLeft(x, y-12);//修正座標
		else 	animation.SetTopLeft(x, y);
		animation.OnShow();
	}
	void man::OnShow(int i)
	{
		///////////////////////////////////////////////////////////////////顯示角色/////////////////////////////////////////////////
		animation.SetTopLeft(x, y);
		animation.OnShow();
		///////////////////////////////////////////////////////////////////顯示子彈/////////////////////////////////////////////////
		if (shoot.size() != 0) {
			for (int count = 0; count < this->GetBullet(); count++) {
				shoot[count]->OnShow();
			}
		}
		///////////////////////////////////////////////////////////////////顯示能量條/////////////////////////////////////////////////
		MagicBar.SetTopLeft(MagicX, MagicY);
		MagicBar.ShowBitmap();
		for (int i = 0; i < 100 - magic; i++)
		{
			if (characteristic == "ice")
			{
				Black.SetTopLeft(MagicX + (2 * i), MagicY + 1);
				Black.ShowBitmap();
			}
			if (characteristic == "fire")
			{
				Black.SetTopLeft(MagicX +200 - (2 * i), MagicY + 1);
				Black.ShowBitmap();
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}