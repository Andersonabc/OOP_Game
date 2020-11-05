#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Neji.h"

namespace game_framework {
	Neji::Neji()
	{
		Initialize();
	}
	Neji::~Neji()
	{
	}
	int Neji::GetX1()
	{
		///////////////////////////////////////////////////////圖片x座標修正///////////////////////////////////////////////
		if (isSkill && SkillMovie.GetCurrentBitmapNumber() >= 18 && SkillMovie.GetCurrentBitmapNumber() <= 38) return x + (StandWidth - SkillMovie.Width()) * 2 + 126;
		if (isSkill && SkillMovie.GetCurrentBitmapNumber() >= 57 && SkillMovie.GetCurrentBitmapNumber() <= 77) return x + (StandWidth - SkillMovie.Width()) * 2 + 160;
		if (isSkill && direction == 0) return x + (StandWidth - SkillMovie.Width()) * 2;
		if (direction == 1) return x;
		return x + (StandWidth - animation.Width()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Neji::GetY1()
	{
		///////////////////////////////////////////////////////圖片y座標修正///////////////////////////////////////////////
		if(isSkill && SkillMovie.GetCurrentBitmapNumber() >=18+direction*39 && SkillMovie.GetCurrentBitmapNumber()<=38+ direction *39) return y + (StandHeight - SkillMovie.Height()) * 2 + 64;
		if (isSkill) return y + (StandHeight - SkillMovie.Height()) * 2 + 30;
		return y + (StandHeight - animation.Height()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Neji::GetX2()
	{
		if (isSkill) return GetX1() + SkillMovie.Width() * 2;
		return GetX1() + animation.Width() * 2;
	}
	int Neji::GetY2()
	{
		if (isSkill) return GetY1() + SkillMovie.Height() * 2 - 30;
		return GetY1() + animation.Height() * 2;
	}
	void Neji::AttackMovie()
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
			if (SkillMovie.GetCurrentBitmapNumber() == 38 + direction * 39)
			{
				Move = true;
				isSkill = false;
				Movieflag = false;
				isDie = false;
				isAttacked = false;
				SkillMovie.Reset();
				Skill = rand() % 10;//重新選擇攻擊方式
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Neji::RunSkillsuccessMovie()
	{
		/////////////////////////////////////////////////////////////技能成功/////////////////////////////////////////////////////
		Player->SetDirection(direction);
		if (SkillsuccessMovie.GetCurrentBitmapNumber() == 11 + direction * 57) { Player->SetAttacked(true); }
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 17 + direction * 57) { Player->SetAttacked(true); }
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 32 + direction * 57) { Player->SetAttacked(true); }
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 44 + direction * 57) { Player->SetAttacked(true); }
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 50 + direction * 57) { Player->SetAttacked(true); }
		else if (SkillsuccessMovie.GetCurrentBitmapNumber() == 53 + direction * 57) { Player->SetAttacked(true); }
		if (SkillsuccessMovie.GetCurrentBitmapNumber() == 56 + direction * 57)
		{
			Skillsuccess = false;
			isSkill = false;
			Move = true;
			Movieflag = false;
			isDie = false;
			isAttacked = false;
			Skilldelay = 33;
			SkillsuccessMovie.Reset();
			SkillMovie.Reset();
			Player->SetDie();
			Skill = rand() % 10;//重新選擇攻擊方式
			isShow = true;
		}
		else SkillsuccessMovie.OnMove();
		SkillsuccessMovie.SetTopLeft(picx, picy - SkillsuccessMovie.Height() * 2);
		if(direction==0)picx -= 1;
		else picx += 1;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Neji::Initialize()
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
		isThrow=Movieflag = Skillsuccess = isSkill = Wall = isAttack = isDie = isShooting = isAttacked = rising = isMovingLeft = isMovingRight = isMovingUp = false;
		step_size = 10;
		isShow = Move = true;
		attacknum = 0;
		direction = 0;
		StandHeight = 35;
		StandWidth = 28;
		Total = 109, StandStart = 0, StandNum = 2, RunStart = 3, RunNum = 17, JumpStart = 21, JumpNum = 0, AttackStart = 22, AttackNum = 50, ThrowStart = 73, ThrowNum = -1, HurtStart = 73, HurtNum = 2, DieStart = 79, DieNum = 29;
		distance = 200;
		Playerdirection = 1;
		Blood = 128;
		delay = 2;
		Skilldelay = 33;
		Skill = rand() % 10;
		Diedelay = 30;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Neji::UI(bool Hit)
	{
		///////////////////////////////////////////////////依照對方位置決定面向哪裡/////////////////////////////////////////////////////////
		if ((Player->GetX2()-Player->GetX1())/2+Player->GetX1() < (GetX2()-GetX1())/2+GetX1())
		{
			if (!GetAttack() && GetAttacked()==0 && !GetDie() && !GetisSkill() && GetAttacknum() == 0)
			{
				_direction = 1;
				SetDirection(0);
			}
		}
		else if ((Player->GetX2() - Player->GetX1()) / 2 + Player->GetX1() > (GetX2() - GetX1()) / 2 + GetX2())
		{
			if (!GetAttack() && GetAttacked()==0 && !GetDie() && !GetisSkill() && GetAttacknum() == 0)
			{
				_direction = 0;
				SetDirection(1);
			}
		}
		/////////////////////////////////////////////////////判斷距離//////////////////////////////////////////////////////////////
		if (!isAttack) Playerdirection = _direction;
		if (Playerdirection == 0) _distance = Player->GetX1() - GetX2();
		else _distance = Player->GetX2() - GetX1();
		_distance = abs(_distance);
		distance = _distance;
		/////////////////////////////////////////////////////擊倒後使用回天/////////////////////////////////////////////////////
		if (!Player->GetSkillsuccess())
		{
			if (Diedelay <= 1 || (isSkill && (SkillMovie.GetCurrentBitmapNumber() >= 0 + direction * 39 && SkillMovie.GetCurrentBitmapNumber() <= 17 + direction * 39 || SkillMovie.GetCurrentBitmapNumber() == 0)))
			{
				if (SkillMovie.GetCurrentBitmapNumber() < 39 && direction == 1)
					SkillMovie.Movetonum(39);
				isSkill = true;
				Move = false;
				isAttacked = false;
				isDie = false;
				SkillMovie.OnMove();
				if (SkillMovie.GetCurrentBitmapNumber() == 17|| SkillMovie.GetCurrentBitmapNumber() == 17 + 39)
				{
					isDie = false;
					Move = true;
					isAttacked = false;
					SkillMovie.Reset();
					Diedelay = 30;
					velocity = initial_velocity;
					y = floor - StandHeight * 2;
					isSkill = false;
					attacknum = 0;
				}
			}
			/////////////////////////////////////////////////////技能施放///////////////////////////////////////////////////
			else if (Skill == 9 && times <= 0 && Move && _distance < 190 || isSkill)
			{
				if (!Movieflag)
				{
					if (Player->GetX1() < GetX2()) direction = 0;
					else if (Player->GetX2() > GetX1()) direction = 1;
					SkillMovie.Movetonum(18 + direction * 39);
					Movieflag = true;
					Movie.Init();
					CAudio::Instance()->Play(31);
				}
				isMovingRight = false;
				isMovingLeft = false;
				isSkill = true;
				Move = false;
				isAttacked = false;
				AttackMovie();
				times = rand() % 75 + 30;
			}
			///////////////////////////////////////////////////////攻擊及移動判定/////////////////////////////////////////////
			else if (times <= 0 && Move)
			{
				if (distance > 25)
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
				if (distance <= 25)
				{
					isAttack = true;
					isMovingRight = false;
					isMovingLeft = false;
					attacknum = 1;
					times = rand() % 30;
					Wall = false;
				}
			}
			////////////////////////////////////////////////////////攻擊擊中判定//////////////////////////////////////////////////////
			if (!Player->GetisMolding() && !Player->GetisSkill() && Hit && !Player->GetisDie() && (GetCurrentBitmapNumber() == 22 + 5 + GetDirection() * 109 || GetCurrentBitmapNumber() == 45 + GetDirection() * 109|| GetCurrentBitmapNumber() == 59  + GetDirection() * 109))
			{
				Player->SetAttacked(true);
				Player->ChangeChakura(Player->GetChakura() - 30);
			}
			/////////////////////////////////////////////////////////技能擊中判定///////////////////////////////////////////////////////
			if (!Player->GetisMolding() && !Player->GetisSkill() && Hit && !Player->GetisDie() && GetisSkill() && GetSkillMovie().GetCurrentBitmapNumber() >= 12 + GetDirection() * 39 && GetSkillMovie().GetCurrentBitmapNumber() <= 17 + GetDirection() * 39)
			{
				Player->SetAttacked(true);
				Player->SetDirection(direction);
				Player->ChangeChakura(Player->GetChakura() - 30);
				if (GetSkillMovie().GetCurrentBitmapNumber() == 16 + GetDirection() * 39) Player->SetDie();
			}
			/////////////////////////////////////////////////////////技能動畫判定////////////////////////////////////////////////////////////////
			if (!Player->GetisMolding() && !Player->GetisSkill() && GetisSkill() && Hit && GetSkillMovie().GetCurrentBitmapNumber() >= 27 + GetDirection() * 39 && GetSkillMovie().GetCurrentBitmapNumber() <= 38 + GetDirection() * 39 && !GetSkillsuccess())
			{
				SetpicXY();
				Player->SetMove(false);
				SetisShow(false);
				SetSkillsuccess();
				GetSkillsuccessMovie()->Movetonum(0 + GetDirection() * 57);
			}
			/////////////////////////////////////////////////////////////角色delay///////////////////////////////////////////////////////////////////
			if (Move) times--;
		}
	}
	void Neji::SetpicXY()
	{
		//////////////////////////////////////////////////////設定技能動畫位置到玩家旁邊/////////////////////////////////////////////////////////
		if (direction == 0) picx = Player->GetX2() + 20;
		else picx = Player->GetX1() - 20 - StandWidth;
		picy = Player->GetY2();
	}
	void Neji::OnShow()
	{
		//////////////////////////////////////////////顯示//////////////////////////////////////////////////////////
		for (int count = 0; count < (int)shoot.size(); count++) shoot[count]->OnShow();
		if (!isSkill)
		{
			animation.SetTopLeft(GetX1(), GetY1());
			animation.OnShow(2);
		}
		else if (!Skillsuccess)
		{
			SkillMovie.SetTopLeft(GetX1(), GetY1() - 30);
			SkillMovie.OnShow(2);
		}
		if (Skillsuccess) SkillsuccessMovie.OnShow(2);
	}
	void Neji::LoadBitmap()
	{
		////////////////////////////////////////////////////////////讀取圖片//////////////////////////////////////////
		animation.AddBitmap(NejiStand, RGB(0, 128, 128));			//0
		animation.AddBitmap(NejiStand, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiStand, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiRun1, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiRun1, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiRun1, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiRun2, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiRun2, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiRun2, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiRun3, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiRun3, RGB(0, 128, 128));			//10
		animation.AddBitmap(NejiRun3, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiRun4, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiRun4, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiRun4, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiRun5, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiRun5, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiRun5, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiRun6, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiRun6, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiRun6, RGB(0, 128, 128));			//20
		animation.AddBitmap(NejiSkill15, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo1, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo1, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo1, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo2, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo2, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo2, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo3, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo3, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo3, RGB(0, 128, 128));			//30
		animation.AddBitmap(NejiCombo4, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo4, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo4, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo5, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo5, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo5, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo6, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo6, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo6, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo7, RGB(0, 128, 128));			//40
		animation.AddBitmap(NejiCombo7, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo7, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo8, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo8, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo8, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo9, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo9, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo9, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo10, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo10, RGB(0, 128, 128));			//50
		animation.AddBitmap(NejiCombo10, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo11, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo11, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo11, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo12, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo12, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo12, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo13, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo13, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo13, RGB(0, 128, 128));			//60
		animation.AddBitmap(NejiCombo14, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo14, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo14, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo15, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo15, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo15, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo16, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo16, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo16, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo17, RGB(0, 128, 128));			//70
		animation.AddBitmap(NejiCombo17, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo17, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//80
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiHurt1, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiHurt2, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//90
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiDie1, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiDie2, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiDie2, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiDie2, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiDie3, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiDie3, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiDie3, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//100
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiDie4, RGB(0, 128, 128));			//8	
		animation.AddBitmap(NejiStand2, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiStand2, RGB(0, 128, 128));			//110
		animation.AddBitmap(NejiStand2, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiRun7, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiRun7, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiRun7, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiRun8, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiRun8, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiRun8, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiRun9, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiRun9, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiRun9, RGB(0, 128, 128));			//120
		animation.AddBitmap(NejiRun10, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiRun10, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiRun10, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiRun11, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiRun11, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiRun11, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiRun12, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiRun12, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiRun12, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiSkill44, RGB(0, 128, 128));			//130
		animation.AddBitmap(NejiCombo18, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo18, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo18, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo19, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo19, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo19, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo21, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo21, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo21, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo22, RGB(0, 128, 128));			//140
		animation.AddBitmap(NejiCombo22, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo22, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo23, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo23, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo23, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo24, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo24, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo24, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo25, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo25, RGB(0, 128, 128));			//150
		animation.AddBitmap(NejiCombo25, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo26, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo26, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo26, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo27, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo27, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo27, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo28, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo28, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo28, RGB(0, 128, 128));			//160
		animation.AddBitmap(NejiCombo29, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo29, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo29, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo30, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo30, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo30, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo31, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo31, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo31, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo32, RGB(0, 128, 128));			//170
		animation.AddBitmap(NejiCombo32, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiCombo32, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiCombo33, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiCombo33, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiCombo33, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiCombo34, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiCombo34, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiCombo34, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiCombo35, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiCombo35, RGB(0, 128, 128));			//180
		animation.AddBitmap(NejiCombo35, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//190
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiHurt3, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiHurt4, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//200
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiDie5, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiDie6, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiDie6, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiDie6, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiDie7, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiDie7, RGB(0, 128, 128));			//7
		animation.AddBitmap(NejiDie7, RGB(0, 128, 128));			//8
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//9
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//210
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//1
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//2
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//3
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//4
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//5
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//6
		animation.AddBitmap(NejiDie8, RGB(0, 128, 128));			//7
		SkillMovie.AddBitmap(NejiSkill1, RGB(0, 128, 128));			//0
		SkillMovie.AddBitmap(NejiSkill1, RGB(0, 128, 128));			//1
		SkillMovie.AddBitmap(NejiSkill1, RGB(0, 128, 128));			//2
		SkillMovie.AddBitmap(NejiSkill2, RGB(0, 128, 128));			//3
		SkillMovie.AddBitmap(NejiSkill2, RGB(0, 128, 128));			//4
		SkillMovie.AddBitmap(NejiSkill2, RGB(0, 128, 128));			//5
		SkillMovie.AddBitmap(NejiSkill3, RGB(0, 128, 128));			//6
		SkillMovie.AddBitmap(NejiSkill3, RGB(0, 128, 128));			//7
		SkillMovie.AddBitmap(NejiSkill3, RGB(0, 128, 128));			//8
		SkillMovie.AddBitmap(NejiSkill4, RGB(0, 128, 128));			//9
		SkillMovie.AddBitmap(NejiSkill4, RGB(0, 128, 128));			//10
		SkillMovie.AddBitmap(NejiSkill4, RGB(0, 128, 128));			//1
		SkillMovie.AddBitmap(NejiSkill5, RGB(0, 128, 128));			//2
		SkillMovie.AddBitmap(NejiSkill5, RGB(0, 128, 128));			//3
		SkillMovie.AddBitmap(NejiSkill5, RGB(0, 128, 128));			//4
		SkillMovie.AddBitmap(NejiSkill6, RGB(0, 128, 128));			//5
		SkillMovie.AddBitmap(NejiSkill6, RGB(0, 128, 128));			//6
		SkillMovie.AddBitmap(NejiSkill6, RGB(0, 128, 128));			//7
		SkillMovie.AddBitmap(NejiSkill7, RGB(0, 128, 128));			//8
		SkillMovie.AddBitmap(NejiSkill7, RGB(0, 128, 128));			//9
		SkillMovie.AddBitmap(NejiSkill7, RGB(0, 128, 128));			//20
		SkillMovie.AddBitmap(NejiSkill8, RGB(0, 128, 128));			//1
		SkillMovie.AddBitmap(NejiSkill8, RGB(0, 128, 128));			//2
		SkillMovie.AddBitmap(NejiSkill8, RGB(0, 128, 128));			//3
		SkillMovie.AddBitmap(NejiSkill9, RGB(0, 128, 128));			//4
		SkillMovie.AddBitmap(NejiSkill9, RGB(0, 128, 128));			//5
		SkillMovie.AddBitmap(NejiSkill9, RGB(0, 128, 128));			//6
		SkillMovie.AddBitmap(NejiSkill10, RGB(0, 128, 128));		//7	
		SkillMovie.AddBitmap(NejiSkill10, RGB(0, 128, 128));		//8	
		SkillMovie.AddBitmap(NejiSkill10, RGB(0, 128, 128));		//9	
		SkillMovie.AddBitmap(NejiSkill11, RGB(0, 128, 128));		//30
		SkillMovie.AddBitmap(NejiSkill11, RGB(0, 128, 128));		//1
		SkillMovie.AddBitmap(NejiSkill11, RGB(0, 128, 128));		//2	
		SkillMovie.AddBitmap(NejiSkill12, RGB(0, 128, 128));		//3	
		SkillMovie.AddBitmap(NejiSkill12, RGB(0, 128, 128));		//4	
		SkillMovie.AddBitmap(NejiSkill12, RGB(0, 128, 128));		//5	
		SkillMovie.AddBitmap(NejiSkill13, RGB(0, 128, 128));		//6	
		SkillMovie.AddBitmap(NejiSkill13, RGB(0, 128, 128));		//7	
		SkillMovie.AddBitmap(NejiSkill13, RGB(0, 128, 128));		//8	
		SkillMovie.AddBitmap(NejiSkill33, RGB(0, 128, 128));		//9
		SkillMovie.AddBitmap(NejiSkill33, RGB(0, 128, 128));		//40
		SkillMovie.AddBitmap(NejiSkill33, RGB(0, 128, 128));		//1
		SkillMovie.AddBitmap(NejiSkill34, RGB(0, 128, 128));		//2
		SkillMovie.AddBitmap(NejiSkill34, RGB(0, 128, 128));		//3
		SkillMovie.AddBitmap(NejiSkill34, RGB(0, 128, 128));		//4
		SkillMovie.AddBitmap(NejiSkill35, RGB(0, 128, 128));		//5
		SkillMovie.AddBitmap(NejiSkill35, RGB(0, 128, 128));		//6
		SkillMovie.AddBitmap(NejiSkill35, RGB(0, 128, 128));		//7
		SkillMovie.AddBitmap(NejiSkill36, RGB(0, 128, 128));		//8
		SkillMovie.AddBitmap(NejiSkill36, RGB(0, 128, 128));		//9
		SkillMovie.AddBitmap(NejiSkill36, RGB(0, 128, 128));		//50
		SkillMovie.AddBitmap(NejiSkill37, RGB(0, 128, 128));		//1
		SkillMovie.AddBitmap(NejiSkill37, RGB(0, 128, 128));		//2
		SkillMovie.AddBitmap(NejiSkill37, RGB(0, 128, 128));		//3
		SkillMovie.AddBitmap(NejiSkill38, RGB(0, 128, 128));		//4
		SkillMovie.AddBitmap(NejiSkill38, RGB(0, 128, 128));		//5
		SkillMovie.AddBitmap(NejiSkill38, RGB(0, 128, 128));		//6
		SkillMovie.AddBitmap(NejiSkill39, RGB(0, 128, 128));		//7
		SkillMovie.AddBitmap(NejiSkill39, RGB(0, 128, 128));		//8
		SkillMovie.AddBitmap(NejiSkill39, RGB(0, 128, 128));		//9
		SkillMovie.AddBitmap(NejiSkill40, RGB(0, 128, 128));		//60
		SkillMovie.AddBitmap(NejiSkill40, RGB(0, 128, 128));		//1
		SkillMovie.AddBitmap(NejiSkill40, RGB(0, 128, 128));		//2
		SkillMovie.AddBitmap(NejiSkill41, RGB(0, 128, 128));		//3
		SkillMovie.AddBitmap(NejiSkill41, RGB(0, 128, 128));		//4
		SkillMovie.AddBitmap(NejiSkill41, RGB(0, 128, 128));		//5
		SkillMovie.AddBitmap(NejiSkill42, RGB(0, 128, 128));		//6
		SkillMovie.AddBitmap(NejiSkill42, RGB(0, 128, 128));		//7
		SkillMovie.AddBitmap(NejiSkill42, RGB(0, 128, 128));		//8
		SkillMovie.AddBitmap(NejiSkill43, RGB(0, 128, 128));		//9
		SkillMovie.AddBitmap(NejiSkill43, RGB(0, 128, 128));		//70
		SkillMovie.AddBitmap(NejiSkill43, RGB(0, 128, 128));		//1
		SkillMovie.AddBitmap(NejiSkill44, RGB(0, 128, 128));		//2
		SkillMovie.AddBitmap(NejiSkill44, RGB(0, 128, 128));		//3
		SkillMovie.AddBitmap(NejiSkill44, RGB(0, 128, 128));		//4
		SkillMovie.AddBitmap(NejiSkill45, RGB(0, 128, 128));		//5
		SkillMovie.AddBitmap(NejiSkill45, RGB(0, 128, 128));		//6
		SkillMovie.AddBitmap(NejiSkill45, RGB(0, 128, 128));		//7
		SkillsuccessMovie.AddBitmap(NejiSkill14, RGB(0, 128, 128));	//0
		SkillsuccessMovie.AddBitmap(NejiSkill14, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill14, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill15, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill15, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill15, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill16, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill16, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill16, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill17, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill17, RGB(0, 128, 128));	//10
		SkillsuccessMovie.AddBitmap(NejiSkill17, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill18, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill18, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill18, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill19, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill19, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill19, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill20, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill20, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill20, RGB(0, 128, 128));	//20
		SkillsuccessMovie.AddBitmap(NejiSkill21, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill21, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill21, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill22, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill22, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill22, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill23, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill23, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill23, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill24, RGB(0, 128, 128));	//30
		SkillsuccessMovie.AddBitmap(NejiSkill24, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill24, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill25, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill25, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill25, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill26, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill26, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill26, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill27, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill27, RGB(0, 128, 128));	//40
		SkillsuccessMovie.AddBitmap(NejiSkill27, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill28, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill28, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill28, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill29, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill29, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill29, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill30, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill30, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill30, RGB(0, 128, 128));	//50
		SkillsuccessMovie.AddBitmap(NejiSkill31, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill31, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill31, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill32, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill32, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill32, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill46, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill46, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill46, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill47, RGB(0, 128, 128));	//60
		SkillsuccessMovie.AddBitmap(NejiSkill47, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill47, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill48, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill48, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill48, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill49, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill49, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill49, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill50, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill50, RGB(0, 128, 128));	//70
		SkillsuccessMovie.AddBitmap(NejiSkill50, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill51, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill51, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill51, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill52, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill52, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill52, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill53, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill53, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill53, RGB(0, 128, 128));	//80
		SkillsuccessMovie.AddBitmap(NejiSkill54, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill54, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill54, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill55, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill55, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill55, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill56, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill56, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill56, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill57, RGB(0, 128, 128));	//90
		SkillsuccessMovie.AddBitmap(NejiSkill57, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill57, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill58, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill58, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill58, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill59, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill59, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill59, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill60, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill60, RGB(0, 128, 128));	//100
		SkillsuccessMovie.AddBitmap(NejiSkill60, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill61, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill61, RGB(0, 128, 128));	//3
		SkillsuccessMovie.AddBitmap(NejiSkill61, RGB(0, 128, 128));	//4
		SkillsuccessMovie.AddBitmap(NejiSkill62, RGB(0, 128, 128));	//5
		SkillsuccessMovie.AddBitmap(NejiSkill62, RGB(0, 128, 128));	//6
		SkillsuccessMovie.AddBitmap(NejiSkill62, RGB(0, 128, 128));	//7
		SkillsuccessMovie.AddBitmap(NejiSkill63, RGB(0, 128, 128));	//8
		SkillsuccessMovie.AddBitmap(NejiSkill63, RGB(0, 128, 128));	//9
		SkillsuccessMovie.AddBitmap(NejiSkill63, RGB(0, 128, 128));	//0
		SkillsuccessMovie.AddBitmap(NejiSkill64, RGB(0, 128, 128));	//1
		SkillsuccessMovie.AddBitmap(NejiSkill64, RGB(0, 128, 128));	//2
		SkillsuccessMovie.AddBitmap(NejiSkill64, RGB(0, 128, 128));	//3
		Movie.LoadBitmap(NejiSkillUI, RGB(0, 128, 128));			
		SkillMovie.SetDelayCount(1);								
		SkillMovie.Reset();
		SkillsuccessMovie.SetDelayCount(1);
		SkillsuccessMovie.Reset();
	}																  
}																	  
																	