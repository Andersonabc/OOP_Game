#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Shikamaru.h"

namespace game_framework {
	Shikamaru::Shikamaru()
	{
		Initialize();
	}
	Shikamaru::~Shikamaru()
	{
	}
	void Shikamaru::AttackMovie()
	{	
		/////////////////////////////////////////////////////////////播放技能動畫///////////////////////////////////////////////
		if (Movie.isStart())
		{
			Movie.OnMove();
			Player->SetMove(false);
		}
		////////////////////////////////////////////////////////////技能判定/////////////////////////////////////////////////////
		if (!Movie.isStart())
		{
			if (!Skillsuccess) { SkillMovie.OnMove(); Player->SetMove(true); }
			else RunSkillsuccessMovie();
			if (SkillMovie.GetCurrentBitmapNumber() == 26 + direction * 27)
			{
				Move = true;
				isSkill = false;
				Movieflag = false;
				isDie = false;
				isAttacked = false;
				Skill = rand() % 10;//重新選擇攻擊方式
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Shikamaru::RunSkillsuccessMovie()
	{
		/////////////////////////////////////////////////////////////技能成功/////////////////////////////////////////////////////
		if (SkillsuccessMovie.GetCurrentBitmapNumber() == 0+direction*43 && picy < 460) 
		{
			picy += 20;//井野從空中落下
		}
		//////////////////////////////////////////////////////////////井野攻擊////////////////////////////////////////////////////
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 20 + direction * 43 || SkillsuccessMovie.GetCurrentBitmapNumber() == 29 + direction * 43)
		{
			shoot.push_back(new Shurikan(picx, picy- SkillsuccessMovie.Height(), direction));
			SkillsuccessMovie.OnMove();
		}
		//////////////////////////////////////////////////////////////丁次落下//////////////////////////////////////////////////
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 38 + direction * 43 && picy < 600)
		{
			picy += 20;
		}
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 38 + direction * 43 && picy >= 600)
		{
			SetpicXY();
			SkillsuccessMovie.OnMove();
		}
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() > 38 + direction * 43)
		{
			if (SkillsuccessMovie.GetCurrentBitmapNumber() == 42 + direction * 43) SkillsuccessMovie.Movetonum(39+ direction * 43);
			else SkillsuccessMovie.OnMove();
			if (picy < 460 && Skilldelay>=0)
			{
				picy += 20;
				picx -= SasukeDistance;
			}
			if (picy == 460) Player->SetAttacked(true);
			if (Skilldelay-- <= 0)
			{
				picy -= 20;//丁次離開
				picx -= SasukeDistance*2;
			}
			///////////////////////////////////技能結束///////////////////////////////
			if (Skilldelay <= 0 && picy<0)
			{
				Skillsuccess = false;
				isSkill = false;
				Move = true;
				Movieflag = false;
				isDie = false;
				isAttacked = false;
				Skilldelay = 33;
				SkillsuccessMovie.Reset();
				Player->SetDie();
				Skill = rand() % 10;
			}
		}
		else SkillsuccessMovie.OnMove();
		SkillsuccessMovie.SetTopLeft(picx, picy - SkillsuccessMovie.Height()*2);
	}
	int Shikamaru::GetX1()
	{
		///////////////////////////////////////////////////////圖片x座標修正///////////////////////////////////////////////
		if (isSkill && direction == 0) return x + (StandWidth - SkillMovie.Width()) * 2;
		if (direction == 1) return x;
		return x + (StandWidth - animation.Width()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Shikamaru::GetY1()
	{
		///////////////////////////////////////////////////////圖片y座標修正///////////////////////////////////////////////
		if (isSkill) return y + (StandHeight - SkillMovie.Height()) * 2 + 30;
		return y + (StandHeight - animation.Height()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Shikamaru::GetX2()
	{
		if (isSkill) return GetX1() + SkillMovie.Width() * 2;
		return GetX1() + animation.Width() * 2;
	}
	int Shikamaru::GetY2()
	{
		if (isSkill) return GetY1() + SkillMovie.Height() * 2 - 30;
		return GetY1() + animation.Height() * 2;
	}
	void Shikamaru::Initialize()
	{
		////////////////////////////////////////////////////////初始化///////////////////////////////////////////////////////////////////////
		floor = 460;
		const int X_POS = 500;
		const int Y_POS = 460 - 39;
		const int INITIAL_VELOCITY = 18;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		x = X_POS;
		y = Y_POS;
		isThrow=Movieflag=Skillsuccess=isSkill=Wall=isAttack=isDie = isShooting = isAttacked = rising = isMovingLeft = isMovingRight = isMovingUp= false;
		step_size = 10;
		Move =isShow= true;
		attacknum = direction = 0;
		StandHeight = 42;
		StandWidth = 21;
		Total = 89, StandStart = 0, StandNum = 26, RunStart = 27, RunNum = 5, JumpStart = 33, JumpNum = 4; AttackStart = 38; AttackNum = 8, ThrowStart = 47, ThrowNum = 8,HurtStart=56,HurtNum=2,DieStart=59,DieNum=29;
		distance = 200;
		Playerdirection = 1;
		Blood = 128;
		delay = 2;
		Skilldelay = 33;
		Skill = rand() % 10;
		_direction = _distance = 1;
		Diedelay = 30;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Shikamaru::UI(bool Hit)
	{
		///////////////////////////////////////////////////依照對方位置決定面向哪裡/////////////////////////////////////////////////////////
		if (Player->GetX2() < GetX1())
		{
			if (!GetAttack() && !GetAttacked() && !GetDie() && !GetisSkill() && GetAttacknum() == 0)
			{
				_direction = 1;
				SetDirection(0);
			}
		}
		else if (Player->GetX1() > GetX2())
		{
			if (!GetAttack() && !GetAttacked() && !GetDie() && !GetisSkill() && GetAttacknum() == 0)
			{
				_direction = 0;
				SetDirection(1);
			}
		}
		if (_direction == 0) _distance = Player->GetX2() - GetX1();
		else _distance = Player->GetX1() - GetX2();
		_distance = abs(_distance);
		/////////////////////////////////////////////////////判斷要移動的距離//////////////////////////////////////////////////////////////
		if (!isAttack) distance = 200 - _distance;
		if (!isAttack) Playerdirection = _direction;
		if (!Player->GetSkillsuccess())
		{
			if (isAttacked)
			{
				isSkill = false;
				Move = true;
				Movieflag = false;
			}
			/////////////////////////////////////////////////////技能施放///////////////////////////////////////////////////
			else if (Skill == 9 && times <= 0 && Move && distance < 190 || isSkill)
			{
				if (!Movieflag)
				{
					if (Player->GetX1() < GetX2()) direction = 0;
					else if (Player->GetX2() > GetX1()) direction = 1;
					SkillMovie.Movetonum(0 + direction * 27);
					Movieflag = true;
					Movie.Init();
					CAudio::Instance()->Play(31);
				}
				isMovingRight = false;
				isMovingLeft = false;
				isSkill = true;
				Move = false;
				AttackMovie();
				times = rand() % 75 + 30;
			}
			///////////////////////////////////////////////////////攻擊及移動判定/////////////////////////////////////////////
			else if (times <= 0 && Move)
			{
				if (distance < 200 || Wall)
				{
					//////////////////////////////////////////判斷是否走到牆壁/////////////////////////////////////////////////
					if (Playerdirection == 1 && GetX2() + distance >= 640&&!Wall)
					{
						Playerdirection = 0;
						distance += 200 - (GetX2() + distance - 640);//移動到另一邊
						Wall = true;
					}
					else if (Playerdirection == 0 && GetX1() - distance <= 0&& !Wall)
					{
						Playerdirection = 1;
						distance += 200 + (GetX1() - distance);
						Wall = true;
					}
					//////////////////////////////////////與佐助拉開200的距離///////////////////////////////////////////////////
					if (Playerdirection == 1)
					{
						isMovingRight = true;
						isMovingLeft = false;
						distance -= 7;
					}
					else
					{
						isMovingLeft = true;
						isMovingRight = false;
						distance -= 7;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				isAttack = true;
				/////////////////////////////////////////////攻擊///////////////////////////////////////////////////////////////////////
				if (distance <= 0)
				{
					isMovingRight = false;
					isMovingLeft = false;
					if (_direction == 1) direction = 0;
					else direction = 1;
					isThrow = true;
					times = rand() % 75 + 30;
					isAttack = false;
					Wall = false;
				}
				////////////////////////////////////////////////////////////////////////////////////////////
			}
			/////////////////////////////////////////////////////////技能擊中判定///////////////////////////////////////////////////////
			if (!Player->GetisMolding() && !Player->GetisSkill() && GetisSkill() && Hit && GetSkillMovie().GetCurrentBitmapNumber() > 7 + GetDirection() * 27 && GetSkillMovie().GetCurrentBitmapNumber() < 17 + GetDirection() * 27 && !GetSkillsuccess())
			{
				SetpicXY();
				SetSasukeX((Player->GetX1() + Player->GetX2()) / 2);
				Player->SetMove(false);
				SetSkillsuccess();
				SetSasukeDistance();
				GetSkillsuccessMovie()->Movetonum(0 + GetDirection() * 43);
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (Move) times--;
		}
	}
	void Shikamaru::SetpicXY()
	{
		if (direction == 0) picx = GetX2() + 20;
		if (direction == 1) picx = GetX1() - 20;
		picy = 0;
	}
	void Shikamaru::SetSasukeDistance()
	{
		SasukeDistance = (picx + SkillMovie.Width() - SasukeX)/23;
	}
	void Shikamaru::OnShow()
	{
		//////////////////////////////////////////////顯示//////////////////////////////////////////////////////////
		for (int count = 0; count < (int)shoot.size(); count++) shoot[count]->OnShow();
		if (!isSkill)
		{
			animation.SetTopLeft(GetX1(), GetY1());
			animation.OnShow(2);
		}
		else
		{
			SkillMovie.SetTopLeft(GetX1(), GetY1() - 30);
			SkillMovie.OnShow(2);
		}
		if (Skillsuccess) SkillsuccessMovie.OnShow(2);
	}
	void Shikamaru::LoadBitmap()
	{
		////////////////////////////////////////////////////////////讀取圖片//////////////////////////////////////////
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//0
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand1, RGB(255, 100, 100));		//5
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//6
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//10
		animation.AddBitmap(Shikamarustand2, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//5
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//6
		animation.AddBitmap(Shikamarustand3, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//20
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//5
		animation.AddBitmap(Shikamarustand4, RGB(255, 100, 100));		//6
		animation.AddBitmap(ShikamaruRun1, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruRun1, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruRun1, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruRun2, RGB(255, 100, 100));			//30
		animation.AddBitmap(ShikamaruRun2, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruRun2, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruJump1, RGB(255, 100, 100));		//3
		animation.AddBitmap(ShikamaruJump2, RGB(255, 100, 100));		//4
		animation.AddBitmap(ShikamaruJump1, RGB(255, 100, 100));		//5
		animation.AddBitmap(ShikamaruJump1, RGB(255, 100, 100));		//6
		animation.AddBitmap(ShikamaruJump1, RGB(255, 100, 100));		//7
		animation.AddBitmap(ShikamarujumpKick1, RGB(255, 100, 100));	//8
		animation.AddBitmap(ShikamarujumpKick1, RGB(255, 100, 100));	//9
		animation.AddBitmap(ShikamarujumpKick1, RGB(255, 100, 100));	//40
		animation.AddBitmap(ShikamarujumpKick2, RGB(255, 100, 100));	//1
		animation.AddBitmap(ShikamarujumpKick2, RGB(255, 100, 100));	//2
		animation.AddBitmap(ShikamarujumpKick2, RGB(255, 100, 100));	//3
		animation.AddBitmap(ShikamarujumpKick3, RGB(255, 100, 100));	//4
		animation.AddBitmap(ShikamarujumpKick3, RGB(255, 100, 100));	//5
		animation.AddBitmap(ShikamarujumpKick3, RGB(255, 100, 100));	//6
		animation.AddBitmap(Shikamaruthrow1, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamaruthrow1, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamaruthrow1, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamaruthrow2, RGB(255, 100, 100));		//50
		animation.AddBitmap(Shikamaruthrow2, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamaruthrow2, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamaruthrow3, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamaruthrow3, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamaruthrow3, RGB(255, 100, 100));		//5
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//60
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//3
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//4
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie1, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//70
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//3
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//4
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie2, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruDie3, RGB(255, 100, 100));			//80
		animation.AddBitmap(ShikamaruDie3, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruDie4, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruDie4, RGB(255, 100, 100));			//3
		animation.AddBitmap(ShikamaruDie5, RGB(255, 100, 100));			//4
		animation.AddBitmap(ShikamaruDie5, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie6, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie6, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie7, RGB(255, 100, 100));			//8
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//89
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//90
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand5, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//5
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//6
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamarustand6, RGB(255, 100, 100));		//100
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//5
		animation.AddBitmap(Shikamarustand7, RGB(255, 100, 100));		//6
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//110
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//4
		animation.AddBitmap(Shikamarustand8, RGB(255, 100, 100));		//5
		animation.AddBitmap(ShikamaruRun3, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruRun3, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruRun3, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruRun4, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruRun4, RGB(255, 100, 100));			//120
		animation.AddBitmap(ShikamaruRun4, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruJump3, RGB(255, 100, 100));		//2
		animation.AddBitmap(ShikamaruJump4, RGB(255, 100, 100));		//3
		animation.AddBitmap(ShikamaruJump3, RGB(255, 100, 100));		//4
		animation.AddBitmap(ShikamaruJump3, RGB(255, 100, 100));		//5
		animation.AddBitmap(ShikamaruJump3, RGB(255, 100, 100));		//6
		animation.AddBitmap(ShikamarujumpKick4, RGB(255, 100, 100));	//7
		animation.AddBitmap(ShikamarujumpKick4, RGB(255, 100, 100));	//8
		animation.AddBitmap(ShikamarujumpKick4, RGB(255, 100, 100));	//9
		animation.AddBitmap(ShikamarujumpKick5, RGB(255, 100, 100));	//130
		animation.AddBitmap(ShikamarujumpKick5, RGB(255, 100, 100));	//1
		animation.AddBitmap(ShikamarujumpKick5, RGB(255, 100, 100));	//2
		animation.AddBitmap(ShikamarujumpKick6, RGB(255, 100, 100));	//3
		animation.AddBitmap(ShikamarujumpKick6, RGB(255, 100, 100));	//4
		animation.AddBitmap(ShikamarujumpKick6, RGB(255, 100, 100));	//5
		animation.AddBitmap(Shikamaruthrow4, RGB(255, 100, 100));		//6
		animation.AddBitmap(Shikamaruthrow4, RGB(255, 100, 100));		//7
		animation.AddBitmap(Shikamaruthrow4, RGB(255, 100, 100));		//8
		animation.AddBitmap(Shikamaruthrow5, RGB(255, 100, 100));		//9
		animation.AddBitmap(Shikamaruthrow5, RGB(255, 100, 100));		//140
		animation.AddBitmap(Shikamaruthrow5, RGB(255, 100, 100));		//1
		animation.AddBitmap(Shikamaruthrow6, RGB(255, 100, 100));		//2
		animation.AddBitmap(Shikamaruthrow6, RGB(255, 100, 100));		//3
		animation.AddBitmap(Shikamaruthrow6, RGB(255, 100, 100));		//4
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//150
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//3
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//4
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie8, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//9
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//160
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//1
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//2
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//3
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//4
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//5
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//6
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//7
		animation.AddBitmap(ShikamaruDie9, RGB(255, 100, 100));			//8
		animation.AddBitmap(ShikamaruDie10, RGB(255, 100, 100));		//9
		animation.AddBitmap(ShikamaruDie10, RGB(255, 100, 100));		//170
		animation.AddBitmap(ShikamaruDie11, RGB(255, 100, 100));		//1
		animation.AddBitmap(ShikamaruDie11, RGB(255, 100, 100));		//2
		animation.AddBitmap(ShikamaruDie12, RGB(255, 100, 100));		//3
		animation.AddBitmap(ShikamaruDie12, RGB(255, 100, 100));		//4
		animation.AddBitmap(ShikamaruDie13, RGB(255, 100, 100));		//5
		animation.AddBitmap(ShikamaruDie13, RGB(255, 100, 100));		//6
		animation.AddBitmap(ShikamaruDie14, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//0
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill2, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill2, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill2, RGB(255, 100, 100));		//5
		SkillMovie.AddBitmap(ShikamaruSkill2, RGB(255, 100, 100));		//6
		SkillMovie.AddBitmap(ShikamaruSkill2, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//8
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//9
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//10
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//5
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//6
		SkillMovie.AddBitmap(ShikamaruSkill3, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//8
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//9
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//20
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//5
		SkillMovie.AddBitmap(ShikamaruSkill1, RGB(255, 100, 100));		//6
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//8
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//9
		SkillMovie.AddBitmap(ShikamaruSkill21, RGB(255, 100, 100));		//30
		SkillMovie.AddBitmap(ShikamaruSkill21, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill21, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill21, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill21, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//5
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//6
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//8
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//9
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill22, RGB(255, 100, 100));		//5
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//6
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//7
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//8
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//9
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//1
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//2
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//3
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//4
		SkillMovie.AddBitmap(ShikamaruSkill20, RGB(255, 100, 100));		//5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill4, RGB(255, 100, 100));	 //0
		SkillsuccessMovie.AddBitmap(ShikamaruSkill5, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill5, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill5, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill6, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill6, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill6, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill7, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill7, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill7, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill8, RGB(255, 100, 100));	 //10
		SkillsuccessMovie.AddBitmap(ShikamaruSkill8, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill8, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill9, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill9, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill9, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill10, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill10, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill10, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill11, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill11, RGB(255, 100, 100));	 //20
		SkillsuccessMovie.AddBitmap(ShikamaruSkill11, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill12, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill12, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill12, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill13, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill13, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill13, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill14, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill14, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill14, RGB(255, 100, 100));	 //30
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill15, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill4, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill16, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill17, RGB(255, 100, 100));	 //40
		SkillsuccessMovie.AddBitmap(ShikamaruSkill18, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill19, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill23, RGB(255, 100, 100));	 //0
		SkillsuccessMovie.AddBitmap(ShikamaruSkill24, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill24, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill24, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill25, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill25, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill25, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill26, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill26, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill26, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill27, RGB(255, 100, 100));	 //10
		SkillsuccessMovie.AddBitmap(ShikamaruSkill27, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill27, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill28, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill28, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill28, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill29, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill29, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill29, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill30, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill30, RGB(255, 100, 100));	 //20
		SkillsuccessMovie.AddBitmap(ShikamaruSkill30, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill31, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill31, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill31, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill32, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill32, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill32, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill33, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill33, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill33, RGB(255, 100, 100));	 //30
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //2
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //3
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //4
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //5
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //6
		SkillsuccessMovie.AddBitmap(ShikamaruSkill34, RGB(255, 100, 100));	 //7
		SkillsuccessMovie.AddBitmap(ShikamaruSkill23, RGB(255, 100, 100));	 //8
		SkillsuccessMovie.AddBitmap(ShikamaruSkill16, RGB(255, 100, 100));	 //9
		SkillsuccessMovie.AddBitmap(ShikamaruSkill17, RGB(255, 100, 100));	 //40
		SkillsuccessMovie.AddBitmap(ShikamaruSkill18, RGB(255, 100, 100));	 //1
		SkillsuccessMovie.AddBitmap(ShikamaruSkill19, RGB(255, 100, 100));	 //2
		Movie.LoadBitmap(ShikamaruSkillUI, RGB(255, 100, 100));
		SkillsuccessMovie.SetDelayCount(1);									 
		SkillsuccessMovie.Reset();											 
		SkillMovie.SetDelayCount(1);									  
		SkillMovie.Reset();												
	}																	  
}																		  