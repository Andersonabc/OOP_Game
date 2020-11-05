#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Orochimaru.h"

namespace game_framework {
	Orochimaru::Orochimaru()
	{
		Initialize();
	}
	Orochimaru::~Orochimaru()
	{
	}
	int Orochimaru::GetX1()
	{
		///////////////////////////////////////////////////////圖片x座標修正///////////////////////////////////////////////
		if (isSkill || isSkill2) return picx;
		if (direction == 1) return x;
		return x + (StandWidth - animation.Width()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Orochimaru::GetY1()
	{
		///////////////////////////////////////////////////////圖片y座標修正///////////////////////////////////////////////
		if (isSkill || isSkill2) return picy;
		return y + (StandHeight - animation.Height()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Orochimaru::GetX2()
	{
		if (isSkill || isSkill2) return GetX1() + SkillMovie.Width() * 2;
		return GetX1() + animation.Width() * 2;
	}
	int Orochimaru::GetY2()
	{
		if (isSkill || isSkill2) return GetY1() + SkillMovie.Height() * 2;
		return GetY1() + animation.Height() * 2;
	}
	void Orochimaru::AttackMovie()
	{
		/////////////////////////////////////////////////////////////播放技能動畫///////////////////////////////////////////////
		if (Movie.isStart())
		{
			Movie.OnMove();
			Player->SetMove(false);
			picy = 160;
			if (direction == 0) picx = 980;//設定蛇出來的起始位置
			else picx = -300;			
			SkillMovie.Movetonum(1+direction * 2);//蛇咬
		}
		////////////////////////////////////////////////////////////技能判定/////////////////////////////////////////////////////
		if (!Movie.isStart())
		{
			if (!Skillsuccess) 
			{
				if (direction == 0) picx -= 20;
				else picx += 20;
				Player->SetMove(true); 
			}
			else
				 RunSkillsuccessMovie();
			///////////////////////////////////////////////////////超過技能範圍//////////////////////////////////////////////////
			if (!Skillsuccess && (direction==0 && picx+SkillMovie.Width()*2<=640) || (direction == 1 && picx >= 0))
			{
				Return = true;
			}
			//////////////////////////////////////////////////////回頭///////////////////////////////////////////////////////////////
			if (!Skillsuccess && Return)
			{
				if (direction == 0) picx += 40;
				else picx -= 40;
			}
			///////////////////////////////////////////////////////////技能結束////////////////////////////////////////////////////
			if (Return && ((picx == 980 && direction == 0) || (picx == -300 && direction == 1)))
			{
				Move = true;
				isSkill = false;
				Movieflag = false;
				isDie = false;
				isAttacked = false;
				Return = false;
				SkillMovie.Reset();
				Skill = rand() % 10;
				picx = picy = -400;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Orochimaru::AttackMovie2()
	{
		/////////////////////////////////////////////////////////////播放技能動畫///////////////////////////////////////////////
		if (Movie.isStart())
		{
			Movie.OnMove();
			Player->SetMove(false);
			picy = 160;
			if (direction == 0) picx = 980;//設定蛇出來的起始位置
			else picx = -300;
			SkillMovie.Movetonum(0+direction*2);//蛇撞
		}
		////////////////////////////////////////////////////////////技能判定/////////////////////////////////////////////////////
		if (!Movie.isStart())
		{
			if (direction == 0) picx -= 20;
			else picx += 20;
			Player->SetMove(true);
			///////////////////////////////////////////////////////超過技能範圍//////////////////////////////////////////////////
			if ((direction == 0 && picx + SkillMovie.Width() * 2 <= 640) || (direction == 1 && picx >= 0))
			{
				Return = true;
			}
			//////////////////////////////////////////////////////回頭///////////////////////////////////////////////////////////////
			if (Return)
			{
				if (direction == 0) picx += 40;
				else picx -= 40;
			}
			///////////////////////////////////////////////////////////技能結束////////////////////////////////////////////////////
			if (Return && ((picx == 980 && direction == 0) || (picx == -300 && direction == 1)))
			{
				Move = true;
				isSkill2 = false;
				Movieflag = false;
				isDie = false;
				isAttacked = false;
				Return = false;
				Skillsuccess = false;
				SkillMovie.Reset();
				Skill = rand() % 10;
				picx = picy = -400;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
	void Orochimaru::RunSkillsuccessMovie()
	{
		/////////////////////////////////////////////////////////////技能成功/////////////////////////////////////////////////////
		if (SkillsuccessMovie.GetCurrentBitmapNumber() == 23)
		{
			Return = true;
			Skillsuccess = false;
			SkillsuccessMovie.Reset();
			Player->SetXY(SasukeX, SasukeY);
			Player->SetDie(2);
		}
		///////////////////////////////////////////////////////////技能結束回頭////////////////////////////////////////////////////
		else if ((direction == 0 && picx + SkillMovie.Width() * 2 >= 640) || (direction == 1 && picx <= 0))
		{
			if (direction == 0) picx -= 20;
			else picx += 20;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		SkillsuccessMovie.OnMove();
		if (SkillsuccessMovie.GetCurrentBitmapNumber() % 6 == 5) {Player->Attacked(); Player->SubBlood(3);}
		SkillsuccessMovie.SetTopLeft(picx, picy);
	}
	void Orochimaru::Initialize()
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
		isSkill2=Return=isThrow = Movieflag = Skillsuccess = isSkill = Wall = isAttack = isDie = isShooting = isAttacked = rising = isMovingLeft = isMovingRight = isMovingUp = false;
		step_size = 10;
		isShow = Move = true;
		attacknum = 0;
		direction = 0;
		StandHeight = 44;
		StandWidth = 22;
		Total = 123, StandStart = 0, StandNum = 8, RunStart = 9, RunNum = 23, JumpStart = 33, JumpNum = 0; AttackStart = 33; AttackNum = 53, ThrowStart = 87, ThrowNum = 0, HurtStart = 87, HurtNum = 2, DieStart = 93, DieNum = 29;
		distance = 200;
		Playerdirection = 1;
		Blood = 128;
		delay = 2;
		Skilldelay = 33;
		Skill = rand() % 10;
		Diedelay = 30;
		picx = picy = -400;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Orochimaru::UI(bool Hit)
	{
		///////////////////////////////////////////////////依照對方位置決定面向哪裡/////////////////////////////////////////////////////////
		if (!Player->GetisMolding() && !Player->GetisSkill() && Hit && !Player->GetisDie() && (GetCurrentBitmapNumber() == 38 + GetDirection() * 123 || GetCurrentBitmapNumber() == 53 + GetDirection() * 123 || GetCurrentBitmapNumber() == 74 + GetDirection() * 123))
		{
			Player->SetAttacked(true);
		}
		if (!Player->GetisMolding() && !Player->GetisSkill() && GetisSkill() && Hit && SkillMovie.GetCurrentBitmapNumber() == 1 && !GetSkillsuccess() && !Return)
		{
			Player->SetMove(false);
			SasukeX = Player->Getx();
			SasukeY = Player->Gety();
			Player->SetXY(-100, -100);
			SetSkillsuccess();
			GetSkillsuccessMovie()->Movetonum(0 + direction * 24);
		}
		if (!Player->GetisMolding() && !Player->GetisSkill() && GetisSkill() && Hit && SkillMovie.GetCurrentBitmapNumber() == 0 && !Player->GetisDie())
		{
			Player->SetMove(false);
			Player->SetDie(3);
		}
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
		/////////////////////////////////////////////////////判斷距離//////////////////////////////////////////////////////////////
		if (!isAttack) Playerdirection = _direction;
		if (Playerdirection == 0) _distance = Player->GetX1() - (x+StandWidth*2);
		else _distance = Player->GetX2() - x;
		_distance = abs(_distance);
		distance = _distance;
		/////////////////////////////////////////////////////技能1施放///////////////////////////////////////////////////
		if (!Player->GetSkillsuccess())
		{
			if (isAttacked)
			{
				isSkill = false;
				Move = true;
				Movieflag = false;
			}
			else if (Skill == 9 && times <= 0 && Move && distance < 190 || isSkill)
			{
				if (!Movieflag)
				{
					if (Player->GetX1() < GetX2()) direction = 0;
					else if (Player->GetX2() > GetX1()) direction = 1;
					SkillMovie.Movetonum(1);
					Movieflag = true;
					Movie.Init();
					CAudio::Instance()->Play(31);
					picx = picy = -400;
				}
				isMovingRight = false;
				isMovingLeft = false;
				isSkill = true;
				Move = false;
				AttackMovie();
				times = rand() % 75 + 30;
			}
			/////////////////////////////////////////////////////技能2施放///////////////////////////////////////////////////
			else if ((Skill == 8 || Skill == 7) &&times <= 0 && Move && distance < 190 || isSkill2)
			{
				if (!Movieflag)
				{
					if (Player->GetX1() < GetX2()) direction = 0;
					else if (Player->GetX2() > GetX1()) direction = 1;
					SkillMovie.Movetonum(0);
					Movieflag = true;
					Movie.Init();
					CAudio::Instance()->Play(31);
					picx = picy = -400;
				}
				isMovingRight = false;
				isMovingLeft = false;
				isSkill2 = true;
				Move = false;
				AttackMovie2();
				times = rand() % 75 + 30;
			}
			///////////////////////////////////////////////////////攻擊及移動判定/////////////////////////////////////////////
			else if (times <= 0 && Move)
			{
				TRACE("%d--------------\n", distance);
				if (distance <= 50)
				{
					isAttack = true;
					isMovingRight = false;
					isMovingLeft = false;
					attacknum = 1;
					times = rand() % 30;
					Wall = false;
				}
				else if (distance > 50)
				{
					if (Playerdirection == 1)
					{
						isMovingRight = false;
						isMovingLeft = true;
					}
					else
					{
						isMovingLeft = false;
						isMovingRight = true;
					}
				}
			}
			if (Move) times--;
		}
	}
	void Orochimaru::SetpicXY()
	{
	}
	void Orochimaru::OnShow()
	{
		//////////////////////////////////////////////顯示//////////////////////////////////////////////////////////
		if (!isSkill && !isSkill2)
		{
			animation.SetTopLeft(GetX1(), GetY1());
			animation.OnShow(2);
		}
		else if (!Skillsuccess)
		{
			SkillMovie.SetTopLeft(picx, picy);
			SkillMovie.OnShow(2);
		}
		if (Skillsuccess) SkillsuccessMovie.OnShow(2);
	}
	bool Orochimaru::GetisSkill()
	{
		return isSkill||isSkill2;
	}
	void Orochimaru::LoadBitmap()
	{
		////////////////////////////////////////////////////////////讀取圖片//////////////////////////////////////////
		animation.AddBitmap(OrochimaruStand1, RGB(255, 255, 255));		//0
		animation.AddBitmap(OrochimaruStand1, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruStand1, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruStand2, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruStand2, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruStand2, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruStand3, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruStand3, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruStand3, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruRun1, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruRun1, RGB(255, 255, 255));		//10
		animation.AddBitmap(OrochimaruRun1, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun2, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruRun2, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruRun2, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruRun3, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruRun3, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruRun3, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruRun4, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruRun4, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruRun4, RGB(255, 255, 255));		//20
		animation.AddBitmap(OrochimaruRun5, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun5, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruRun5, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruRun6, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruRun6, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruRun6, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruRun7, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruRun7, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruRun7, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruRun8, RGB(255, 255, 255));		//30
		animation.AddBitmap(OrochimaruRun8, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun8, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo1, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo1, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo1, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo2, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo2, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo2, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo3, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo3, RGB(255, 255, 255));		//40
		animation.AddBitmap(OrochimaruCombo3, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo4, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo4, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo4, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo5, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo5, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo5, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo6, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo6, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo6, RGB(255, 255, 255));		//50
		animation.AddBitmap(OrochimaruCombo7, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo7, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo7, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo8, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo8, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo8, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo9, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo9, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo9, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo10, RGB(255, 255, 255));		//60
		animation.AddBitmap(OrochimaruCombo10, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo10, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo11, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo11, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo11, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo12, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo12, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo12, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo13, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo13, RGB(255, 255, 255));		//70
		animation.AddBitmap(OrochimaruCombo13, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo14, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo14, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo14, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo15, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo15, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo15, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo16, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo16, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo16, RGB(255, 255, 255));		//80
		animation.AddBitmap(OrochimaruCombo17, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo17, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo17, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo18, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo18, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo18, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//90
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruHurt, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruDie1, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruDie1, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruDie1, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//100
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruDie2, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie3, RGB(255, 255, 255));		//110
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//120
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie4, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruStand4, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruStand4, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruStand4, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruStand5, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruStand5, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruStand5, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruStand6, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruStand6, RGB(255, 255, 255));		//130
		animation.AddBitmap(OrochimaruStand6, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun9, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruRun9, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruRun9, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruRun10, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruRun10, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruRun10, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruRun11, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruRun11, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruRun11, RGB(255, 255, 255));		//140
		animation.AddBitmap(OrochimaruRun12, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun12, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruRun12, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruRun13, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruRun13, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruRun13, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruRun14, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruRun14, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruRun14, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruRun15, RGB(255, 255, 255));		//150
		animation.AddBitmap(OrochimaruRun15, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruRun15, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruRun16, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruRun16, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruRun16, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo19, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo19, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo19, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo20, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo20, RGB(255, 255, 255));		//160
		animation.AddBitmap(OrochimaruCombo20, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo21, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo21, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo21, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo22, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo22, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo22, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo23, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo23, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo23, RGB(255, 255, 255));		//170
		animation.AddBitmap(OrochimaruCombo24, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo24, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo24, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo25, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo25, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo25, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo26, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo26, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo26, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo27, RGB(255, 255, 255));		//180
		animation.AddBitmap(OrochimaruCombo27, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo27, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo28, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo28, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo28, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo29, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo29, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo29, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo30, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo30, RGB(255, 255, 255));		//190
		animation.AddBitmap(OrochimaruCombo30, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo31, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo31, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo31, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo32, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo32, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo32, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo33, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo33, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruCombo33, RGB(255, 255, 255));		//200
		animation.AddBitmap(OrochimaruCombo34, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruCombo34, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruCombo34, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruCombo35, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruCombo35, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruCombo35, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruCombo36, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruCombo36, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruCombo36, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//210
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruHurt2, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie5, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie5, RGB(255, 255, 255));		//220
		animation.AddBitmap(OrochimaruDie5, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruDie6, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//230
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruDie7, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//5
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//6
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//7
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//8
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//9
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//240
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//1
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//2
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//3
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//4
		animation.AddBitmap(OrochimaruDie8, RGB(255, 255, 255));		//5
		SkillMovie.AddBitmap(OrochimaruSkill1, RGB(255, 255, 255));
		SkillMovie.AddBitmap(OrochimaruSkill2, RGB(255, 255, 255));
		SkillMovie.AddBitmap(OrochimaruSkill5, RGB(255, 255, 255));
		SkillMovie.AddBitmap(OrochimaruSkill6, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill3, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill4, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill7, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		SkillsuccessMovie.AddBitmap(OrochimaruSkill8, RGB(255, 255, 255));
		Movie.LoadBitmap(OrochimaruSkillUI, RGB(255, 255, 255));
		SkillMovie.SetDelayCount(1);
		SkillMovie.Reset();
		SkillsuccessMovie.SetDelayCount(1);
		SkillsuccessMovie.Reset();
	}
}
