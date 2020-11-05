#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "EnemyAI.h"

namespace game_framework {
	EnemyAI::EnemyAI()
	{
		unsigned seed;
		seed = (unsigned)time(NULL); // 取得時
		srand(seed); // 以時間序列當亂數種子
		times = 0;
		times = rand() % 75;
		Diedelay = 30;
	}
	EnemyAI::~EnemyAI()
	{
		int num = (int)shoot.size();
		for (int i = 0; i < num; i++)
		{
			delete shoot[0];
			shoot.erase(shoot.begin());
		}
	}
	int EnemyAI::GetX1()
	{
		///////////////////////////////////////////////////////圖片x座標修正///////////////////////////////////////////////
		if (direction == 1) return x;
		return x + (StandWidth - animation.Width()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int EnemyAI::GetY1()
	{
		///////////////////////////////////////////////////////圖片y座標修正///////////////////////////////////////////////
		return y + (StandHeight - animation.Height()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int EnemyAI::GetX2()
	{
		return GetX1() + animation.Width() * 2;
	}
	int EnemyAI::GetY2()
	{
		return GetY1() + animation.Height() * 2;
	}
	void EnemyAI::SetonFloor()
	{
		y = floor - StandHeight * 2;
	}
	void EnemyAI::OnMove()
	{
		animation.SetDelayCount(1);
		//////////////被攻擊/////////////////////////
		if (isAttacked && !isDie && !isSkill) Attacked();
		else if (Move)
		{
			////////////////////////////////////////使用技能、攻擊、集氣、移動、跳躍、恢復查克拉/////////////////////////////////////////////////////////
			if (attacknum > 0) Attack();
			else if (isThrow&&GetY2() >= floor) Throw();
			else if (isMovingLeft || isMovingRight || isMovingUp) MovePlayer();
			else Stand();
			if(!Player->GetSkillsuccess())jump();
			///////////////////////////////////////////////////////////////////////////////////////////////
		}
		///////////////////////////////倒地///////////////////////////////////////////
		if (isDie && !isSkill) Die();
		//////////////////////////////投擲物移動/////////////////////////////////////
		if (shoot.size() != 0) 
		{
			for (int count = 0; count < (int)shoot.size(); count++) 
			{
				shoot[count]->Move();
				if ((shoot[count]->GetX2() < 0 && direction==0) || (shoot[count]->GetX1() > 640 && direction == 1))
				{
					delete shoot[count];
					shoot.erase(shoot.begin() + count);
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::jump()
	{
		////////////////////////////////////////////跳躍///////////////////////////////////////////
		if (rising)  			// 上升狀態
		{
			if (velocity > 0)
			{
				y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity -= 2;
			}
			else
			{
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else  				// 下降狀態
		{
			if (GetY2() < floor)  // 當y座標還沒碰到地板
			{
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity += 2;
				if (attacknum == 0) animation.Movetonum(JumpStart + direction * Total);
			}
			else
			{
				y = floor - StandHeight*2;  // 當y座標低於地板，更正為地板上
				velocity = initial_velocity; // 重設上升初始速度
				if (isMovingUp && attacknum == 0)
				{
					Move = false;
					////////////////////////跳躍結束動作/////////////////////////////
					if (!(animation.GetCurrentBitmapNumber() >= JumpStart+2 + direction * Total && animation.GetCurrentBitmapNumber() <= JumpNum + JumpStart + direction * Total))animation.Movetonum(JumpStart+2 + direction * Total);
					else animation.OnMove();
					if (animation.GetCurrentBitmapNumber() == JumpNum + JumpStart +1 + direction * Total)
					{
						Move = true;
						isMovingUp = false;
					}
					//////////////////////////////////////////////////////
				}
			}
		}
	}
	void EnemyAI::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void EnemyAI::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void EnemyAI::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void EnemyAI::SetDirection(int flag)
	{
		direction = flag;
	}
	void EnemyAI::SetAttacked(int flag)
	{
		if(!isDie) isAttacked = flag;
	}
	void EnemyAI::SetDie(int _direction)
	{
		direction = _direction;
		CAudio::Instance()->Play(29);
		isDie = true;
	}
	void EnemyAI::SetSkillsuccess()
	{
		Skillsuccess = true;
	}
	bool EnemyAI::GetSkillsuccess()
	{
		return Skillsuccess;
	}
	int EnemyAI::GetDirection()
	{
		return direction;
	}
	bool EnemyAI::GetMovingLeft()
	{
		return isMovingLeft;
	}
	bool EnemyAI::GetMovingRight()
	{
		return isMovingRight;
	}
	void EnemyAI::SetXY(int nx, int ny)
	{
		x = nx, y = ny;
	}
	void EnemyAI::SetisShow(bool flag)
	{
		isShow = flag;
	}
	bool EnemyAI::GetMove()
	{
		return Move;
	}
	void EnemyAI::Addattacknum()
	{
		attacknum++;
	}
	bool EnemyAI::GetAttack()
	{
		return isAttack;
	}
	bool EnemyAI::GetDie()
	{
		return isDie;
	}
	bool EnemyAI::GetAttacked()
	{
		return isAttacked;
	}
	int EnemyAI::Getblood()
	{
		return Blood;
	}
	int EnemyAI::Setblood(int _blood)
	{
		return Blood = _blood;
	}
	int EnemyAI::GetAttacknum()
	{
		return attacknum;
	}
	int EnemyAI::GetCurrentBitmapNumber()
	{
		return animation.GetCurrentBitmapNumber();
	}
	void EnemyAI::SetSasukeX(int x)
	{
		SasukeX = x;
	}
	void EnemyAI::SetMove(bool flag)
	{
		Move = flag;
	}
	vector<Shurikan*> EnemyAI::GetShurikan()
	{
		return shoot;
	}
	CAnimation EnemyAI::GetSkillMovie()
	{
		return SkillMovie;
	}
	CAnimation * EnemyAI::GetSkillsuccessMovie()
	{
		return &SkillsuccessMovie;
	}
	void EnemyAI::SetShurikanDelete(int flag)
	{
		delete shoot[flag];
		shoot.erase(shoot.begin() + flag);
	}
	bool EnemyAI::GetisSkill()
	{
		return isSkill;
	}
	void EnemyAI::SetPlayer(Sasuke *_player)
	{
		Player = _player;
	}
	skillstart* EnemyAI::Getskillstart()
	{
		return &Movie;
	}
	void EnemyAI::Attack()
	{
		/////////////////////////////////////////////////攻擊動畫//////////////////////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= AttackStart + direction * Total && animation.GetCurrentBitmapNumber() < AttackStart + AttackNum + direction * Total))
			animation.Movetonum(AttackStart + direction * Total);
		else
			animation.OnMove();
		if (animation.GetCurrentBitmapNumber() == AttackStart + AttackNum + direction * Total) 
		{
			attacknum = 0;
			Skill = rand() % 10;
			isAttack = false;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::Attacked()
	{
		/////////////////////////////////////////////////////////////被攻擊////////////////////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= HurtStart + direction * Total && animation.GetCurrentBitmapNumber() < HurtStart + HurtNum + direction * Total))
		{
			animation.Movetonum(HurtStart + direction * Total);
			CAudio::Instance()->Play(29);
		}
		else
			animation.OnMove();
		/////////////////////////////////////////////////////////////角色擊退////////////////////////////////////////////////////////////
		if (direction == 0 && GetX2() + 4 <= 640) x += 4;
		else if (direction == 1 && GetX1() - 4 >= 0)x -= 4;
		/////////////////////////////////////////////////////////////減少血量////////////////////////////////////////////////////////////
		if (animation.GetCurrentBitmapNumber() == HurtStart + HurtNum + direction * Total) isAttacked = false;
		if (Blood > 0) Blood -= 2;
		attacknum = 0;
		isAttack = false;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::Throw()
	{
		////////////////////////////////////////////////////////////丟擲物品/////////////////////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= ThrowStart + direction * Total && animation.GetCurrentBitmapNumber() < ThrowStart + ThrowNum + direction * Total))
			animation.Movetonum(ThrowStart + direction * Total);
		else
			animation.OnMove();
		if (animation.GetCurrentBitmapNumber() == ThrowStart + ThrowNum + direction * Total)
		{
			shoot.push_back(new Shurikan(this->GetX1(), (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), direction));//新增一個Shurikan
			isThrow = false;
			Skill = rand() % 10;//重新選擇一項攻擊方式
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::MovePlayer()
	{
		////////////////////////////////////////////////////左移////////////////////////////////////////////////
		if (isMovingLeft)
		{
			if (GetX1() > 0)
				x -= step_size;
			if (GetY2() >= floor)
			{
				if (!(animation.GetCurrentBitmapNumber() >= RunStart + direction * Total && animation.GetCurrentBitmapNumber() < RunStart + RunNum + direction * Total))
				{
					animation.Movetonum(RunStart + direction * Total);
				}
				else
				{
					animation.OnMove();
				}
			}
			direction = 0;
		}
		////////////////////////////////////////////////////右移////////////////////////////////////////////////
		else if (isMovingRight)
		{
			if (GetX2() < 640)
				x += step_size;
			if (GetY2() >= floor)
			{
				if (!(animation.GetCurrentBitmapNumber() >= RunStart + direction * Total && animation.GetCurrentBitmapNumber() < RunStart + RunNum + direction * Total))
				{
					animation.Movetonum(RunStart + direction * Total);
				}
				else
				{
					animation.OnMove();
				}
			}
			direction = 1;
		}
	}
	void EnemyAI::Die()
	{
		////////////////////////////////////人物倒地/////////////////////////////////////////////////////////////
		Move = false;
		if (animation.GetCurrentBitmapNumber() < DieStart + direction * Total || animation.GetCurrentBitmapNumber() > DieStart + DieNum + direction * Total)	animation.Movetonum(DieStart + direction * Total);
		if (animation.GetCurrentBitmapNumber() >= DieStart + 12 + direction * Total && animation.GetCurrentBitmapNumber() <= DieStart + 17 + direction * Total)
		{
			velocity -= 3;
			if (GetY2() < floor) y -= velocity;// 當後半段動畫角色從空中落下
		}
		if (animation.GetCurrentBitmapNumber() >= DieStart + direction * Total && animation.GetCurrentBitmapNumber() <= DieStart + 5 + direction * Total)
		{
			y -= velocity;// 當前半段動畫角色被擊飛至空中
			velocity -= 3;
		}
		if (animation.GetCurrentBitmapNumber() >= DieStart + direction * Total && animation.GetCurrentBitmapNumber() <= DieStart + 17 + direction * Total)
		{
			////////////////////////////////////////角色往後飛////////////////////////////////
			if (direction == 0 && GetX2() + 7 <= 640) x += 7;
			else if (direction == 1 && GetX1() - 7 >= 0) x -= 7;
			////////////////////////////////////////////////////////////////////////////////////
		}
		if (GetY2() < floor)  y -= velocity;//////////////////確保不超過地面且到達地面
		if (animation.GetCurrentBitmapNumber() == DieStart + 18 + direction * Total) CAudio::Instance()->Play(30);
		if (animation.GetCurrentBitmapNumber() == DieStart + DieNum + direction * Total)
		{
			//////////////////////////////倒地延遲////////////////////////////////
			if (Diedelay-- <= 0)
			{
				isDie = false;
				Move = true;
				isAttacked = false;
				SkillMovie.Reset();
				Diedelay = 30;
				velocity = initial_velocity;
				y = floor - StandHeight * 2;
				attacknum = 0;
			}
			//////////////////////////////////////////////////////////////////////
		}
		else animation.OnMove();
		/////////////////////////////////減少血量/////////////////////////////////////
		if (Blood > 0 && delay-- <= 0 && animation.GetCurrentBitmapNumber() != DieStart + DieNum + direction * Total)
		{
			Blood -= 2;
			delay = 2;
		}
		///////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::Stand()
	{
		/////////////////////////////////站在原地////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= StandStart + direction * Total && animation.GetCurrentBitmapNumber() < StandStart + StandNum + direction * Total))
			animation.Movetonum(StandStart + direction * Total);
		else
			animation.OnMove();
		//////////////////////////////////////////////////////////////////////////////////////
	}
	void EnemyAI::SetSkill()
	{
		Skill = 9;//demo用
	}
	void EnemyAI::SetSkill2()
	{
		Skill = 8;//demo用
	}
}
